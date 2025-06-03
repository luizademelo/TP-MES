Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Includes necessary headers for ALTS handshaker implementation
#include "src/core/tsi/alts/handshaker/alts_tsi_handshaker.h"

#include <grpc/credentials.h>
#include <grpc/grpc_security.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>
#include <grpc/support/sync.h>
#include <grpc/support/thd_id.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/surface/channel.h"
#include "src/core/tsi/alts/frame_protector/alts_frame_protector.h"
#include "src/core/tsi/alts/handshaker/alts_handshaker_client.h"
#include "src/core/tsi/alts/handshaker/alts_shared_resource.h"
#include "src/core/tsi/alts/zero_copy_frame_protector/alts_zero_copy_grpc_protector.h"
#include "src/core/util/env.h"
#include "src/core/util/memory.h"
#include "src/core/util/sync.h"
#include "upb/mem/arena.hpp"

namespace {
// Constants for experimental ALTS handshaker keepalive parameters
constexpr absl::string_view kUseGrpcExperimentalAltsHandshakerKeepaliveParams =
    "GRPC_EXPERIMENTAL_ALTS_HANDSHAKER_KEEPALIVE_PARAMS";

constexpr int kExperimentalKeepAliveTimeoutMs = 10 * 1000;  // 10 seconds
constexpr int kExperimentalKeepAliveTimeMs = 10 * 60 * 1000;  // 10 minutes
}

// Main structure representing ALTS TSI handshaker
struct alts_tsi_handshaker {
  tsi_handshaker base;  // Base TSI handshaker structure
  grpc_slice target_name;  // Target name for handshake
  bool is_client;  // Whether this is a client handshaker
  bool has_sent_start_message = false;  // Flag if start message was sent
  bool has_created_handshaker_client = false;  // Flag if client was created
  char* handshaker_service_url;  // URL of handshaker service
  grpc_pollset_set* interested_parties;  // Interested parties for polling
  grpc_alts_credentials_options* options;  // ALTS credentials options
  alts_handshaker_client_vtable* client_vtable_for_testing = nullptr;  // For testing
  grpc_channel* channel = nullptr;  // gRPC channel to handshaker service
  bool use_dedicated_cq;  // Whether to use dedicated completion queue

  grpc_core::Mutex mu;  // Mutex for thread safety
  alts_handshaker_client* client = nullptr;  // Handshaker client instance

  bool shutdown = false;  // Shutdown flag

  size_t max_frame_size;  // Maximum frame size for protection

  std::optional<std::string> preferred_transport_protocols;  // Preferred protocols
};

// Structure representing ALTS TSI handshaker result
typedef struct alts_tsi_handshaker_result {
  tsi_handshaker_result base;  // Base TSI handshaker result
  char* peer_identity;  // Peer's identity (service account)
  char* key_data;  // Key material for frame protection
  unsigned char* unused_bytes;  // Any unused bytes from handshake
  size_t unused_bytes_size;  // Size of unused bytes
  grpc_slice rpc_versions;  // Negotiated RPC versions
  bool is_client;  // Whether this result is from client side
  grpc_slice serialized_context;  // Serialized ALTS context

  size_t max_frame_size;  // Maximum frame size for protection
  std::optional<std::string> negotiated_transport_protocol;  // Negotiated protocol
} alts_tsi_handshaker_result;

// Extracts peer information from handshaker result
static tsi_result handshaker_result_extract_peer(
    const tsi_handshaker_result* self, tsi_peer* peer) {
  if (self == nullptr || peer == nullptr) {
    LOG(ERROR) << "Invalid argument to handshaker_result_extract_peer()";
    return TSI_INVALID_ARGUMENT;
  }
  alts_tsi_handshaker_result* result =
      reinterpret_cast<alts_tsi_handshaker_result*>(
          const_cast<tsi_handshaker_result*>(self));
  // Determine number of peer properties based on whether transport protocol was negotiated
  const int peer_properties_count =
      (result && result->negotiated_transport_protocol.has_value())
          ? (kTsiAltsMinNumOfPeerProperties + 1)
          : kTsiAltsMinNumOfPeerProperties;
  tsi_result ok = tsi_construct_peer(peer_properties_count, peer);
  int index = 0;
  if (ok != TSI_OK) {
    LOG(ERROR) << "Failed to construct tsi peer";
    return ok;
  }
  
  // Set various peer properties
  CHECK_NE(&peer->properties[index], nullptr);
  ok = tsi_construct_string_peer_property_from_cstring(
      TSI_CERTIFICATE_TYPE_PEER_PROPERTY, TSI_ALTS_CERTIFICATE_TYPE,
      &peer->properties[index]);
  if (ok != TSI_OK) {
    tsi_peer_destruct(peer);
    LOG(ERROR) << "Failed to set tsi peer property";
    return ok;
  }
  index++;
  
  // Set peer identity property
  CHECK_NE(&peer->properties[index], nullptr);
  ok = tsi_construct_string_peer_property_from_cstring(
      TSI_ALTS_SERVICE_ACCOUNT_PEER_PROPERTY, result->peer_identity,
      &peer->properties[index]);
  if (ok != TSI_OK) {
    tsi_peer_destruct(peer);
    LOG(ERROR) << "Failed to set tsi peer property";
  }
  index++;
  
  // Set RPC versions property
  CHECK_NE(&peer->properties[index], nullptr);
  ok = tsi_construct_string_peer_property(
      TSI_ALTS_RPC_VERSIONS,
      reinterpret_cast<char*>(GRPC_SLICE_START_PTR(result->rpc_versions)),
      GRPC_SLICE_LENGTH(result->rpc_versions), &peer->properties[index]);
  if (ok != TSI_OK) {
    tsi_peer_destruct(peer);
    LOG(ERROR) << "Failed to set tsi peer property";
  }
  index++;
  
  // Set ALTS context property
  CHECK_NE(&peer->properties[index], nullptr);
  ok = tsi_construct_string_peer_property(
      TSI_ALTS_CONTEXT,
      reinterpret_cast<char*>(GRPC_SLICE_START_PTR(result->serialized_context)),
      GRPC_SLICE_LENGTH(result->serialized_context), &peer->properties[index]);
  if (ok != TSI_OK) {
    tsi_peer_destruct(peer);
    LOG(ERROR) << "Failed to set tsi peer property";
  }
  index++;
  
  // Set security level property
  CHECK_NE(&peer->properties[index], nullptr);
  ok = tsi_construct_string_peer_property_from_cstring(
      TSI_SECURITY_LEVEL_PEER_PROPERTY,
      tsi_security_level_to_string(TSI_PRIVACY_AND_INTEGRITY),
      &peer->properties[index]);
  if (ok != TSI_OK) {
    tsi_peer_destruct(peer);
    LOG(ERROR) << "Failed to set tsi peer property";
  }
  
  // Set negotiated transport protocol if available
  if (result->negotiated_transport_protocol.has_value()) {
    index++;
    CHECK_NE(&peer->properties[index], nullptr);
    ok = tsi_construct_string_peer_property_from_cstring(
        TSI_ALTS_NEGOTIATED_TRANSPORT_PROTOCOL,
        result->negotiated_transport_protocol.value().c_str(),
        &peer->properties[index]);
    if (ok != TSI_OK) {
      tsi_peer_destruct(peer);
      LOG(ERROR) << "Failed to set tsi peer property";
    }
  }
  CHECK(++index == peer_properties_count);
  return ok;
}

// Gets frame protector type (normal or zero-copy)
static tsi_result handshaker_result_get_frame_protector_type(
    const tsi_handshaker_result* ,
    tsi_frame_protector_type* frame_protector_type) {
  *frame_protector_type = TSI_FRAME_PROTECTOR_NORMAL_OR_ZERO_COPY;
  return TSI_OK;
}

// Creates zero-copy GRPC protector from handshaker result
static tsi_result handshaker_result_create_zero_copy_grpc_protector(
    const tsi_handshaker_result* self, size_t* max_output_protected_frame_size,
    tsi_zero_copy_grpc_protector** protector) {
  if (self == nullptr || protector == nullptr) {
    LOG(ERROR) << "Invalid arguments to create_zero_copy_grpc_protector()";
    return TSI_INVALID_ARGUMENT;
  }
  alts_tsi_handshaker_result* result =
      reinterpret_cast<alts_tsi_handshaker_result*>(
          const_cast<tsi_handshaker_result*>(self));

  // Determine maximum frame size based on negotiation
  size_t max_frame_size = kTsiAltsMinFrameSize;
  if (result->max_frame_size) {
    size_t peer_max_frame_size = result->max_frame_size;
    max_frame_size = std::min<size_t>(peer_max_frame_size,
                                      max_output_protected_frame_size == nullptr
                                          ? kTsiAltsMaxFrameSize
                                          : *max_output_protected_frame_size);
    max_frame_size = std::max<size_t>(max_frame_size, kTsiAltsMinFrameSize);
  }
  max_output_protected_frame_size = &max_frame_size;
  VLOG(2) << "After Frame Size Negotiation, maximum frame size used by frame "
             "protector equals "
          << *max_output_protected_frame_size;
  
  // Create zero-copy protector using negotiated key material
  tsi_result ok = alts_zero_copy_grpc_protector_create(
      grpc_core::GsecKeyFactory({reinterpret_cast<uint8_t*>(result->key_data),
                                 kAltsAes128GcmRekeyKeyLength},
                                true),
      result->is_client,
      false, false,
      max_output_protected_frame_size, protector);
  if (ok != TSI_OK) {
    LOG(ERROR) << "Failed to create zero-copy grpc protector";
  }
  return ok;
}

// Creates normal frame protector from handshaker result
static tsi_result handshaker_result_create_frame_protector(
    const tsi_handshaker_result* self, size_t* max_output_protected_frame_size,
    tsi_frame_protector** protector) {
  if (self == nullptr || protector == nullptr) {
    LOG(ERROR)
        << "Invalid arguments to handshaker_result_create_frame_protector()";
    return TSI_INVALID_ARGUMENT;
  }
  alts_tsi_handshaker_result* result =
      reinterpret_cast<alts_tsi_handshaker_result*>(
          const_cast<tsi_handshaker_result*>(self));
  // Create normal frame protector using negotiated key material
  tsi_result ok = alts_create_frame_protector(
      reinterpret_cast<const uint8_t*>(result->key_data),
      kAltsAes128GcmRekeyKeyLength, result->is_client, true,
      max_output_protected_frame_size, protector);
  if (ok != TSI_OK) {
    LOG(ERROR) << "Failed to create frame protector";
  }
  return ok;
}

// Gets any unused bytes from handshake
static tsi_result handshaker_result_get_unused_bytes(
    const tsi_handshaker_result* self, const unsigned char** bytes,
    size_t* bytes_size) {
  if (self == nullptr || bytes == nullptr || bytes_size == nullptr) {
    LOG(ERROR) << "Invalid arguments to handshaker_result_get_unused_bytes()";
    return TSI_INVALID_ARGUMENT;
  }
  alts_tsi_handshaker_result* result =
      reinterpret_cast<alts_tsi_handshaker_result*>(
          const_cast<tsi_handshaker_result*>(self));
  *bytes = result->unused_bytes;
  *bytes_size = result->unused_bytes_size;
  return TSI_OK;
}

// Destroys handshaker result and frees resources
static void handshaker_result_destroy(tsi_handshaker_result* self) {
  if (self == nullptr) {
    return;
  }
  alts_tsi_handshaker_result* result =
      reinterpret_cast<alts_tsi_handshaker_result*>(
          const_cast<tsi_handshaker_result*>(self));
  gpr_free(result->peer_identity);
  gpr_free(result->key_data);
  gpr_free(result->unused_bytes);
  grpc_core::CSliceUnref(result->rpc_versions);
  grpc_core::CSliceUnref(result->serialized_context);
  gpr_free(result);
}

// Vtable for handshaker result operations
static const tsi_handshaker_result_vtable result_vtable = {
    handshaker_result_extract_peer,
    handshaker_result_get_frame_protector_type,
    handshaker_result_create_zero_copy_grpc_protector,
    handshaker_result_create_frame_protector,
    handshaker_result_get_unused_bytes,
    handshaker_result_destroy};

// Creates ALTS TSI handshaker result from handshaker response
tsi_result alts_tsi_handshaker_result_create(grpc_gcp_HandshakerResp* resp,
                                             bool is_client,
                                             tsi_handshaker_result** result) {
  if (result == nullptr || resp == nullptr) {
    LOG(ERROR) << "Invalid arguments to create_handshaker_result()";
    return TSI_INVALID_ARGUMENT;
  }
  
  // Validate handshaker response fields
  const grpc_gcp_HandshakerResult* hresult =
      grpc_gcp_HandshakerResp_result(resp);
  const grpc_gcp_Identity* identity =
      grpc_gcp_HandshakerResult_peer_identity(hresult);
  if (identity == nullptr) {
    LOG(ERROR) << "Invalid identity";
    return TSI_FAILED_PRECONDITION;
  }
  
  upb_StringView peer_service_account =
      grpc_gcp_Identity_service_account(identity);
  if (peer_service_account.size == 0) {
    LOG(ERROR) << "Invalid peer service account";
    return TSI_FAILED_PRECONDITION;
  }
  
  upb_StringView key_data = grpc_gcp_HandshakerResult_key_data(hresult);
  if (key_data.size < kAltsAes128GcmRekeyKeyLength) {
    LOG(ERROR) << "Bad key length";
    return TSI_FAILED_PRECONDITION;
  }
  
  const grpc_gcp_RpcProtocolVersions* peer_rpc_version =
      grpc_gcp_HandshakerResult_peer_rpc_versions(hresult);
  if (peer_rpc_version == nullptr) {
    LOG(ERROR) << "Peer does not set RPC protocol versions.";
    return TSI_FAILED_PRECONDITION;
  }
  
  upb_StringView application_protocol =
      grpc_gcp_HandshakerResult_application_protocol(hresult);
  if (application_protocol.size == 0) {
    LOG(ERROR) << "Invalid application protocol";
    return TSI_FAILED_PRECONDITION;
  }
  
  upb_StringView record_protocol =
      grpc_gcp_HandshakerResult_record_protocol(hresult);
  if (record_protocol.size == 0) {
    LOG(ERROR) << "Invalid record protocol";
    return TSI_FAILED_PRECONDITION;
  }
  
  const grpc_gcp_Identity* local_identity =
      grpc_gcp_HandshakerResult_local_identity(hresult);
  if (local_identity == nullptr) {
    LOG(ERROR) << "Invalid local identity";
    return TSI_FAILED_PRECONDITION;
  }
  
  // Allocate and initialize handshaker result structure
  alts_tsi_handshaker_result* sresult =
      static_cast<alts_tsi_handshaker_result*>(
          gpr_zalloc(sizeof(alts_tsi_handshaker_result)));
  
  // Copy key material
  sresult->key_data =
      static_cast<char*>(gpr_zalloc(kAltsAes128GcmRekeyKeyLength));
  memcpy(sresult->key_data, key_data.data, kAltsAes128GcmRekeyKeyLength);
  
  // Copy peer identity
  sresult->peer_identity =
      static_cast<char*>(gpr_zalloc(peer_service_account.size + 1));
  memcpy(sresult->peer_identity, peer_service_account.data,
         peer_service_account.size);
  
  // Set max frame size
  sresult->max_frame_size = grpc_gcp_HandshakerResult_max_frame_size(hresult);
  
  // Handle negotiated transport protocol if present
  const grpc_gcp_NegotiatedTransportProtocol* negotiated_transport_protocol =
      grpc_gcp_HandshakerResult_transport_protocol(hresult);
  sresult->negotiated_transport_protocol = std::nullopt;
  if (negotiated_transport_protocol != nullptr) {
    upb_StringView transport_protocol