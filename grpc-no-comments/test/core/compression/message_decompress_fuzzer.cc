
// Copyright 2019 gRPC authors.

#include <grpc/compression.h>
#include <grpc/grpc.h>
#include <grpc/slice.h>
#include <grpc/slice_buffer.h>
#include <stdint.h>

#include <cstdint>
#include <vector>

#include "fuzztest/fuzztest.h"
#include "src/core/lib/compression/message_compress.h"

using fuzztest::Arbitrary;
using fuzztest::ElementOf;
using fuzztest::VectorOf;

void CheckDecompresses(grpc_compression_algorithm compression_algorithm,
                       std::vector<uint8_t> buffer) {
  grpc_init();
  grpc_slice_buffer input_buffer;
  grpc_slice_buffer_init(&input_buffer);
  grpc_slice_buffer_add(
      &input_buffer,
      grpc_slice_from_copied_buffer(
          reinterpret_cast<const char*>(buffer.data()), buffer.size()));
  grpc_slice_buffer output_buffer;
  grpc_slice_buffer_init(&output_buffer);

  grpc_msg_decompress(compression_algorithm, &input_buffer, &output_buffer);

  grpc_slice_buffer_destroy(&input_buffer);
  grpc_slice_buffer_destroy(&output_buffer);
  grpc_shutdown();
}
FUZZ_TEST(MyTestSuite, CheckDecompresses)
    .WithDomains(ElementOf({GRPC_COMPRESS_NONE, GRPC_COMPRESS_DEFLATE,
                            GRPC_COMPRESS_GZIP}),
                 VectorOf(Arbitrary<uint8_t>()).WithMinSize(1));
