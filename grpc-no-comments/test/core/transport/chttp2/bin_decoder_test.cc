
// Copyright 2016 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/bin_decoder.h"

#include <grpc/support/alloc.h>
#include <string.h>

#include <memory>

#include "absl/log/log.h"
#include "gtest/gtest.h"
#include "src/core/ext/transport/chttp2/transport/bin_encoder.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/slice/slice_string_helpers.h"
#include "src/core/util/string.h"
#include "test/core/test_util/test_config.h"

static int all_ok = 1;

static void expect_slice_eq(grpc_slice expected, grpc_slice slice,
                            const char* debug, int line) {
  if (!grpc_slice_eq(slice, expected)) {
    char* hs = grpc_dump_slice(slice, GPR_DUMP_HEX | GPR_DUMP_ASCII);
    char* he = grpc_dump_slice(expected, GPR_DUMP_HEX | GPR_DUMP_ASCII);
    LOG(ERROR) << "FAILED:" << line << ": " << debug << "\ngot:  " << hs
               << "\nwant: " << he;
    gpr_free(hs);
    gpr_free(he);
    all_ok = 0;
  }
  grpc_slice_unref(expected);
  grpc_slice_unref(slice);
}

static grpc_slice base64_encode(const char* s) {
  grpc_slice ss = grpc_slice_from_copied_string(s);
  grpc_slice out = grpc_chttp2_base64_encode(ss);
  grpc_slice_unref(ss);
  return out;
}

static grpc_slice base64_decode(const char* s) {
  grpc_slice ss = grpc_slice_from_copied_string(s);
  grpc_slice out = grpc_chttp2_base64_decode(ss);
  grpc_slice_unref(ss);
  return out;
}

static grpc_slice base64_decode_with_length(const char* s,
                                            size_t output_length) {
  grpc_slice ss = grpc_slice_from_copied_string(s);
  grpc_slice out = grpc_chttp2_base64_decode_with_length(ss, output_length);
  grpc_slice_unref(ss);
  return out;
}

static size_t base64_infer_length(const char* s) {
  grpc_slice ss = grpc_slice_from_copied_string(s);
  size_t out = grpc_chttp2_base64_infer_length_after_decode(ss);
  grpc_slice_unref(ss);
  return out;
}

#define EXPECT_DECODED_LENGTH(s, expected) \
  ASSERT_EQ((expected), base64_infer_length((s)));

#define EXPECT_SLICE_EQ(expected, slice)                                    \
  expect_slice_eq(                                                          \
      grpc_slice_from_copied_buffer(expected, sizeof(expected) - 1), slice, \
      #slice, __LINE__);

#define ENCODE_AND_DECODE(s) \
  EXPECT_SLICE_EQ(           \
      s, grpc_chttp2_base64_decode_with_length(base64_encode(s), strlen(s)));

TEST(BinDecoderTest, MainTest) {
  grpc_core::ExecCtx exec_ctx;

  ENCODE_AND_DECODE("");
  ENCODE_AND_DECODE("f");
  ENCODE_AND_DECODE("foo");
  ENCODE_AND_DECODE("fo");
  ENCODE_AND_DECODE("foob");
  ENCODE_AND_DECODE("fooba");
  ENCODE_AND_DECODE("foobar");

  ENCODE_AND_DECODE("\xc0\xc1\xc2\xc3\xc4\xc5");

  EXPECT_SLICE_EQ("", base64_decode(""));

  EXPECT_SLICE_EQ("f", base64_decode("Zg=="));

  EXPECT_SLICE_EQ("fo", base64_decode("Zm8="));

  EXPECT_SLICE_EQ("foo", base64_decode("Zm9v"));

  EXPECT_SLICE_EQ("foob", base64_decode("Zm9vYg=="));

  EXPECT_SLICE_EQ("fooba", base64_decode("Zm9vYmE="));

  EXPECT_SLICE_EQ("foobar", base64_decode("Zm9vYmFy"));

  EXPECT_SLICE_EQ("\xc0\xc1\xc2\xc3\xc4\xc5", base64_decode("wMHCw8TF"));

  EXPECT_SLICE_EQ("", base64_decode("a"));
  EXPECT_SLICE_EQ("", base64_decode("ab"));
  EXPECT_SLICE_EQ("", base64_decode("abc"));

  EXPECT_SLICE_EQ("", base64_decode("Zm:v"));
  EXPECT_SLICE_EQ("", base64_decode("Zm=v"));

  EXPECT_SLICE_EQ("", base64_decode_with_length("Zg", 2));
  EXPECT_SLICE_EQ("", base64_decode_with_length("Zm8", 3));
  EXPECT_SLICE_EQ("", base64_decode_with_length("Zm9v", 4));

  EXPECT_SLICE_EQ("", base64_decode_with_length("Zm:v", 3));
  EXPECT_SLICE_EQ("", base64_decode_with_length("Zm=v", 3));

  EXPECT_DECODED_LENGTH("", 0);
  EXPECT_DECODED_LENGTH("ab", 1);
  EXPECT_DECODED_LENGTH("abc", 2);
  EXPECT_DECODED_LENGTH("abcd", 3);
  EXPECT_DECODED_LENGTH("abcdef", 4);
  EXPECT_DECODED_LENGTH("abcdefg", 5);
  EXPECT_DECODED_LENGTH("abcdefgh", 6);

  EXPECT_DECODED_LENGTH("ab==", 1);
  EXPECT_DECODED_LENGTH("abc=", 2);
  EXPECT_DECODED_LENGTH("abcd", 3);
  EXPECT_DECODED_LENGTH("abcdef==", 4);
  EXPECT_DECODED_LENGTH("abcdefg=", 5);
  EXPECT_DECODED_LENGTH("abcdefgh", 6);

  EXPECT_DECODED_LENGTH("a", 0);
  EXPECT_DECODED_LENGTH("a===", 0);
  EXPECT_DECODED_LENGTH("abcde", 0);
  EXPECT_DECODED_LENGTH("abcde===", 0);
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestGrpcScope grpc_scope;
  return RUN_ALL_TESTS();
}
