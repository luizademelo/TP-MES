
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_CHANNEL_CHANNEL_STACK_H
#define GRPC_SRC_CORE_LIB_CHANNEL_CHANNEL_STACK_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <grpc/slice.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>
#include <stddef.h>

#include <functional>
#include <memory>

#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/call_combiner.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/polling_entity.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/transport/call_final_info.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/telemetry/metrics.h"
#include "src/core/util/manual_constructor.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/time.h"
#include "src/core/util/time_precise.h"
#include "src/core/util/unique_type_name.h"

namespace grpc_core {
class Blackboard;
}

struct grpc_channel_element_args {
  grpc_channel_stack* channel_stack;
  grpc_core::ChannelArgs channel_args;
  int is_first;
  int is_last;
  const grpc_core::Blackboard* old_blackboard;
  grpc_core::Blackboard* new_blackboard;
};
struct grpc_call_element_args {
  grpc_call_stack* call_stack;
  const void* server_transport_data;
  gpr_cycle_counter start_time;  // Note: not populated in subchannel stack.
  grpc_core::Timestamp deadline;
  grpc_core::Arena* arena;
  grpc_core::CallCombiner* call_combiner;
};

struct grpc_channel_filter {

  void (*start_transport_stream_op_batch)(grpc_call_element* elem,
                                          grpc_transport_stream_op_batch* op);

  void (*start_transport_op)(grpc_channel_element* elem, grpc_transport_op* op);

  size_t sizeof_call_data;

  grpc_error_handle (*init_call_elem)(grpc_call_element* elem,
                                      const grpc_call_element_args* args);
  void (*set_pollset_or_pollset_set)(grpc_call_element* elem,
                                     grpc_polling_entity* pollent);

  void (*destroy_call_elem)(grpc_call_element* elem,
                            const grpc_call_final_info* final_info,
                            grpc_closure* then_schedule_closure);

  size_t sizeof_channel_data;

  grpc_error_handle (*init_channel_elem)(grpc_channel_element* elem,
                                         grpc_channel_element_args* args);

  void (*post_init_channel_elem)(grpc_channel_stack* stk,
                                 grpc_channel_element* elem);

  void (*destroy_channel_elem)(grpc_channel_element* elem);

  void (*get_channel_info)(grpc_channel_element* elem,
                           const grpc_channel_info* channel_info);

  grpc_core::UniqueTypeName name;
};

struct grpc_channel_element {
  const grpc_channel_filter* filter;
  void* channel_data;
};

struct grpc_call_element {
  const grpc_channel_filter* filter;
  void* channel_data;
  void* call_data;
};

struct grpc_channel_stack {
  grpc_stream_refcount refcount;
  size_t count;

  size_t call_stack_size;

  grpc_core::ManualConstructor<std::function<void()>> on_destroy;

  class ChannelStackDataSource final : public grpc_core::channelz::DataSource {
   public:
    using grpc_core::channelz::DataSource::DataSource;
    ~ChannelStackDataSource() { ResetDataSource(); }
    void AddData(grpc_core::channelz::DataSink sink) override;
  };

  grpc_core::ManualConstructor<ChannelStackDataSource> channelz_data_source;

  grpc_core::ManualConstructor<
      std::shared_ptr<grpc_event_engine::experimental::EventEngine>>
      event_engine;

  grpc_event_engine::experimental::EventEngine* EventEngine() const {
    return event_engine->get();
  }

  grpc_core::ManualConstructor<
      std::shared_ptr<grpc_core::GlobalStatsPluginRegistry::StatsPluginGroup>>
      stats_plugin_group;

  void IncrementRefCount();
  void Unref();
  void Unref(const grpc_core::DebugLocation& location, const char* reason);
  grpc_core::RefCountedPtr<grpc_channel_stack> Ref() {
    IncrementRefCount();
    return grpc_core::RefCountedPtr<grpc_channel_stack>(this);
  }
};

struct grpc_call_stack {

  grpc_stream_refcount refcount;
  size_t count;

  void IncrementRefCount();
  void Unref();
  grpc_core::RefCountedPtr<grpc_call_stack> Ref() {
    IncrementRefCount();
    return grpc_core::RefCountedPtr<grpc_call_stack>(this);
  }
};

grpc_channel_element* grpc_channel_stack_element(grpc_channel_stack* stack,
                                                 size_t i);

grpc_channel_element* grpc_channel_stack_last_element(
    grpc_channel_stack* stack);

size_t grpc_channel_stack_filter_instance_number(
    grpc_channel_stack* channel_stack, grpc_channel_element* elem);

grpc_call_element* grpc_call_stack_element(grpc_call_stack* stack, size_t i);

size_t grpc_channel_stack_size(const grpc_channel_filter** filters,
                               size_t filter_count);

grpc_error_handle grpc_channel_stack_init(
    int initial_refs, grpc_iomgr_cb_func destroy, void* destroy_arg,
    const grpc_channel_filter** filters, size_t filter_count,
    const grpc_core::ChannelArgs& args, const char* name,
    grpc_channel_stack* stack,
    const grpc_core::Blackboard* old_blackboard = nullptr,
    grpc_core::Blackboard* new_blackboard = nullptr);

void grpc_channel_stack_destroy(grpc_channel_stack* stack);

grpc_error_handle grpc_call_stack_init(grpc_channel_stack* channel_stack,
                                       int initial_refs,
                                       grpc_iomgr_cb_func destroy,
                                       void* destroy_arg,
                                       const grpc_call_element_args* elem_args);

void grpc_call_stack_set_pollset_or_pollset_set(grpc_call_stack* call_stack,
                                                grpc_polling_entity* pollent);

#ifndef NDEBUG
#define GRPC_CALL_STACK_REF(call_stack, reason) \
  grpc_stream_ref(&(call_stack)->refcount, reason)
#define GRPC_CALL_STACK_UNREF(call_stack, reason) \
  grpc_stream_unref(&(call_stack)->refcount, reason)
#define GRPC_CHANNEL_STACK_REF(channel_stack, reason) \
  grpc_stream_ref(&(channel_stack)->refcount, reason)
#define GRPC_CHANNEL_STACK_UNREF(channel_stack, reason) \
  grpc_stream_unref(&(channel_stack)->refcount, reason)
#else
#define GRPC_CALL_STACK_REF(call_stack, reason) \
  do {                                          \
    grpc_stream_ref(&(call_stack)->refcount);   \
    (void)(reason);                             \
  } while (0);
#define GRPC_CALL_STACK_UNREF(call_stack, reason) \
  do {                                            \
    grpc_stream_unref(&(call_stack)->refcount);   \
    (void)(reason);                               \
  } while (0);
#define GRPC_CHANNEL_STACK_REF(channel_stack, reason) \
  do {                                                \
    grpc_stream_ref(&(channel_stack)->refcount);      \
    (void)(reason);                                   \
  } while (0);
#define GRPC_CHANNEL_STACK_UNREF(channel_stack, reason) \
  do {                                                  \
    grpc_stream_unref(&(channel_stack)->refcount);      \
    (void)(reason);                                     \
  } while (0);
#endif

inline void grpc_channel_stack::IncrementRefCount() {
  GRPC_CHANNEL_STACK_REF(this, "smart_pointer");
}

inline void grpc_channel_stack::Unref() {
  GRPC_CHANNEL_STACK_UNREF(this, "smart_pointer");
}

inline void grpc_channel_stack::Unref(const grpc_core::DebugLocation&,
                                      const char* reason) {
  GRPC_CHANNEL_STACK_UNREF(this, reason);
}

inline void grpc_call_stack::IncrementRefCount() {
  GRPC_CALL_STACK_REF(this, "smart_pointer");
}

inline void grpc_call_stack::Unref() {
  GRPC_CALL_STACK_UNREF(this, "smart_pointer");
}

void grpc_call_stack_destroy(grpc_call_stack* stack,
                             const grpc_call_final_info* final_info,
                             grpc_closure* then_schedule_closure);

void grpc_call_stack_ignore_set_pollset_or_pollset_set(
    grpc_call_element* elem, grpc_polling_entity* pollent);

void grpc_call_next_op(grpc_call_element* elem,
                       grpc_transport_stream_op_batch* op);

void grpc_channel_next_op(grpc_channel_element* elem, grpc_transport_op* op);

void grpc_channel_next_get_info(grpc_channel_element* elem,
                                const grpc_channel_info* channel_info);

grpc_channel_stack* grpc_channel_stack_from_top_element(
    grpc_channel_element* elem);

grpc_call_stack* grpc_call_stack_from_top_element(grpc_call_element* elem);

void grpc_channel_stack_no_post_init(grpc_channel_stack* stk,
                                     grpc_channel_element* elem);

#endif
