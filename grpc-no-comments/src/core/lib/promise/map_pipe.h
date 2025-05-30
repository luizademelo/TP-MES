// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_MAP_PIPE_H
#define GRPC_SRC_CORE_LIB_PROMISE_MAP_PIPE_H

#include <grpc/support/port_platform.h>

#include "absl/log/log.h"
#include "absl/status/status.h"
#include "src/core/lib/promise/detail/promise_factory.h"
#include "src/core/lib/promise/for_each.h"
#include "src/core/lib/promise/map.h"
#include "src/core/lib/promise/pipe.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/promise/try_seq.h"

namespace grpc_core {

template <typename T, typename Filter>
auto MapPipe(PipeReceiver<T> src, PipeSender<T> dst, Filter filter_factory) {
  return ForEach(
      std::move(src),
      [filter_factory = promise_detail::RepeatedPromiseFactory<T, Filter>(
           std::move(filter_factory)),
       dst = std::move(dst)](T t) mutable {
        return TrySeq(
            [] {
              GRPC_TRACE_VLOG(promise_primitives, 2) << "MapPipe: start map";
              return Empty{};
            },
            filter_factory.Make(std::move(t)),
            [&dst](T t) {
              GRPC_TRACE_VLOG(promise_primitives, 2) << "MapPipe: start push";
              return Map(dst.Push(std::move(t)), [](bool successful_push) {
                if (successful_push) {
                  return absl::OkStatus();
                }
                return absl::CancelledError();
              });
            });
      });
}

template <typename T>
class PipeMapper {
 public:
  static PipeMapper Intercept(PipeSender<T>& intercept_sender) {
    PipeMapper<T> r;
    r.interceptor_.sender.Swap(&intercept_sender);
    return r;
  }

  static PipeMapper Intercept(PipeReceiver<T>& intercept_receiver) {
    PipeMapper<T> r;
    r.interceptor_.receiver.Swap(&intercept_receiver);
    return r;
  }

  template <typename Filter>
  auto TakeAndRun(Filter filter) {
    return MapPipe(std::move(interceptor_.receiver),
                   std::move(interceptor_.sender), std::move(filter));
  }

 private:
  PipeMapper() = default;
  Pipe<T> interceptor_;
};

}

#endif
