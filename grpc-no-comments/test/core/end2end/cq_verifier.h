
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CORE_END2END_CQ_VERIFIER_H
#define GRPC_TEST_CORE_END2END_CQ_VERIFIER_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <grpc/slice.h>
#include <grpc/support/time.h>
#include <stdint.h>

#include <functional>
#include <string>
#include <variant>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/functional/any_invocable.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/time.h"

namespace grpc_core {

class CqVerifier {
 public:

  struct Maybe {
    bool* seen = nullptr;
  };

  struct AnyStatus {
    bool* result = nullptr;
  };

  struct PerformAction {
    std::function<void(bool success)> action;
  };

  struct MaybePerformAction {
    std::function<void(bool success)> action;
  };

  using ExpectedResult =
      std::variant<bool, Maybe, AnyStatus, PerformAction, MaybePerformAction>;

  struct Failure {
    SourceLocation location;
    std::string message;
    std::vector<std::string> expected;
    std::vector<std::string> message_details;
  };

  class SuccessfulStateString {
   public:
    virtual std::string GetSuccessfulStateString() = 0;

   protected:
    ~SuccessfulStateString() = default;
  };

  static void FailUsingGprCrash(const Failure& failure);
  static void FailUsingGprCrashWithStdio(const Failure& failure);
  static void FailUsingGtestFail(const Failure& failure);

  explicit CqVerifier(
      grpc_completion_queue* cq,
      absl::AnyInvocable<void(Failure) const> fail = FailUsingGprCrash,
      absl::AnyInvocable<
          void(grpc_event_engine::experimental::EventEngine::Duration) const>
          step_fn = nullptr);
  ~CqVerifier();

  CqVerifier(const CqVerifier&) = delete;
  CqVerifier& operator=(const CqVerifier&) = delete;

  void Verify(Duration timeout = Duration::Seconds(10),
              SourceLocation location = SourceLocation());

  void VerifyEmpty(Duration timeout = Duration::Seconds(1),
                   SourceLocation location = SourceLocation());

  void ClearSuccessfulStateStrings(void* tag);
  void AddSuccessfulStateString(void* tag,
                                SuccessfulStateString* successful_state_string);

  void Expect(void* tag, ExpectedResult result,
              SourceLocation location = SourceLocation());

  std::string ToString() const;
  std::vector<std::string> ToStrings() const;
  std::string ToShortString() const;
  std::vector<std::string> ToShortStrings() const;

  void SetLogVerifications(bool log_verifications) {
    log_verifications_ = log_verifications;
  }

  static void* tag(intptr_t t) { return reinterpret_cast<void*>(t); }

 private:
  struct Expectation {
    SourceLocation location;
    void* tag;
    ExpectedResult result;

    std::string ToString() const;
    std::string ToShortString() const;
  };

  void FailNoEventReceived(const SourceLocation& location) const;
  void FailUnexpectedEvent(grpc_event* ev,
                           const SourceLocation& location) const;
  bool AllMaybes() const;
  grpc_event Step(gpr_timespec deadline);

  grpc_completion_queue* const cq_;
  std::vector<Expectation> expectations_;
  absl::AnyInvocable<void(Failure) const> fail_;
  absl::AnyInvocable<void(
      grpc_event_engine::experimental::EventEngine::Duration) const>
      step_fn_;
  absl::flat_hash_map<void*, std::vector<SuccessfulStateString*>>
      successful_state_strings_;
  bool log_verifications_ = true;
  bool added_expectations_ = false;
};

}

int byte_buffer_eq_slice(grpc_byte_buffer* bb, grpc_slice b);
int byte_buffer_eq_string(grpc_byte_buffer* bb, const char* str);
int contains_metadata(grpc_metadata_array* array, const char* key,
                      const char* value);
int contains_metadata_slices(grpc_metadata_array* array, grpc_slice key,
                             grpc_slice value);

#endif
