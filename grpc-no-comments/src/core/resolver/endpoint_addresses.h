
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_RESOLVER_ENDPOINT_ADDRESSES_H
#define GRPC_SRC_CORE_RESOLVER_ENDPOINT_ADDRESSES_H

#include <grpc/support/port_platform.h>

#include <set>
#include <string>
#include <utility>
#include <vector>

#include "absl/functional/function_ref.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/resolved_address.h"

#define GRPC_ARG_NO_SUBCHANNEL_PREFIX "grpc.internal.no_subchannel."

#define GRPC_ARG_ADDRESS_WEIGHT GRPC_ARG_NO_SUBCHANNEL_PREFIX "address.weight"

#define GRPC_ARG_ADDRESS_NAME "grpc.address_name"

namespace grpc_core {

class EndpointAddresses final {
 public:

  EndpointAddresses(const grpc_resolved_address& address,
                    const ChannelArgs& args);

  EndpointAddresses(std::vector<grpc_resolved_address> addresses,
                    const ChannelArgs& args);

  EndpointAddresses(const EndpointAddresses& other);
  EndpointAddresses& operator=(const EndpointAddresses& other);

  EndpointAddresses(EndpointAddresses&& other) noexcept;
  EndpointAddresses& operator=(EndpointAddresses&& other) noexcept;

  bool operator==(const EndpointAddresses& other) const {
    return Cmp(other) == 0;
  }
  bool operator!=(const EndpointAddresses& other) const {
    return Cmp(other) != 0;
  }
  bool operator<(const EndpointAddresses& other) const {
    return Cmp(other) < 0;
  }

  int Cmp(const EndpointAddresses& other) const;

  const grpc_resolved_address& address() const { return addresses_[0]; }

  const std::vector<grpc_resolved_address>& addresses() const {
    return addresses_;
  }
  const ChannelArgs& args() const { return args_; }

  std::string ToString() const;

 private:
  std::vector<grpc_resolved_address> addresses_;
  ChannelArgs args_;
};

using EndpointAddressesList = std::vector<EndpointAddresses>;

struct ResolvedAddressLessThan {
  bool operator()(const grpc_resolved_address& addr1,
                  const grpc_resolved_address& addr2) const;
};

class EndpointAddressSet final {
 public:
  explicit EndpointAddressSet(
      const std::vector<grpc_resolved_address>& addresses)
      : addresses_(addresses.begin(), addresses.end()) {}

  bool operator==(const EndpointAddressSet& other) const;
  bool operator<(const EndpointAddressSet& other) const;

  std::string ToString() const;

 private:
  std::set<grpc_resolved_address, ResolvedAddressLessThan> addresses_;
};

class EndpointAddressesIterator {
 public:
  virtual ~EndpointAddressesIterator() = default;

  virtual void ForEach(
      absl::FunctionRef<void(const EndpointAddresses&)> callback) const = 0;
};

class EndpointAddressesListIterator final : public EndpointAddressesIterator {
 public:
  explicit EndpointAddressesListIterator(EndpointAddressesList endpoints)
      : endpoints_(std::move(endpoints)) {}

  void ForEach(absl::FunctionRef<void(const EndpointAddresses&)> callback)
      const override {
    for (const auto& endpoint : endpoints_) {
      callback(endpoint);
    }
  }

 private:
  EndpointAddressesList endpoints_;
};

class SingleEndpointIterator final : public EndpointAddressesIterator {
 public:
  explicit SingleEndpointIterator(EndpointAddresses endpoint)
      : endpoint_(std::move(endpoint)) {}

  void ForEach(absl::FunctionRef<void(const EndpointAddresses&)> callback)
      const override {
    callback(endpoint_);
  }

 private:
  EndpointAddresses endpoint_;
};

}

#endif
