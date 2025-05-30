
// Copyright 2015 gRPC authors.

#include "test/cpp/interop/stress_interop_client.h"

#include <grpcpp/create_channel.h>

#include <memory>
#include <string>
#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "src/core/util/crash.h"
#include "test/cpp/interop/interop_client.h"
#include "test/cpp/util/metrics_server.h"

namespace grpc {
namespace testing {

using std::pair;
using std::vector;

WeightedRandomTestSelector::WeightedRandomTestSelector(
    const vector<pair<TestCaseType, int>>& tests)
    : tests_(tests) {
  total_weight_ = 0;
  for (auto it = tests.begin(); it != tests.end(); it++) {
    total_weight_ += it->second;
  }
}

TestCaseType WeightedRandomTestSelector::GetNextTest() const {
  int random = 0;
  TestCaseType selected_test = UNKNOWN_TEST;

  random = rand() % total_weight_;

  int weight_sofar = 0;
  for (auto it = tests_.begin(); it != tests_.end(); it++) {
    weight_sofar += it->second;
    if (random < weight_sofar) {
      selected_test = it->first;
      break;
    }
  }

  CHECK(selected_test != UNKNOWN_TEST);
  return selected_test;
}

StressTestInteropClient::StressTestInteropClient(
    int test_id, const std::string& server_address,
    ChannelCreationFunc channel_creation_func,
    const WeightedRandomTestSelector& test_selector, long test_duration_secs,
    long sleep_duration_ms, bool do_not_abort_on_transient_failures)
    : test_id_(test_id),
      server_address_(server_address),
      channel_creation_func_(std::move(channel_creation_func)),
      interop_client_(new InteropClient(channel_creation_func_, false,
                                        do_not_abort_on_transient_failures)),
      test_selector_(test_selector),
      test_duration_secs_(test_duration_secs),
      sleep_duration_ms_(sleep_duration_ms) {}

void StressTestInteropClient::MainLoop(
    const std::shared_ptr<QpsGauge>& qps_gauge) {
  LOG(INFO) << "Running test " << test_id_
            << ". ServerAddr: " << server_address_;

  gpr_timespec test_end_time;
  if (test_duration_secs_ < 0) {
    test_end_time = gpr_inf_future(GPR_CLOCK_REALTIME);
  } else {
    test_end_time =
        gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                     gpr_time_from_seconds(test_duration_secs_, GPR_TIMESPAN));
  }

  qps_gauge->Reset();

  while (gpr_time_cmp(gpr_now(GPR_CLOCK_REALTIME), test_end_time) < 0) {

    TestCaseType test_case = test_selector_.GetNextTest();
    VLOG(2) << test_id_ << " - Executing the test case " << test_case;
    RunTest(test_case);

    qps_gauge->Incr();

    if (sleep_duration_ms_ > 0) {
      gpr_timespec sleep_time =
          gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                       gpr_time_from_millis(sleep_duration_ms_, GPR_TIMESPAN));
      gpr_sleep_until(sleep_time);
    }
  }
}

bool StressTestInteropClient::RunTest(TestCaseType test_case) {
  bool is_success = false;
  switch (test_case) {
    case EMPTY_UNARY: {
      is_success = interop_client_->DoEmpty();
      break;
    }
    case LARGE_UNARY: {
      is_success = interop_client_->DoLargeUnary();
      break;
    }
    case CLIENT_COMPRESSED_UNARY: {
      is_success = interop_client_->DoClientCompressedUnary();
      break;
    }
    case CLIENT_COMPRESSED_STREAMING: {
      is_success = interop_client_->DoClientCompressedStreaming();
      break;
    }
    case CLIENT_STREAMING: {
      is_success = interop_client_->DoRequestStreaming();
      break;
    }
    case SERVER_STREAMING: {
      is_success = interop_client_->DoResponseStreaming();
      break;
    }
    case SERVER_COMPRESSED_UNARY: {
      is_success = interop_client_->DoServerCompressedUnary();
      break;
    }
    case SERVER_COMPRESSED_STREAMING: {
      is_success = interop_client_->DoServerCompressedStreaming();
      break;
    }
    case SLOW_CONSUMER: {
      is_success = interop_client_->DoResponseStreamingWithSlowConsumer();
      break;
    }
    case HALF_DUPLEX: {
      is_success = interop_client_->DoHalfDuplex();
      break;
    }
    case PING_PONG: {
      is_success = interop_client_->DoPingPong();
      break;
    }
    case CANCEL_AFTER_BEGIN: {
      is_success = interop_client_->DoCancelAfterBegin();
      break;
    }
    case CANCEL_AFTER_FIRST_RESPONSE: {
      is_success = interop_client_->DoCancelAfterFirstResponse();
      break;
    }
    case TIMEOUT_ON_SLEEPING_SERVER: {
      is_success = interop_client_->DoTimeoutOnSleepingServer();
      break;
    }
    case EMPTY_STREAM: {
      is_success = interop_client_->DoEmptyStream();
      break;
    }
    case STATUS_CODE_AND_MESSAGE: {
      is_success = interop_client_->DoStatusWithMessage();
      break;
    }
    case CUSTOM_METADATA: {
      is_success = interop_client_->DoCustomMetadata();
      break;
    }
    default: {
      grpc_core::Crash(absl::StrFormat("Invalid test case (%d)", test_case));
      break;
    }
  }

  return is_success;
}

}
}
