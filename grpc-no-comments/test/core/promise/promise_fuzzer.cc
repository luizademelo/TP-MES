// Copyright 2021 gRPC authors.

#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <tuple>
#include <utility>
#include <vector>

#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"
#include "absl/status/status.h"
#include "fuzztest/fuzztest.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/join.h"
#include "src/core/lib/promise/map.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/promise/promise.h"
#include "src/core/lib/promise/race.h"
#include "src/core/lib/promise/seq.h"
#include "test/core/promise/promise_fuzzer.pb.h"

bool squelch = true;
bool leak_check = true;

namespace grpc_core {

using IntHdl = std::shared_ptr<int>;

template <typename T>
using PromiseFactory = std::function<Promise<T>(T)>;

namespace {
class Fuzzer {
 public:
  void Run(const promise_fuzzer::Msg& msg) {

    if (!msg.has_promise()) {
      return;
    }

    activity_ = MakeActivity(
        [msg, this] {
          return Seq(MakePromise(msg.promise()),
                     [] { return absl::OkStatus(); });
        },
        Scheduler{this},
        [this](absl::Status status) {

          CHECK(!done_);

          if (expected_status_.has_value()) {
            CHECK(status == *expected_status_);
          }

          done_ = true;
        });
    for (int i = 0; !done_ && activity_ != nullptr && i < msg.actions_size();
         i++) {

      const auto& action = msg.actions(i);
      switch (action.action_type_case()) {

        case promise_fuzzer::Action::kForceWakeup:
          activity_->ForceWakeup();
          break;

        case promise_fuzzer::Action::kCancel:
          ExpectCancelled();
          activity_.reset();
          break;

        case promise_fuzzer::Action::kFlushWakeup:
          if (wakeup_ != nullptr) std::exchange(wakeup_, nullptr)();
          break;

        case promise_fuzzer::Action::kDropWaker: {
          int n = action.drop_waker();
          auto v = std::move(wakers_[n]);
          wakers_.erase(n);
          break;
        }

        case promise_fuzzer::Action::kAwakeWaker: {
          int n = action.awake_waker();
          auto v = std::move(wakers_[n]);
          wakers_.erase(n);
          for (auto& w : v) {
            w.Wakeup();
          }
          break;
        }
        case promise_fuzzer::Action::ACTION_TYPE_NOT_SET:
          break;
      }
    }
    ExpectCancelled();
    activity_.reset();
    if (wakeup_ != nullptr) std::exchange(wakeup_, nullptr)();
    CHECK(done_);
  }

 private:

  struct Scheduler {
    Fuzzer* fuzzer;
    template <typename ActivityType>
    class BoundScheduler {
     public:
      explicit BoundScheduler(Scheduler scheduler)
          : fuzzer_(scheduler.fuzzer) {}
      void ScheduleWakeup() {
        CHECK(static_cast<ActivityType*>(this) == fuzzer_->activity_.get());
        CHECK(fuzzer_->wakeup_ == nullptr);
        fuzzer_->wakeup_ = [this]() {
          static_cast<ActivityType*>(this)->RunScheduledWakeup();
        };
      }

     private:
      Fuzzer* fuzzer_;
    };
  };

  void ExpectCancelled() {
    if (!done_ && !expected_status_.has_value()) {
      expected_status_ = absl::CancelledError();
    }
  }

  PromiseFactory<IntHdl> MakePromiseFactory(
      const promise_fuzzer::PromiseFactory& p) {
    switch (p.promise_factory_type_case()) {
      case promise_fuzzer::PromiseFactory::kPromise:
        return [p, this](IntHdl) { return MakePromise(p.promise()); };
      case promise_fuzzer::PromiseFactory::kLast:
        return [](IntHdl h) { return [h]() { return h; }; };
      case promise_fuzzer::PromiseFactory::PROMISE_FACTORY_TYPE_NOT_SET:
        break;
    }
    return [](IntHdl) {
      return []() -> Poll<IntHdl> { return std::make_shared<int>(42); };
    };
  }

  Promise<IntHdl> MakePromise(const promise_fuzzer::Promise& p) {
    switch (p.promise_type_case()) {
      case promise_fuzzer::Promise::kSeq:
        switch (p.seq().promise_factories_size()) {
          case 1:
            return Seq(MakePromise(p.seq().first()),
                       MakePromiseFactory(p.seq().promise_factories(0)));
          case 2:
            return Seq(MakePromise(p.seq().first()),
                       MakePromiseFactory(p.seq().promise_factories(0)),
                       MakePromiseFactory(p.seq().promise_factories(1)));
          case 3:
            return Seq(MakePromise(p.seq().first()),
                       MakePromiseFactory(p.seq().promise_factories(0)),
                       MakePromiseFactory(p.seq().promise_factories(1)),
                       MakePromiseFactory(p.seq().promise_factories(2)));
          case 4:
            return Seq(MakePromise(p.seq().first()),
                       MakePromiseFactory(p.seq().promise_factories(0)),
                       MakePromiseFactory(p.seq().promise_factories(1)),
                       MakePromiseFactory(p.seq().promise_factories(2)),
                       MakePromiseFactory(p.seq().promise_factories(3)));
          case 5:
            return Seq(MakePromise(p.seq().first()),
                       MakePromiseFactory(p.seq().promise_factories(0)),
                       MakePromiseFactory(p.seq().promise_factories(1)),
                       MakePromiseFactory(p.seq().promise_factories(2)),
                       MakePromiseFactory(p.seq().promise_factories(3)),
                       MakePromiseFactory(p.seq().promise_factories(4)));
          case 6:
            return Seq(MakePromise(p.seq().first()),
                       MakePromiseFactory(p.seq().promise_factories(0)),
                       MakePromiseFactory(p.seq().promise_factories(1)),
                       MakePromiseFactory(p.seq().promise_factories(2)),
                       MakePromiseFactory(p.seq().promise_factories(3)),
                       MakePromiseFactory(p.seq().promise_factories(4)),
                       MakePromiseFactory(p.seq().promise_factories(5)));
        }
        break;
      case promise_fuzzer::Promise::kJoin:
        switch (p.join().promises_size()) {
          case 1:
            return Map(Join(MakePromise(p.join().promises(0))),
                       [](std::tuple<IntHdl> t) { return std::get<0>(t); });
          case 2:
            return Map(
                Join(MakePromise(p.join().promises(0)),
                     MakePromise(p.join().promises(1))),
                [](std::tuple<IntHdl, IntHdl> t) { return std::get<0>(t); });
          case 3:
            return Map(Join(MakePromise(p.join().promises(0)),
                            MakePromise(p.join().promises(1)),
                            MakePromise(p.join().promises(2))),
                       [](std::tuple<IntHdl, IntHdl, IntHdl> t) {
                         return std::get<0>(t);
                       });
          case 4:
            return Map(Join(MakePromise(p.join().promises(0)),
                            MakePromise(p.join().promises(1)),
                            MakePromise(p.join().promises(2)),
                            MakePromise(p.join().promises(3))),
                       [](std::tuple<IntHdl, IntHdl, IntHdl, IntHdl> t) {
                         return std::get<0>(t);
                       });
          case 5:
            return Map(
                Join(MakePromise(p.join().promises(0)),
                     MakePromise(p.join().promises(1)),
                     MakePromise(p.join().promises(2)),
                     MakePromise(p.join().promises(3)),
                     MakePromise(p.join().promises(4))),
                [](std::tuple<IntHdl, IntHdl, IntHdl, IntHdl, IntHdl> t) {
                  return std::get<0>(t);
                });
          case 6:
            return Map(
                Join(MakePromise(p.join().promises(0)),
                     MakePromise(p.join().promises(1)),
                     MakePromise(p.join().promises(2)),
                     MakePromise(p.join().promises(3)),
                     MakePromise(p.join().promises(4)),
                     MakePromise(p.join().promises(5))),
                [](std::tuple<IntHdl, IntHdl, IntHdl, IntHdl, IntHdl, IntHdl>
                       t) { return std::get<0>(t); });
        }
        break;
      case promise_fuzzer::Promise::kRace:
        switch (p.race().promises_size()) {
          case 1:
            return Race(MakePromise(p.race().promises(0)));
          case 2:
            return Race(MakePromise(p.race().promises(0)),
                        MakePromise(p.race().promises(1)));
          case 3:
            return Race(MakePromise(p.race().promises(0)),
                        MakePromise(p.race().promises(1)),
                        MakePromise(p.race().promises(2)));
          case 4:
            return Race(MakePromise(p.race().promises(0)),
                        MakePromise(p.race().promises(1)),
                        MakePromise(p.race().promises(2)),
                        MakePromise(p.race().promises(3)));
          case 5:
            return Race(MakePromise(p.race().promises(0)),
                        MakePromise(p.race().promises(1)),
                        MakePromise(p.race().promises(2)),
                        MakePromise(p.race().promises(3)),
                        MakePromise(p.race().promises(4)));
          case 6:
            return Race(MakePromise(p.race().promises(0)),
                        MakePromise(p.race().promises(1)),
                        MakePromise(p.race().promises(2)),
                        MakePromise(p.race().promises(3)),
                        MakePromise(p.race().promises(4)),
                        MakePromise(p.race().promises(5)));
        }
        break;
      case promise_fuzzer::Promise::kNever:
        return Never<IntHdl>();
      case promise_fuzzer::Promise::kSleepFirstN: {
        int n = p.sleep_first_n();
        return [n]() mutable -> Poll<IntHdl> {
          if (n <= 0) return std::make_shared<int>(0);
          n--;
          return Pending{};
        };
      }
      case promise_fuzzer::Promise::kCancelFromInside:
        return [this]() -> Poll<IntHdl> {
          this->activity_.reset();
          return Pending{};
        };
      case promise_fuzzer::Promise::kWaitOnceOnWaker: {
        bool called = false;
        auto config = p.wait_once_on_waker();
        return [this, config, called]() mutable -> Poll<IntHdl> {
          if (!called) {
            if (config.owning()) {
              wakers_[config.waker()].push_back(
                  GetContext<Activity>()->MakeOwningWaker());
            } else {
              wakers_[config.waker()].push_back(
                  GetContext<Activity>()->MakeNonOwningWaker());
            }
            return Pending();
          }
          return std::make_shared<int>(3);
        };
      }
      case promise_fuzzer::Promise::PromiseTypeCase::PROMISE_TYPE_NOT_SET:
        break;
    }
    return [] { return std::make_shared<int>(42); };
  }

  ActivityPtr activity_;

  std::function<void()> wakeup_;

  std::optional<absl::Status> expected_status_;

  bool done_ = false;

  std::map<int, std::vector<Waker>> wakers_;
};

void Run(promise_fuzzer::Msg msg) { Fuzzer().Run(msg); }
FUZZ_TEST(PromiseFuzzer, Run);

}
}
