
// Copyright 2017 gRPC authors.

#include "src/core/channelz/channel_trace.h"

#include <grpc/support/alloc.h>
#include <grpc/support/json.h>
#include <grpc/support/port_platform.h>

#include <memory>
#include <utility>

#include "absl/strings/str_cat.h"
#include "src/core/channelz/channelz.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/string.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"

namespace grpc_core {
namespace channelz {

ChannelTrace::TraceEvent::TraceEvent(Severity severity, const grpc_slice& data,
                                     RefCountedPtr<BaseNode> referenced_entity)
    : timestamp_(Timestamp::Now().as_timespec(GPR_CLOCK_REALTIME)),
      severity_(severity),
      data_(data),
      memory_usage_(sizeof(TraceEvent) + grpc_slice_memory_usage(data)),
      referenced_entity_(std::move(referenced_entity)) {}

ChannelTrace::TraceEvent::TraceEvent(Severity severity, const grpc_slice& data)
    : TraceEvent(severity, data, nullptr) {}

ChannelTrace::TraceEvent::~TraceEvent() { CSliceUnref(data_); }

RefCountedPtr<BaseNode> ChannelTrace::TraceEvent::referenced_entity() const {
  return referenced_entity_;
}

ChannelTrace::ChannelTrace(size_t max_event_memory)
    : max_event_memory_(max_event_memory),
      time_created_(Timestamp::Now().as_timespec(GPR_CLOCK_REALTIME)) {}

ChannelTrace::~ChannelTrace() {
  if (max_event_memory_ == 0) {
    return;
  }
  TraceEvent* it = head_trace_;
  while (it != nullptr) {
    TraceEvent* to_free = it;
    it = it->next();
    delete to_free;
  }
}

void ChannelTrace::AddTraceEventHelper(TraceEvent* new_trace_event) {
  MutexLock lock(&mu_);
  ++num_events_logged_;

  if (head_trace_ == nullptr) {
    head_trace_ = tail_trace_ = new_trace_event;
  } else {

    tail_trace_->set_next(new_trace_event);
    tail_trace_ = tail_trace_->next();
  }
  event_list_memory_usage_ += new_trace_event->memory_usage();

  while (event_list_memory_usage_ > max_event_memory_) {
    TraceEvent* to_free = head_trace_;
    event_list_memory_usage_ -= to_free->memory_usage();
    head_trace_ = head_trace_->next();
    delete to_free;
  }
}

void ChannelTrace::AddTraceEvent(Severity severity, const grpc_slice& data) {
  if (max_event_memory_ == 0) {
    CSliceUnref(data);
    return;
  }
  AddTraceEventHelper(new TraceEvent(severity, data));
}

void ChannelTrace::AddTraceEventWithReference(
    Severity severity, const grpc_slice& data,
    RefCountedPtr<BaseNode> referenced_entity) {
  if (max_event_memory_ == 0) {
    CSliceUnref(data);
    return;
  }

  AddTraceEventHelper(
      new TraceEvent(severity, data, std::move(referenced_entity)));
}

std::string ChannelTrace::TraceEvent::description() const {
  char* description = grpc_slice_to_c_string(data_);
  std::string s(description);
  gpr_free(description);
  return s;
}

void ChannelTrace::ForEachTraceEventLocked(
    absl::FunctionRef<void(gpr_timespec, Severity, std::string,
                           RefCountedPtr<BaseNode>)>
        callback) const {
  TraceEvent* it = head_trace_;
  while (it != nullptr) {
    callback(it->timestamp(), it->severity(), it->description(),
             it->referenced_entity());
    it = it->next();
  }
}

Json ChannelTrace::RenderJson() const {

  if (max_event_memory_ == 0) {
    return Json();
  }
  Json::Object object = {
      {"creationTimestamp",
       Json::FromString(gpr_format_timespec(time_created_))},
  };
  MutexLock lock(&mu_);
  if (num_events_logged_ > 0) {
    object["numEventsLogged"] =
        Json::FromString(absl::StrCat(num_events_logged_));
  }

  Json::Array array;
  ForEachTraceEventLocked([&array](gpr_timespec timestamp, Severity severity,
                                   std::string description,
                                   RefCountedPtr<BaseNode> referenced_entity) {
    Json::Object object = {
        {"description", Json::FromString(description)},
        {"severity", Json::FromString(SeverityString(severity))},
        {"timestamp", Json::FromString(gpr_format_timespec(timestamp))},
    };
    if (referenced_entity != nullptr) {
      const bool is_channel =
          (referenced_entity->type() ==
               BaseNode::EntityType::kTopLevelChannel ||
           referenced_entity->type() == BaseNode::EntityType::kInternalChannel);
      object[is_channel ? "channelRef" : "subchannelRef"] = Json::FromObject({
          {(is_channel ? "channelId" : "subchannelId"),
           Json::FromString(absl::StrCat(referenced_entity->uuid()))},
      });
    }
    array.emplace_back(Json::FromObject(std::move(object)));
  });
  if (!array.empty()) {
    object["events"] = Json::FromArray(std::move(array));
  }
  return Json::FromObject(std::move(object));
}

std::string ChannelTrace::creation_timestamp() const {
  return gpr_format_timespec(time_created_);
}

}
}
