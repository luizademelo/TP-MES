
// Copyright 2016 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/status.h>

#include <atomic>
#include <map>
#include <optional>
#include <regex>
#include <string>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/globals.h"
#include "absl/log/log.h"
#include "absl/log/log_entry.h"
#include "absl/log/log_sink.h"
#include "absl/log/log_sink_registry.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "gtest/gtest.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {

class VerifyLogNoiseLogSink : public absl::LogSink {
 public:
  explicit VerifyLogNoiseLogSink(const absl::LogSeverityAtLeast severity,
                                 const int verbosity)
      : log_noise_absent_(true) {
    saved_absl_severity_ = absl::MinLogLevel();
    absl::SetMinLogLevel(severity);

    saved_absl_verbosity_ = absl::SetGlobalVLogLevel(verbosity);
    grpc_tracer_set_enabled("all", false);
    absl::AddLogSink(this);
  }

  ~VerifyLogNoiseLogSink() override {
    CHECK(log_noise_absent_)
        << "Unwanted logs present. This will cause log noise. Either user a "
           "tracer (example GRPC_TRACE_LOG or GRPC_TRACE_VLOG) or convert the "
           "statement to VLOG(2).";

    absl::RemoveLogSink(this);
    saved_trace_flags_.Restore();
    absl::SetGlobalVLogLevel(saved_absl_verbosity_);
    absl::SetMinLogLevel(saved_absl_severity_);
  }

  void Send(const absl::LogEntry& entry) override { CheckForNoisyLogs(entry); }

  VerifyLogNoiseLogSink(const VerifyLogNoiseLogSink& other) = delete;
  VerifyLogNoiseLogSink& operator=(const VerifyLogNoiseLogSink& other) = delete;

  void AllowNonErrorLogs(bool allow) {
    allow_non_error_logs_.store(allow, std::memory_order_relaxed);
  }

 private:
  bool IsVlogWithVerbosityMoreThan1(const absl::LogEntry& entry) const {
    return entry.log_severity() == absl::LogSeverity::kInfo &&
           entry.verbosity() >= 1;
  }

  void CheckForNoisyLogs(const absl::LogEntry& entry) {

    static const auto* const allowed_logs_by_module = new std::map<
        absl::string_view, std::regex>(
        {{"cq_verifier.cc", std::regex("^Verify .* for [0-9]+ms")},
         {"chaotic_good_server.cc",
          std::regex("Failed to bind some addresses for.*")},
         {"log.cc",
          std::regex(
              "Prefer WARNING or ERROR. However if you see this "
              "message in a debug environment or test environment "
              "it is safe to ignore this message.|Unknown log verbosity:.*")},
         {"chttp2_server.cc",
          std::regex(
              "Only [0-9]+ addresses added out of total [0-9]+ resolved")},
         {"trace.cc", std::regex("Unknown tracer:.*")},
         {"config.cc", std::regex("gRPC experiments.*")},

         {"http_proxy_fixture.cc", std::regex(".*")},
         {"http_connect_handshaker.cc",
          std::regex("HTTP proxy handshake with .* failed:.*")}});

    if (allow_non_error_logs_.load(std::memory_order_relaxed) &&
        entry.log_severity() != absl::LogSeverity::kError) {
      return;
    }

    if (IsVlogWithVerbosityMoreThan1(entry)) {
      return;
    }

    absl::string_view filename = entry.source_filename();
    auto slash = filename.rfind('/');
    if (slash != absl::string_view::npos) {
      filename = filename.substr(slash + 1);
    }
    slash = filename.rfind('\\');
    if (slash != absl::string_view::npos) {
      filename = filename.substr(slash + 1);
    }
    auto it = allowed_logs_by_module->find(filename);
    if (it != allowed_logs_by_module->end() &&
        std::regex_search(std::string(entry.text_message()), it->second)) {
      return;
    }

    // If we reach here means we have log noise. log_noise_absent_ will make the
    // test fail.
    log_noise_absent_ = false;
    LOG(ERROR) << "🛑 Unwanted log at location : " << entry.source_filename()
               << ":" << entry.source_line() << " " << entry.text_message();
  }

  absl::LogSeverityAtLeast saved_absl_severity_;
  int saved_absl_verbosity_;
  SavedTraceFlags saved_trace_flags_;
  bool log_noise_absent_;
  std::atomic<bool> allow_non_error_logs_{false};
};

void SimpleRequest(CoreEnd2endTest& test) {
  auto c = test.NewClientCall("/foo").Timeout(Duration::Seconds(5)).Create();
  EXPECT_NE(c.GetPeer(), std::nullopt);
  IncomingMetadata server_initial_metadata;
  IncomingStatusOnClient server_status;
  c.NewBatch(1)
      .SendInitialMetadata({})
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_metadata)
      .RecvStatusOnClient(server_status);
  auto s = test.RequestCall(101);
  test.Expect(101, true);
  test.Step();
  EXPECT_NE(c.GetPeer(), std::nullopt);
  EXPECT_NE(s.GetPeer(), std::nullopt);
  IncomingCloseOnServer client_close;
  s.NewBatch(102)
      .SendInitialMetadata({})
      .SendStatusFromServer(GRPC_STATUS_UNIMPLEMENTED, "xyz", {})
      .RecvCloseOnServer(client_close);
  test.Expect(102, true);
  test.Expect(1, true);
  test.Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_UNIMPLEMENTED);
  EXPECT_EQ(server_status.message(), "xyz");
  EXPECT_EQ(s.method(), "/foo");
  EXPECT_FALSE(client_close.was_cancelled());
}

CORE_END2END_TEST(NoLoggingTests, NoLoggingTest) {
// This test makes sure that we don't get log noise when making an rpc

#ifdef GPR_WINDOWS
  if (IsEventEngineListenerEnabled()) {
    GTEST_SKIP() << "not for windows + event engine listener";
  }
#endif
  VerifyLogNoiseLogSink nolog_verifier(absl::LogSeverityAtLeast::kInfo, 2);

  nolog_verifier.AllowNonErrorLogs(true);
  SimpleRequest(*this);
  nolog_verifier.AllowNonErrorLogs(false);
  for (int i = 0; i < 10; i++) {
    SimpleRequest(*this);
  }
}

TEST(Fuzzers, NoLoggingTestRegression1) {
  NoLoggingTests_NoLoggingTest(
      CoreTestConfigurationNamed("Chttp2FullstackCompression"),
      ParseTestProto(R"pb(config_vars { verbosity: "\000" trace: "" })pb"));
}

TEST(Fuzzers, NoLoggingTestRegression2) {
  NoLoggingTests_NoLoggingTest(
      CoreTestConfigurationNamed("Chttp2Fullstack"),
      ParseTestProto(R"pb(config_vars { trace: "\177 " })pb"));
}

}
