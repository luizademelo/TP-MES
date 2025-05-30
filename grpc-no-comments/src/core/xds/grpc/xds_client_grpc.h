
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_CLIENT_GRPC_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_CLIENT_GRPC_H

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include <memory>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/telemetry/metrics.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/useful.h"
#include "src/core/xds/grpc/certificate_provider_store.h"
#include "src/core/xds/grpc/xds_bootstrap_grpc.h"
#include "src/core/xds/xds_client/lrs_client.h"
#include "src/core/xds/xds_client/xds_client.h"
#include "src/core/xds/xds_client/xds_transport.h"

namespace grpc_core {

class GrpcXdsClient final : public XdsClient {
 public:

  static constexpr absl::string_view kServerKey = "#server";

  static absl::StatusOr<RefCountedPtr<GrpcXdsClient>> GetOrCreate(
      absl::string_view key, const ChannelArgs& args, const char* reason);

  GrpcXdsClient(absl::string_view key,
                std::shared_ptr<GrpcXdsBootstrap> bootstrap,
                const ChannelArgs& args,
                RefCountedPtr<XdsTransportFactory> transport_factory,
                std::shared_ptr<GlobalStatsPluginRegistry::StatsPluginGroup>
                    stats_plugin_group);

  static absl::string_view ChannelArgName() {
    return GRPC_ARG_NO_SUBCHANNEL_PREFIX "xds_client";
  }
  static int ChannelArgsCompare(const XdsClient* a, const XdsClient* b) {
    return QsortCompare(a, b);
  }

  void ResetBackoff() override;

  grpc_pollset_set* interested_parties() const;

  CertificateProviderStore& certificate_provider_store() const {
    return *certificate_provider_store_;
  }

  absl::string_view key() const { return key_; }

  LrsClient& lrs_client() { return *lrs_client_; }

  static grpc_slice DumpAllClientConfigs();

 private:
  class MetricsReporter;

  void ReportCallbackMetrics(CallbackMetricReporter& reporter);
  void Orphaned() override;

  std::string key_;
  OrphanablePtr<CertificateProviderStore> certificate_provider_store_;
  std::shared_ptr<GlobalStatsPluginRegistry::StatsPluginGroup>
      stats_plugin_group_;
  std::unique_ptr<RegisteredMetricCallback> registered_metric_callback_;
  RefCountedPtr<LrsClient> lrs_client_;
};

namespace internal {
void SetXdsChannelArgsForTest(grpc_channel_args* args);
void UnsetGlobalXdsClientsForTest();

void SetXdsFallbackBootstrapConfig(const char* config);
}

}

#endif
