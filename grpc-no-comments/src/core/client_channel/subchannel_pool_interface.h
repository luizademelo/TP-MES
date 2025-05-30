
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_CLIENT_CHANNEL_SUBCHANNEL_POOL_INTERFACE_H
#define GRPC_SRC_CORE_CLIENT_CHANNEL_SUBCHANNEL_POOL_INTERFACE_H

#include <grpc/support/port_platform.h>

#include <string>

#include "absl/strings/string_view.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/useful.h"

namespace grpc_core {

class Subchannel;

class SubchannelKey final {
 public:
  SubchannelKey(const grpc_resolved_address& address, const ChannelArgs& args);

  SubchannelKey(const SubchannelKey& other) = default;
  SubchannelKey& operator=(const SubchannelKey& other) = default;
  SubchannelKey(SubchannelKey&& other) noexcept = default;
  SubchannelKey& operator=(SubchannelKey&& other) noexcept = default;

  bool operator<(const SubchannelKey& other) const {
    return Compare(other) < 0;
  }
  bool operator>(const SubchannelKey& other) const {
    return Compare(other) > 0;
  }
  bool operator==(const SubchannelKey& other) const {
    return Compare(other) == 0;
  }

  int Compare(const SubchannelKey& other) const;

  const grpc_resolved_address& address() const { return address_; }
  const ChannelArgs& args() const { return args_; }

  std::string ToString() const;

 private:
  grpc_resolved_address address_;
  ChannelArgs args_;
};

class SubchannelPoolInterface : public RefCounted<SubchannelPoolInterface> {
 public:
  SubchannelPoolInterface()
      : RefCounted(GRPC_TRACE_FLAG_ENABLED(subchannel_pool)
                       ? "SubchannelPoolInterface"
                       : nullptr) {}
  ~SubchannelPoolInterface() override {}

  static absl::string_view ChannelArgName();
  static int ChannelArgsCompare(const SubchannelPoolInterface* a,
                                const SubchannelPoolInterface* b) {
    return QsortCompare(a, b);
  }

  virtual RefCountedPtr<Subchannel> RegisterSubchannel(
      const SubchannelKey& key, RefCountedPtr<Subchannel> constructed) = 0;

  virtual void UnregisterSubchannel(const SubchannelKey& key,
                                    Subchannel* subchannel) = 0;

  virtual RefCountedPtr<Subchannel> FindSubchannel(
      const SubchannelKey& key) = 0;
};

}

#endif
