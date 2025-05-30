
// Copyright 2015 gRPC authors.

#include <grpc/compression.h>
#include <grpc/slice.h>
#include <stdint.h>
#include <stdlib.h>

#include <memory>

#include "absl/log/log.h"
#include "gtest/gtest.h"
#include "src/core/util/useful.h"
#include "test/core/test_util/test_config.h"

TEST(CompressionTest, CompressionAlgorithmParse) {
  size_t i;
  const char* valid_names[] = {"identity", "gzip", "deflate"};
  const grpc_compression_algorithm valid_algorithms[] = {
      GRPC_COMPRESS_NONE,
      GRPC_COMPRESS_GZIP,
      GRPC_COMPRESS_DEFLATE,
  };
  const char* invalid_names[] = {"gzip2", "foo", "", "2gzip"};

  VLOG(2) << "test_compression_algorithm_parse";

  for (i = 0; i < GPR_ARRAY_SIZE(valid_names); i++) {
    const char* valid_name = valid_names[i];
    grpc_compression_algorithm algorithm;
    const int success = grpc_compression_algorithm_parse(
        grpc_slice_from_static_string(valid_name), &algorithm);
    ASSERT_NE(success, 0);
    ASSERT_EQ(algorithm, valid_algorithms[i]);
  }

  for (i = 0; i < GPR_ARRAY_SIZE(invalid_names); i++) {
    const char* invalid_name = invalid_names[i];
    grpc_compression_algorithm algorithm;
    int success;
    success = grpc_compression_algorithm_parse(
        grpc_slice_from_static_string(invalid_name), &algorithm);
    ASSERT_EQ(success, 0);

  }
}

TEST(CompressionTest, CompressionAlgorithmName) {
  int success;
  const char* name;
  size_t i;
  const char* valid_names[] = {"identity", "gzip", "deflate"};
  const grpc_compression_algorithm valid_algorithms[] = {
      GRPC_COMPRESS_NONE,
      GRPC_COMPRESS_GZIP,
      GRPC_COMPRESS_DEFLATE,
  };

  VLOG(2) << "test_compression_algorithm_name";

  for (i = 0; i < GPR_ARRAY_SIZE(valid_algorithms); i++) {
    success = grpc_compression_algorithm_name(valid_algorithms[i], &name);
    ASSERT_NE(success, 0);
    ASSERT_STREQ(name, valid_names[i]);
  }

  success =
      grpc_compression_algorithm_name(GRPC_COMPRESS_ALGORITHMS_COUNT, &name);
  ASSERT_EQ(success, 0);

}

TEST(CompressionTest, CompressionAlgorithmForLevel) {
  VLOG(2) << "test_compression_algorithm_for_level";

  {

    uint32_t accepted_encodings = 0;
    grpc_core::SetBit(&accepted_encodings, GRPC_COMPRESS_NONE);

    ASSERT_EQ(GRPC_COMPRESS_NONE,
              grpc_compression_algorithm_for_level(GRPC_COMPRESS_LEVEL_NONE,
                                                   accepted_encodings));

    ASSERT_EQ(GRPC_COMPRESS_NONE,
              grpc_compression_algorithm_for_level(GRPC_COMPRESS_LEVEL_LOW,
                                                   accepted_encodings));

    ASSERT_EQ(GRPC_COMPRESS_NONE,
              grpc_compression_algorithm_for_level(GRPC_COMPRESS_LEVEL_MED,
                                                   accepted_encodings));

    ASSERT_EQ(GRPC_COMPRESS_NONE,
              grpc_compression_algorithm_for_level(GRPC_COMPRESS_LEVEL_HIGH,
                                                   accepted_encodings));
  }

  {

    uint32_t accepted_encodings = 0;
    grpc_core::SetBit(&accepted_encodings, GRPC_COMPRESS_NONE);
    grpc_core::SetBit(&accepted_encodings, GRPC_COMPRESS_GZIP);

    ASSERT_EQ(GRPC_COMPRESS_NONE,
              grpc_compression_algorithm_for_level(GRPC_COMPRESS_LEVEL_NONE,
                                                   accepted_encodings));

    ASSERT_EQ(GRPC_COMPRESS_GZIP,
              grpc_compression_algorithm_for_level(GRPC_COMPRESS_LEVEL_LOW,
                                                   accepted_encodings));

    ASSERT_EQ(GRPC_COMPRESS_GZIP,
              grpc_compression_algorithm_for_level(GRPC_COMPRESS_LEVEL_MED,
                                                   accepted_encodings));

    ASSERT_EQ(GRPC_COMPRESS_GZIP,
              grpc_compression_algorithm_for_level(GRPC_COMPRESS_LEVEL_HIGH,
                                                   accepted_encodings));
  }

  {

    uint32_t accepted_encodings = 0;
    grpc_core::SetBit(&accepted_encodings, GRPC_COMPRESS_NONE);
    grpc_core::SetBit(&accepted_encodings, GRPC_COMPRESS_DEFLATE);

    ASSERT_EQ(GRPC_COMPRESS_NONE,
              grpc_compression_algorithm_for_level(GRPC_COMPRESS_LEVEL_NONE,
                                                   accepted_encodings));

    ASSERT_EQ(GRPC_COMPRESS_DEFLATE,
              grpc_compression_algorithm_for_level(GRPC_COMPRESS_LEVEL_LOW,
                                                   accepted_encodings));

    ASSERT_EQ(GRPC_COMPRESS_DEFLATE,
              grpc_compression_algorithm_for_level(GRPC_COMPRESS_LEVEL_MED,
                                                   accepted_encodings));

    ASSERT_EQ(GRPC_COMPRESS_DEFLATE,
              grpc_compression_algorithm_for_level(GRPC_COMPRESS_LEVEL_HIGH,
                                                   accepted_encodings));
  }

  {

    uint32_t accepted_encodings = 0;
    grpc_core::SetBit(&accepted_encodings, GRPC_COMPRESS_NONE);
    grpc_core::SetBit(&accepted_encodings, GRPC_COMPRESS_GZIP);
    grpc_core::SetBit(&accepted_encodings, GRPC_COMPRESS_DEFLATE);

    ASSERT_EQ(GRPC_COMPRESS_NONE,
              grpc_compression_algorithm_for_level(GRPC_COMPRESS_LEVEL_NONE,
                                                   accepted_encodings));

    ASSERT_EQ(GRPC_COMPRESS_GZIP,
              grpc_compression_algorithm_for_level(GRPC_COMPRESS_LEVEL_LOW,
                                                   accepted_encodings));

    ASSERT_EQ(GRPC_COMPRESS_DEFLATE,
              grpc_compression_algorithm_for_level(GRPC_COMPRESS_LEVEL_MED,
                                                   accepted_encodings));

    ASSERT_EQ(GRPC_COMPRESS_DEFLATE,
              grpc_compression_algorithm_for_level(GRPC_COMPRESS_LEVEL_HIGH,
                                                   accepted_encodings));
  }

  {

    uint32_t accepted_encodings = 0;
    grpc_core::SetBit(&accepted_encodings, GRPC_COMPRESS_NONE);
    grpc_core::SetBit(&accepted_encodings, GRPC_COMPRESS_GZIP);
    grpc_core::SetBit(&accepted_encodings, GRPC_COMPRESS_DEFLATE);

    ASSERT_EQ(GRPC_COMPRESS_NONE,
              grpc_compression_algorithm_for_level(GRPC_COMPRESS_LEVEL_NONE,
                                                   accepted_encodings));

    ASSERT_EQ(GRPC_COMPRESS_GZIP,
              grpc_compression_algorithm_for_level(GRPC_COMPRESS_LEVEL_LOW,
                                                   accepted_encodings));

    ASSERT_EQ(GRPC_COMPRESS_DEFLATE,
              grpc_compression_algorithm_for_level(GRPC_COMPRESS_LEVEL_MED,
                                                   accepted_encodings));

    ASSERT_EQ(GRPC_COMPRESS_DEFLATE,
              grpc_compression_algorithm_for_level(GRPC_COMPRESS_LEVEL_HIGH,
                                                   accepted_encodings));
  }
}

TEST(CompressionTest, CompressionEnableDisableAlgorithm) {
  grpc_compression_options options;
  grpc_compression_algorithm algorithm;

  VLOG(2) << "test_compression_enable_disable_algorithm";

  grpc_compression_options_init(&options);
  for (algorithm = GRPC_COMPRESS_NONE;
       algorithm < GRPC_COMPRESS_ALGORITHMS_COUNT;
       algorithm = static_cast<grpc_compression_algorithm>(
           static_cast<int>(algorithm) + 1)) {

    ASSERT_NE(
        grpc_compression_options_is_algorithm_enabled(&options, algorithm), 0);
  }

  for (algorithm = GRPC_COMPRESS_NONE;
       algorithm < GRPC_COMPRESS_ALGORITHMS_COUNT;
       algorithm = static_cast<grpc_compression_algorithm>(
           static_cast<int>(algorithm) + 1)) {
    grpc_compression_options_disable_algorithm(&options, algorithm);
    ASSERT_EQ(
        grpc_compression_options_is_algorithm_enabled(&options, algorithm), 0);
  }

  for (algorithm = GRPC_COMPRESS_NONE;
       algorithm < GRPC_COMPRESS_ALGORITHMS_COUNT;
       algorithm = static_cast<grpc_compression_algorithm>(
           static_cast<int>(algorithm) + 1)) {
    grpc_compression_options_enable_algorithm(&options, algorithm);
    ASSERT_NE(
        grpc_compression_options_is_algorithm_enabled(&options, algorithm), 0);
  }
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestGrpcScope grpc_scope;
  return RUN_ALL_TESTS();
}
