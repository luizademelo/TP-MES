// Copyright 2022 gRPC authors.

#include "src/core/lib/slice/slice.h"

#include <grpc/event_engine/slice.h>
#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <string>
#include <utility>

#include "absl/log/check.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/slice/slice_refcount.h"

namespace grpc_event_engine::experimental {

namespace slice_detail {

uint32_t BaseSlice::Hash() const { return grpc_slice_hash(slice_); }

template <>
MutableSlice CopyConstructors<MutableSlice>::FromCopiedString(std::string s) {
  return MutableSlice(grpc_slice_from_cpp_string(std::move(s)));
}

template <>
Slice CopyConstructors<Slice>::FromCopiedString(std::string s) {
  return Slice(grpc_slice_from_cpp_string(std::move(s)));
}

}

MutableSlice::MutableSlice(const grpc_slice& slice)
    : slice_detail::BaseSlice(slice) {
  DCHECK(slice.refcount == nullptr || slice.refcount->IsUnique());
}

MutableSlice::~MutableSlice() { grpc_core::CSliceUnref(c_slice()); }

Slice Slice::TakeOwned() {
  if (c_slice().refcount == nullptr) {
    return Slice(c_slice());
  }
  if (c_slice().refcount == grpc_slice_refcount::NoopRefcount()) {
    return Slice(grpc_slice_copy(c_slice()));
  }
  return Slice(TakeCSlice());
}

Slice Slice::AsOwned() const {
  if (c_slice().refcount == nullptr) {
    return Slice(c_slice());
  }
  if (c_slice().refcount == grpc_slice_refcount::NoopRefcount()) {
    return Slice(grpc_slice_copy(c_slice()));
  }
  return Slice(grpc_core::CSliceRef(c_slice()));
}

MutableSlice Slice::TakeMutable() {
  if (c_slice().refcount == nullptr) {
    return MutableSlice(c_slice());
  }
  if (c_slice().refcount != grpc_slice_refcount::NoopRefcount() &&
      c_slice().refcount->IsUnique()) {
    return MutableSlice(TakeCSlice());
  }
  return MutableSlice(grpc_slice_copy(c_slice()));
}

Slice::~Slice() { grpc_core::CSliceUnref(c_slice()); }

Slice Slice::Ref() const { return Slice(grpc_core::CSliceRef(c_slice())); }

Slice Slice::FromRefcountAndBytes(grpc_slice_refcount* r, const uint8_t* begin,
                                  const uint8_t* end) {
  grpc_slice out;
  out.refcount = r;
  if (r != grpc_slice_refcount::NoopRefcount()) r->Ref({});
  out.data.refcounted.bytes = const_cast<uint8_t*>(begin);
  out.data.refcounted.length = end - begin;
  return Slice(out);
}

}
