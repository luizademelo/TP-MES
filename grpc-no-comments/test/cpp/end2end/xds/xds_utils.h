// Copyright 2017 gRPC authors.

#ifndef GRPC_TEST_CPP_END2END_XDS_XDS_UTILS_H
#define GRPC_TEST_CPP_END2END_XDS_XDS_UTILS_H

#include <string>
#include <vector>

#include "absl/strings/string_view.h"
#include "envoy/config/cluster/v3/cluster.pb.h"
#include "envoy/config/endpoint/v3/endpoint.pb.h"
#include "envoy/config/listener/v3/listener.pb.h"
#include "envoy/config/route/v3/route.pb.h"
#include "envoy/extensions/filters/network/http_connection_manager/v3/http_connection_manager.pb.h"
#include "test/cpp/end2end/xds/xds_server.h"

namespace grpc {
namespace testing {

class XdsBootstrapBuilder {
 public:
  XdsBootstrapBuilder() {}
  XdsBootstrapBuilder& SetIgnoreResourceDeletion() {
    ignore_resource_deletion_ = true;
    return *this;
  }
  XdsBootstrapBuilder& SetFailOnDataErrors() {
    fail_on_data_errors_ = true;
    return *this;
  }
  XdsBootstrapBuilder& SetTrustedXdsServer() {
    trusted_xds_server_ = true;
    return *this;
  }
  XdsBootstrapBuilder& SetServers(absl::Span<const absl::string_view> servers) {
    servers_ = std::vector<std::string>(servers.begin(), servers.end());
    return *this;
  }
  XdsBootstrapBuilder& SetXdsChannelCredentials(
      const std::string& type, const std::string& config = "") {
    xds_channel_creds_type_ = type;
    xds_channel_creds_config_ = config;
    return *this;
  }
  XdsBootstrapBuilder& SetClientDefaultListenerResourceNameTemplate(
      const std::string& client_default_listener_resource_name_template) {
    client_default_listener_resource_name_template_ =
        client_default_listener_resource_name_template;
    return *this;
  }
  XdsBootstrapBuilder& AddCertificateProviderPlugin(
      const std::string& key, const std::string& name,
      const std::string& plugin_config = "") {
    plugins_[key] = {name, plugin_config};
    return *this;
  }
  XdsBootstrapBuilder& AddAuthority(
      const std::string& authority, const std::string& server = "",
      const std::string& client_listener_resource_name_template = "") {
    return AddAuthority(authority,
                        server.empty() ? std::vector<std::string>()
                                       : std::vector<std::string>({server}),
                        client_listener_resource_name_template);
  }
  XdsBootstrapBuilder& AddAuthority(
      const std::string& authority, const std::vector<std::string>& servers,
      const std::string& client_listener_resource_name_template = "") {
    authorities_[authority] = {servers, client_listener_resource_name_template};
    return *this;
  }
  XdsBootstrapBuilder& SetServerListenerResourceNameTemplate(
      const std::string& server_listener_resource_name_template = "") {
    server_listener_resource_name_template_ =
        server_listener_resource_name_template;
    return *this;
  }

  std::string Build();

 private:
  struct PluginInfo {
    std::string name;
    std::string plugin_config;
  };
  struct AuthorityInfo {
    std::vector<std::string> servers;
    std::string client_listener_resource_name_template;
  };

  std::string MakeXdsServersText(absl::Span<const std::string> server_uris);
  std::string MakeNodeText();
  std::string MakeCertificateProviderText();
  std::string MakeAuthorityText();

  bool ignore_resource_deletion_ = false;
  bool fail_on_data_errors_ = false;
  bool trusted_xds_server_ = false;
  std::vector<std::string> servers_;
  std::string xds_channel_creds_type_ = "fake";
  std::string xds_channel_creds_config_;
  std::string client_default_listener_resource_name_template_;
  std::map<std::string , PluginInfo> plugins_;
  std::map<std::string , AuthorityInfo> authorities_;
  std::string server_listener_resource_name_template_ =
      "grpc/server?xds.resource.listening_address=%s";
};

class XdsResourceUtils {
 public:
  using HttpConnectionManager = envoy::extensions::filters::network::
      http_connection_manager::v3::HttpConnectionManager;
  using Listener = envoy::config::listener::v3::Listener;
  using RouteConfiguration = envoy::config::route::v3::RouteConfiguration;
  using Cluster = envoy::config::cluster::v3::Cluster;
  using ClusterLoadAssignment =
      envoy::config::endpoint::v3::ClusterLoadAssignment;

  class HcmAccessor {
   public:
    virtual ~HcmAccessor() = default;
    virtual HttpConnectionManager Unpack(const Listener& listener) const = 0;
    virtual void Pack(const HttpConnectionManager& hcm,
                      Listener* listener) const = 0;
  };

  class ClientHcmAccessor : public HcmAccessor {
   public:
    HttpConnectionManager Unpack(const Listener& listener) const override;
    void Pack(const HttpConnectionManager& hcm,
              Listener* listener) const override;
  };

  class ServerHcmAccessor : public HcmAccessor {
   public:
    HttpConnectionManager Unpack(const Listener& listener) const override;
    void Pack(const HttpConnectionManager& hcm,
              Listener* listener) const override;
  };

  static const char kDefaultLocalityRegion[];
  static const char kDefaultLocalityZone[];
  static const uint32_t kDefaultLocalityWeight = 3;
  static const int kDefaultLocalityPriority = 0;

  static const char kServerName[];
  static const char kDefaultRouteConfigurationName[];
  static const char kDefaultClusterName[];
  static const char kDefaultEdsServiceName[];
  static const char kDefaultServerRouteConfigurationName[];

  static Listener DefaultListener();
  static RouteConfiguration DefaultRouteConfig();
  static Cluster DefaultCluster();
  static Listener DefaultServerListener();
  static RouteConfiguration DefaultServerRouteConfig();
  static HttpConnectionManager DefaultHcm();

  static std::string GetServerListenerName(int port);

  static Listener PopulateServerListenerNameAndPort(
      const Listener& listener_template, int port);

  static void SetListenerAndRouteConfiguration(
      AdsServiceImpl* ads_service, Listener listener,
      const RouteConfiguration& route_config, bool use_rds = false,
      const HcmAccessor& hcm_accessor = ClientHcmAccessor());

  static void SetServerListenerNameAndRouteConfiguration(
      AdsServiceImpl* ads_service, Listener listener, int port,
      const RouteConfiguration& route_config, bool use_rds = false) {
    SetListenerAndRouteConfiguration(
        ads_service, PopulateServerListenerNameAndPort(listener, port),
        route_config, use_rds, ServerHcmAccessor());
  }

  static void SetRouteConfiguration(AdsServiceImpl* ads_service,
                                    const RouteConfiguration& route_config,
                                    bool use_rds = false,
                                    const Listener* listener_to_copy = nullptr);

  static std::string LocalityNameString(absl::string_view sub_zone);

  struct EdsResourceArgs {

    struct Endpoint {
      explicit Endpoint(
          int port,
          ::envoy::config::core::v3::HealthStatus health_status =
              ::envoy::config::core::v3::HealthStatus::UNKNOWN,
          int lb_weight = 1, std::vector<int> additional_ports = {},
          absl::string_view hostname = "",
          const std::map<std::string, std::string >& metadata = {})
          : port(port),
            health_status(health_status),
            lb_weight(lb_weight),
            additional_ports(std::move(additional_ports)),
            hostname(hostname),
            metadata(metadata) {}

      int port;
      ::envoy::config::core::v3::HealthStatus health_status;
      int lb_weight;
      std::vector<int> additional_ports;
      std::string hostname;
      std::map<std::string, std::string > metadata;
    };

    struct Locality {
      Locality(std::string sub_zone, std::vector<Endpoint> endpoints,
               uint32_t lb_weight = kDefaultLocalityWeight,
               int priority = kDefaultLocalityPriority)
          : sub_zone(std::move(sub_zone)),
            endpoints(std::move(endpoints)),
            lb_weight(lb_weight),
            priority(priority) {}

      const std::string sub_zone;
      std::vector<Endpoint> endpoints;
      uint32_t lb_weight;
      int priority;
    };

    EdsResourceArgs() = default;
    explicit EdsResourceArgs(std::vector<Locality> locality_list)
        : locality_list(std::move(locality_list)) {}

    std::vector<Locality> locality_list;
    std::map<std::string, uint32_t> drop_categories;
    ::envoy::type::v3::FractionalPercent::DenominatorType drop_denominator =
        ::envoy::type::v3::FractionalPercent::MILLION;
  };

  static ClusterLoadAssignment BuildEdsResource(
      const EdsResourceArgs& args,
      absl::string_view eds_service_name = kDefaultEdsServiceName);
};

}
}

#endif
