
// Copyright 2018 gRPC authors.

#include "src/core/resolver/endpoint_addresses.h"

#include <grpc/support/port_platform.h>
#include <string.h>

#include <string>
#include <utility>
#include <vector>

#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/useful.h"

namespace grpc_core {

EndpointAddresses::EndpointAddresses(const grpc_resolved_address& address,
                                     const ChannelArgs& args)
    : addresses_(1, address), args_(args) {}

EndpointAddresses::EndpointAddresses(
    std::vector<grpc_resolved_address> addresses, const ChannelArgs& args)
    : addresses_(std::move(addresses)), args_(args) {
  CHECK(!addresses_.empty());
}

EndpointAddresses::EndpointAddresses(const EndpointAddresses& other)
    : addresses_(other.addresses_), args_(other.args_) {}

EndpointAddresses& EndpointAddresses::operator=(
    const EndpointAddresses& other) {
  if (&other == this) return *this;
  addresses_ = other.addresses_;
  args_ = other.args_;
  return *this;
}

EndpointAddresses::EndpointAddresses(EndpointAddresses&& other) noexcept
    : addresses_(std::move(other.addresses_)), args_(std::move(other.args_)) {}

EndpointAddresses& EndpointAddresses::operator=(
    EndpointAddresses&& other) noexcept {
  addresses_ = std::move(other.addresses_);
  args_ = std::move(other.args_);
  return *this;
}

int EndpointAddresses::Cmp(const EndpointAddresses& other) const {
  for (size_t i = 0; i < addresses_.size(); ++i) {
    if (other.addresses_.size() == i) return 1;
    if (addresses_[i].len > other.addresses_[i].len) return 1;
    if (addresses_[i].len < other.addresses_[i].len) return -1;
    int retval =
        memcmp(addresses_[i].addr, other.addresses_[i].addr, addresses_[i].len);
    if (retval != 0) return retval;
  }
  if (other.addresses_.size() > addresses_.size()) return -1;
  return QsortCompare(args_, other.args_);
}

std::string EndpointAddresses::ToString() const {
  std::vector<std::string> addr_strings;
  for (const auto& address : addresses_) {
    auto addr_str = grpc_sockaddr_to_string(&address, false);
    addr_strings.push_back(addr_str.ok() ? std::move(*addr_str)
                                         : addr_str.status().ToString());
  }
  std::vector<std::string> parts = {
      absl::StrCat("addrs=[", absl::StrJoin(addr_strings, ", "), "]")};
  if (args_ != ChannelArgs()) {
    parts.emplace_back(absl::StrCat("args=", args_.ToString()));
  }
  return absl::StrJoin(parts, " ");
}

bool ResolvedAddressLessThan::operator()(
    const grpc_resolved_address& addr1,
    const grpc_resolved_address& addr2) const {
  if (addr1.len < addr2.len) return true;
  return memcmp(addr1.addr, addr2.addr, addr1.len) < 0;
}

bool EndpointAddressSet::operator==(const EndpointAddressSet& other) const {
  if (addresses_.size() != other.addresses_.size()) return false;
  auto other_it = other.addresses_.begin();
  for (auto it = addresses_.begin(); it != addresses_.end(); ++it) {
    CHECK(other_it != other.addresses_.end());
    if (it->len != other_it->len ||
        memcmp(it->addr, other_it->addr, it->len) != 0) {
      return false;
    }
    ++other_it;
  }
  return true;
}

bool EndpointAddressSet::operator<(const EndpointAddressSet& other) const {
  auto other_it = other.addresses_.begin();
  for (auto it = addresses_.begin(); it != addresses_.end(); ++it) {
    if (other_it == other.addresses_.end()) return false;
    if (it->len < other_it->len) return true;
    if (it->len > other_it->len) return false;
    int r = memcmp(it->addr, other_it->addr, it->len);
    if (r != 0) return r < 0;
    ++other_it;
  }
  return other_it != other.addresses_.end();
}

std::string EndpointAddressSet::ToString() const {
  std::vector<std::string> parts;
  parts.reserve(addresses_.size());
  for (const auto& address : addresses_) {
    parts.push_back(
        grpc_sockaddr_to_string(&address, false).value_or("<unknown>"));
  }
  return absl::StrCat("{", absl::StrJoin(parts, ", "), "}");
}

}
