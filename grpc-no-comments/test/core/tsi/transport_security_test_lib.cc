
// Copyright 2017 gRPC authors.

#include "test/core/tsi/transport_security_test_lib.h"

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <openssl/asn1.h>
#include <openssl/bio.h>
#include <openssl/bn.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "absl/log/check.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/tsi/transport_security_interface.h"
#include "src/core/util/crash.h"
#include "src/core/util/memory.h"

static void notification_signal(tsi_test_fixture* fixture) {
  gpr_mu_lock(&fixture->mu);
  fixture->notified = true;
  gpr_cv_signal(&fixture->cv);
  gpr_mu_unlock(&fixture->mu);
}

static void notification_wait(tsi_test_fixture* fixture) {
  gpr_mu_lock(&fixture->mu);
  while (!fixture->notified) {
    gpr_cv_wait(&fixture->cv, &fixture->mu, gpr_inf_future(GPR_CLOCK_REALTIME));
  }
  fixture->notified = false;
  gpr_mu_unlock(&fixture->mu);
}

typedef struct handshaker_args {
  tsi_test_fixture* fixture;
  unsigned char* handshake_buffer;
  size_t handshake_buffer_size;
  bool is_client;
  bool transferred_data;
  bool appended_unused_bytes;
  grpc_error_handle error;
} handshaker_args;

static handshaker_args* handshaker_args_create(tsi_test_fixture* fixture,
                                               bool is_client) {
  CHECK_NE(fixture, nullptr);
  CHECK_NE(fixture->config, nullptr);
  handshaker_args* args = new handshaker_args();
  args->fixture = fixture;
  args->handshake_buffer_size = fixture->handshake_buffer_size;
  args->handshake_buffer =
      static_cast<unsigned char*>(gpr_zalloc(args->handshake_buffer_size));
  args->is_client = is_client;
  args->error = absl::OkStatus();
  return args;
}

static void handshaker_args_destroy(handshaker_args* args) {
  gpr_free(args->handshake_buffer);
  delete args;
}

static void do_handshaker_next(handshaker_args* args);

static void setup_handshakers(tsi_test_fixture* fixture) {
  CHECK_NE(fixture, nullptr);
  CHECK_NE(fixture->vtable, nullptr);
  CHECK_NE(fixture->vtable->setup_handshakers, nullptr);
  fixture->vtable->setup_handshakers(fixture);
}

static void check_unused_bytes(tsi_test_fixture* fixture) {
  tsi_handshaker_result* result_with_unused_bytes =
      fixture->has_client_finished_first ? fixture->server_result
                                         : fixture->client_result;
  tsi_handshaker_result* result_without_unused_bytes =
      fixture->has_client_finished_first ? fixture->client_result
                                         : fixture->server_result;
  const unsigned char* bytes = nullptr;
  size_t bytes_size = 0;
  CHECK(tsi_handshaker_result_get_unused_bytes(result_with_unused_bytes, &bytes,
                                               &bytes_size) == TSI_OK);
  CHECK_EQ(bytes_size, strlen(TSI_TEST_UNUSED_BYTES));
  CHECK_EQ(memcmp(bytes, TSI_TEST_UNUSED_BYTES, bytes_size), 0);
  CHECK(tsi_handshaker_result_get_unused_bytes(result_without_unused_bytes,
                                               &bytes, &bytes_size) == TSI_OK);
  CHECK_EQ(bytes_size, 0u);
  CHECK_EQ(bytes, nullptr);
}

static void check_handshake_results(tsi_test_fixture* fixture) {
  CHECK_NE(fixture, nullptr);
  CHECK_NE(fixture->vtable, nullptr);
  CHECK_NE(fixture->vtable->check_handshaker_peers, nullptr);

  fixture->vtable->check_handshaker_peers(fixture);

  if (fixture->test_unused_bytes) {
    tsi_test_channel* channel = fixture->channel;
    if (fixture->server_result != nullptr &&
        fixture->client_result != nullptr) {
      check_unused_bytes(fixture);
    }
    channel->bytes_written_to_server_channel = 0;
    channel->bytes_written_to_client_channel = 0;
    channel->bytes_read_from_client_channel = 0;
    channel->bytes_read_from_server_channel = 0;
  }
}

static void send_bytes_to_peer(tsi_test_channel* test_channel,
                               const unsigned char* buf, size_t buf_size,
                               bool is_client) {
  CHECK_NE(test_channel, nullptr);
  CHECK_NE(buf, nullptr);
  uint8_t* channel =
      is_client ? test_channel->server_channel : test_channel->client_channel;
  CHECK_NE(channel, nullptr);
  size_t* bytes_written = is_client
                              ? &test_channel->bytes_written_to_server_channel
                              : &test_channel->bytes_written_to_client_channel;
  CHECK_NE(bytes_written, nullptr);
  CHECK_LE(*bytes_written + buf_size,
           static_cast<size_t>(TSI_TEST_DEFAULT_CHANNEL_SIZE));

  memcpy(channel + *bytes_written, buf, buf_size);
  *bytes_written += buf_size;
}

static void maybe_append_unused_bytes(handshaker_args* args) {
  CHECK_NE(args, nullptr);
  CHECK_NE(args->fixture, nullptr);
  tsi_test_fixture* fixture = args->fixture;
  if (fixture->test_unused_bytes && !args->appended_unused_bytes) {
    args->appended_unused_bytes = true;
    send_bytes_to_peer(
        fixture->channel,
        reinterpret_cast<const unsigned char*>(TSI_TEST_UNUSED_BYTES),
        strlen(TSI_TEST_UNUSED_BYTES), args->is_client);
    if (fixture->client_result != nullptr &&
        fixture->server_result == nullptr) {
      fixture->has_client_finished_first = true;
    }
  }
}

static void receive_bytes_from_peer(tsi_test_channel* test_channel,
                                    unsigned char** buf, size_t* buf_size,
                                    bool is_client) {
  CHECK_NE(test_channel, nullptr);
  CHECK_NE(*buf, nullptr);
  CHECK_NE(buf_size, nullptr);
  uint8_t* channel =
      is_client ? test_channel->client_channel : test_channel->server_channel;
  CHECK_NE(channel, nullptr);
  size_t* bytes_read = is_client
                           ? &test_channel->bytes_read_from_client_channel
                           : &test_channel->bytes_read_from_server_channel;
  size_t* bytes_written = is_client
                              ? &test_channel->bytes_written_to_client_channel
                              : &test_channel->bytes_written_to_server_channel;
  CHECK_NE(bytes_read, nullptr);
  CHECK_NE(bytes_written, nullptr);
  size_t to_read = *buf_size < *bytes_written - *bytes_read
                       ? *buf_size
                       : *bytes_written - *bytes_read;

  memcpy(*buf, channel + *bytes_read, to_read);
  *buf_size = to_read;
  *bytes_read += to_read;
}

void tsi_test_frame_protector_send_message_to_peer(
    tsi_test_frame_protector_config* config, tsi_test_channel* channel,
    tsi_frame_protector* protector, bool is_client) {

  CHECK_NE(config, nullptr);
  CHECK_NE(channel, nullptr);
  CHECK_NE(protector, nullptr);
  unsigned char* protected_buffer =
      static_cast<unsigned char*>(gpr_zalloc(config->protected_buffer_size));
  size_t message_size =
      is_client ? config->client_message_size : config->server_message_size;
  uint8_t* message =
      is_client ? config->client_message : config->server_message;
  CHECK_NE(message, nullptr);
  const unsigned char* message_bytes =
      reinterpret_cast<unsigned char*>(message);
  tsi_result result = TSI_OK;

  while (message_size > 0 && result == TSI_OK) {
    size_t protected_buffer_size_to_send = config->protected_buffer_size;
    size_t processed_message_size = message_size;

    result = tsi_frame_protector_protect(
        protector, message_bytes, &processed_message_size, protected_buffer,
        &protected_buffer_size_to_send);
    CHECK(result == TSI_OK);

    send_bytes_to_peer(channel, protected_buffer, protected_buffer_size_to_send,
                       is_client);
    message_bytes += processed_message_size;
    message_size -= processed_message_size;

    if (message_size == 0) {
      size_t still_pending_size;
      do {
        protected_buffer_size_to_send = config->protected_buffer_size;
        result = tsi_frame_protector_protect_flush(
            protector, protected_buffer, &protected_buffer_size_to_send,
            &still_pending_size);
        CHECK(result == TSI_OK);
        send_bytes_to_peer(channel, protected_buffer,
                           protected_buffer_size_to_send, is_client);
      } while (still_pending_size > 0 && result == TSI_OK);
      CHECK(result == TSI_OK);
    }
  }
  CHECK(result == TSI_OK);
  gpr_free(protected_buffer);
}

void tsi_test_frame_protector_receive_message_from_peer(
    tsi_test_frame_protector_config* config, tsi_test_channel* channel,
    tsi_frame_protector* protector, unsigned char* message,
    size_t* bytes_received, bool is_client) {

  CHECK_NE(config, nullptr);
  CHECK_NE(channel, nullptr);
  CHECK_NE(protector, nullptr);
  CHECK_NE(message, nullptr);
  CHECK_NE(bytes_received, nullptr);
  size_t read_offset = 0;
  size_t message_offset = 0;
  size_t read_from_peer_size = 0;
  tsi_result result = TSI_OK;
  bool done = false;
  unsigned char* read_buffer = static_cast<unsigned char*>(
      gpr_zalloc(config->read_buffer_allocated_size));
  unsigned char* message_buffer = static_cast<unsigned char*>(
      gpr_zalloc(config->message_buffer_allocated_size));

  while (!done && result == TSI_OK) {

    if (read_from_peer_size == 0) {
      read_from_peer_size = config->read_buffer_allocated_size;
      receive_bytes_from_peer(channel, &read_buffer, &read_from_peer_size,
                              is_client);
      read_offset = 0;
    }
    if (read_from_peer_size == 0) {
      done = true;
    }

    size_t message_buffer_size;
    do {
      message_buffer_size = config->message_buffer_allocated_size;
      size_t processed_size = read_from_peer_size;
      result = tsi_frame_protector_unprotect(
          protector, read_buffer + read_offset, &processed_size, message_buffer,
          &message_buffer_size);
      CHECK(result == TSI_OK);
      if (message_buffer_size > 0) {
        memcpy(message + message_offset, message_buffer, message_buffer_size);
        message_offset += message_buffer_size;
      }
      read_offset += processed_size;
      read_from_peer_size -= processed_size;
    } while ((read_from_peer_size > 0 || message_buffer_size > 0) &&
             result == TSI_OK);
    CHECK(result == TSI_OK);
  }
  CHECK(result == TSI_OK);
  *bytes_received = message_offset;
  gpr_free(read_buffer);
  gpr_free(message_buffer);
}

grpc_error_handle on_handshake_next_done(
    tsi_result result, void* user_data, const unsigned char* bytes_to_send,
    size_t bytes_to_send_size, tsi_handshaker_result* handshaker_result) {
  handshaker_args* args = static_cast<handshaker_args*>(user_data);
  CHECK_NE(args, nullptr);
  CHECK_NE(args->fixture, nullptr);
  tsi_test_fixture* fixture = args->fixture;
  grpc_error_handle error;

  if (result == TSI_INCOMPLETE_DATA) {
    CHECK_EQ(bytes_to_send_size, 0u);
    notification_signal(fixture);
    return error;
  }
  if (result != TSI_OK) {
    notification_signal(fixture);
    return GRPC_ERROR_CREATE(
        absl::StrCat("Handshake failed (", tsi_result_to_string(result), ")"));
  }

  if (handshaker_result != nullptr) {
    tsi_handshaker_result** result_to_write =
        args->is_client ? &fixture->client_result : &fixture->server_result;
    CHECK_EQ(*result_to_write, nullptr);
    *result_to_write = handshaker_result;
  }

  if (bytes_to_send_size > 0) {
    send_bytes_to_peer(fixture->channel, bytes_to_send, bytes_to_send_size,
                       args->is_client);
    args->transferred_data = true;
  }
  if (handshaker_result != nullptr) {
    maybe_append_unused_bytes(args);
  }
  notification_signal(fixture);
  return error;
}

static void on_handshake_next_done_wrapper(
    tsi_result result, void* user_data, const unsigned char* bytes_to_send,
    size_t bytes_to_send_size, tsi_handshaker_result* handshaker_result) {
  handshaker_args* args = static_cast<handshaker_args*>(user_data);
  args->error = on_handshake_next_done(result, user_data, bytes_to_send,
                                       bytes_to_send_size, handshaker_result);
}

static bool is_handshake_finished_properly(handshaker_args* args) {
  CHECK_NE(args, nullptr);
  CHECK_NE(args->fixture, nullptr);
  tsi_test_fixture* fixture = args->fixture;
  return (args->is_client && fixture->client_result != nullptr) ||
         (!args->is_client && fixture->server_result != nullptr);
}

static void do_handshaker_next(handshaker_args* args) {

  CHECK_NE(args, nullptr);
  CHECK_NE(args->fixture, nullptr);
  tsi_test_fixture* fixture = args->fixture;
  tsi_handshaker* handshaker =
      args->is_client ? fixture->client_handshaker : fixture->server_handshaker;
  if (is_handshake_finished_properly(args)) {
    return;
  }
  tsi_handshaker_result* handshaker_result = nullptr;
  unsigned char* bytes_to_send = nullptr;
  size_t bytes_to_send_size = 0;
  tsi_result result = TSI_OK;

  do {
    size_t buf_size = args->handshake_buffer_size;
    receive_bytes_from_peer(fixture->channel, &args->handshake_buffer,
                            &buf_size, args->is_client);
    if (buf_size > 0) {
      args->transferred_data = true;
    }

    result = tsi_handshaker_next(
        handshaker, args->handshake_buffer, buf_size,
        const_cast<const unsigned char**>(&bytes_to_send), &bytes_to_send_size,
        &handshaker_result, &on_handshake_next_done_wrapper, args);
    if (result != TSI_ASYNC) {
      args->error = on_handshake_next_done(
          result, args, bytes_to_send, bytes_to_send_size, handshaker_result);
      if (!args->error.ok()) {
        return;
      }
    }
  } while (result == TSI_INCOMPLETE_DATA);
  notification_wait(fixture);
}

void tsi_test_do_handshake(tsi_test_fixture* fixture) {

  setup_handshakers(fixture);
  handshaker_args* client_args =
      handshaker_args_create(fixture, true );
  handshaker_args* server_args =
      handshaker_args_create(fixture, false );

  do {
    client_args->transferred_data = false;
    server_args->transferred_data = false;
    do_handshaker_next(client_args);
    if (!client_args->error.ok()) {
      break;
    }
    do_handshaker_next(server_args);
    if (!server_args->error.ok()) {
      break;
    }

    CHECK(client_args->transferred_data || server_args->transferred_data);
  } while (fixture->client_result == nullptr ||
           fixture->server_result == nullptr);

  check_handshake_results(fixture);

  handshaker_args_destroy(client_args);
  handshaker_args_destroy(server_args);
}

static void tsi_test_do_ping_pong(tsi_test_frame_protector_config* config,
                                  tsi_test_channel* channel,
                                  tsi_frame_protector* client_frame_protector,
                                  tsi_frame_protector* server_frame_protector) {
  CHECK_NE(config, nullptr);
  CHECK_NE(channel, nullptr);
  CHECK_NE(client_frame_protector, nullptr);
  CHECK_NE(server_frame_protector, nullptr);

  tsi_test_frame_protector_send_message_to_peer(
      config, channel, client_frame_protector, true );
  unsigned char* server_received_message =
      static_cast<unsigned char*>(gpr_zalloc(TSI_TEST_DEFAULT_CHANNEL_SIZE));
  size_t server_received_message_size = 0;
  tsi_test_frame_protector_receive_message_from_peer(
      config, channel, server_frame_protector, server_received_message,
      &server_received_message_size, false );
  CHECK(config->client_message_size == server_received_message_size);
  CHECK_EQ(memcmp(config->client_message, server_received_message,
                  server_received_message_size),
           0);

  tsi_test_frame_protector_send_message_to_peer(
      config, channel, server_frame_protector, false );
  unsigned char* client_received_message =
      static_cast<unsigned char*>(gpr_zalloc(TSI_TEST_DEFAULT_CHANNEL_SIZE));
  size_t client_received_message_size = 0;
  tsi_test_frame_protector_receive_message_from_peer(
      config, channel, client_frame_protector, client_received_message,
      &client_received_message_size, true );
  CHECK_EQ(config->server_message_size, client_received_message_size);
  CHECK_EQ(memcmp(config->server_message, client_received_message,
                  client_received_message_size),
           0);
  gpr_free(server_received_message);
  gpr_free(client_received_message);
}

void tsi_test_frame_protector_do_round_trip_no_handshake(
    tsi_test_frame_protector_fixture* fixture) {
  CHECK_NE(fixture, nullptr);
  tsi_test_do_ping_pong(fixture->config, fixture->channel,
                        fixture->client_frame_protector,
                        fixture->server_frame_protector);
}

void tsi_test_do_round_trip(tsi_test_fixture* fixture) {

  CHECK_NE(fixture, nullptr);
  CHECK_NE(fixture->config, nullptr);
  tsi_test_frame_protector_config* config = fixture->config;
  tsi_frame_protector* client_frame_protector = nullptr;
  tsi_frame_protector* server_frame_protector = nullptr;

  tsi_test_do_handshake(fixture);

  size_t client_max_output_protected_frame_size =
      config->client_max_output_protected_frame_size;
  CHECK(tsi_handshaker_result_create_frame_protector(
            fixture->client_result,
            client_max_output_protected_frame_size == 0
                ? nullptr
                : &client_max_output_protected_frame_size,
            &client_frame_protector) == TSI_OK);
  size_t server_max_output_protected_frame_size =
      config->server_max_output_protected_frame_size;
  CHECK(tsi_handshaker_result_create_frame_protector(
            fixture->server_result,
            server_max_output_protected_frame_size == 0
                ? nullptr
                : &server_max_output_protected_frame_size,
            &server_frame_protector) == TSI_OK);
  tsi_test_do_ping_pong(config, fixture->channel, client_frame_protector,
                        server_frame_protector);

  tsi_frame_protector_destroy(client_frame_protector);
  tsi_frame_protector_destroy(server_frame_protector);
}

static unsigned char* generate_random_message(size_t size) {
  size_t i;
  unsigned char chars[] = "abcdefghijklmnopqrstuvwxyz1234567890";
  unsigned char* output =
      static_cast<unsigned char*>(gpr_zalloc(sizeof(unsigned char) * size));
  for (i = 0; i < size - 1; ++i) {
    output[i] = chars[rand() % static_cast<int>(sizeof(chars) - 1)];
  }
  return output;
}

tsi_test_frame_protector_config* tsi_test_frame_protector_config_create(
    bool use_default_read_buffer_allocated_size,
    bool use_default_message_buffer_allocated_size,
    bool use_default_protected_buffer_size, bool use_default_client_message,
    bool use_default_server_message,
    bool use_default_client_max_output_protected_frame_size,
    bool use_default_server_max_output_protected_frame_size) {
  tsi_test_frame_protector_config* config =
      static_cast<tsi_test_frame_protector_config*>(
          gpr_zalloc(sizeof(*config)));

  config->read_buffer_allocated_size =
      use_default_read_buffer_allocated_size
          ? TSI_TEST_DEFAULT_BUFFER_SIZE
          : TSI_TEST_SMALL_READ_BUFFER_ALLOCATED_SIZE;

  config->message_buffer_allocated_size =
      use_default_message_buffer_allocated_size
          ? TSI_TEST_DEFAULT_BUFFER_SIZE
          : TSI_TEST_SMALL_MESSAGE_BUFFER_ALLOCATED_SIZE;

  config->protected_buffer_size = use_default_protected_buffer_size
                                      ? TSI_TEST_DEFAULT_PROTECTED_BUFFER_SIZE
                                      : TSI_TEST_SMALL_PROTECTED_BUFFER_SIZE;

  config->client_message_size = use_default_client_message
                                    ? TSI_TEST_BIG_MESSAGE_SIZE
                                    : TSI_TEST_SMALL_MESSAGE_SIZE;
  config->client_message =
      use_default_client_message
          ? generate_random_message(TSI_TEST_BIG_MESSAGE_SIZE)
          : generate_random_message(TSI_TEST_SMALL_MESSAGE_SIZE);

  config->server_message_size = use_default_server_message
                                    ? TSI_TEST_BIG_MESSAGE_SIZE
                                    : TSI_TEST_SMALL_MESSAGE_SIZE;
  config->server_message =
      use_default_server_message
          ? generate_random_message(TSI_TEST_BIG_MESSAGE_SIZE)
          : generate_random_message(TSI_TEST_SMALL_MESSAGE_SIZE);

  config->client_max_output_protected_frame_size =
      use_default_client_max_output_protected_frame_size
          ? 0
          : TSI_TEST_SMALL_CLIENT_MAX_OUTPUT_PROTECTED_FRAME_SIZE;

  config->server_max_output_protected_frame_size =
      use_default_server_max_output_protected_frame_size
          ? 0
          : TSI_TEST_SMALL_SERVER_MAX_OUTPUT_PROTECTED_FRAME_SIZE;
  return config;
}

void tsi_test_frame_protector_config_set_buffer_size(
    tsi_test_frame_protector_config* config, size_t read_buffer_allocated_size,
    size_t message_buffer_allocated_size, size_t protected_buffer_size,
    size_t client_max_output_protected_frame_size,
    size_t server_max_output_protected_frame_size) {
  CHECK_NE(config, nullptr);
  config->read_buffer_allocated_size = read_buffer_allocated_size;
  config->message_buffer_allocated_size = message_buffer_allocated_size;
  config->protected_buffer_size = protected_buffer_size;
  config->client_max_output_protected_frame_size =
      client_max_output_protected_frame_size;
  config->server_max_output_protected_frame_size =
      server_max_output_protected_frame_size;
}

void tsi_test_frame_protector_config_destroy(
    tsi_test_frame_protector_config* config) {
  if (config == nullptr) {
    return;
  }
  gpr_free(config->client_message);
  gpr_free(config->server_message);
  gpr_free(config);
}

static tsi_test_channel* tsi_test_channel_create() {
  tsi_test_channel* channel = grpc_core::Zalloc<tsi_test_channel>();
  channel->client_channel =
      static_cast<uint8_t*>(gpr_zalloc(TSI_TEST_DEFAULT_CHANNEL_SIZE));
  channel->server_channel =
      static_cast<uint8_t*>(gpr_zalloc(TSI_TEST_DEFAULT_CHANNEL_SIZE));
  channel->bytes_written_to_client_channel = 0;
  channel->bytes_written_to_server_channel = 0;
  channel->bytes_read_from_client_channel = 0;
  channel->bytes_read_from_server_channel = 0;
  return channel;
}

static void tsi_test_channel_destroy(tsi_test_channel* channel) {
  if (channel == nullptr) {
    return;
  }
  gpr_free(channel->client_channel);
  gpr_free(channel->server_channel);
  gpr_free(channel);
}

void tsi_test_fixture_init(tsi_test_fixture* fixture) {
  memset(fixture, 0, sizeof(tsi_test_fixture));
  fixture->config = tsi_test_frame_protector_config_create(
      true, true, true, true, true, true, true);
  fixture->handshake_buffer_size = TSI_TEST_DEFAULT_BUFFER_SIZE;
  fixture->channel = tsi_test_channel_create();
  fixture->test_unused_bytes = true;
  fixture->has_client_finished_first = false;
  gpr_mu_init(&fixture->mu);
  gpr_cv_init(&fixture->cv);
  fixture->notified = false;
}

void tsi_test_fixture_destroy(tsi_test_fixture* fixture) {
  if (fixture == nullptr) {
    return;
  }
  tsi_test_frame_protector_config_destroy(fixture->config);
  tsi_handshaker_destroy(fixture->client_handshaker);
  tsi_handshaker_destroy(fixture->server_handshaker);
  tsi_handshaker_result_destroy(fixture->client_result);
  tsi_handshaker_result_destroy(fixture->server_result);
  tsi_test_channel_destroy(fixture->channel);
  CHECK_NE(fixture->vtable, nullptr);
  CHECK_NE(fixture->vtable->destruct, nullptr);
  gpr_mu_destroy(&fixture->mu);
  gpr_cv_destroy(&fixture->cv);
  fixture->vtable->destruct(fixture);
}

tsi_test_frame_protector_fixture* tsi_test_frame_protector_fixture_create() {
  tsi_test_frame_protector_fixture* fixture =
      static_cast<tsi_test_frame_protector_fixture*>(
          gpr_zalloc(sizeof(*fixture)));
  fixture->config = tsi_test_frame_protector_config_create(
      true, true, true, true, true, true, true);
  fixture->channel = tsi_test_channel_create();
  return fixture;
}

void tsi_test_frame_protector_fixture_init(
    tsi_test_frame_protector_fixture* fixture,
    tsi_frame_protector* client_frame_protector,
    tsi_frame_protector* server_frame_protector) {
  CHECK_NE(fixture, nullptr);
  fixture->client_frame_protector = client_frame_protector;
  fixture->server_frame_protector = server_frame_protector;
}

void tsi_test_frame_protector_fixture_destroy(
    tsi_test_frame_protector_fixture* fixture) {
  if (fixture == nullptr) {
    return;
  }
  tsi_test_frame_protector_config_destroy(fixture->config);
  tsi_test_channel_destroy(fixture->channel);
  tsi_frame_protector_destroy(fixture->client_frame_protector);
  tsi_frame_protector_destroy(fixture->server_frame_protector);
  gpr_free(fixture);
}

std::string GenerateSelfSignedCertificate(
    const SelfSignedCertificateOptions& options) {

  BIGNUM* bignum = BN_new();
  CHECK(BN_set_word(bignum, RSA_F4));
  BIGNUM* n = BN_new();
  CHECK(BN_set_word(n, 2048));
  EVP_PKEY* key = EVP_PKEY_new();

  X509* x509 = X509_new();

#if OPENSSL_VERSION_NUMBER < 0x30000000L
  RSA* rsa = RSA_new();
  CHECK(RSA_generate_key_ex(rsa, 2048, bignum, nullptr));
  CHECK(EVP_PKEY_assign_RSA(key, rsa));
  CHECK(X509_set_version(x509, 2));
#else
  key = EVP_RSA_gen(2048);
  CHECK(X509_set_version(x509, X509_VERSION_3));
#endif

  ASN1_UTCTIME* infinite_past = ASN1_UTCTIME_new();
  CHECK(ASN1_UTCTIME_set(infinite_past, 0));
#if OPENSSL_VERSION_NUMBER < 0x10100000
  CHECK(X509_set_notBefore(x509, infinite_past));
#else
  CHECK(X509_set1_notBefore(x509, infinite_past));
#endif
  ASN1_UTCTIME_free(infinite_past);
  ASN1_GENERALIZEDTIME* infinite_future = ASN1_GENERALIZEDTIME_new();
  CHECK(ASN1_GENERALIZEDTIME_set_string(infinite_future, "99991231235959Z"));
#if OPENSSL_VERSION_NUMBER < 0x10100000
  CHECK(X509_set_notAfter(x509, infinite_future));
#else
  CHECK(X509_set1_notAfter(x509, infinite_future));
#endif
  ASN1_GENERALIZEDTIME_free(infinite_future);

  X509_NAME* subject_name = X509_NAME_new();
  CHECK(X509_NAME_add_entry_by_txt(
      subject_name, "CN", MBSTRING_ASC,
      reinterpret_cast<const unsigned char*>(options.common_name.c_str()),
      -1, -1,
      0));
  CHECK(X509_NAME_add_entry_by_txt(
      subject_name, "O", MBSTRING_ASC,
      reinterpret_cast<const unsigned char*>(options.organization.c_str()),
      -1, -1,
      0));
  CHECK(X509_NAME_add_entry_by_txt(subject_name, "OU", MBSTRING_ASC,
                                   reinterpret_cast<const unsigned char*>(
                                       options.organizational_unit.c_str()),
                                   -1, -1,
                                   0));
  CHECK(X509_set_subject_name(x509, subject_name));
  X509_NAME_free(subject_name);

  CHECK(X509_set_pubkey(x509, key));
  CHECK(X509_sign(x509, key, EVP_sha256()));

  BIO* bio = BIO_new(BIO_s_mem());
  CHECK(PEM_write_bio_X509(bio, x509));
  const uint8_t* data = nullptr;
  size_t len = 0;

#ifdef OPENSSL_IS_BORINGSSL
  CHECK(BIO_mem_contents(bio, &data, &len));
#else
  len = BIO_get_mem_data(bio, &data);
#endif
  std::string pem = std::string(reinterpret_cast<const char*>(data), len);

  EVP_PKEY_free(key);
  X509_free(x509);
  BIO_free(bio);
  BN_free(bignum);
  BN_free(n);
  return pem;
}

X509* ReadPemCert(absl::string_view pem_cert) {
  BIO* cert_bio =
      BIO_new_mem_buf(pem_cert.data(), static_cast<int>(pem_cert.size()));

  if (cert_bio == nullptr) {
    return nullptr;
  }
  X509* cert = PEM_read_bio_X509(cert_bio, nullptr, nullptr, nullptr);
  BIO_free(cert_bio);
  return cert;
}

X509_CRL* ReadCrl(absl::string_view crl_pem) {
  BIO* crl_bio =
      BIO_new_mem_buf(crl_pem.data(), static_cast<int>(crl_pem.size()));

  if (crl_bio == nullptr) {
    return nullptr;
  }
  X509_CRL* crl = PEM_read_bio_X509_CRL(crl_bio, nullptr, nullptr, nullptr);
  BIO_free(crl_bio);
  return crl;
}

std::string Protect(tsi_frame_protector* protector, absl::string_view buffer) {
  static constexpr size_t kMaxBufferSize = 4096;
  CHECK(protector != nullptr);
  CHECK(buffer.size() < kMaxBufferSize);
  uint8_t* message_bytes =
      const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(buffer.data()));
  size_t message_size = buffer.size();
  uint8_t protected_buffer[kMaxBufferSize];
  uint8_t* cur = protected_buffer;
  uint8_t* end = cur + sizeof(protected_buffer);
  tsi_result result = TSI_OK;
  while (message_size > 0) {
    size_t protected_buffer_size_to_send = static_cast<size_t>(end - cur);
    size_t processed_message_size = message_size;
    result = tsi_frame_protector_protect(protector, message_bytes,
                                         &processed_message_size, cur,
                                         &protected_buffer_size_to_send);
    if (result != TSI_OK) break;
    message_bytes += processed_message_size;
    message_size -= processed_message_size;
    cur += protected_buffer_size_to_send;
    if (cur == end) break;
  }
  size_t still_pending_size;
  do {
    size_t protected_buffer_size_to_send = static_cast<size_t>(end - cur);
    result = tsi_frame_protector_protect_flush(
        protector, cur, &protected_buffer_size_to_send, &still_pending_size);
    if (result != TSI_OK) break;
    cur += protected_buffer_size_to_send;
    if (cur == end) break;
  } while (still_pending_size > 0);
  CHECK_EQ(result, TSI_OK);
  std::string protected_bytes(reinterpret_cast<const char*>(protected_buffer),
                              cur - protected_buffer);
  return protected_bytes;
}

std::string Unprotect(tsi_frame_protector* protector,
                      absl::string_view buffer) {
  static constexpr size_t kMaxBufferSize = 4096;
  CHECK(protector != nullptr);
  CHECK(buffer.size() < kMaxBufferSize);
  uint8_t* protected_bytes =
      const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(buffer.data()));
  size_t protected_size = buffer.size();
  uint8_t message_buffer[kMaxBufferSize];
  uint8_t* cur = message_buffer;
  uint8_t* end = cur + sizeof(message_buffer);
  tsi_result result = TSI_OK;
  bool keep_looping = false;
  while (protected_size > 0 || keep_looping) {
    size_t unprotected_buffer_size_written = static_cast<size_t>(end - cur);
    size_t processed_message_size = protected_size;
    result = tsi_frame_protector_unprotect(protector, protected_bytes,
                                           &processed_message_size, cur,
                                           &unprotected_buffer_size_written);
    if (result != TSI_OK) break;
    protected_bytes += processed_message_size;
    protected_size -= processed_message_size;
    cur += unprotected_buffer_size_written;

    if (cur == end) {
      CHECK(false) << "message_buffer too small";
    } else if (unprotected_buffer_size_written > 0) {
      keep_looping = true;
    } else {
      keep_looping = false;
    }
  }
  CHECK_EQ(result, TSI_OK);
  std::string message_bytes(reinterpret_cast<const char*>(message_buffer),
                            cur - message_buffer);
  return message_bytes;
}
