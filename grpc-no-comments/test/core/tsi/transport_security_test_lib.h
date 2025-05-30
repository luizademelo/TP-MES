
// Copyright 2017 gRPC authors.

#ifndef GRPC_TEST_CORE_TSI_TRANSPORT_SECURITY_TEST_LIB_H
#define GRPC_TEST_CORE_TSI_TRANSPORT_SECURITY_TEST_LIB_H

#include <grpc/support/sync.h>
#include <openssl/x509v3.h>

#include "src/core/tsi/transport_security_interface.h"

#define TSI_TEST_TINY_HANDSHAKE_BUFFER_SIZE 32
#define TSI_TEST_SMALL_HANDSHAKE_BUFFER_SIZE 128
#define TSI_TEST_SMALL_READ_BUFFER_ALLOCATED_SIZE 41
#define TSI_TEST_SMALL_PROTECTED_BUFFER_SIZE 37
#define TSI_TEST_SMALL_MESSAGE_BUFFER_ALLOCATED_SIZE 42
#define TSI_TEST_SMALL_CLIENT_MAX_OUTPUT_PROTECTED_FRAME_SIZE 39
#define TSI_TEST_SMALL_SERVER_MAX_OUTPUT_PROTECTED_FRAME_SIZE 43
#define TSI_TEST_DEFAULT_BUFFER_SIZE 4096
#define TSI_TEST_DEFAULT_PROTECTED_BUFFER_SIZE 16384
#define TSI_TEST_DEFAULT_CHANNEL_SIZE 32768
#define TSI_TEST_BIG_MESSAGE_SIZE 17000
#define TSI_TEST_SMALL_MESSAGE_SIZE 10
#define TSI_TEST_NUM_OF_ARGUMENTS 7
#define TSI_TEST_NUM_OF_COMBINATIONS 128
#define TSI_TEST_UNUSED_BYTES "HELLO GOOGLE"

typedef struct tsi_test_fixture tsi_test_fixture;

typedef struct tsi_test_frame_protector_fixture
    tsi_test_frame_protector_fixture;

typedef struct tsi_test_frame_protector_config tsi_test_frame_protector_config;

typedef struct tsi_test_channel tsi_test_channel;

typedef struct tsi_test_fixture_vtable {
  void (*setup_handshakers)(tsi_test_fixture* fixture);
  void (*check_handshaker_peers)(tsi_test_fixture* fixture);
  void (*destruct)(tsi_test_fixture* fixture);
} tsi_test_fixture_vtable;

struct tsi_test_fixture {
  const tsi_test_fixture_vtable* vtable;

  tsi_handshaker* client_handshaker;
  tsi_handshaker* server_handshaker;

  tsi_handshaker_result* client_result;
  tsi_handshaker_result* server_result;

  size_t handshake_buffer_size;

  tsi_test_channel* channel;

  tsi_test_frame_protector_config* config;

  bool has_client_finished_first;

  bool test_unused_bytes;

  gpr_cv cv;
  gpr_mu mu;
  bool notified;
};

struct tsi_test_frame_protector_fixture {

  tsi_frame_protector* client_frame_protector;
  tsi_frame_protector* server_frame_protector;

  tsi_test_channel* channel;

  tsi_test_frame_protector_config* config;
};

struct tsi_test_channel {

  uint8_t* client_channel;
  uint8_t* server_channel;

  size_t bytes_written_to_client_channel;
  size_t bytes_written_to_server_channel;

  size_t bytes_read_from_client_channel;
  size_t bytes_read_from_server_channel;
};

struct tsi_test_frame_protector_config {

  size_t read_buffer_allocated_size;

  size_t message_buffer_allocated_size;

  size_t protected_buffer_size;

  size_t client_max_output_protected_frame_size;
  size_t server_max_output_protected_frame_size;

  uint8_t* client_message;
  uint8_t* server_message;

  size_t client_message_size;
  size_t server_message_size;
};

tsi_test_frame_protector_config* tsi_test_frame_protector_config_create(
    bool use_default_read_buffer_allocated_size,
    bool use_default_message_buffer_allocated_size,
    bool use_default_protected_buffer_size, bool use_default_client_message,
    bool use_default_server_message,
    bool use_default_client_max_output_protected_frame_size,
    bool use_default_server_max_output_protected_frame_size);

void tsi_test_frame_protector_config_set_buffer_size(
    tsi_test_frame_protector_config* config, size_t read_buffer_allocated_size,
    size_t message_buffer_allocated_size, size_t protected_buffer_size,
    size_t client_max_output_protected_frame_size,
    size_t server_max_output_protected_frame_size);

void tsi_test_frame_protector_config_destroy(
    tsi_test_frame_protector_config* config);

void tsi_test_fixture_init(tsi_test_fixture* fixture);

void tsi_test_fixture_destroy(tsi_test_fixture* fixture);

tsi_test_frame_protector_fixture* tsi_test_frame_protector_fixture_create();

void tsi_test_frame_protector_fixture_init(
    tsi_test_frame_protector_fixture* fixture,
    tsi_frame_protector* client_frame_protector,
    tsi_frame_protector* server_frame_protector);

void tsi_test_frame_protector_fixture_destroy(
    tsi_test_frame_protector_fixture* fixture);

void tsi_test_frame_protector_send_message_to_peer(
    tsi_test_frame_protector_config* config, tsi_test_channel* channel,
    tsi_frame_protector* protector, bool is_client);

void tsi_test_frame_protector_receive_message_from_peer(
    tsi_test_frame_protector_config* config, tsi_test_channel* channel,
    tsi_frame_protector* protector, unsigned char* message,
    size_t* bytes_received, bool is_client);

void tsi_test_do_handshake(tsi_test_fixture* fixture);

void tsi_test_do_round_trip(tsi_test_fixture* fixture);

void tsi_test_frame_protector_do_round_trip_no_handshake(
    tsi_test_frame_protector_fixture* fixture);

struct SelfSignedCertificateOptions {
  std::string common_name;
  std::string organization;
  std::string organizational_unit;
};

std::string GenerateSelfSignedCertificate(
    const SelfSignedCertificateOptions& options);

X509* ReadPemCert(absl::string_view pem_cert);

X509_CRL* ReadCrl(absl::string_view crl_pem);

std::string Protect(tsi_frame_protector* protector, absl::string_view buffer);

std::string Unprotect(tsi_frame_protector* protector, absl::string_view buffer);

#endif
