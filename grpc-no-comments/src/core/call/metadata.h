// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_CALL_METADATA_H
#define GRPC_SRC_CORE_CALL_METADATA_H

#include <grpc/support/port_platform.h>

#include "src/core/call/metadata_batch.h"
#include "src/core/lib/promise/try_seq.h"

namespace grpc_core {

using ServerMetadata = grpc_metadata_batch;
using ServerMetadataHandle = Arena::PoolPtr<ServerMetadata>;

using ClientMetadata = grpc_metadata_batch;
using ClientMetadataHandle = Arena::PoolPtr<ClientMetadata>;

template <typename T>
class ServerMetadataOrHandle {
 public:
  using ValueType = Arena::PoolPtr<T>;

  static ServerMetadataOrHandle Ok(ValueType value) {
    return ServerMetadataOrHandle{nullptr, std::move(value)};
  }
  static ServerMetadataOrHandle Failure(ServerMetadataHandle server_metadata) {
    return ServerMetadataOrHandle{std::move(server_metadata), nullptr};
  }

  bool ok() const { return server_metadata_ == nullptr; }
  ServerMetadataHandle& metadata() {
    CHECK(!ok());
    return server_metadata_;
  }
  ValueType& operator*() {
    CHECK(ok());
    return value_;
  }
  const ServerMetadataHandle& metadata() const {
    CHECK(!ok());
    return server_metadata_;
  }
  const ValueType& operator*() const {
    CHECK(ok());
    return value_;
  }

  ServerMetadataHandle TakeMetadata() && {
    CHECK(!ok());
    return std::move(server_metadata_);
  }

  ValueType TakeValue() && {
    CHECK(ok());
    return std::move(value_);
  }

 private:
  ServerMetadataOrHandle(ServerMetadataHandle server_metadata, ValueType value)
      : server_metadata_(std::move(server_metadata)),
        value_(std::move(value)) {}

  ServerMetadataHandle server_metadata_;
  ValueType value_;
};

template <typename T>
struct FailureStatusCastImpl<ServerMetadataOrHandle<T>, ServerMetadataHandle> {
  static ServerMetadataOrHandle<T> Cast(ServerMetadataHandle t) {
    return ServerMetadataOrHandle<T>::Failure(std::move(t));
  }
};

template <typename T>
struct FailureStatusCastImpl<ServerMetadataOrHandle<T>, ServerMetadataHandle&> {
  static ServerMetadataOrHandle<T> Cast(ServerMetadataHandle& t) {
    return ServerMetadataOrHandle<T>::Failure(std::move(t));
  }
};

template <>
struct FailureStatusCastImpl<ServerMetadataHandle, ServerMetadataHandle&> {
  static ServerMetadataHandle Cast(ServerMetadataHandle& t) {
    return std::move(t);
  }
};

template <typename T>
inline bool IsStatusOk(const ServerMetadataOrHandle<T>& x) {
  return x.ok();
}

namespace promise_detail {
template <typename T>
struct AllowGenericTrySeqTraits<ServerMetadataOrHandle<T>> {
  static constexpr bool value = false;
};
template <typename T>
struct TrySeqTraitsWithSfinae<ServerMetadataOrHandle<T>> {
  using UnwrappedType = Arena::PoolPtr<T>;
  using WrappedType = ServerMetadataOrHandle<T>;
  template <typename Next>
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static auto CallFactory(
      Next* next, ServerMetadataOrHandle<T>&& status) {
    return next->Make(std::move(*status));
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static bool IsOk(
      const ServerMetadataOrHandle<T>& status) {
    return status.ok();
  }
  static std::string ErrorString(const ServerMetadataOrHandle<T>& status) {
    return status.metadata()->DebugString();
  }
  template <typename R>
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static R ReturnValue(
      ServerMetadataOrHandle<T>&& status) {
    return FailureStatusCast<R>(status.metadata());
  }
};
}

template <typename Sink>
void AbslStringify(Sink& sink, const Arena::PoolPtr<grpc_metadata_batch>& md) {
  if (md == nullptr) {
    sink.Append("nullptr");
    return;
  }
  sink.Append("ServerMetadata{");
  sink.Append(md->DebugString());
  sink.Append("}");
}

inline bool IsStatusOk(const ServerMetadataHandle& m) {
  return m->get(GrpcStatusMetadata()).value_or(GRPC_STATUS_UNKNOWN) ==
         GRPC_STATUS_OK;
}

ServerMetadataHandle ServerMetadataFromStatus(const absl::Status& status);

ServerMetadataHandle CancelledServerMetadataFromStatus(
    const absl::Status& status);

inline ServerMetadataHandle ServerMetadataFromStatus(grpc_status_code code) {
  auto hdl = Arena::MakePooledForOverwrite<ServerMetadata>();
  hdl->Set(GrpcStatusMetadata(), code);
  return hdl;
}
inline ServerMetadataHandle CancelledServerMetadataFromStatus(
    grpc_status_code code) {
  auto hdl = Arena::MakePooledForOverwrite<ServerMetadata>();
  hdl->Set(GrpcStatusMetadata(), code);
  hdl->Set(GrpcCallWasCancelled(), true);
  return hdl;
}

ServerMetadataHandle ServerMetadataFromStatus(grpc_status_code code,
                                              absl::string_view message);
ServerMetadataHandle CancelledServerMetadataFromStatus(
    grpc_status_code code, absl::string_view message);

template <>
struct StatusCastImpl<ServerMetadataHandle, absl::Status> {
  static ServerMetadataHandle Cast(const absl::Status& m) {
    return ServerMetadataFromStatus(m);
  }
};

template <>
struct StatusCastImpl<ServerMetadataHandle, const absl::Status&> {
  static ServerMetadataHandle Cast(const absl::Status& m) {
    return ServerMetadataFromStatus(m);
  }
};

template <>
struct StatusCastImpl<ServerMetadataHandle, absl::Status&> {
  static ServerMetadataHandle Cast(const absl::Status& m) {
    return ServerMetadataFromStatus(m);
  }
};

template <typename T>
struct StatusCastImpl<
    ServerMetadataHandle, T,
    absl::void_t<decltype(&StatusCastImpl<absl::Status, T>::Cast)>> {
  static ServerMetadataHandle Cast(const T& m) {
    return ServerMetadataFromStatus(StatusCast<absl::Status>(m));
  }
};

}

#endif
