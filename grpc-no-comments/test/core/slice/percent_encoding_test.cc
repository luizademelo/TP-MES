
// Copyright 2016 gRPC authors.

#include "src/core/lib/slice/percent_encoding.h"

#include <grpc/support/alloc.h>
#include <stddef.h>

#include <memory>
#include <utility>

#include "absl/log/log.h"
#include "gtest/gtest.h"
#include "src/core/lib/slice/slice_string_helpers.h"
#include "src/core/util/string.h"
#include "test/core/test_util/test_config.h"

#define TEST_VECTOR(raw, encoded, dict) \
  test_vector(raw, sizeof(raw) - 1, encoded, sizeof(encoded) - 1, dict)

#define TEST_NONCONFORMANT_VECTOR(encoded, permissive_unencoded) \
  test_nonconformant_vector(encoded, sizeof(encoded) - 1,        \
                            permissive_unencoded,                \
                            sizeof(permissive_unencoded) - 1)

static void test_vector(const char* raw, size_t raw_length, const char* encoded,
                        size_t encoded_length,
                        grpc_core::PercentEncodingType type) {
  char* raw_msg = gpr_dump(raw, raw_length, GPR_DUMP_HEX | GPR_DUMP_ASCII);
  char* encoded_msg =
      gpr_dump(encoded, encoded_length, GPR_DUMP_HEX | GPR_DUMP_ASCII);
  VLOG(2) << "Trial:\nraw = " << raw_msg << "\nencoded = " << encoded_msg;
  gpr_free(raw_msg);
  gpr_free(encoded_msg);

  auto raw_slice = grpc_core::Slice::FromCopiedBuffer(raw, raw_length);
  auto encoded_slice =
      grpc_core::Slice::FromCopiedBuffer(encoded, encoded_length);
  auto raw2encoded_slice = grpc_core::PercentEncodeSlice(raw_slice.Ref(), type);
  auto encoded2raw_permissive_slice =
      grpc_core::PermissivePercentDecodeSlice(encoded_slice.Ref());

  char* raw2encoded_msg = grpc_dump_slice(raw2encoded_slice.c_slice(),
                                          GPR_DUMP_HEX | GPR_DUMP_ASCII);
  char* encoded2raw_permissive_msg = grpc_dump_slice(
      encoded2raw_permissive_slice.c_slice(), GPR_DUMP_HEX | GPR_DUMP_ASCII);
  VLOG(2) << "Result:\nraw2encoded = " << raw2encoded_msg
          << "\nencoded2raw_permissive = " << encoded2raw_permissive_msg;
  gpr_free(raw2encoded_msg);
  gpr_free(encoded2raw_permissive_msg);

  ASSERT_EQ(raw_slice, encoded2raw_permissive_slice);
  ASSERT_EQ(encoded_slice, raw2encoded_slice);
}

static void test_nonconformant_vector(const char* encoded,
                                      size_t encoded_length,
                                      const char* permissive_unencoded,
                                      size_t permissive_unencoded_length) {
  char* permissive_unencoded_msg =
      gpr_dump(permissive_unencoded, permissive_unencoded_length,
               GPR_DUMP_HEX | GPR_DUMP_ASCII);
  char* encoded_msg =
      gpr_dump(encoded, encoded_length, GPR_DUMP_HEX | GPR_DUMP_ASCII);
  VLOG(2) << "Trial:\nraw = " << permissive_unencoded_msg
          << "\nencoded = " << encoded_msg;
  gpr_free(permissive_unencoded_msg);
  gpr_free(encoded_msg);

  auto permissive_unencoded_slice = grpc_core::Slice::FromCopiedBuffer(
      permissive_unencoded, permissive_unencoded_length);
  auto encoded_slice =
      grpc_core::Slice::FromCopiedBuffer(encoded, encoded_length);
  auto encoded2raw_permissive_slice =
      grpc_core::PermissivePercentDecodeSlice(std::move(encoded_slice));

  char* encoded2raw_permissive_msg = grpc_dump_slice(
      encoded2raw_permissive_slice.c_slice(), GPR_DUMP_HEX | GPR_DUMP_ASCII);
  VLOG(2) << "Result:\nencoded2raw_permissive = " << encoded2raw_permissive_msg;
  gpr_free(encoded2raw_permissive_msg);

  ASSERT_EQ(permissive_unencoded_slice, encoded2raw_permissive_slice);
}

TEST(PercentEncodingTest, MainTest) {
  TEST_VECTOR(
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_.~",
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_.~",
      grpc_core::PercentEncodingType::URL);
  TEST_VECTOR("\x00", "%00", grpc_core::PercentEncodingType::URL);
  TEST_VECTOR("\x01", "%01", grpc_core::PercentEncodingType::URL);
  TEST_VECTOR("a b", "a%20b", grpc_core::PercentEncodingType::URL);
  TEST_VECTOR(" b", "%20b", grpc_core::PercentEncodingType::URL);
  TEST_VECTOR("a b", "a b", grpc_core::PercentEncodingType::Compatible);
  TEST_VECTOR(" b", " b", grpc_core::PercentEncodingType::Compatible);
  TEST_VECTOR("\x0f", "%0F", grpc_core::PercentEncodingType::URL);
  TEST_VECTOR("\xff", "%FF", grpc_core::PercentEncodingType::URL);
  TEST_VECTOR("\xee", "%EE", grpc_core::PercentEncodingType::URL);
  TEST_VECTOR("%2", "%252", grpc_core::PercentEncodingType::URL);
  TEST_NONCONFORMANT_VECTOR("%", "%");
  TEST_NONCONFORMANT_VECTOR("%A", "%A");
  TEST_NONCONFORMANT_VECTOR("%AG", "%AG");
  TEST_NONCONFORMANT_VECTOR("\0", "\0");
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestGrpcScope grpc_scope;
  return RUN_ALL_TESTS();
}
