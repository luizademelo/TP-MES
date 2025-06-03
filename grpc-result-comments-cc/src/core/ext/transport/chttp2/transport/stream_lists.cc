Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/stream_lists.h"

#include <grpc/support/port_platform.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/ext/transport/chttp2/transport/internal.h"
#include "src/core/ext/transport/chttp2/transport/legacy_frame.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/util/bitset.h"

// Returns a string representation of the stream list ID for logging purposes
static const char* stream_list_id_string(grpc_chttp2_stream_list_id id) {
  switch (id) {
    case GRPC_CHTTP2_LIST_WRITABLE:
      return "writable";
    case GRPC_CHTTP2_LIST_WRITING:
      return "writing";
    case GRPC_CHTTP2_LIST_STALLED_BY_TRANSPORT:
      return "stalled_by_transport";
    case GRPC_CHTTP2_LIST_STALLED_BY_STREAM:
      return "stalled_by_stream";
    case GRPC_CHTTP2_LIST_WAITING_FOR_CONCURRENCY:
      return "waiting_for_concurrency";
    case STREAM_LIST_COUNT:
      GPR_UNREACHABLE_CODE(return "unknown");
  }
  GPR_UNREACHABLE_CODE(return "unknown");
}

// Checks if a specific stream list is empty
static bool stream_list_empty(grpc_chttp2_transport* t,
                              grpc_chttp2_stream_list_id id) {
  return t->lists[id].head == nullptr;
}

// Removes and returns the head of the specified stream list
// Returns true if a stream was popped, false if the list was empty
static bool stream_list_pop(grpc_chttp2_transport* t,
                            grpc_chttp2_stream** stream,
                            grpc_chttp2_stream_list_id id) {
  grpc_chttp2_stream* s = t->lists[id].head;
  if (s) {
    grpc_chttp2_stream* new_head = s->links[id].next;
    CHECK(s->included.is_set(id));
    if (new_head) {
      t->lists[id].head = new_head;
      new_head->links[id].prev = nullptr;
    } else {
      t->lists[id].head = nullptr;
      t->lists[id].tail = nullptr;
    }
    s->included.clear(id);
  }
  *stream = s;
  if (s && GRPC_TRACE_FLAG_ENABLED(http2_stream_state)) {
    LOG(INFO) << t << "[" << s->id << "][" << (t->is_client ? "cli" : "svr")
              << "]: pop from " << stream_list_id_string(id);
  }
  return s != nullptr;
}

// Removes a specific stream from the specified list
static void stream_list_remove(grpc_chttp2_transport* t, grpc_chttp2_stream* s,
                               grpc_chttp2_stream_list_id id) {
  CHECK(s->included.is_set(id));
  s->included.clear(id);
  // Update previous node's next pointer
  if (s->links[id].prev) {
    s->links[id].prev->links[id].next = s->links[id].next;
  } else {
    CHECK(t->lists[id].head == s);
    t->lists[id].head = s->links[id].next;
  }
  // Update next node's previous pointer
  if (s->links[id].next) {
    s->links[id].next->links[id].prev = s->links[id].prev;
  } else {
    t->lists[id].tail = s->links[id].prev;
  }
  GRPC_TRACE_LOG(http2_stream_state, INFO)
      << t << "[" << s->id << "][" << (t->is_client ? "cli" : "svr")
      << "]: remove from " << stream_list_id_string(id);
}

// Removes a stream from a list if it exists in that list
// Returns true if the stream was removed, false if it wasn't in the list
static bool stream_list_maybe_remove(grpc_chttp2_transport* t,
                                     grpc_chttp2_stream* s,
                                     grpc_chttp2_stream_list_id id) {
  if (s->included.is_set(id)) {
    stream_list_remove(t, s, id);
    return true;
  } else {
    return false;
  }
}

// Adds a stream to the tail of the specified list
static void stream_list_add_tail(grpc_chttp2_transport* t,
                                 grpc_chttp2_stream* s,
                                 grpc_chttp2_stream_list_id id) {
  grpc_chttp2_stream* old_tail;
  CHECK(!s->included.is_set(id));
  old_tail = t->lists[id].tail;
  s->links[id].next = nullptr;
  s->links[id].prev = old_tail;
  if (old_tail) {
    old_tail->links[id].next = s;
  } else {
    t->lists[id].head = s;
  }
  t->lists[id].tail = s;
  s->included.set(id);
  GRPC_TRACE_LOG(http2_stream_state, INFO)
      << t << "[" << s->id << "][" << (t->is_client ? "cli" : "svr")
      << "]: add to " << stream_list_id_string(id);
}

// Adds a stream to a list if it's not already in that list
// Returns true if the stream was added, false if it was already in the list
static bool stream_list_add(grpc_chttp2_transport* t, grpc_chttp2_stream* s,
                            grpc_chttp2_stream_list_id id) {
  if (s->included.is_set(id)) {
    return false;
  }
  stream_list_add_tail(t, s, id);
  return true;
}

// Public API functions for specific stream list operations:

// Adds a stream to the writable list
bool grpc_chttp2_list_add_writable_stream(grpc_chttp2_transport* t,
                                          grpc_chttp2_stream* s) {
  CHECK_NE(s->id, 0u);
  return stream_list_add(t, s, GRPC_CHTTP2_LIST_WRITABLE);
}

// Pops a stream from the writable list
bool grpc_chttp2_list_pop_writable_stream(grpc_chttp2_transport* t,
                                          grpc_chttp2_stream** s) {
  return stream_list_pop(t, s, GRPC_CHTTP2_LIST_WRITABLE);
}

// Removes a stream from the writable list if present
bool grpc_chttp2_list_remove_writable_stream(grpc_chttp2_transport* t,
                                             grpc_chttp2_stream* s) {
  return stream_list_maybe_remove(t, s, GRPC_CHTTP2_LIST_WRITABLE);
}

// Adds a stream to the writing list
bool grpc_chttp2_list_add_writing_stream(grpc_chttp2_transport* t,
                                         grpc_chttp2_stream* s) {
  return stream_list_add(t, s, GRPC_CHTTP2_LIST_WRITING);
}

// Checks if there are any streams in the writing list
bool grpc_chttp2_list_have_writing_streams(grpc_chttp2_transport* t) {
  return !stream_list_empty(t, GRPC_CHTTP2_LIST_WRITING);
}

// Pops a stream from the writing list
bool grpc_chttp2_list_pop_writing_stream(grpc_chttp2_transport* t,
                                         grpc_chttp2_stream** s) {
  return stream_list_pop(t, s, GRPC_CHTTP2_LIST_WRITING);
}

// Adds a stream to the waiting for concurrency list
void grpc_chttp2_list_add_waiting_for_concurrency(grpc_chttp2_transport* t,
                                                  grpc_chttp2_stream* s) {
  stream_list_add(t, s, GRPC_CHTTP2_LIST_WAITING_FOR_CONCURRENCY);
}

// Pops a stream from the waiting for concurrency list
bool grpc_chttp2_list_pop_waiting_for_concurrency(grpc_chttp2_transport* t,
                                                  grpc_chttp2_stream** s) {
  return stream_list_pop(t, s, GRPC_CHTTP2_LIST_WAITING_FOR_CONCURRENCY);
}

// Removes a stream from the waiting for concurrency list if present
void grpc_chttp2_list_remove_waiting_for_concurrency(grpc_chttp2_transport* t,
                                                     grpc_chttp2_stream* s) {
  stream_list_maybe_remove(t, s, GRPC_CHTTP2_LIST_WAITING_FOR_CONCURRENCY);
}

// Adds a stream to the stalled by transport list
void grpc_chttp2_list_add_stalled_by_transport(grpc_chttp2_transport* t,
                                               grpc_chttp2_stream* s) {
  stream_list_add(t, s, GRPC_CHTTP2_LIST_STALLED_BY_TRANSPORT);
}

// Pops a stream from the stalled by transport list
bool grpc_chttp2_list_pop_stalled_by_transport(grpc_chttp2_transport* t,
                                               grpc_chttp2_stream** s) {
  return stream_list_pop(t, s, GRPC_CHTTP2_LIST_STALLED_BY_TRANSPORT);
}

// Removes a stream from the stalled by transport list if present
void grpc_chttp2_list_remove_stalled_by_transport(grpc_chttp2_transport* t,
                                                  grpc_chttp2_stream* s) {
  stream_list_maybe_remove(t, s, GRPC_CHTTP2_LIST_STALLED_BY_TRANSPORT);
}

// Adds a stream to the stalled by stream list
void grpc_chttp2_list_add_stalled_by_stream(grpc_chttp2_transport* t,
                                            grpc_chttp2_stream* s) {
  stream_list_add(t, s, GRPC_CHTTP2_LIST_STALLED_BY_STREAM);
}

// Pops a stream from the stalled by stream list
bool grpc_chttp2_list_pop_stalled_by_stream(grpc_chttp2_transport* t,
                                            grpc_chttp2_stream** s) {
  return stream_list_pop(t, s, GRPC_CHTTP2_LIST_STALLED_BY_STREAM);
}

// Removes a stream from the stalled by stream list if present
bool grpc_chttp2_list_remove_stalled_by_stream(grpc_chttp2_transport* t,
                                               grpc_chttp2_stream* s) {
  return stream_list_maybe_remove(t, s, GRPC_CHTTP2_LIST_STALLED_BY_STREAM);
}
```