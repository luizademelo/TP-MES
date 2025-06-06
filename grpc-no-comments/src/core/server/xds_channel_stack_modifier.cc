
// Copyright 2021 gRPC authors.

#include "src/core/server/xds_channel_stack_modifier.h"

#include <grpc/support/port_platform.h>

#include <algorithm>
#include <initializer_list>
#include <string>

#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/surface/channel_init.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/util/useful.h"

namespace grpc_core {
namespace {

void* XdsChannelStackModifierArgCopy(void* p) {
  XdsChannelStackModifier* arg = static_cast<XdsChannelStackModifier*>(p);
  return arg->Ref().release();
}

void XdsChannelStackModifierArgDestroy(void* p) {
  XdsChannelStackModifier* arg = static_cast<XdsChannelStackModifier*>(p);
  arg->Unref();
}

int XdsChannelStackModifierArgCmp(void* p, void* q) {
  return QsortCompare(p, q);
}

const grpc_arg_pointer_vtable kChannelArgVtable = {
    XdsChannelStackModifierArgCopy, XdsChannelStackModifierArgDestroy,
    XdsChannelStackModifierArgCmp};

const char* kXdsChannelStackModifierChannelArgName =
    "grpc.internal.xds_channel_stack_modifier";

}

void XdsChannelStackModifier::ModifyChannelStack(ChannelStackBuilder& builder) {

  auto insert_before = builder.mutable_stack()->end();
  for (auto it = builder.mutable_stack()->begin();
       it != builder.mutable_stack()->end(); ++it) {
    for (absl::string_view predicate_name : {"server", "census_server"}) {
      if (predicate_name == (*it)->name.name()) insert_before = it + 1;
    }
  }
  for (const grpc_channel_filter* filter : filters_) {
    insert_before = builder.mutable_stack()->insert(insert_before, filter);
    ++insert_before;
  }
}

grpc_arg XdsChannelStackModifier::MakeChannelArg() const {
  return grpc_channel_arg_pointer_create(
      const_cast<char*>(kXdsChannelStackModifierChannelArgName),
      const_cast<XdsChannelStackModifier*>(this), &kChannelArgVtable);
}

absl::string_view XdsChannelStackModifier::ChannelArgName() {
  return kXdsChannelStackModifierChannelArgName;
}

RefCountedPtr<XdsChannelStackModifier>
XdsChannelStackModifier::GetFromChannelArgs(const grpc_channel_args& args) {
  XdsChannelStackModifier* config_selector_provider =
      grpc_channel_args_find_pointer<XdsChannelStackModifier>(
          &args, kXdsChannelStackModifierChannelArgName);
  return config_selector_provider != nullptr ? config_selector_provider->Ref()
                                             : nullptr;
}

void RegisterXdsChannelStackModifier(CoreConfiguration::Builder* builder) {
  builder->channel_init()->RegisterPostProcessor(
      GRPC_SERVER_CHANNEL,
      ChannelInit::PostProcessorSlot::kXdsChannelStackModifier,
      [](ChannelStackBuilder& builder) {
        auto channel_stack_modifier =
            builder.channel_args().GetObjectRef<XdsChannelStackModifier>();
        if (channel_stack_modifier != nullptr) {
          return channel_stack_modifier->ModifyChannelStack(builder);
        }
      });
}

}
