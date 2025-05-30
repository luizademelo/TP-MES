// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CORE_END2END_END2END_TESTS_H
#define GRPC_TEST_CORE_END2END_END2END_TESTS_H

#include <grpc/byte_buffer.h>
#include <grpc/compression.h>
#include <grpc/credentials.h>
#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/impl/propagation_bits.h>
#include <grpc/status.h>
#include <grpc/support/alloc.h>
#include <grpc/support/time.h>
#include <stdint.h>
#include <stdio.h>

#include <algorithm>
#include <functional>
#include <initializer_list>
#include <map>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"
#include "absl/memory/memory.h"
#include "absl/meta/type_traits.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "gtest/gtest.h"
#include "src/core/config/config_vars.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/event_engine/shim.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/surface/call_test_only.h"
#include "src/core/lib/surface/channel.h"
#include "src/core/util/bitset.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/time.h"
#include "src/core/util/wait_for_single_owner.h"
#include "test/core/call/batch_builder.h"
#include "test/core/end2end/cq_verifier.h"
#include "test/core/end2end/end2end_test_fuzzer.pb.h"
#include "test/core/event_engine/event_engine_test_utils.h"
#include "test/core/test_util/fuzz_config_vars.h"
#include "test/core/test_util/postmortem.h"
#include "test/core/test_util/test_config.h"

#ifdef GRPC_END2END_TEST_INCLUDE_FUZZER
#include "fuzztest/fuzztest.h"
#include "test/core/test_util/fuzz_config_vars_helpers.h"
#endif

#define CA_CERT_PATH "src/core/tsi/test_creds/ca.pem"

#define FEATURE_MASK_DOES_NOT_SUPPORT_RETRY (1 << 0)
#define FEATURE_MASK_SUPPORTS_HOSTNAME_VERIFICATION (1 << 1)

#define FEATURE_MASK_SUPPORTS_PER_CALL_CREDENTIALS (1 << 2)

#define FEATURE_MASK_SUPPORTS_PER_CALL_CREDENTIALS_LEVEL_INSECURE (1 << 3)
#define FEATURE_MASK_SUPPORTS_REQUEST_PROXYING (1 << 4)
#define FEATURE_MASK_SUPPORTS_CLIENT_CHANNEL (1 << 5)
#define FEATURE_MASK_IS_HTTP2 (1 << 6)
#define FEATURE_MASK_ENABLES_TRACES (1 << 7)
#define FEATURE_MASK_1BYTE_AT_A_TIME (1 << 8)
#define FEATURE_MASK_DOES_NOT_SUPPORT_WRITE_BUFFERING (1 << 9)
#define FEATURE_MASK_DOES_NOT_SUPPORT_CLIENT_HANDSHAKE_COMPLETE_FIRST (1 << 10)
#define FEATURE_MASK_IS_MINSTACK (1 << 11)
#define FEATURE_MASK_IS_SECURE (1 << 12)
#define FEATURE_MASK_DO_NOT_FUZZ (1 << 13)
#define FEATURE_MASK_DO_NOT_GTEST (1 << 14)

#define FEATURE_MASK_EXCLUDE_FROM_EXPERIMENT_RUNS (1 << 15)
#define FEATURE_MASK_IS_CALL_V3 (1 << 16)
#define FEATURE_MASK_IS_LOCAL_TCP_CREDS (1 << 17)

#define FAIL_AUTH_CHECK_SERVER_ARG_NAME "fail_auth_check"

namespace grpc_core {

class CoreTestFixture {
 public:
  virtual ~CoreTestFixture() = default;

  virtual grpc_server* MakeServer(
      const ChannelArgs& args, grpc_completion_queue* cq,
      absl::AnyInvocable<void(grpc_server*)>& pre_server_start) = 0;
  virtual grpc_channel* MakeClient(const ChannelArgs& args,
                                   grpc_completion_queue* cq) = 0;
};

Slice RandomSlice(size_t length);
Slice RandomBinarySlice(size_t length);

struct CoreTestConfiguration {

  const char* name;

  uint32_t feature_mask;

  const char* overridden_call_host;

  std::function<std::unique_ptr<CoreTestFixture>(
      const ChannelArgs& client_args, const ChannelArgs& server_args)>
      create_fixture;
};

const CoreTestConfiguration* CoreTestConfigurationNamed(absl::string_view name);

template <typename Sink>
void AbslStringify(Sink& sink, const CoreTestConfiguration* config) {
  sink.Append(
      absl::StrCat("CoreTestConfigurationNamed(\"", config->name, "\")"));
}

inline std::ostream& operator<<(std::ostream& out,
                                const CoreTestConfiguration* config) {
  return out << "CoreTestConfigurationNamed(\"" << config->name << "\")";
}

class CoreEnd2endTest {
 public:
  CoreEnd2endTest(const CoreTestConfiguration* config,
                  const core_end2end_test_fuzzer::Msg* fuzzing_args,
                  absl::string_view suite_name);
  ~CoreEnd2endTest();

  void SetCqVerifierStepFn(
      absl::AnyInvocable<
          void(grpc_event_engine::experimental::EventEngine::Duration) const>
          step_fn) {
    step_fn_ = std::move(step_fn);
  }
  void SetQuiesceEventEngine(
      absl::AnyInvocable<
          void(std::shared_ptr<grpc_event_engine::experimental::EventEngine>&&)>
          quiesce_event_engine) {
    quiesce_event_engine_ = std::move(quiesce_event_engine);
  }

  class Call;
  struct RegisteredCall {
    void* p;
  };

  class TestNotification {
   public:
    explicit TestNotification(CoreEnd2endTest* test) : test_(test) {}

    bool WaitForNotificationWithTimeout(absl::Duration wait_time) {
      if (test_->fuzzing_) {
        Timestamp end = Timestamp::Now() + Duration::NanosecondsRoundUp(
                                               ToInt64Nanoseconds(wait_time));
        while (true) {
          if (base_.HasBeenNotified()) return true;
          auto now = Timestamp::Now();
          if (now >= end) return false;
          test_->step_fn_(now - end);
        }
      } else {
        return base_.WaitForNotificationWithTimeout(wait_time);
      }
    }

    void Notify() { base_.Notify(); }

   private:
    Notification base_;
    CoreEnd2endTest* const test_;
  };

  class ClientCallBuilder {
   public:
    ClientCallBuilder(CoreEnd2endTest& test, std::string method)
        : test_(test),
          call_selector_(UnregisteredCall{std::move(method), std::nullopt}) {}
    ClientCallBuilder(CoreEnd2endTest& test, RegisteredCall registered_call)
        : test_(test), call_selector_(registered_call.p) {}

    ClientCallBuilder& Host(std::string host) {
      std::get<UnregisteredCall>(call_selector_).host = std::move(host);
      return *this;
    }

    ClientCallBuilder& Timeout(Duration timeout) {
      if (timeout == Duration::Infinity()) {
        deadline_ = gpr_inf_future(GPR_CLOCK_REALTIME);
        return *this;
      }
      deadline_ = grpc_timeout_milliseconds_to_deadline(timeout.millis());
      return *this;
    }

    Call Create();

   private:
    CoreEnd2endTest& test_;
    struct UnregisteredCall {
      std::string method;
      std::optional<std::string> host;
    };
    std::variant<void*, UnregisteredCall> call_selector_;
    grpc_call* parent_call_ = nullptr;
    uint32_t propagation_mask_ = GRPC_PROPAGATE_DEFAULTS;
    gpr_timespec deadline_ = gpr_inf_future(GPR_CLOCK_REALTIME);
  };

  class Call {
   public:
    Call(grpc_call* call, CoreEnd2endTest* test) : call_(call), test_(test) {}
    Call(const Call&) = delete;
    Call& operator=(const Call&) = delete;
    Call(Call&& other) noexcept
        : call_(std::exchange(other.call_, nullptr)),
          test_(std::exchange(other.test_, nullptr)) {}
    ~Call() {
      if (call_ != nullptr) grpc_call_unref(call_);
    }

    BatchBuilder NewBatch(int tag) {
      return BatchBuilder(call_, &test_->cq_verifier(), tag);
    }

    void Cancel() { grpc_call_cancel(call_, nullptr); }
    void CancelWithStatus(grpc_status_code status, const char* message) {
      grpc_call_cancel_with_status(call_, status, message, nullptr);
    }

    std::optional<std::string> GetPeer() {
      char* peer = grpc_call_get_peer(call_);
      if (peer == nullptr) return std::nullopt;
      std::string result(peer);
      gpr_free(peer);
      return result;
    }

    void SetCredentials(grpc_call_credentials* creds) {
      EXPECT_EQ(grpc_call_set_credentials(call_, creds), GRPC_CALL_OK);
      grpc_call_credentials_release(creds);
    }

    std::unique_ptr<grpc_auth_context, void (*)(grpc_auth_context*)>
    GetAuthContext() {
      return std::unique_ptr<grpc_auth_context, void (*)(grpc_auth_context*)>(
          grpc_call_auth_context(call_), grpc_auth_context_release);
    }

    grpc_call** call_ptr() { return &call_; }
    grpc_call* c_call() const { return call_; }

   private:
    grpc_call* call_ = nullptr;
    CoreEnd2endTest* test_;
  };

  class IncomingCall {
   public:
    IncomingCall(CoreEnd2endTest& test, int tag);
    IncomingCall(CoreEnd2endTest& test, void* method, IncomingMessage* message,
                 int tag);
    IncomingCall(const IncomingCall&) = delete;
    IncomingCall& operator=(const IncomingCall&) = delete;
    IncomingCall(IncomingCall&&) noexcept = default;

    BatchBuilder NewBatch(int tag) { return impl_->call.NewBatch(tag); }
    void Cancel() { impl_->call.Cancel(); }

    std::string method() const {
      return std::string(StringViewFromSlice(impl_->call_details.method));
    }

    std::string host() const {
      return std::string(StringViewFromSlice(impl_->call_details.host));
    }

    std::optional<std::string> GetInitialMetadata(absl::string_view key) const;

    std::optional<std::string> GetPeer() { return impl_->call.GetPeer(); }

    std::unique_ptr<grpc_auth_context, void (*)(grpc_auth_context*)>
    GetAuthContext() {
      return impl_->call.GetAuthContext();
    }

    grpc_call* c_call() { return impl_->call.c_call(); }

    BitSet<GRPC_COMPRESS_ALGORITHMS_COUNT> GetEncodingsAcceptedByPeer() {
      return BitSet<GRPC_COMPRESS_ALGORITHMS_COUNT>::FromInt(
          grpc_call_test_only_get_encodings_accepted_by_peer(c_call()));
    }

   private:
    struct Impl {
      explicit Impl(CoreEnd2endTest* test) : call(nullptr, test) {
        grpc_call_details_init(&call_details);
        grpc_metadata_array_init(&request_metadata);
      }
      ~Impl() {
        grpc_call_details_destroy(&call_details);
        grpc_metadata_array_destroy(&request_metadata);
      }
      Call call;
      grpc_call_details call_details;
      grpc_metadata_array request_metadata;
    };
    std::unique_ptr<Impl> impl_;
  };

  class ServerRegisteredMethod {
   public:
    ServerRegisteredMethod(
        CoreEnd2endTest* test, absl::string_view name,
        grpc_server_register_method_payload_handling payload_handling);

    void* handle() { return *handle_; }

   private:
    std::shared_ptr<void*> handle_ = std::make_shared<void*>(nullptr);
  };

  ServerRegisteredMethod RegisterServerMethod(
      absl::string_view name,
      grpc_server_register_method_payload_handling payload_handling) {
    return ServerRegisteredMethod(this, name, payload_handling);
  }

  ClientCallBuilder NewClientCall(std::string method) {
    return ClientCallBuilder(*this, std::move(method));
  }
  ClientCallBuilder NewClientCall(RegisteredCall registered_method) {
    return ClientCallBuilder(*this, registered_method);
  }

  IncomingCall RequestCall(int tag) { return IncomingCall(*this, tag); }

  IncomingCall RequestRegisteredCall(ServerRegisteredMethod method, int tag) {
    return IncomingCall(*this, method.handle(), nullptr, tag);
  }
  IncomingCall RequestRegisteredCall(ServerRegisteredMethod method,
                                     IncomingMessage* message, int tag) {
    return IncomingCall(*this, method.handle(), message, tag);
  }

  using ExpectedResult = CqVerifier::ExpectedResult;
  using Maybe = CqVerifier::Maybe;
  using PerformAction = CqVerifier::PerformAction;
  using MaybePerformAction = CqVerifier::MaybePerformAction;
  using AnyStatus = CqVerifier::AnyStatus;

  void Expect(int tag, ExpectedResult result, SourceLocation whence = {}) {
    expectations_++;
    cq_verifier().Expect(CqVerifier::tag(tag), std::move(result), whence);
  }

  void Step(std::optional<Duration> timeout = std::nullopt,
            SourceLocation whence = {}) {
    if (expectations_ == 0) {
      cq_verifier().VerifyEmpty(timeout.value_or(Duration::Seconds(1)), whence);
      return;
    }
    expectations_ = 0;
    cq_verifier().Verify(timeout.value_or(fuzzing_ ? Duration::Minutes(10)
                                                   : Duration::Seconds(10)),
                         whence);
  }

  void InitClient(const ChannelArgs& args) {
    initialized_ = true;
    if (client_ != nullptr) ShutdownAndDestroyClient();
    auto& f = fixture();
    client_ = f.MakeClient(args, cq_);
    CHECK_NE(client_, nullptr);
  }

  void InitServer(const ChannelArgs& args) {
    initialized_ = true;
    if (server_ != nullptr) ShutdownAndDestroyServer();
    auto& f = fixture();
    server_ = f.MakeServer(args, cq_, pre_server_start_);
    CHECK_NE(server_, nullptr);
  }

  void ShutdownAndDestroyClient() {
    if (client_ == nullptr) return;
    grpc_channel_destroy(client_);
    client_ = nullptr;
  }

  void ShutdownServerAndNotify(int tag) {
    grpc_server_shutdown_and_notify(server_, cq_, CqVerifier::tag(tag));
  }

  void DestroyServer() {
    if (server_ == nullptr) return;
    grpc_server_destroy(server_);
    server_ = nullptr;
  }

  void ShutdownAndDestroyServer() {
    if (server_ == nullptr) return;
    ShutdownServerAndNotify(-1);
    Expect(-1, AnyStatus{});
    Step();
    DestroyServer();
  }

  void CancelAllCallsOnServer() { grpc_server_cancel_all_calls(server_); }

  void PingServerFromClient(int tag) {
    grpc_channel_ping(client_, cq_, CqVerifier::tag(tag), nullptr);
  }

  RegisteredCall RegisterCallOnClient(const char* method, const char* host) {
    ForceInitialized();
    return RegisteredCall{
        grpc_channel_register_call(client_, method, host, nullptr)};
  }

  grpc_connectivity_state CheckConnectivityState(bool try_to_connect) {
    return grpc_channel_check_connectivity_state(client_, try_to_connect);
  }

  void WatchConnectivityState(grpc_connectivity_state last_observed_state,
                              Duration deadline, int tag) {
    grpc_channel_watch_connectivity_state(
        client_, last_observed_state,
        grpc_timeout_milliseconds_to_deadline(deadline.millis()), cq_,
        CqVerifier::tag(tag));
  }

  grpc_channel* client() {
    ForceInitialized();
    return client_;
  }

  grpc_server* server() {
    ForceInitialized();
    return server_;
  }

  grpc_completion_queue* cq() {
    ForceInitialized();
    return cq_;
  }

  Timestamp TimestampAfterDuration(Duration duration) {
    return Timestamp::FromTimespecRoundUp(
        grpc_timeout_milliseconds_to_deadline(duration.millis()));
  }

  void SetPostGrpcInitFunc(absl::AnyInvocable<void()> fn) {
    CHECK(fixture_ == nullptr);
    post_grpc_init_func_ = std::move(fn);
  }

  const CoreTestConfiguration* test_config() const { return test_config_; }

  bool fuzzing() const { return fuzzing_; }

  CoreTestFixture& fixture() {
    if (fixture_ == nullptr) {
      grpc_init();
      post_grpc_init_func_();
      cq_ = grpc_completion_queue_create_for_next(nullptr);
      fixture_ = test_config()->create_fixture(ChannelArgs(), ChannelArgs());
    }
    return *fixture_;
  }

 private:
  void ForceInitialized();

  CqVerifier& cq_verifier() {
    if (cq_verifier_ == nullptr) {
      fixture();
      cq_verifier_ = absl::make_unique<CqVerifier>(
          cq_,
          fuzzing_ ? CqVerifier::FailUsingGprCrashWithStdio
                   : CqVerifier::FailUsingGprCrash,
          step_fn_ == nullptr
              ? nullptr
              : absl::AnyInvocable<void(
                    grpc_event_engine::experimental::EventEngine::Duration)
                                       const>(
                    [this](
                        grpc_event_engine::experimental::EventEngine::Duration
                            d) { step_fn_(d); }));
    }
    return *cq_verifier_;
  }

  PostMortem post_mortem_;
  const CoreTestConfiguration* const test_config_;
  const bool fuzzing_;
  std::unique_ptr<CoreTestFixture> fixture_;
  grpc_completion_queue* cq_ = nullptr;
  grpc_server* server_ = nullptr;
  grpc_channel* client_ = nullptr;
  std::unique_ptr<CqVerifier> cq_verifier_;
  absl::AnyInvocable<void(grpc_server*)> pre_server_start_ = [](grpc_server*) {
  };
  int expectations_ = 0;
  bool initialized_ = false;
  absl::AnyInvocable<void()> post_grpc_init_func_ = []() {};
  absl::AnyInvocable<void(
      grpc_event_engine::experimental::EventEngine::Duration) const>
      step_fn_ = nullptr;
  absl::AnyInvocable<void(
      std::shared_ptr<grpc_event_engine::experimental::EventEngine>)>
      quiesce_event_engine_ =
          WaitForSingleOwner<grpc_event_engine::experimental::EventEngine>;
};

#define DECLARE_SUITE(name)                                                    \
  class name : public ::testing::TestWithParam<const CoreTestConfiguration*> { \
   public:                                                                     \
    static std::vector<const CoreTestConfiguration*> AllSuiteConfigs(          \
        bool fuzzing);                                                         \
  };

DECLARE_SUITE(CoreEnd2endTests);

DECLARE_SUITE(SecureEnd2endTests);

DECLARE_SUITE(CoreLargeSendTests);

DECLARE_SUITE(CoreClientChannelTests);

DECLARE_SUITE(CoreDeadlineTests);

DECLARE_SUITE(CoreDeadlineSingleHopTests);

DECLARE_SUITE(Http2SingleHopTests);

DECLARE_SUITE(Http2FullstackSingleHopTests);

DECLARE_SUITE(RetryTests);

DECLARE_SUITE(WriteBufferingTests);

DECLARE_SUITE(Http2Tests);

DECLARE_SUITE(RetryHttp2Tests);

DECLARE_SUITE(ResourceQuotaTests);

DECLARE_SUITE(PerCallCredsTests);

DECLARE_SUITE(PerCallCredsOnInsecureTests);

DECLARE_SUITE(NoLoggingTests);

DECLARE_SUITE(ProxyAuthTests);

#undef DECLARE_SUITE

core_end2end_test_fuzzer::Msg ParseTestProto(std::string text);

std::vector<CoreTestConfiguration> End2endTestConfigs();

inline auto MaybeAddNullConfig(
    std::vector<const CoreTestConfiguration*> configs) {
  if (configs.empty()) {
    configs.push_back(nullptr);
  }
  return configs;
}

}

#define SKIP_IF_MINSTACK()                                    \
  if (test_config()->feature_mask & FEATURE_MASK_IS_MINSTACK) \
  GTEST_SKIP() << "Skipping test for minstack"

#define SKIP_IF_FUZZING() \
  if (fuzzing()) GTEST_SKIP() << "Skipping test for fuzzing"

#define SKIP_IF_V3()                                           \
  if (test_config()->feature_mask & FEATURE_MASK_IS_CALL_V3) { \
    GTEST_SKIP() << "Disabled for initial v3 testing";         \
  }

#define SKIP_IF_LOCAL_TCP_CREDS()                                      \
  if (test_config()->feature_mask & FEATURE_MASK_IS_LOCAL_TCP_CREDS) { \
    GTEST_SKIP() << "Disabled for Local TCP Connection";               \
  }

#ifndef GRPC_END2END_TEST_INCLUDE_FUZZER
#define CORE_END2END_FUZZER(suite, name)
#else
#define CORE_END2END_FUZZER(suite, name)                                  \
  FUZZ_TEST(Fuzzers, suite##_##name)                                      \
      .WithDomains(::fuzztest::ElementOf(grpc_core::MaybeAddNullConfig(   \
                       suite::AllSuiteConfigs(true))),                    \
                   ::fuzztest::Arbitrary<core_end2end_test_fuzzer::Msg>() \
                       .WithProtobufField("config_vars", AnyConfigVars()));
#endif

#if defined(FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION) || \
    defined(GRPC_END2END_TEST_NO_GTEST)
#define CORE_END2END_TEST_P(suite, name)
#else
#define CORE_END2END_TEST_P(suite, name)                                     \
  TEST_P(suite, name) {                                                      \
    if ((GetParam()->feature_mask & FEATURE_MASK_IS_CALL_V3) &&              \
        (grpc_core::ConfigVars::Get().PollStrategy() == "poll")) {           \
      GTEST_SKIP() << "call-v3 not supported with poll poller";              \
    }                                                                        \
    CoreEnd2endTest_##suite##_##name(GetParam(), nullptr, #suite).RunTest(); \
  }
#endif

#ifdef FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION
#define CORE_END2END_INSTANTIATE_TEST_SUITE_P(suite)
#else
#define CORE_END2END_INSTANTIATE_TEST_SUITE_P(suite)                           \
  INSTANTIATE_TEST_SUITE_P(, suite,                                            \
                           ::testing::ValuesIn(suite::AllSuiteConfigs(false)), \
                           [](auto info) { return info.param->name; });        \
  GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(suite);
#endif

#define CORE_END2END_TEST(suite, name)                                         \
  class CoreEnd2endTest_##suite##_##name final                                 \
      : public grpc_core::CoreEnd2endTest {                                    \
   public:                                                                     \
    using grpc_core::CoreEnd2endTest::CoreEnd2endTest;                         \
    void RunTest();                                                            \
  };                                                                           \
  void suite##_##name(const grpc_core::CoreTestConfiguration* config,          \
                      core_end2end_test_fuzzer::Msg msg) {                     \
    if (config == nullptr) return;                                             \
    if (absl::StartsWith(#name, "DISABLED_")) GTEST_SKIP() << "disabled test"; \
    if (!IsEventEngineListenerEnabled() || !IsEventEngineClientEnabled() ||    \
        !IsEventEngineDnsEnabled()) {                                          \
      GTEST_SKIP() << "fuzzers need event engine";                             \
    }                                                                          \
    if (IsEventEngineDnsNonClientChannelEnabled() &&                           \
        !grpc_event_engine::experimental::                                     \
            EventEngineExperimentDisabledForPython()) {                        \
      GTEST_SKIP() << "event_engine_dns_non_client_channel experiment breaks " \
                      "fuzzing currently";                                     \
    }                                                                          \
    CoreEnd2endTest_##suite##_##name(config, &msg, #suite).RunTest();          \
    grpc_event_engine::experimental::ShutdownDefaultEventEngine();             \
  }                                                                            \
  CORE_END2END_TEST_P(suite, name)                                             \
  CORE_END2END_FUZZER(suite, name)                                             \
  void CoreEnd2endTest_##suite##_##name::RunTest()

#define CORE_END2END_TEST_INCOMPATIBLE_WITH_FUZZING(suite, name) \
  class CoreEnd2endTest_##suite##_##name final                   \
      : public grpc_core::CoreEnd2endTest {                      \
   public:                                                       \
    using grpc_core::CoreEnd2endTest::CoreEnd2endTest;           \
    void RunTest();                                              \
  };                                                             \
  CORE_END2END_TEST_P(suite, name)                               \
  void CoreEnd2endTest_##suite##_##name::RunTest()

#define CORE_END2END_TEST_SUITE(suite, configs)                                \
  CORE_END2END_INSTANTIATE_TEST_SUITE_P(suite)                                 \
  std::vector<const grpc_core::CoreTestConfiguration*> suite::AllSuiteConfigs( \
      bool fuzzing) {                                                          \
    return configs;                                                            \
  }

#endif
