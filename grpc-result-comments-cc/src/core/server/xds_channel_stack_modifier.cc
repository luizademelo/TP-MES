Here's the commented version of the code:

```c++
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

// Copies an XdsChannelStackModifier argument for channel args
void* XdsChannelStackModifierArgCopy(void* p) {
  XdsChannelStackModifier* arg = static_cast<XdsChannelStackModifier*>(p);
  return arg->Ref().release();
}

// Destroys an XdsChannelStackModifier argument for channel args
void XdsChannelStackModifierArgDestroy(void* p) {
  XdsChannelStackModifier* arg = static_cast<XdsChannelStackModifier*>(p);
  arg->Unref();
}

// Compares two XdsChannelStackModifier arguments for channel args
int XdsChannelStackModifierArgCmp(void* p, void* q) {
  return QsortCompare(p, q);
}

// Vtable for managing XdsChannelStackModifier in channel args
const grpc_arg_pointer_vtable kChannelArgVtable = {
    XdsChannelStackModifierArgCopy, XdsChannelStackModifierArgDestroy,
    XdsChannelStackModifierArgCmp};

// Channel argument name for XdsChannelStackModifier
const char* kXdsChannelStackModifierChannelArgName =
    "grpc.internal.xds_channel_stack_modifier";

}  // namespace

// Modifies the channel stack by inserting filters at specific positions
void XdsChannelStackModifier::ModifyChannelStack(ChannelStackBuilder& builder) {
  // Find the position to insert filters after certain existing filters
  auto insert_before = builder.mutable_stack()->end();
  for (auto it = builder.mutable_stack()->begin();
       it != builder.mutable_stack()->end(); ++it) {
    // Look for either "server" or "census_server" filters
    for (absl::string_view predicate_name : {"server", "census_server"}) {
      if (predicate_name == (*it)->name.name()) insert_before = it + 1;
    }
  }
  // Insert all configured filters at the found position
  for (const grpc_channel_filter* filter : filters_) {
    insert_before = builder.mutable_stack()->insert(insert_before, filter);
    ++insert_before;
  }
}

// Creates a channel argument containing this XdsChannelStackModifier
grpc_arg XdsChannelStackModifier::MakeChannelArg() const {
  return grpc_channel_arg_pointer_create(
      const_cast<char*>(kXdsChannelStackModifierChannelArgName),
      const_cast<XdsChannelStackModifier*>(this), &kChannelArgVtable);
}

// Returns the channel argument name used for XdsChannelStackModifier
absl::string_view XdsChannelStackModifier::ChannelArgName() {
  return kXdsChannelStackModifierChannelArgName;
}

// Retrieves the XdsChannelStackModifier from channel arguments if present
RefCountedPtr<XdsChannelStackModifier>
XdsChannelStackModifier::GetFromChannelArgs(const grpc_channel_args& args) {
  XdsChannelStackModifier* config_selector_provider =
      grpc_channel_args_find_pointer<XdsChannelStackModifier>(
          &args, kXdsChannelStackModifierChannelArgName);
  return config_selector_provider != nullptr ? config_selector_provider->Ref()
                                             : nullptr;
}

// Registers the XdsChannelStackModifier post-processor with core configuration
void RegisterXdsChannelStackModifier(CoreConfiguration::Builder* builder) {
  builder->channel_init()->RegisterPostProcessor(
      GRPC_SERVER_CHANNEL,
      ChannelInit::PostProcessorSlot::kXdsChannelStackModifier,
      [](ChannelStackBuilder& builder) {
        // Get the XdsChannelStackModifier from channel args if present
        auto channel_stack_modifier =
            builder.channel_args().GetObjectRef<XdsChannelStackModifier>();
        if (channel_stack_modifier != nullptr) {
          // Modify the channel stack if we have a modifier
          return channel_stack_modifier->ModifyChannelStack(builder);
        }
      });
}

}  // namespace grpc_core
```

The comments explain:
1. The purpose of each function and important blocks of code
2. The channel argument management functions (copy, destroy, compare)
3. The filter insertion logic in ModifyChannelStack
4. The registration process for the channel stack modifier
5. Key operations like getting the modifier from channel args
6. The overall purpose of the XdsChannelStackModifier class

The comments are concise but provide enough context to understand what each part does and why it's important. I've maintained the original code structure while adding explanatory comments where they're most helpful for maintenance.