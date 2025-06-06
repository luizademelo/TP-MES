
// Copyright 2016 gRPC authors.

#include "src/core/handshaker/http_connect/http_proxy_mapper.h"

#include <grpc/impl/channel_arg_names.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>
#include <string.h>

#include <memory>
#include <optional>
#include <string>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/ascii.h"
#include "absl/strings/escaping.h"
#include "absl/strings/match.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"
#include "src/core/handshaker/http_connect/http_connect_handshaker.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/resolve_address.h"
#include "src/core/util/env.h"
#include "src/core/util/host_port.h"
#include "src/core/util/memory.h"
#include "src/core/util/string.h"
#include "src/core/util/uri.h"

namespace grpc_core {
namespace {

bool ServerInCIDRRange(const grpc_resolved_address& server_address,
                       absl::string_view cidr_range) {
  std::pair<absl::string_view, absl::string_view> possible_cidr =
      absl::StrSplit(cidr_range, absl::MaxSplits('/', 1), absl::SkipEmpty());
  if (possible_cidr.first.empty() || possible_cidr.second.empty()) {
    return false;
  }
  auto proxy_address = StringToSockaddr(possible_cidr.first, 0);
  if (!proxy_address.ok()) {
    return false;
  }
  uint32_t mask_bits = 0;
  if (absl::SimpleAtoi(possible_cidr.second, &mask_bits)) {
    grpc_sockaddr_mask_bits(&*proxy_address, mask_bits);
    return grpc_sockaddr_match_subnet(&server_address, &*proxy_address,
                                      mask_bits);
  }
  return false;
}

bool ExactMatchOrSubdomain(absl::string_view host_name,
                           absl::string_view host_name_or_domain) {
  return absl::EndsWithIgnoreCase(host_name, host_name_or_domain);
}

bool AddressIncluded(const std::optional<grpc_resolved_address>& target_address,
                     absl::string_view host_name,
                     absl::string_view addresses_and_subnets) {
  for (absl::string_view entry :
       absl::StrSplit(addresses_and_subnets, ',', absl::SkipEmpty())) {
    absl::string_view sanitized_entry = absl::StripAsciiWhitespace(entry);
    if (ExactMatchOrSubdomain(host_name, sanitized_entry) ||
        (target_address.has_value() &&
         ServerInCIDRRange(*target_address, sanitized_entry))) {
      return true;
    }
  }
  return false;
}

std::optional<std::string> GetHttpProxyServer(
    const ChannelArgs& args, std::optional<std::string>* user_cred) {
  CHECK_NE(user_cred, nullptr);
  absl::StatusOr<URI> uri;

  std::optional<std::string> uri_str = args.GetOwnedString(GRPC_ARG_HTTP_PROXY);
  if (!uri_str.has_value()) uri_str = GetEnv("grpc_proxy");
  if (!uri_str.has_value()) uri_str = GetEnv("https_proxy");
  if (!uri_str.has_value()) uri_str = GetEnv("http_proxy");
  if (!uri_str.has_value()) return std::nullopt;

  if (uri_str->empty()) return std::nullopt;
  uri = URI::Parse(*uri_str);
  if (!uri.ok() || uri->authority().empty()) {
    LOG(ERROR) << "cannot parse value of 'http_proxy' env var. Error: "
               << uri.status();
    return std::nullopt;
  }
  if (uri->scheme() != "http") {
    LOG(ERROR) << "'" << uri->scheme() << "' scheme not supported in proxy URI";
    return std::nullopt;
  }
  if (uri->host_port().empty()) {
    LOG(ERROR) << "host is not present in proxy URI";
    return std::nullopt;
  }
  if (!uri->user_info().empty()) {
    VLOG(2) << "userinfo found in proxy URI";
    *user_cred = uri->user_info();
  }
  return uri->host_port();
}

std::string MaybeAddDefaultPort(absl::string_view target) {
  absl::string_view host;
  absl::string_view port;
  SplitHostPort(target, &host, &port);
  if (port.empty()) {
    return JoinHostPort(host, kDefaultSecurePortInt);
  }
  return std::string(target);
}

std::optional<std::string> GetChannelArgOrEnvVarValue(
    const ChannelArgs& args, absl::string_view channel_arg,
    const char* env_var) {
  auto arg_value = args.GetOwnedString(channel_arg);
  if (arg_value.has_value()) {
    return arg_value;
  }
  return GetEnv(env_var);
}

std::optional<grpc_resolved_address> GetAddressProxyServer(
    const ChannelArgs& args) {
  auto address_value = GetChannelArgOrEnvVarValue(
      args, GRPC_ARG_ADDRESS_HTTP_PROXY, HttpProxyMapper::kAddressProxyEnvVar);
  if (!address_value.has_value()) {
    return std::nullopt;
  }
  auto address = StringToSockaddr(*address_value);
  if (!address.ok()) {
    LOG(ERROR) << "cannot parse value of '"
               << std::string(HttpProxyMapper::kAddressProxyEnvVar)
               << "' env var. Error: " << address.status().ToString();
    return std::nullopt;
  }
  return *address;
}

}

std::optional<std::string> HttpProxyMapper::MapName(
    absl::string_view server_uri, ChannelArgs* args) {
  if (!args->GetBool(GRPC_ARG_ENABLE_HTTP_PROXY).value_or(true)) {
    return std::nullopt;
  }
  std::optional<std::string> user_cred;
  auto name_to_resolve = GetHttpProxyServer(*args, &user_cred);
  if (!name_to_resolve.has_value()) return name_to_resolve;
  absl::StatusOr<URI> uri = URI::Parse(server_uri);
  if (!uri.ok() || uri->path().empty()) {
    LOG(ERROR) << "'http_proxy' environment variable set, but cannot "
                  "parse server URI '"
               << server_uri << "' -- not using proxy. Error: " << uri.status();
    return std::nullopt;
  }
  if (uri->scheme() == "unix") {
    VLOG(2) << "not using proxy for Unix domain socket '" << server_uri << "'";
    return std::nullopt;
  }
  if (uri->scheme() == "vsock") {
    VLOG(2) << "not using proxy for VSock '" << server_uri << "'";
    return std::nullopt;
  }

  auto no_proxy_str = GetEnv("no_grpc_proxy");
  if (!no_proxy_str.has_value()) {
    no_proxy_str = GetEnv("no_proxy");
  }
  if (no_proxy_str.has_value()) {
    std::string server_host;
    std::string server_port;
    if (!SplitHostPort(absl::StripPrefix(uri->path(), "/"), &server_host,
                       &server_port)) {
      VLOG(2) << "unable to split host and port, not checking no_proxy list "
                 "for host '"
              << server_uri << "'";
    } else {
      auto address = StringToSockaddr(server_host, 0);
      if (AddressIncluded(address.ok()
                              ? std::optional<grpc_resolved_address>(*address)
                              : std::nullopt,
                          server_host, *no_proxy_str)) {
        VLOG(2) << "not using proxy for host in no_proxy list '" << server_uri
                << "'";
        return std::nullopt;
      }
    }
  }
  *args = args->Set(GRPC_ARG_HTTP_CONNECT_SERVER,
                    MaybeAddDefaultPort(absl::StripPrefix(uri->path(), "/")));
  if (user_cred.has_value()) {

    std::string encoded_user_cred = absl::Base64Escape(*user_cred);
    *args = args->Set(
        GRPC_ARG_HTTP_CONNECT_HEADERS,
        absl::StrCat("Proxy-Authorization:Basic ", encoded_user_cred));
  }
  return name_to_resolve;
}

std::optional<grpc_resolved_address> HttpProxyMapper::MapAddress(
    const grpc_resolved_address& address, ChannelArgs* args) {
  auto proxy_address = GetAddressProxyServer(*args);
  if (!proxy_address.has_value()) {
    return std::nullopt;
  }
  auto address_string = grpc_sockaddr_to_string(&address, true);
  if (!address_string.ok()) {
    LOG(ERROR) << "Unable to convert address to string: "
               << address_string.status();
    return std::nullopt;
  }
  std::string host_name, port;
  if (!SplitHostPort(*address_string, &host_name, &port)) {
    LOG(ERROR) << "Address " << *address_string
               << " cannot be split in host and port";
    return std::nullopt;
  }
  auto enabled_addresses = GetChannelArgOrEnvVarValue(
      *args, GRPC_ARG_ADDRESS_HTTP_PROXY_ENABLED_ADDRESSES,
      kAddressProxyEnabledAddressesEnvVar);
  if (!enabled_addresses.has_value() ||
      !AddressIncluded(address, host_name, *enabled_addresses)) {
    return std::nullopt;
  }
  *args = args->Set(GRPC_ARG_HTTP_CONNECT_SERVER, *address_string);
  return proxy_address;
}

void RegisterHttpProxyMapper(CoreConfiguration::Builder* builder) {
  builder->proxy_mapper_registry()->Register(
      true ,
      std::unique_ptr<ProxyMapperInterface>(new HttpProxyMapper()));
}

}
