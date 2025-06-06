
// Copyright 2017 gRPC authors.

#include "src/core/tsi/fake_transport_security.h"

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "gtest/gtest.h"
#include "src/core/credentials/transport/security_connector.h"
#include "src/core/tsi/transport_security.h"
#include "src/core/util/crash.h"
#include "test/core/test_util/test_config.h"
#include "test/core/tsi/transport_security_test_lib.h"

typedef struct fake_tsi_test_fixture {
  tsi_test_fixture base;
} fake_tsi_test_fixture;

static void fake_test_setup_handshakers(tsi_test_fixture* fixture) {
  fixture->client_handshaker =
      tsi_create_fake_handshaker(true );
  fixture->server_handshaker =
      tsi_create_fake_handshaker(false );
}

static void validate_handshaker_peers(tsi_handshaker_result* result) {
  ASSERT_NE(result, nullptr);
  tsi_peer peer;
  ASSERT_EQ(tsi_handshaker_result_extract_peer(result, &peer), TSI_OK);
  const tsi_peer_property* property =
      tsi_peer_get_property_by_name(&peer, TSI_CERTIFICATE_TYPE_PEER_PROPERTY);
  ASSERT_NE(property, nullptr);
  ASSERT_EQ(memcmp(property->value.data, TSI_FAKE_CERTIFICATE_TYPE,
                   property->value.length),
            0);
  property =
      tsi_peer_get_property_by_name(&peer, TSI_SECURITY_LEVEL_PEER_PROPERTY);
  ASSERT_NE(property, nullptr);
  ASSERT_EQ(memcmp(property->value.data, TSI_FAKE_SECURITY_LEVEL,
                   property->value.length),
            0);
  tsi_peer_destruct(&peer);
}

static void fake_test_check_handshaker_peers(tsi_test_fixture* fixture) {
  validate_handshaker_peers(fixture->client_result);
  validate_handshaker_peers(fixture->server_result);
}

static void fake_test_destruct(tsi_test_fixture* fixture) { gpr_free(fixture); }

static const struct tsi_test_fixture_vtable vtable = {
    fake_test_setup_handshakers, fake_test_check_handshaker_peers,
    fake_test_destruct};

static tsi_test_fixture* fake_tsi_test_fixture_create() {
  fake_tsi_test_fixture* fake_fixture =
      static_cast<fake_tsi_test_fixture*>(gpr_zalloc(sizeof(*fake_fixture)));
  tsi_test_fixture_init(&fake_fixture->base);
  fake_fixture->base.vtable = &vtable;
  return &fake_fixture->base;
}

TEST(FakeTransportSecurityTest, FakeTsiTestDoHandshakeTinyHandshakeBuffer) {
  tsi_test_fixture* fixture = fake_tsi_test_fixture_create();
  fixture->handshake_buffer_size = TSI_TEST_TINY_HANDSHAKE_BUFFER_SIZE;
  tsi_test_do_handshake(fixture);
  tsi_test_fixture_destroy(fixture);
}

TEST(FakeTransportSecurityTest, FakeTsiTestDoHandshakeSmallHandshakeBuffer) {
  tsi_test_fixture* fixture = fake_tsi_test_fixture_create();
  fixture->handshake_buffer_size = TSI_TEST_SMALL_HANDSHAKE_BUFFER_SIZE;
  tsi_test_do_handshake(fixture);
  tsi_test_fixture_destroy(fixture);
}

TEST(FakeTransportSecurityTest, FakeTsiTestDoHandshake) {
  tsi_test_fixture* fixture = fake_tsi_test_fixture_create();
  tsi_test_do_handshake(fixture);
  tsi_test_fixture_destroy(fixture);
}

TEST(FakeTransportSecurityTest, FakeTsiTestDoRoundTripForAllConfigs) {
  unsigned int* bit_array = static_cast<unsigned int*>(
      gpr_zalloc(sizeof(unsigned int) * TSI_TEST_NUM_OF_ARGUMENTS));
  const unsigned int mask = 1U << (TSI_TEST_NUM_OF_ARGUMENTS - 1);
  for (unsigned int val = 0; val < TSI_TEST_NUM_OF_COMBINATIONS; val++) {
    unsigned int v = val;
    for (unsigned int ind = 0; ind < TSI_TEST_NUM_OF_ARGUMENTS; ind++) {
      bit_array[ind] = (v & mask) ? 1 : 0;
      v <<= 1;
    }
    tsi_test_fixture* fixture = fake_tsi_test_fixture_create();
    fake_tsi_test_fixture* fake_fixture =
        reinterpret_cast<fake_tsi_test_fixture*>(fixture);
    tsi_test_frame_protector_config_destroy(fake_fixture->base.config);
    fake_fixture->base.config = tsi_test_frame_protector_config_create(
        bit_array[0], bit_array[1], bit_array[2], bit_array[3], bit_array[4],
        bit_array[5], bit_array[6]);
    tsi_test_do_round_trip(&fake_fixture->base);
    tsi_test_fixture_destroy(fixture);
  }
  gpr_free(bit_array);
}

TEST(FakeTransportSecurityTest, FakeTsiTestDoRoundTripOddBufferSize) {
  const size_t odd_sizes[] = {1025, 2051, 4103, 8207, 16409};
  const size_t size = sizeof(odd_sizes) / sizeof(size_t);
  for (size_t ind1 = 0; ind1 < size; ind1++) {
    for (size_t ind2 = 0; ind2 < size; ind2++) {
      for (size_t ind3 = 0; ind3 < size; ind3++) {
        for (size_t ind4 = 0; ind4 < size; ind4++) {
          for (size_t ind5 = 0; ind5 < size; ind5++) {
            tsi_test_fixture* fixture = fake_tsi_test_fixture_create();
            fake_tsi_test_fixture* fake_fixture =
                reinterpret_cast<fake_tsi_test_fixture*>(fixture);
            tsi_test_frame_protector_config_set_buffer_size(
                fake_fixture->base.config, odd_sizes[ind1], odd_sizes[ind2],
                odd_sizes[ind3], odd_sizes[ind4], odd_sizes[ind5]);
            tsi_test_do_round_trip(&fake_fixture->base);
            tsi_test_fixture_destroy(fixture);
          }
        }
      }
    }
  }
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestGrpcScope grpc_scope;
  return RUN_ALL_TESTS();
}
