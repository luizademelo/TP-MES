// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_DETAIL_JOIN_STATE_H
#define GRPC_SRC_CORE_LIB_PROMISE_DETAIL_JOIN_STATE_H

#include <grpc/support/port_platform.h>

#include <tuple>
#include <type_traits>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/promise/detail/promise_like.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/util/bitset.h"
#include "src/core/util/construct_destruct.h"

namespace grpc_core {
namespace promise_detail {
template <class Traits, typename... Ps>
struct JoinState;

template <class Traits, typename P0, typename P1>
struct JoinState<Traits, P0, P1> {
  template <typename T>
  using UnwrappedType = decltype(Traits::Unwrapped(std::declval<T>()));
  using Promise0 = PromiseLike<P0>;
  using Result0 = UnwrappedType<typename Promise0::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise0 promise0;
    GPR_NO_UNIQUE_ADDRESS Result0 result0;
  };
  using Promise1 = PromiseLike<P1>;
  using Result1 = UnwrappedType<typename Promise1::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise1 promise1;
    GPR_NO_UNIQUE_ADDRESS Result1 result1;
  };
  GPR_NO_UNIQUE_ADDRESS BitSet<2> ready;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(P0&& p0, P1&& p1) {
    Construct(&promise0, std::forward<P0>(p0));
    Construct(&promise1, std::forward<P1>(p1));
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(const JoinState& other) =
      delete;
  JoinState& operator=(const JoinState& other) = delete;
  JoinState& operator=(JoinState&& other) = delete;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(JoinState&& other) noexcept {
    DCHECK(other.ready.none());
    Construct(&promise0, std::move(other.promise0));
    Construct(&promise1, std::move(other.promise1));
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION ~JoinState() {
    if (ready.is_set(0)) {
      Destruct(&result0);
    } else {
      Destruct(&promise0);
    }
    if (ready.is_set(1)) {
      Destruct(&result1);
    } else {
      Destruct(&promise1);
    }
  }
  using Result =
      typename Traits::template ResultType<std::tuple<Result0, Result1>>;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll<Result> PollOnce() {
    if (!ready.is_set(0)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 1/2";
      auto poll = promise0();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 1/2 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(0);
          Destruct(&promise0);
          Construct(&result0, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 1/2 already ready";
    }
    if (!ready.is_set(1)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 2/2";
      auto poll = promise1();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 2/2 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(1);
          Destruct(&promise1);
          Construct(&result1, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 2/2 already ready";
    }
    if (ready.all()) {
      return Traits::FinalReturn(std::move(result0), std::move(result1));
    }
    return Pending{};
  }
};

template <class Traits, typename P0, typename P1, typename P2>
struct JoinState<Traits, P0, P1, P2> {
  template <typename T>
  using UnwrappedType = decltype(Traits::Unwrapped(std::declval<T>()));
  using Promise0 = PromiseLike<P0>;
  using Result0 = UnwrappedType<typename Promise0::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise0 promise0;
    GPR_NO_UNIQUE_ADDRESS Result0 result0;
  };
  using Promise1 = PromiseLike<P1>;
  using Result1 = UnwrappedType<typename Promise1::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise1 promise1;
    GPR_NO_UNIQUE_ADDRESS Result1 result1;
  };
  using Promise2 = PromiseLike<P2>;
  using Result2 = UnwrappedType<typename Promise2::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise2 promise2;
    GPR_NO_UNIQUE_ADDRESS Result2 result2;
  };
  GPR_NO_UNIQUE_ADDRESS BitSet<3> ready;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(P0&& p0, P1&& p1, P2&& p2) {
    Construct(&promise0, std::forward<P0>(p0));
    Construct(&promise1, std::forward<P1>(p1));
    Construct(&promise2, std::forward<P2>(p2));
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(const JoinState& other) =
      delete;
  JoinState& operator=(const JoinState& other) = delete;
  JoinState& operator=(JoinState&& other) = delete;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(JoinState&& other) noexcept {
    DCHECK(other.ready.none());
    Construct(&promise0, std::move(other.promise0));
    Construct(&promise1, std::move(other.promise1));
    Construct(&promise2, std::move(other.promise2));
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION ~JoinState() {
    if (ready.is_set(0)) {
      Destruct(&result0);
    } else {
      Destruct(&promise0);
    }
    if (ready.is_set(1)) {
      Destruct(&result1);
    } else {
      Destruct(&promise1);
    }
    if (ready.is_set(2)) {
      Destruct(&result2);
    } else {
      Destruct(&promise2);
    }
  }
  using Result = typename Traits::template ResultType<
      std::tuple<Result0, Result1, Result2>>;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll<Result> PollOnce() {
    if (!ready.is_set(0)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 1/3";
      auto poll = promise0();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 1/3 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(0);
          Destruct(&promise0);
          Construct(&result0, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 1/3 already ready";
    }
    if (!ready.is_set(1)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 2/3";
      auto poll = promise1();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 2/3 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(1);
          Destruct(&promise1);
          Construct(&result1, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 2/3 already ready";
    }
    if (!ready.is_set(2)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 3/3";
      auto poll = promise2();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 3/3 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(2);
          Destruct(&promise2);
          Construct(&result2, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 3/3 already ready";
    }
    if (ready.all()) {
      return Traits::FinalReturn(std::move(result0), std::move(result1),
                                 std::move(result2));
    }
    return Pending{};
  }
};

template <class Traits, typename P0, typename P1, typename P2, typename P3>
struct JoinState<Traits, P0, P1, P2, P3> {
  template <typename T>
  using UnwrappedType = decltype(Traits::Unwrapped(std::declval<T>()));
  using Promise0 = PromiseLike<P0>;
  using Result0 = UnwrappedType<typename Promise0::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise0 promise0;
    GPR_NO_UNIQUE_ADDRESS Result0 result0;
  };
  using Promise1 = PromiseLike<P1>;
  using Result1 = UnwrappedType<typename Promise1::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise1 promise1;
    GPR_NO_UNIQUE_ADDRESS Result1 result1;
  };
  using Promise2 = PromiseLike<P2>;
  using Result2 = UnwrappedType<typename Promise2::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise2 promise2;
    GPR_NO_UNIQUE_ADDRESS Result2 result2;
  };
  using Promise3 = PromiseLike<P3>;
  using Result3 = UnwrappedType<typename Promise3::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise3 promise3;
    GPR_NO_UNIQUE_ADDRESS Result3 result3;
  };
  GPR_NO_UNIQUE_ADDRESS BitSet<4> ready;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(P0&& p0, P1&& p1, P2&& p2,
                                                 P3&& p3) {
    Construct(&promise0, std::forward<P0>(p0));
    Construct(&promise1, std::forward<P1>(p1));
    Construct(&promise2, std::forward<P2>(p2));
    Construct(&promise3, std::forward<P3>(p3));
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(const JoinState& other) =
      delete;
  JoinState& operator=(const JoinState& other) = delete;
  JoinState& operator=(JoinState&& other) = delete;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(JoinState&& other) noexcept {
    DCHECK(other.ready.none());
    Construct(&promise0, std::move(other.promise0));
    Construct(&promise1, std::move(other.promise1));
    Construct(&promise2, std::move(other.promise2));
    Construct(&promise3, std::move(other.promise3));
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION ~JoinState() {
    if (ready.is_set(0)) {
      Destruct(&result0);
    } else {
      Destruct(&promise0);
    }
    if (ready.is_set(1)) {
      Destruct(&result1);
    } else {
      Destruct(&promise1);
    }
    if (ready.is_set(2)) {
      Destruct(&result2);
    } else {
      Destruct(&promise2);
    }
    if (ready.is_set(3)) {
      Destruct(&result3);
    } else {
      Destruct(&promise3);
    }
  }
  using Result = typename Traits::template ResultType<
      std::tuple<Result0, Result1, Result2, Result3>>;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll<Result> PollOnce() {
    if (!ready.is_set(0)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 1/4";
      auto poll = promise0();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 1/4 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(0);
          Destruct(&promise0);
          Construct(&result0, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 1/4 already ready";
    }
    if (!ready.is_set(1)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 2/4";
      auto poll = promise1();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 2/4 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(1);
          Destruct(&promise1);
          Construct(&result1, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 2/4 already ready";
    }
    if (!ready.is_set(2)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 3/4";
      auto poll = promise2();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 3/4 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(2);
          Destruct(&promise2);
          Construct(&result2, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 3/4 already ready";
    }
    if (!ready.is_set(3)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 4/4";
      auto poll = promise3();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 4/4 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(3);
          Destruct(&promise3);
          Construct(&result3, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 4/4 already ready";
    }
    if (ready.all()) {
      return Traits::FinalReturn(std::move(result0), std::move(result1),
                                 std::move(result2), std::move(result3));
    }
    return Pending{};
  }
};

template <class Traits, typename P0, typename P1, typename P2, typename P3,
          typename P4>
struct JoinState<Traits, P0, P1, P2, P3, P4> {
  template <typename T>
  using UnwrappedType = decltype(Traits::Unwrapped(std::declval<T>()));
  using Promise0 = PromiseLike<P0>;
  using Result0 = UnwrappedType<typename Promise0::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise0 promise0;
    GPR_NO_UNIQUE_ADDRESS Result0 result0;
  };
  using Promise1 = PromiseLike<P1>;
  using Result1 = UnwrappedType<typename Promise1::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise1 promise1;
    GPR_NO_UNIQUE_ADDRESS Result1 result1;
  };
  using Promise2 = PromiseLike<P2>;
  using Result2 = UnwrappedType<typename Promise2::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise2 promise2;
    GPR_NO_UNIQUE_ADDRESS Result2 result2;
  };
  using Promise3 = PromiseLike<P3>;
  using Result3 = UnwrappedType<typename Promise3::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise3 promise3;
    GPR_NO_UNIQUE_ADDRESS Result3 result3;
  };
  using Promise4 = PromiseLike<P4>;
  using Result4 = UnwrappedType<typename Promise4::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise4 promise4;
    GPR_NO_UNIQUE_ADDRESS Result4 result4;
  };
  GPR_NO_UNIQUE_ADDRESS BitSet<5> ready;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(P0&& p0, P1&& p1, P2&& p2,
                                                 P3&& p3, P4&& p4) {
    Construct(&promise0, std::forward<P0>(p0));
    Construct(&promise1, std::forward<P1>(p1));
    Construct(&promise2, std::forward<P2>(p2));
    Construct(&promise3, std::forward<P3>(p3));
    Construct(&promise4, std::forward<P4>(p4));
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(const JoinState& other) =
      delete;
  JoinState& operator=(const JoinState& other) = delete;
  JoinState& operator=(JoinState&& other) = delete;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(JoinState&& other) noexcept {
    DCHECK(other.ready.none());
    Construct(&promise0, std::move(other.promise0));
    Construct(&promise1, std::move(other.promise1));
    Construct(&promise2, std::move(other.promise2));
    Construct(&promise3, std::move(other.promise3));
    Construct(&promise4, std::move(other.promise4));
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION ~JoinState() {
    if (ready.is_set(0)) {
      Destruct(&result0);
    } else {
      Destruct(&promise0);
    }
    if (ready.is_set(1)) {
      Destruct(&result1);
    } else {
      Destruct(&promise1);
    }
    if (ready.is_set(2)) {
      Destruct(&result2);
    } else {
      Destruct(&promise2);
    }
    if (ready.is_set(3)) {
      Destruct(&result3);
    } else {
      Destruct(&promise3);
    }
    if (ready.is_set(4)) {
      Destruct(&result4);
    } else {
      Destruct(&promise4);
    }
  }
  using Result = typename Traits::template ResultType<
      std::tuple<Result0, Result1, Result2, Result3, Result4>>;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll<Result> PollOnce() {
    if (!ready.is_set(0)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 1/5";
      auto poll = promise0();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 1/5 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(0);
          Destruct(&promise0);
          Construct(&result0, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 1/5 already ready";
    }
    if (!ready.is_set(1)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 2/5";
      auto poll = promise1();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 2/5 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(1);
          Destruct(&promise1);
          Construct(&result1, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 2/5 already ready";
    }
    if (!ready.is_set(2)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 3/5";
      auto poll = promise2();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 3/5 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(2);
          Destruct(&promise2);
          Construct(&result2, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 3/5 already ready";
    }
    if (!ready.is_set(3)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 4/5";
      auto poll = promise3();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 4/5 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(3);
          Destruct(&promise3);
          Construct(&result3, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 4/5 already ready";
    }
    if (!ready.is_set(4)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 5/5";
      auto poll = promise4();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 5/5 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(4);
          Destruct(&promise4);
          Construct(&result4, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 5/5 already ready";
    }
    if (ready.all()) {
      return Traits::FinalReturn(std::move(result0), std::move(result1),
                                 std::move(result2), std::move(result3),
                                 std::move(result4));
    }
    return Pending{};
  }
};

template <class Traits, typename P0, typename P1, typename P2, typename P3,
          typename P4, typename P5>
struct JoinState<Traits, P0, P1, P2, P3, P4, P5> {
  template <typename T>
  using UnwrappedType = decltype(Traits::Unwrapped(std::declval<T>()));
  using Promise0 = PromiseLike<P0>;
  using Result0 = UnwrappedType<typename Promise0::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise0 promise0;
    GPR_NO_UNIQUE_ADDRESS Result0 result0;
  };
  using Promise1 = PromiseLike<P1>;
  using Result1 = UnwrappedType<typename Promise1::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise1 promise1;
    GPR_NO_UNIQUE_ADDRESS Result1 result1;
  };
  using Promise2 = PromiseLike<P2>;
  using Result2 = UnwrappedType<typename Promise2::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise2 promise2;
    GPR_NO_UNIQUE_ADDRESS Result2 result2;
  };
  using Promise3 = PromiseLike<P3>;
  using Result3 = UnwrappedType<typename Promise3::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise3 promise3;
    GPR_NO_UNIQUE_ADDRESS Result3 result3;
  };
  using Promise4 = PromiseLike<P4>;
  using Result4 = UnwrappedType<typename Promise4::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise4 promise4;
    GPR_NO_UNIQUE_ADDRESS Result4 result4;
  };
  using Promise5 = PromiseLike<P5>;
  using Result5 = UnwrappedType<typename Promise5::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise5 promise5;
    GPR_NO_UNIQUE_ADDRESS Result5 result5;
  };
  GPR_NO_UNIQUE_ADDRESS BitSet<6> ready;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(P0&& p0, P1&& p1, P2&& p2,
                                                 P3&& p3, P4&& p4, P5&& p5) {
    Construct(&promise0, std::forward<P0>(p0));
    Construct(&promise1, std::forward<P1>(p1));
    Construct(&promise2, std::forward<P2>(p2));
    Construct(&promise3, std::forward<P3>(p3));
    Construct(&promise4, std::forward<P4>(p4));
    Construct(&promise5, std::forward<P5>(p5));
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(const JoinState& other) =
      delete;
  JoinState& operator=(const JoinState& other) = delete;
  JoinState& operator=(JoinState&& other) = delete;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(JoinState&& other) noexcept {
    DCHECK(other.ready.none());
    Construct(&promise0, std::move(other.promise0));
    Construct(&promise1, std::move(other.promise1));
    Construct(&promise2, std::move(other.promise2));
    Construct(&promise3, std::move(other.promise3));
    Construct(&promise4, std::move(other.promise4));
    Construct(&promise5, std::move(other.promise5));
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION ~JoinState() {
    if (ready.is_set(0)) {
      Destruct(&result0);
    } else {
      Destruct(&promise0);
    }
    if (ready.is_set(1)) {
      Destruct(&result1);
    } else {
      Destruct(&promise1);
    }
    if (ready.is_set(2)) {
      Destruct(&result2);
    } else {
      Destruct(&promise2);
    }
    if (ready.is_set(3)) {
      Destruct(&result3);
    } else {
      Destruct(&promise3);
    }
    if (ready.is_set(4)) {
      Destruct(&result4);
    } else {
      Destruct(&promise4);
    }
    if (ready.is_set(5)) {
      Destruct(&result5);
    } else {
      Destruct(&promise5);
    }
  }
  using Result = typename Traits::template ResultType<
      std::tuple<Result0, Result1, Result2, Result3, Result4, Result5>>;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll<Result> PollOnce() {
    if (!ready.is_set(0)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 1/6";
      auto poll = promise0();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 1/6 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(0);
          Destruct(&promise0);
          Construct(&result0, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 1/6 already ready";
    }
    if (!ready.is_set(1)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 2/6";
      auto poll = promise1();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 2/6 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(1);
          Destruct(&promise1);
          Construct(&result1, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 2/6 already ready";
    }
    if (!ready.is_set(2)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 3/6";
      auto poll = promise2();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 3/6 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(2);
          Destruct(&promise2);
          Construct(&result2, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 3/6 already ready";
    }
    if (!ready.is_set(3)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 4/6";
      auto poll = promise3();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 4/6 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(3);
          Destruct(&promise3);
          Construct(&result3, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 4/6 already ready";
    }
    if (!ready.is_set(4)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 5/6";
      auto poll = promise4();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 5/6 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(4);
          Destruct(&promise4);
          Construct(&result4, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 5/6 already ready";
    }
    if (!ready.is_set(5)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 6/6";
      auto poll = promise5();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 6/6 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(5);
          Destruct(&promise5);
          Construct(&result5, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 6/6 already ready";
    }
    if (ready.all()) {
      return Traits::FinalReturn(std::move(result0), std::move(result1),
                                 std::move(result2), std::move(result3),
                                 std::move(result4), std::move(result5));
    }
    return Pending{};
  }
};

template <class Traits, typename P0, typename P1, typename P2, typename P3,
          typename P4, typename P5, typename P6>
struct JoinState<Traits, P0, P1, P2, P3, P4, P5, P6> {
  template <typename T>
  using UnwrappedType = decltype(Traits::Unwrapped(std::declval<T>()));
  using Promise0 = PromiseLike<P0>;
  using Result0 = UnwrappedType<typename Promise0::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise0 promise0;
    GPR_NO_UNIQUE_ADDRESS Result0 result0;
  };
  using Promise1 = PromiseLike<P1>;
  using Result1 = UnwrappedType<typename Promise1::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise1 promise1;
    GPR_NO_UNIQUE_ADDRESS Result1 result1;
  };
  using Promise2 = PromiseLike<P2>;
  using Result2 = UnwrappedType<typename Promise2::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise2 promise2;
    GPR_NO_UNIQUE_ADDRESS Result2 result2;
  };
  using Promise3 = PromiseLike<P3>;
  using Result3 = UnwrappedType<typename Promise3::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise3 promise3;
    GPR_NO_UNIQUE_ADDRESS Result3 result3;
  };
  using Promise4 = PromiseLike<P4>;
  using Result4 = UnwrappedType<typename Promise4::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise4 promise4;
    GPR_NO_UNIQUE_ADDRESS Result4 result4;
  };
  using Promise5 = PromiseLike<P5>;
  using Result5 = UnwrappedType<typename Promise5::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise5 promise5;
    GPR_NO_UNIQUE_ADDRESS Result5 result5;
  };
  using Promise6 = PromiseLike<P6>;
  using Result6 = UnwrappedType<typename Promise6::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise6 promise6;
    GPR_NO_UNIQUE_ADDRESS Result6 result6;
  };
  GPR_NO_UNIQUE_ADDRESS BitSet<7> ready;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(P0&& p0, P1&& p1, P2&& p2,
                                                 P3&& p3, P4&& p4, P5&& p5,
                                                 P6&& p6) {
    Construct(&promise0, std::forward<P0>(p0));
    Construct(&promise1, std::forward<P1>(p1));
    Construct(&promise2, std::forward<P2>(p2));
    Construct(&promise3, std::forward<P3>(p3));
    Construct(&promise4, std::forward<P4>(p4));
    Construct(&promise5, std::forward<P5>(p5));
    Construct(&promise6, std::forward<P6>(p6));
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(const JoinState& other) =
      delete;
  JoinState& operator=(const JoinState& other) = delete;
  JoinState& operator=(JoinState&& other) = delete;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(JoinState&& other) noexcept {
    DCHECK(other.ready.none());
    Construct(&promise0, std::move(other.promise0));
    Construct(&promise1, std::move(other.promise1));
    Construct(&promise2, std::move(other.promise2));
    Construct(&promise3, std::move(other.promise3));
    Construct(&promise4, std::move(other.promise4));
    Construct(&promise5, std::move(other.promise5));
    Construct(&promise6, std::move(other.promise6));
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION ~JoinState() {
    if (ready.is_set(0)) {
      Destruct(&result0);
    } else {
      Destruct(&promise0);
    }
    if (ready.is_set(1)) {
      Destruct(&result1);
    } else {
      Destruct(&promise1);
    }
    if (ready.is_set(2)) {
      Destruct(&result2);
    } else {
      Destruct(&promise2);
    }
    if (ready.is_set(3)) {
      Destruct(&result3);
    } else {
      Destruct(&promise3);
    }
    if (ready.is_set(4)) {
      Destruct(&result4);
    } else {
      Destruct(&promise4);
    }
    if (ready.is_set(5)) {
      Destruct(&result5);
    } else {
      Destruct(&promise5);
    }
    if (ready.is_set(6)) {
      Destruct(&result6);
    } else {
      Destruct(&promise6);
    }
  }
  using Result = typename Traits::template ResultType<std::tuple<
      Result0, Result1, Result2, Result3, Result4, Result5, Result6>>;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll<Result> PollOnce() {
    if (!ready.is_set(0)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 1/7";
      auto poll = promise0();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 1/7 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(0);
          Destruct(&promise0);
          Construct(&result0, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 1/7 already ready";
    }
    if (!ready.is_set(1)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 2/7";
      auto poll = promise1();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 2/7 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(1);
          Destruct(&promise1);
          Construct(&result1, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 2/7 already ready";
    }
    if (!ready.is_set(2)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 3/7";
      auto poll = promise2();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 3/7 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(2);
          Destruct(&promise2);
          Construct(&result2, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 3/7 already ready";
    }
    if (!ready.is_set(3)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 4/7";
      auto poll = promise3();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 4/7 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(3);
          Destruct(&promise3);
          Construct(&result3, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 4/7 already ready";
    }
    if (!ready.is_set(4)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 5/7";
      auto poll = promise4();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 5/7 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(4);
          Destruct(&promise4);
          Construct(&result4, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 5/7 already ready";
    }
    if (!ready.is_set(5)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 6/7";
      auto poll = promise5();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 6/7 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(5);
          Destruct(&promise5);
          Construct(&result5, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 6/7 already ready";
    }
    if (!ready.is_set(6)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 7/7";
      auto poll = promise6();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 7/7 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(6);
          Destruct(&promise6);
          Construct(&result6, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 7/7 already ready";
    }
    if (ready.all()) {
      return Traits::FinalReturn(std::move(result0), std::move(result1),
                                 std::move(result2), std::move(result3),
                                 std::move(result4), std::move(result5),
                                 std::move(result6));
    }
    return Pending{};
  }
};

template <class Traits, typename P0, typename P1, typename P2, typename P3,
          typename P4, typename P5, typename P6, typename P7>
struct JoinState<Traits, P0, P1, P2, P3, P4, P5, P6, P7> {
  template <typename T>
  using UnwrappedType = decltype(Traits::Unwrapped(std::declval<T>()));
  using Promise0 = PromiseLike<P0>;
  using Result0 = UnwrappedType<typename Promise0::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise0 promise0;
    GPR_NO_UNIQUE_ADDRESS Result0 result0;
  };
  using Promise1 = PromiseLike<P1>;
  using Result1 = UnwrappedType<typename Promise1::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise1 promise1;
    GPR_NO_UNIQUE_ADDRESS Result1 result1;
  };
  using Promise2 = PromiseLike<P2>;
  using Result2 = UnwrappedType<typename Promise2::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise2 promise2;
    GPR_NO_UNIQUE_ADDRESS Result2 result2;
  };
  using Promise3 = PromiseLike<P3>;
  using Result3 = UnwrappedType<typename Promise3::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise3 promise3;
    GPR_NO_UNIQUE_ADDRESS Result3 result3;
  };
  using Promise4 = PromiseLike<P4>;
  using Result4 = UnwrappedType<typename Promise4::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise4 promise4;
    GPR_NO_UNIQUE_ADDRESS Result4 result4;
  };
  using Promise5 = PromiseLike<P5>;
  using Result5 = UnwrappedType<typename Promise5::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise5 promise5;
    GPR_NO_UNIQUE_ADDRESS Result5 result5;
  };
  using Promise6 = PromiseLike<P6>;
  using Result6 = UnwrappedType<typename Promise6::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise6 promise6;
    GPR_NO_UNIQUE_ADDRESS Result6 result6;
  };
  using Promise7 = PromiseLike<P7>;
  using Result7 = UnwrappedType<typename Promise7::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise7 promise7;
    GPR_NO_UNIQUE_ADDRESS Result7 result7;
  };
  GPR_NO_UNIQUE_ADDRESS BitSet<8> ready;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(P0&& p0, P1&& p1, P2&& p2,
                                                 P3&& p3, P4&& p4, P5&& p5,
                                                 P6&& p6, P7&& p7) {
    Construct(&promise0, std::forward<P0>(p0));
    Construct(&promise1, std::forward<P1>(p1));
    Construct(&promise2, std::forward<P2>(p2));
    Construct(&promise3, std::forward<P3>(p3));
    Construct(&promise4, std::forward<P4>(p4));
    Construct(&promise5, std::forward<P5>(p5));
    Construct(&promise6, std::forward<P6>(p6));
    Construct(&promise7, std::forward<P7>(p7));
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(const JoinState& other) =
      delete;
  JoinState& operator=(const JoinState& other) = delete;
  JoinState& operator=(JoinState&& other) = delete;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(JoinState&& other) noexcept {
    DCHECK(other.ready.none());
    Construct(&promise0, std::move(other.promise0));
    Construct(&promise1, std::move(other.promise1));
    Construct(&promise2, std::move(other.promise2));
    Construct(&promise3, std::move(other.promise3));
    Construct(&promise4, std::move(other.promise4));
    Construct(&promise5, std::move(other.promise5));
    Construct(&promise6, std::move(other.promise6));
    Construct(&promise7, std::move(other.promise7));
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION ~JoinState() {
    if (ready.is_set(0)) {
      Destruct(&result0);
    } else {
      Destruct(&promise0);
    }
    if (ready.is_set(1)) {
      Destruct(&result1);
    } else {
      Destruct(&promise1);
    }
    if (ready.is_set(2)) {
      Destruct(&result2);
    } else {
      Destruct(&promise2);
    }
    if (ready.is_set(3)) {
      Destruct(&result3);
    } else {
      Destruct(&promise3);
    }
    if (ready.is_set(4)) {
      Destruct(&result4);
    } else {
      Destruct(&promise4);
    }
    if (ready.is_set(5)) {
      Destruct(&result5);
    } else {
      Destruct(&promise5);
    }
    if (ready.is_set(6)) {
      Destruct(&result6);
    } else {
      Destruct(&promise6);
    }
    if (ready.is_set(7)) {
      Destruct(&result7);
    } else {
      Destruct(&promise7);
    }
  }
  using Result = typename Traits::template ResultType<std::tuple<
      Result0, Result1, Result2, Result3, Result4, Result5, Result6, Result7>>;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll<Result> PollOnce() {
    if (!ready.is_set(0)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 1/8";
      auto poll = promise0();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 1/8 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(0);
          Destruct(&promise0);
          Construct(&result0, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 1/8 already ready";
    }
    if (!ready.is_set(1)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 2/8";
      auto poll = promise1();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 2/8 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(1);
          Destruct(&promise1);
          Construct(&result1, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 2/8 already ready";
    }
    if (!ready.is_set(2)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 3/8";
      auto poll = promise2();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 3/8 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(2);
          Destruct(&promise2);
          Construct(&result2, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 3/8 already ready";
    }
    if (!ready.is_set(3)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 4/8";
      auto poll = promise3();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 4/8 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(3);
          Destruct(&promise3);
          Construct(&result3, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 4/8 already ready";
    }
    if (!ready.is_set(4)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 5/8";
      auto poll = promise4();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 5/8 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(4);
          Destruct(&promise4);
          Construct(&result4, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 5/8 already ready";
    }
    if (!ready.is_set(5)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 6/8";
      auto poll = promise5();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 6/8 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(5);
          Destruct(&promise5);
          Construct(&result5, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 6/8 already ready";
    }
    if (!ready.is_set(6)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 7/8";
      auto poll = promise6();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 7/8 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(6);
          Destruct(&promise6);
          Construct(&result6, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 7/8 already ready";
    }
    if (!ready.is_set(7)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 8/8";
      auto poll = promise7();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 8/8 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(7);
          Destruct(&promise7);
          Construct(&result7, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 8/8 already ready";
    }
    if (ready.all()) {
      return Traits::FinalReturn(std::move(result0), std::move(result1),
                                 std::move(result2), std::move(result3),
                                 std::move(result4), std::move(result5),
                                 std::move(result6), std::move(result7));
    }
    return Pending{};
  }
};

template <class Traits, typename P0, typename P1, typename P2, typename P3,
          typename P4, typename P5, typename P6, typename P7, typename P8>
struct JoinState<Traits, P0, P1, P2, P3, P4, P5, P6, P7, P8> {
  template <typename T>
  using UnwrappedType = decltype(Traits::Unwrapped(std::declval<T>()));
  using Promise0 = PromiseLike<P0>;
  using Result0 = UnwrappedType<typename Promise0::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise0 promise0;
    GPR_NO_UNIQUE_ADDRESS Result0 result0;
  };
  using Promise1 = PromiseLike<P1>;
  using Result1 = UnwrappedType<typename Promise1::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise1 promise1;
    GPR_NO_UNIQUE_ADDRESS Result1 result1;
  };
  using Promise2 = PromiseLike<P2>;
  using Result2 = UnwrappedType<typename Promise2::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise2 promise2;
    GPR_NO_UNIQUE_ADDRESS Result2 result2;
  };
  using Promise3 = PromiseLike<P3>;
  using Result3 = UnwrappedType<typename Promise3::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise3 promise3;
    GPR_NO_UNIQUE_ADDRESS Result3 result3;
  };
  using Promise4 = PromiseLike<P4>;
  using Result4 = UnwrappedType<typename Promise4::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise4 promise4;
    GPR_NO_UNIQUE_ADDRESS Result4 result4;
  };
  using Promise5 = PromiseLike<P5>;
  using Result5 = UnwrappedType<typename Promise5::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise5 promise5;
    GPR_NO_UNIQUE_ADDRESS Result5 result5;
  };
  using Promise6 = PromiseLike<P6>;
  using Result6 = UnwrappedType<typename Promise6::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise6 promise6;
    GPR_NO_UNIQUE_ADDRESS Result6 result6;
  };
  using Promise7 = PromiseLike<P7>;
  using Result7 = UnwrappedType<typename Promise7::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise7 promise7;
    GPR_NO_UNIQUE_ADDRESS Result7 result7;
  };
  using Promise8 = PromiseLike<P8>;
  using Result8 = UnwrappedType<typename Promise8::Result>;
  union {
    GPR_NO_UNIQUE_ADDRESS Promise8 promise8;
    GPR_NO_UNIQUE_ADDRESS Result8 result8;
  };
  GPR_NO_UNIQUE_ADDRESS BitSet<9> ready;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(P0&& p0, P1&& p1, P2&& p2,
                                                 P3&& p3, P4&& p4, P5&& p5,
                                                 P6&& p6, P7&& p7, P8&& p8) {
    Construct(&promise0, std::forward<P0>(p0));
    Construct(&promise1, std::forward<P1>(p1));
    Construct(&promise2, std::forward<P2>(p2));
    Construct(&promise3, std::forward<P3>(p3));
    Construct(&promise4, std::forward<P4>(p4));
    Construct(&promise5, std::forward<P5>(p5));
    Construct(&promise6, std::forward<P6>(p6));
    Construct(&promise7, std::forward<P7>(p7));
    Construct(&promise8, std::forward<P8>(p8));
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(const JoinState& other) =
      delete;
  JoinState& operator=(const JoinState& other) = delete;
  JoinState& operator=(JoinState&& other) = delete;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION JoinState(JoinState&& other) noexcept {
    DCHECK(other.ready.none());
    Construct(&promise0, std::move(other.promise0));
    Construct(&promise1, std::move(other.promise1));
    Construct(&promise2, std::move(other.promise2));
    Construct(&promise3, std::move(other.promise3));
    Construct(&promise4, std::move(other.promise4));
    Construct(&promise5, std::move(other.promise5));
    Construct(&promise6, std::move(other.promise6));
    Construct(&promise7, std::move(other.promise7));
    Construct(&promise8, std::move(other.promise8));
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION ~JoinState() {
    if (ready.is_set(0)) {
      Destruct(&result0);
    } else {
      Destruct(&promise0);
    }
    if (ready.is_set(1)) {
      Destruct(&result1);
    } else {
      Destruct(&promise1);
    }
    if (ready.is_set(2)) {
      Destruct(&result2);
    } else {
      Destruct(&promise2);
    }
    if (ready.is_set(3)) {
      Destruct(&result3);
    } else {
      Destruct(&promise3);
    }
    if (ready.is_set(4)) {
      Destruct(&result4);
    } else {
      Destruct(&promise4);
    }
    if (ready.is_set(5)) {
      Destruct(&result5);
    } else {
      Destruct(&promise5);
    }
    if (ready.is_set(6)) {
      Destruct(&result6);
    } else {
      Destruct(&promise6);
    }
    if (ready.is_set(7)) {
      Destruct(&result7);
    } else {
      Destruct(&promise7);
    }
    if (ready.is_set(8)) {
      Destruct(&result8);
    } else {
      Destruct(&promise8);
    }
  }
  using Result = typename Traits::template ResultType<
      std::tuple<Result0, Result1, Result2, Result3, Result4, Result5, Result6,
                 Result7, Result8>>;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll<Result> PollOnce() {
    if (!ready.is_set(0)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 1/9";
      auto poll = promise0();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 1/9 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(0);
          Destruct(&promise0);
          Construct(&result0, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 1/9 already ready";
    }
    if (!ready.is_set(1)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 2/9";
      auto poll = promise1();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 2/9 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(1);
          Destruct(&promise1);
          Construct(&result1, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 2/9 already ready";
    }
    if (!ready.is_set(2)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 3/9";
      auto poll = promise2();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 3/9 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(2);
          Destruct(&promise2);
          Construct(&result2, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 3/9 already ready";
    }
    if (!ready.is_set(3)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 4/9";
      auto poll = promise3();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 4/9 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(3);
          Destruct(&promise3);
          Construct(&result3, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 4/9 already ready";
    }
    if (!ready.is_set(4)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 5/9";
      auto poll = promise4();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 5/9 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(4);
          Destruct(&promise4);
          Construct(&result4, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 5/9 already ready";
    }
    if (!ready.is_set(5)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 6/9";
      auto poll = promise5();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 6/9 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(5);
          Destruct(&promise5);
          Construct(&result5, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 6/9 already ready";
    }
    if (!ready.is_set(6)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 7/9";
      auto poll = promise6();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 7/9 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(6);
          Destruct(&promise6);
          Construct(&result6, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 7/9 already ready";
    }
    if (!ready.is_set(7)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 8/9";
      auto poll = promise7();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 8/9 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(7);
          Destruct(&promise7);
          Construct(&result7, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 8/9 already ready";
    }
    if (!ready.is_set(8)) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: begin poll joint 9/9";
      auto poll = promise8();
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: end poll joint 9/9 "
          << (poll.pending()
                  ? "pending"
                  : (Traits::IsOk(poll.value()) ? "ready" : "early-error"));
      if (auto* p = poll.value_if_ready()) {
        if (Traits::IsOk(*p)) {
          ready.set(8);
          Destruct(&promise8);
          Construct(&result8, Traits::Unwrapped(std::move(*p)));
        } else {
          return Traits::template EarlyReturn<Result>(std::move(*p));
        }
      }
    } else {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << "join[" << this << "]: joint 9/9 already ready";
    }
    if (ready.all()) {
      return Traits::FinalReturn(
          std::move(result0), std::move(result1), std::move(result2),
          std::move(result3), std::move(result4), std::move(result5),
          std::move(result6), std::move(result7), std::move(result8));
    }
    return Pending{};
  }
};

}
}

#endif
