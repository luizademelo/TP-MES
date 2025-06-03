Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Include necessary headers for ALTS handshaker client implementation
#include "src/core/tsi/alts/handshaker/alts_handshaker_client.h"

#include <grpc/byte_buffer.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>

#include <list>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_split.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/surface/call.h"
#include "src/core/lib/surface/channel.h"
#include "src/core/tsi/alts/handshaker/alts_shared_resource.h"
#include "src/core/tsi/alts/handshaker/alts_tsi_handshaker_private.h"
#include "src/core/tsi/alts/handshaker/alts_tsi_utils.h"
#include "src/core/util/crash.h"
#include "src/core/util/env.h"
#include "src/core/util/sync.h"
#include "upb/mem/arena.hpp"

// Initial buffer size for ALTS handshaker
#define TSI_ALTS_INITIAL_BUFFER_SIZE 256

// Constants for handshaker operations
const int kHandshakerClientOpNum = 4;
const char kMaxConcurrentStreamsEnvironmentVariable[] =
    "GRPC_ALTS_MAX_CONCURRENT_HANDSHAKES";

// Base structure for ALTS handshaker client
struct alts_handshaker_client {
  const alts_handshaker_client_vtable* vtable;
};

// Structure to hold receive message results
struct recv_message_result {
  tsi_result status;
  const unsigned char* bytes_to_send;
  size_t bytes_to_send_size;
  tsi_handshaker_result* result;
};

// GRPC-specific ALTS handshaker client implementation
typedef struct alts_grpc_handshaker_client {
  alts_handshaker_client base;  // Base handshaker client

  // Reference counting
  gpr_refcount refs;
  
  // Handshaker and GRPC call objects
  alts_tsi_handshaker* handshaker;
  grpc_call* call;

  // GRPC caller function pointer
  alts_grpc_caller grpc_caller;

  // Closure for receiving handshaker service response
  grpc_closure on_handshaker_service_resp_recv;

  // Buffers for sending and receiving data
  grpc_byte_buffer* send_buffer = nullptr;
  grpc_byte_buffer* recv_buffer = nullptr;

  // Flag for testing purposes to simulate read failures
  bool inject_read_failure = false;

  // Metadata array for received initial metadata
  grpc_metadata_array recv_initial_metadata;

  // Callback function and user data for handshaker
  tsi_handshaker_on_next_done_cb cb;
  void* user_data;

  // ALTS credentials options
  grpc_alts_credentials_options* options;

  // Target name for handshake
  grpc_slice target_name;

  // Flag indicating if this is a client-side handshaker
  bool is_client;

  // Received bytes during handshake
  grpc_slice recv_bytes;

  // Buffer for handshake data
  unsigned char* buffer;
  size_t buffer_size;

  // Closure for status received event
  grpc_closure on_status_received;

  // Handshake status code
  grpc_status_code handshake_status_code = GRPC_STATUS_OK;

  // Details of handshake status
  grpc_slice handshake_status_details;

  // Mutex for thread safety
  grpc_core::Mutex mu;

  // Flag indicating if status receiving is finished
  bool receive_status_finished = false;

  // Pending receive message result
  recv_message_result* pending_recv_message_result = nullptr;

  // Maximum frame size for handshake
  size_t max_frame_size;
  
  // Preferred transport protocols
  std::vector<std::string> preferred_transport_protocols;

  // Error string pointer
  std::string* error;
} alts_grpc_handshaker_client;

// Destroys the send buffer in the handshaker client
static void handshaker_client_send_buffer_destroy(
    alts_grpc_handshaker_client* client) {
  CHECK_NE(client, nullptr);
  grpc_byte_buffer_destroy(client->send_buffer);
  client->send_buffer = nullptr;
}

// Checks if handshake is finished properly based on response
static bool is_handshake_finished_properly(grpc_gcp_HandshakerResp* resp) {
  CHECK_NE(resp, nullptr);
  return grpc_gcp_HandshakerResp_result(resp) != nullptr;
}

// Decrements reference count and potentially destroys the client
static void alts_grpc_handshaker_client_unref(
    alts_grpc_handshaker_client* client) {
  if (gpr_unref(&client->refs)) {
    if (client->base.vtable != nullptr &&
        client->base.vtable->destruct != nullptr) {
      client->base.vtable->destruct(&client->base);
    }
    // Clean up all allocated resources
    grpc_byte_buffer_destroy(client->send_buffer);
    grpc_byte_buffer_destroy(client->recv_buffer);
    client->send_buffer = nullptr;
    client->recv_buffer = nullptr;
    grpc_metadata_array_destroy(&client->recv_initial_metadata);
    grpc_core::CSliceUnref(client->recv_bytes);
    grpc_core::CSliceUnref(client->target_name);
    grpc_alts_credentials_options_destroy(client->options);
    gpr_free(client->buffer);
    grpc_core::CSliceUnref(client->handshake_status_details);
    delete client;
  }
}

// Completes the TSI next operation if conditions are met
static void maybe_complete_tsi_next(
    alts_grpc_handshaker_client* client, bool receive_status_finished,
    recv_message_result* pending_recv_message_result) {
  recv_message_result* r;
  {
    grpc_core::MutexLock lock(&client->mu);
    client->receive_status_finished |= receive_status_finished;
    if (pending_recv_message_result != nullptr) {
      CHECK_EQ(client->pending_recv_message_result, nullptr);
      client->pending_recv_message_result = pending_recv_message_result;
    }
    if (client->pending_recv_message_result == nullptr) {
      return;
    }
    const bool have_final_result =
        client->pending_recv_message_result->result != nullptr ||
        client->pending_recv_message_result->status != TSI_OK;
    if (have_final_result && !client->receive_status_finished) {
      return;
    }
    r = client->pending_recv_message_result;
    client->pending_recv_message_result = nullptr;
  }
  // Invoke the callback with the result
  client->cb(r->status, client->user_data, r->bytes_to_send,
             r->bytes_to_send_size, r->result);
  gpr_free(r);
}

// Handles response completion and triggers next steps
static void handle_response_done(alts_grpc_handshaker_client* client,
                                 tsi_result status, std::string error,
                                 const unsigned char* bytes_to_send,
                                 size_t bytes_to_send_size,
                                 tsi_handshaker_result* result) {
  if (client->error != nullptr) *client->error = std::move(error);
  recv_message_result* p = grpc_core::Zalloc<recv_message_result>();
  p->status = status;
  p->bytes_to_send = bytes_to_send;
  p->bytes_to_send_size = bytes_to_send_size;
  p->result = result;
  maybe_complete_tsi_next(client, false, p);
}

// Main handler for handshaker service responses
void alts_handshaker_client_handle_response(alts_handshaker_client* c,
                                            bool is_ok) {
  CHECK_NE(c, nullptr);
  alts_grpc_handshaker_client* client =
      reinterpret_cast<alts_grpc_handshaker_client*>(c);
  grpc_byte_buffer* recv_buffer = client->recv_buffer;
  alts_tsi_handshaker* handshaker = client->handshaker;

  // Validate client state
  if (client->cb == nullptr) {
    LOG(ERROR)
        << "client->cb is nullptr in alts_tsi_handshaker_handle_response()";
    return;
  }
  if (handshaker == nullptr) {
    LOG(ERROR)
        << "handshaker is nullptr in alts_tsi_handshaker_handle_response()";
    handle_response_done(
        client, TSI_INTERNAL_ERROR,
        "handshaker is nullptr in alts_tsi_handshaker_handle_response()",
        nullptr, 0, nullptr);
    return;
  }

  // Check if handshake has been shutdown
  if (alts_tsi_handshaker_has_shutdown(handshaker)) {
    VLOG(2) << "TSI handshake shutdown";
    handle_response_done(client, TSI_HANDSHAKE_SHUTDOWN,
                         "TSI handshake shutdown", nullptr, 0, nullptr);
    return;
  }

  // Check if read operation failed
  if (!is_ok || client->inject_read_failure) {
    VLOG(2) << "read failed on grpc call to handshaker service";
    handle_response_done(client, TSI_INTERNAL_ERROR,
                         "read failed on grpc call to handshaker service",
                         nullptr, 0, nullptr);
    return;
  }
  
  // Validate received buffer
  if (recv_buffer == nullptr) {
    VLOG(2)
        << "recv_buffer is nullptr in alts_tsi_handshaker_handle_response()";
    handle_response_done(
        client, TSI_INTERNAL_ERROR,
        "recv_buffer is nullptr in alts_tsi_handshaker_handle_response()",
        nullptr, 0, nullptr);
    return;
  }

  // Deserialize the response
  upb::Arena arena;
  grpc_gcp_HandshakerResp* resp =
      alts_tsi_utils_deserialize_response(recv_buffer, arena.ptr());
  grpc_byte_buffer_destroy(client->recv_buffer);
  client->recv_buffer = nullptr;

  if (resp == nullptr) {
    LOG(ERROR) << "alts_tsi_utils_deserialize_response() failed";
    handle_response_done(client, TSI_DATA_CORRUPTED,
                         "alts_tsi_utils_deserialize_response() failed",
                         nullptr, 0, nullptr);
    return;
  }

  // Check response status
  const grpc_gcp_HandshakerStatus* resp_status =
      grpc_gcp_HandshakerResp_status(resp);
  if (resp_status == nullptr) {
    LOG(ERROR) << "No status in HandshakerResp";
    handle_response_done(client, TSI_DATA_CORRUPTED,
                         "No status in HandshakerResp", nullptr, 0, nullptr);
    return;
  }

  // Process outbound frames from response
  upb_StringView out_frames = grpc_gcp_HandshakerResp_out_frames(resp);
  unsigned char* bytes_to_send = nullptr;
  size_t bytes_to_send_size = 0;
  if (out_frames.size > 0) {
    bytes_to_send_size = out_frames.size;
    // Resize buffer if needed
    while (bytes_to_send_size > client->buffer_size) {
      client->buffer_size *= 2;
      client->buffer = static_cast<unsigned char*>(
          gpr_realloc(client->buffer, client->buffer_size));
    }
    memcpy(client->buffer, out_frames.data, bytes_to_send_size);
    bytes_to_send = client->buffer;
  }

  // Create handshaker result if handshake is complete
  tsi_handshaker_result* result = nullptr;
  if (is_handshake_finished_properly(resp)) {
    tsi_result status =
        alts_tsi_handshaker_result_create(resp, client->is_client, &result);
    if (status != TSI_OK) {
      LOG(ERROR) << "alts_tsi_handshaker_result_create() failed";
      handle_response_done(client, status,
                           "alts_tsi_handshaker_result_create() failed",
                           nullptr, 0, nullptr);
      return;
    }
    alts_tsi_handshaker_result_set_unused_bytes(
        result, &client->recv_bytes,
        grpc_gcp_HandshakerResp_bytes_consumed(resp));
  }

  // Process handshake status code and details
  grpc_status_code code = static_cast<grpc_status_code>(
      grpc_gcp_HandshakerStatus_code(resp_status));
  std::string error;
  if (code != GRPC_STATUS_OK) {
    upb_StringView details = grpc_gcp_HandshakerStatus_details(resp_status);
    if (details.size > 0) {
      error = absl::StrCat("Status ", code, " from handshaker service: ",
                           absl::string_view(details.data, details.size));
      LOG_EVERY_N_SEC(INFO, 1) << error;
    }
  }

  // Finalize response handling
  handle_response_done(client, alts_tsi_utils_convert_to_tsi_result(code),
                       std::move(error), bytes_to_send, bytes_to_send_size,
                       result);
}

// Continues making GRPC call for handshaker operations
static tsi_result continue_make_grpc_call(alts_grpc_handshaker_client* client,
                                          bool is_start) {
  CHECK_NE(client, nullptr);
  grpc_op ops[kHandshakerClientOpNum];
  memset(ops, 0, sizeof(ops));
  grpc_op* op = ops;
  
  // Set up operations for starting a call
  if (is_start) {
    // Operation to receive status on client
    op->op = GRPC_OP_RECV_STATUS_ON_CLIENT;
    op->data.recv_status_on_client.trailing_metadata = nullptr;
    op->data.recv_status_on_client.status = &client->handshake_status_code;
    op->data.recv_status_on_client.status_details =
        &client->handshake_status_details;
    op->flags = 0;
    op->reserved = nullptr;
    op++;
    CHECK(op - ops <= kHandshakerClientOpNum);
    
    // Start batch operation for receiving status
    gpr_ref(&client->refs);
    grpc_call_error call_error =
        client->grpc_caller(client->call, ops, static_cast<size_t>(op - ops),
                            &client->on_status_received);

    CHECK_EQ(call_error, GRPC_CALL_OK);
    memset(ops, 0, sizeof(ops));
    op = ops;
    
    // Operation to send initial metadata
    op->op = GRPC_OP_SEND_INITIAL_METADATA;
    op->data.send_initial_metadata.count = 0;
    op++;
    CHECK(op - ops <= kHandshakerClientOpNum);
    
    // Operation to receive initial metadata
    op->op = GRPC_OP_RECV_INITIAL_METADATA;
    op->data.recv_initial_metadata.recv_initial_metadata =
        &client->recv_initial_metadata;
    op++;
    CHECK(op - ops <= kHandshakerClientOpNum);
  }
  
  // Operation to send message
  op->op = GRPC_OP_SEND_MESSAGE;
  op->data.send_message.send_message = client->send_buffer;
  op++;
  CHECK(op - ops <= kHandshakerClientOpNum);
  
  // Operation to receive message
  op->op = GRPC_OP_RECV_MESSAGE;
  op->data.recv_message.recv_message = &client->recv_buffer;
  op++;
  CHECK(op - ops <= kHandshakerClientOpNum);
  
  // Execute the batch of operations
  CHECK_NE(client->grpc_caller, nullptr);
  if (client->grpc_caller(client->call, ops, static_cast<size_t>(op - ops),
                          &client->on_handshaker_service_resp_recv) !=
      GRPC_CALL_OK) {
    LOG(ERROR) << "Start batch operation failed";
    return TSI_INTERNAL_ERROR;
  }
  return TSI_OK;
}

// Namespace for handshake queue implementation
namespace {

// Class to manage concurrent handshake operations
class HandshakeQueue {
 public:
  explicit HandshakeQueue(size_t max_outstanding_handshakes)
      : max_outstanding_handshakes_(max_outstanding_handshakes) {}

  // Request a new handshake operation
  void RequestHandshake(alts_grpc_handshaker_client* client) {
    {
      grpc_core::MutexLock lock(&mu_);
      // If queue is full, add to waiting list
      if (outstanding_handshakes_ == max_outstanding_handshakes_) {
        queued_handshakes_.push_back(client);
        return;
      }
      // Otherwise increment counter and proceed
      ++outstanding_handshakes_;
    }
    continue_make_grpc_call(client, true);
  }

  // Called when a handshake operation completes
  void HandshakeDone() {
    alts_grpc_handshaker_client* client = nullptr;
    {
      grpc_core::MutexLock lock(&mu_);
      // If no queued handshakes, just decrement counter
      if (queued_handshakes_.empty()) {
        --outstanding_handshakes_;
        return;
      }
      // Otherwise start next queued handshake
      client = queued_handshakes_.front();
      queued_handshakes_.pop_front();
    }
    continue_make_grpc_call(client, true);
  }

 private:
  grpc