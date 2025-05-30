
// Copyright 2025 gRPC authors.

#include <grpc/grpc.h>
#include <sys/types.h>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <utility>
#include <variant>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/string_view.h"
#include "fuzztest/fuzztest.h"
#include "gtest/gtest.h"
#include "src/core/call/message.h"
#include "src/core/ext/transport/chttp2/transport/frame.h"
#include "src/core/ext/transport/chttp2/transport/message_assembler.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "test/core/transport/chttp2/http2_common_test_inputs.h"

namespace grpc_core {
namespace http2 {
namespace testing {

static uint64_t fuzz_stats_total_len = 0;
static uint64_t fuzz_stats_num_inputs = 0;

SliceBuffer GetFuzzedPayload(
    const std::variant<std::vector<uint8_t>, uint8_t>& step) {
  const std::vector<uint8_t>* fuzzed_input =
      std::get_if<std::vector<uint8_t>>(&step);
  SliceBuffer fuzzed_payload;
  if (fuzzed_input != nullptr) {
    fuzzed_payload.Append(Slice::FromCopiedBuffer(*fuzzed_input));
  }
  return fuzzed_payload;
}

void AssemblerFuzzer(
    std::vector<std::variant<std::vector<uint8_t>, uint8_t>> steps) {

  GrpcMessageAssembler assembler;
  LOG(INFO) << "AssemblerFuzzer num_steps: " << steps.size();
  size_t count_steps = 0;
  for (const auto& step : steps) {
    ++count_steps;
    if (std::holds_alternative<std::vector<uint8_t>>(step)) {
      SliceBuffer payload = GetFuzzedPayload(step);
      fuzz_stats_total_len += payload.Length();
      ++fuzz_stats_num_inputs;
      LOG(INFO) << "    AssemblerFuzzer Data : { Step:" << count_steps
                << ", Length: " << payload.Length()
                << ", Payload:" << payload.JoinIntoString() << " }";

      absl::Status result =
          assembler.AppendNewDataFrame(payload, false);
      VLOG(3) << "      AssemblerFuzzer AppendNewDataFrame result: " << result;
      EXPECT_EQ(payload.Length(), 0);
    } else {
      CHECK(std::holds_alternative<uint8_t>(step));
      const uint8_t num_msgs = std::get<uint8_t>(step);
      LOG(INFO) << "    AssemblerFuzzer Extract : { Step:" << count_steps
                << ", Number of extracts: " << static_cast<int>(num_msgs)
                << " }";
      for (uint8_t count_msgs = 0; count_msgs < num_msgs; count_msgs++) {
        absl::StatusOr<MessageHandle> result = assembler.ExtractMessage();
        if (!result.ok()) {

          LOG(INFO) << "    AssemblerFuzzer Extract Error: " << result.status();
          break;
        } else if (*result == nullptr) {

          LOG(INFO) << "    AssemblerFuzzer Extract : No more data";
          break;
        } else {
          LOG(INFO) << "    AssemblerFuzzer Extracted "
                    << (*result)->payload()->Length() << " Bytes";
        }
      }
    }
  }
  LOG(INFO) << "    AssemblerFuzzer Stats: Total len: " << fuzz_stats_total_len
            << ", Num inputs: " << fuzz_stats_num_inputs
            << " Average Input Length: "
            << (static_cast<double>(fuzz_stats_num_inputs) /
                fuzz_stats_total_len);

}

FUZZ_TEST(GrpcMessageAssemblerTest, AssemblerFuzzer);

}
}
}
