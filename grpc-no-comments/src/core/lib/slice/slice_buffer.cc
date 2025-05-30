
// Copyright 2015 gRPC authors.

#include "src/core/lib/slice/slice_buffer.h"

#include <grpc/slice.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <string.h>

#include <utility>

#include "absl/log/check.h"
#include "src/core/lib/slice/slice_internal.h"

namespace grpc_core {

void SliceBuffer::Append(Slice slice) {
  grpc_slice_buffer_add(&slice_buffer_, slice.TakeCSlice());
}

void SliceBuffer::Append(const SliceBuffer& other) {
  for (size_t i = 0; i < other.Count(); i++) {
    Append(other.RefSlice(i));
  }
}

size_t SliceBuffer::AppendIndexed(Slice slice) {
  return grpc_slice_buffer_add_indexed(&slice_buffer_, slice.TakeCSlice());
}

Slice SliceBuffer::TakeFirst() {
  return Slice(grpc_slice_buffer_take_first(&slice_buffer_));
}

void SliceBuffer::Prepend(Slice slice) {
  grpc_slice_buffer_undo_take_first(&slice_buffer_, slice.TakeCSlice());
}

Slice SliceBuffer::RefSlice(size_t index) const {
  return Slice(CSliceRef(slice_buffer_.slices[index]));
}

std::string SliceBuffer::JoinIntoString() const {
  std::string result;
  result.reserve(slice_buffer_.length);
  for (size_t i = 0; i < slice_buffer_.count; i++) {
    result.append(reinterpret_cast<const char*>(
                      GRPC_SLICE_START_PTR(slice_buffer_.slices[i])),
                  GRPC_SLICE_LENGTH(slice_buffer_.slices[i]));
  }
  return result;
}

Slice SliceBuffer::JoinIntoSlice() const {
  if (slice_buffer_.count == 0) return Slice();
  if (slice_buffer_.count == 1) return RefSlice(0);
  grpc_slice slice = GRPC_SLICE_MALLOC(slice_buffer_.length);
  size_t ofs = 0;
  for (size_t i = 0; i < slice_buffer_.count; i++) {
    memcpy(GRPC_SLICE_START_PTR(slice) + ofs,
           GRPC_SLICE_START_PTR(slice_buffer_.slices[i]),
           GRPC_SLICE_LENGTH(slice_buffer_.slices[i]));
    ofs += GRPC_SLICE_LENGTH(slice_buffer_.slices[i]);
  }
  CHECK(ofs == slice_buffer_.length);
  return Slice(slice);
}

}

#define GROW(x) (3 * (x) / 2)

static void GPR_ATTRIBUTE_NOINLINE do_embiggen(grpc_slice_buffer* sb,
                                               const size_t slice_count,
                                               const size_t slice_offset) {
  if (slice_offset != 0) {

    memmove(sb->base_slices, sb->slices, sb->count * sizeof(grpc_slice));
    sb->slices = sb->base_slices;
  } else {

    const size_t new_capacity = GROW(sb->capacity);
    sb->capacity = new_capacity;
    if (sb->base_slices == sb->inlined) {
      sb->base_slices = static_cast<grpc_slice*>(
          gpr_malloc(new_capacity * sizeof(grpc_slice)));
      memcpy(sb->base_slices, sb->inlined, slice_count * sizeof(grpc_slice));
    } else {
      sb->base_slices = static_cast<grpc_slice*>(
          gpr_realloc(sb->base_slices, new_capacity * sizeof(grpc_slice)));
    }

    sb->slices = sb->base_slices + slice_offset;
  }
}

static void maybe_embiggen(grpc_slice_buffer* sb) {
  if (sb->count == 0) {
    sb->slices = sb->base_slices;
    return;
  }

  size_t slice_offset = static_cast<size_t>(sb->slices - sb->base_slices);
  size_t slice_count = sb->count + slice_offset;
  if (GPR_UNLIKELY(slice_count == sb->capacity)) {
    do_embiggen(sb, slice_count, slice_offset);
  }
}

void grpc_slice_buffer_init(grpc_slice_buffer* sb) {
  sb->count = 0;
  sb->length = 0;
  sb->capacity = GRPC_SLICE_BUFFER_INLINE_ELEMENTS;
  sb->base_slices = sb->slices = sb->inlined;
}

void grpc_slice_buffer_destroy(grpc_slice_buffer* sb) {
  grpc_slice_buffer_reset_and_unref(sb);
  if (sb->base_slices != sb->inlined) {
    gpr_free(sb->base_slices);

    sb->base_slices = sb->slices = sb->inlined;
  }
}

uint8_t* grpc_slice_buffer_tiny_add(grpc_slice_buffer* sb, size_t n) {
  grpc_slice* back;
  uint8_t* out;

  sb->length += n;

  if (sb->count == 0) goto add_first;
  back = &sb->slices[sb->count - 1];
  if (back->refcount) goto add_new;
  if ((back->data.inlined.length + n) > sizeof(back->data.inlined.bytes)) {
    goto add_new;
  }
  out = back->data.inlined.bytes + back->data.inlined.length;
  back->data.inlined.length =
      static_cast<uint8_t>(back->data.inlined.length + n);
  return out;

add_new:
  maybe_embiggen(sb);
add_first:
  back = &sb->slices[sb->count];
  sb->count++;
  back->refcount = nullptr;
  back->data.inlined.length = static_cast<uint8_t>(n);
  return back->data.inlined.bytes;
}

size_t grpc_slice_buffer_add_indexed(grpc_slice_buffer* sb, grpc_slice s) {
  size_t out = sb->count;
  maybe_embiggen(sb);
  sb->slices[out] = s;
  sb->length += GRPC_SLICE_LENGTH(s);
  sb->count = out + 1;
  return out;
}

void grpc_slice_buffer_add(grpc_slice_buffer* sb, grpc_slice s) {
  size_t n = sb->count;
  grpc_slice* back = nullptr;
  if (n != 0) {
    back = &sb->slices[n - 1];
  }
  if (s.refcount != nullptr && back != nullptr &&
      s.refcount == back->refcount &&
      GRPC_SLICE_START_PTR(s) == GRPC_SLICE_END_PTR(*back)) {

    back->data.refcounted.length += GRPC_SLICE_LENGTH(s);
    sb->length += GRPC_SLICE_LENGTH(s);

    grpc_core::CSliceUnref(s);

    return;
  }

  if (!s.refcount && n) {

    if (!back->refcount &&
        back->data.inlined.length < GRPC_SLICE_INLINED_SIZE) {
      if (s.data.inlined.length + back->data.inlined.length <=
          GRPC_SLICE_INLINED_SIZE) {
        memcpy(back->data.inlined.bytes + back->data.inlined.length,
               s.data.inlined.bytes, s.data.inlined.length);
        back->data.inlined.length = static_cast<uint8_t>(
            back->data.inlined.length + s.data.inlined.length);
      } else {
        size_t cp1 = GRPC_SLICE_INLINED_SIZE - back->data.inlined.length;
        memcpy(back->data.inlined.bytes + back->data.inlined.length,
               s.data.inlined.bytes, cp1);
        back->data.inlined.length = GRPC_SLICE_INLINED_SIZE;
        maybe_embiggen(sb);
        back = &sb->slices[n];
        sb->count = n + 1;
        back->refcount = nullptr;
        back->data.inlined.length =
            static_cast<uint8_t>(s.data.inlined.length - cp1);
        memcpy(back->data.inlined.bytes, s.data.inlined.bytes + cp1,
               s.data.inlined.length - cp1);
      }
      sb->length += s.data.inlined.length;
      return;
    }
  }
  grpc_slice_buffer_add_indexed(sb, s);
}

void grpc_slice_buffer_addn(grpc_slice_buffer* sb, grpc_slice* s, size_t n) {
  size_t i;
  for (i = 0; i < n; i++) {
    grpc_slice_buffer_add(sb, s[i]);
  }
}

void grpc_slice_buffer_pop(grpc_slice_buffer* sb) {
  if (sb->count != 0) {
    size_t count = --sb->count;
    sb->length -= GRPC_SLICE_LENGTH(sb->slices[count]);
  }
}

void grpc_slice_buffer_reset_and_unref(grpc_slice_buffer* sb) {
  size_t i;
  for (i = 0; i < sb->count; i++) {
    grpc_core::CSliceUnref(sb->slices[i]);
  }

  sb->count = 0;
  sb->length = 0;
  sb->slices = sb->base_slices;
}

void grpc_slice_buffer_swap(grpc_slice_buffer* a, grpc_slice_buffer* b) {
  size_t a_offset = static_cast<size_t>(a->slices - a->base_slices);
  size_t b_offset = static_cast<size_t>(b->slices - b->base_slices);

  size_t a_count = a->count + a_offset;
  size_t b_count = b->count + b_offset;

  if (a->base_slices == a->inlined) {
    if (b->base_slices == b->inlined) {

      grpc_slice temp[GRPC_SLICE_BUFFER_INLINE_ELEMENTS];
      memcpy(temp, a->base_slices, a_count * sizeof(grpc_slice));
      memcpy(a->base_slices, b->base_slices, b_count * sizeof(grpc_slice));
      memcpy(b->base_slices, temp, a_count * sizeof(grpc_slice));
    } else {

      a->base_slices = b->base_slices;
      b->base_slices = b->inlined;
      memcpy(b->base_slices, a->inlined, a_count * sizeof(grpc_slice));
    }
  } else if (b->base_slices == b->inlined) {

    b->base_slices = a->base_slices;
    a->base_slices = a->inlined;
    memcpy(a->base_slices, b->inlined, b_count * sizeof(grpc_slice));
  } else {

    std::swap(a->base_slices, b->base_slices);
  }

  a->slices = a->base_slices + b_offset;
  b->slices = b->base_slices + a_offset;

  std::swap(a->count, b->count);
  std::swap(a->capacity, b->capacity);
  std::swap(a->length, b->length);
}

void grpc_slice_buffer_move_into(grpc_slice_buffer* src,
                                 grpc_slice_buffer* dst) {

  if (src->count == 0) {
    return;
  }

  if (dst->count == 0) {
    grpc_slice_buffer_swap(src, dst);
    return;
  }

  grpc_slice_buffer_addn(dst, src->slices, src->count);
  src->count = 0;
  src->length = 0;
}

template <bool incref, bool allow_inline>
static void slice_buffer_move_first_maybe_ref(grpc_slice_buffer* src, size_t n,
                                              grpc_slice_buffer* dst) {
  if (n == 0) {
    return;
  }

  CHECK(src->length >= n);
  if (src->length == n) {
    grpc_slice_buffer_move_into(src, dst);
    return;
  }

  size_t output_len = dst->length + n;
  size_t new_input_len = src->length - n;

  while (src->count > 0) {
    grpc_slice slice = grpc_slice_buffer_take_first(src);
    size_t slice_len = GRPC_SLICE_LENGTH(slice);
    if (n > slice_len) {
      grpc_slice_buffer_add(dst, slice);
      n -= slice_len;
    } else if (n == slice_len) {
      grpc_slice_buffer_add(dst, slice);
      break;
    } else if (incref) {
      if (allow_inline) {
        grpc_slice_buffer_undo_take_first(
            src,
            grpc_slice_split_tail_maybe_ref(&slice, n, GRPC_SLICE_REF_BOTH));
      } else {
        grpc_slice_buffer_undo_take_first(
            src, grpc_slice_split_tail_maybe_ref_no_inline(
                     &slice, n, GRPC_SLICE_REF_BOTH));
      }
      CHECK(GRPC_SLICE_LENGTH(slice) == n);
      grpc_slice_buffer_add(dst, slice);
      break;
    } else {
      if (allow_inline) {
        grpc_slice_buffer_undo_take_first(
            src,
            grpc_slice_split_tail_maybe_ref(&slice, n, GRPC_SLICE_REF_TAIL));
      } else {
        grpc_slice_buffer_undo_take_first(
            src, grpc_slice_split_tail_maybe_ref_no_inline(
                     &slice, n, GRPC_SLICE_REF_TAIL));
      }
      CHECK(GRPC_SLICE_LENGTH(slice) == n);
      grpc_slice_buffer_add_indexed(dst, slice);
      break;
    }
  }
  CHECK(dst->length == output_len);
  CHECK(src->length == new_input_len);
  CHECK_GT(src->count, 0u);
}

void grpc_slice_buffer_move_first_no_inline(grpc_slice_buffer* src, size_t n,
                                            grpc_slice_buffer* dst) {
  slice_buffer_move_first_maybe_ref<true, false>(src, n, dst);
}

void grpc_slice_buffer_move_first(grpc_slice_buffer* src, size_t n,
                                  grpc_slice_buffer* dst) {
  slice_buffer_move_first_maybe_ref<true, true>(src, n, dst);
}

void grpc_slice_buffer_move_first_no_ref(grpc_slice_buffer* src, size_t n,
                                         grpc_slice_buffer* dst) {
  slice_buffer_move_first_maybe_ref<false, true>(src, n, dst);
}

void grpc_slice_buffer_move_first_into_buffer(grpc_slice_buffer* src, size_t n,
                                              void* dst) {
  char* dstp = static_cast<char*>(dst);
  CHECK(src->length >= n);

  while (n > 0) {
    grpc_slice slice = grpc_slice_buffer_take_first(src);
    size_t slice_len = GRPC_SLICE_LENGTH(slice);
    if (slice_len > n) {
      memcpy(dstp, GRPC_SLICE_START_PTR(slice), n);
      grpc_slice_buffer_undo_take_first(
          src, grpc_slice_sub_no_ref(slice, n, slice_len));
      n = 0;
    } else if (slice_len == n) {
      memcpy(dstp, GRPC_SLICE_START_PTR(slice), n);
      grpc_core::CSliceUnref(slice);
      n = 0;
    } else {
      memcpy(dstp, GRPC_SLICE_START_PTR(slice), slice_len);
      dstp += slice_len;
      n -= slice_len;
      grpc_core::CSliceUnref(slice);
    }
  }
}

void grpc_slice_buffer_copy_first_into_buffer(const grpc_slice_buffer* src,
                                              size_t n, void* dst) {
  uint8_t* dstp = static_cast<uint8_t*>(dst);
  CHECK(src->length >= n);

  for (size_t i = 0; i < src->count; i++) {
    grpc_slice slice = src->slices[i];
    size_t slice_len = GRPC_SLICE_LENGTH(slice);
    if (slice_len >= n) {
      memcpy(dstp, GRPC_SLICE_START_PTR(slice), n);
      return;
    }
    memcpy(dstp, GRPC_SLICE_START_PTR(slice), slice_len);
    dstp += slice_len;
    n -= slice_len;
  }
}
template <bool allow_inline>
void grpc_slice_buffer_trim_end_impl(grpc_slice_buffer* sb, size_t n,
                                     grpc_slice_buffer* garbage) {
  if (n == 0) return;
  CHECK(n <= sb->length);
  sb->length -= n;
  for (;;) {
    size_t idx = sb->count - 1;
    grpc_slice slice = sb->slices[idx];
    size_t slice_len = GRPC_SLICE_LENGTH(slice);
    if (slice_len > n) {
      if (allow_inline) {
        sb->slices[idx] = grpc_slice_split_head(&slice, slice_len - n);
      } else {
        sb->slices[idx] =
            grpc_slice_split_head_no_inline(&slice, slice_len - n);
      }
      if (garbage) {
        grpc_slice_buffer_add_indexed(garbage, slice);
      } else {
        grpc_core::CSliceUnref(slice);
      }
      return;
    } else if (slice_len == n) {
      if (garbage) {
        grpc_slice_buffer_add_indexed(garbage, slice);
      } else {
        grpc_core::CSliceUnref(slice);
      }
      sb->count = idx;
      return;
    } else {
      if (garbage) {
        grpc_slice_buffer_add_indexed(garbage, slice);
      } else {
        grpc_core::CSliceUnref(slice);
      }
      n -= slice_len;
      sb->count = idx;
    }
  }
}

void grpc_slice_buffer_trim_end_no_inline(grpc_slice_buffer* sb, size_t n,
                                          grpc_slice_buffer* garbage) {
  return grpc_slice_buffer_trim_end_impl<false>(sb, n, garbage);
}

void grpc_slice_buffer_trim_end(grpc_slice_buffer* sb, size_t n,
                                grpc_slice_buffer* garbage) {
  return grpc_slice_buffer_trim_end_impl<true>(sb, n, garbage);
}

grpc_slice grpc_slice_buffer_take_first(grpc_slice_buffer* sb) {
  grpc_slice slice;
  CHECK_GT(sb->count, 0u);
  slice = sb->slices[0];
  sb->slices++;
  sb->count--;
  sb->length -= GRPC_SLICE_LENGTH(slice);

  return slice;
}

void grpc_slice_buffer_remove_first(grpc_slice_buffer* sb) {
  DCHECK_GT(sb->count, 0u);
  sb->length -= GRPC_SLICE_LENGTH(sb->slices[0]);
  grpc_core::CSliceUnref(sb->slices[0]);
  sb->slices++;
  if (--sb->count == 0) {
    sb->slices = sb->base_slices;
  }
}

void grpc_slice_buffer_sub_first(grpc_slice_buffer* sb, size_t begin,
                                 size_t end) {

  sb->length -= GRPC_SLICE_LENGTH(sb->slices[0]);
  sb->slices[0] = grpc_slice_sub_no_ref(sb->slices[0], begin, end);
  sb->length += end - begin;
}

void grpc_slice_buffer_undo_take_first(grpc_slice_buffer* sb,
                                       grpc_slice slice) {
  sb->slices--;
  sb->slices[0] = slice;
  sb->count++;
  sb->length += GRPC_SLICE_LENGTH(slice);
}
