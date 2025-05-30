
// Copyright 2022 gRPC authors.

#include "src/core/xds/grpc/xds_client_grpc.h"

#include <grpc/grpc.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/slice.h>
#include <grpc/support/alloc.h>
#include <grpc/support/string_util.h>

#include <algorithm>
#include <cstddef>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "envoy/service/status/v3/csds.upb.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/event_engine/channel_args_endpoint_config.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/transport/error_utils.h"
#include "src/core/telemetry/metrics.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/down_cast.h"
#include "src/core/util/env.h"
#include "src/core/util/load_file.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"
#include "src/core/util/upb_utils.h"
#include "src/core/xds/grpc/xds_bootstrap_grpc.h"
#include "src/core/xds/grpc/xds_transport_grpc.h"
#include "src/core/xds/xds_client/xds_api.h"
#include "src/core/xds/xds_client/xds_bootstrap.h"
#include "src/core/xds/xds_client/xds_channel_args.h"
#include "src/core/xds/xds_client/xds_client.h"
#include "src/core/xds/xds_client/xds_transport.h"
#include "upb/base/string_view.h"

#ifdef GRPC_XDS_USER_AGENT_NAME_SUFFIX
#define GRPC_XDS_USER_AGENT_NAME_SUFFIX_STRING \
  " " GRPC_XDS_USER_AGENT_NAME_SUFFIX
#else
#define GRPC_XDS_USER_AGENT_NAME_SUFFIX_STRING ""
#endif

#ifdef GRPC_XDS_USER_AGENT_VERSION_SUFFIX
#define GRPC_XDS_USER_AGENT_VERSION_SUFFIX_STRING \
  " " GRPC_XDS_USER_AGENT_VERSION_SUFFIX
#else
#define GRPC_XDS_USER_AGENT_VERSION_SUFFIX_STRING ""
#endif

namespace grpc_core {

namespace {

constexpr absl::string_view kMetricLabelXdsServer = "grpc.xds.server";
constexpr absl::string_view kMetricLabelXdsAuthority = "grpc.xds.authority";
constexpr absl::string_view kMetricLabelXdsResourceType =
    "grpc.xds.resource_type";
constexpr absl::string_view kMetricLabelXdsCacheState = "grpc.xds.cache_state";

const auto kMetricResourceUpdatesValid =
    GlobalInstrumentsRegistry::RegisterUInt64Counter(
        "grpc.xds_client.resource_updates_valid",
        "EXPERIMENTAL.  A counter of resources received that were considered "
        "valid.  The counter will be incremented even for resources that "
        "have not changed.",
        "{resource}", false)
        .Labels(kMetricLabelTarget, kMetricLabelXdsServer,
                kMetricLabelXdsResourceType)
        .Build();

const auto kMetricResourceUpdatesInvalid =
    GlobalInstrumentsRegistry::RegisterUInt64Counter(
        "grpc.xds_client.resource_updates_invalid",
        "EXPERIMENTAL.  A counter of resources received that were considered "
        "invalid.",
        "{resource}", false)
        .Labels(kMetricLabelTarget, kMetricLabelXdsServer,
                kMetricLabelXdsResourceType)
        .Build();

const auto kMetricServerFailure =
    GlobalInstrumentsRegistry::RegisterUInt64Counter(
        "grpc.xds_client.server_failure",
        "EXPERIMENTAL.  A counter of xDS servers going from healthy to "
        "unhealthy.  A server goes unhealthy when we have a connectivity "
        "failure or when the ADS stream fails without seeing a response "
        "message, as per gRFC A57.",
        "{failure}", false)
        .Labels(kMetricLabelTarget, kMetricLabelXdsServer)
        .Build();

const auto kMetricConnected =
    GlobalInstrumentsRegistry::RegisterCallbackInt64Gauge(
        "grpc.xds_client.connected",
        "EXPERIMENTAL.  Whether or not the xDS client currently has a "
        "working ADS stream to the xDS server.  For a given server, this "
        "will be set to 0 when we have a connectivity failure or when the "
        "ADS stream fails without seeing a response message, as per gRFC "
        "A57.  It will be set to 1 when we receive the first response on "
        "an ADS stream.",
        "{bool}", false)
        .Labels(kMetricLabelTarget, kMetricLabelXdsServer)
        .Build();

const auto kMetricResources =
    GlobalInstrumentsRegistry::RegisterCallbackInt64Gauge(
        "grpc.xds_client.resources", "EXPERIMENTAL.  Number of xDS resources.",
        "{resource}", false)
        .Labels(kMetricLabelTarget, kMetricLabelXdsAuthority,
                kMetricLabelXdsResourceType, kMetricLabelXdsCacheState)
        .Build();

}

class GrpcXdsClient::MetricsReporter final : public XdsMetricsReporter {
 public:
  explicit MetricsReporter(GrpcXdsClient& xds_client)
      : xds_client_(xds_client) {}

  void ReportResourceUpdates(absl::string_view xds_server,
                             absl::string_view resource_type,
                             uint64_t num_valid_resources,
                             uint64_t num_invalid_resources) override {
    xds_client_.stats_plugin_group_->AddCounter(
        kMetricResourceUpdatesValid, num_valid_resources,
        {xds_client_.key_, xds_server, resource_type}, {});
    xds_client_.stats_plugin_group_->AddCounter(
        kMetricResourceUpdatesInvalid, num_invalid_resources,
        {xds_client_.key_, xds_server, resource_type}, {});
  }

  void ReportServerFailure(absl::string_view xds_server) override {
    xds_client_.stats_plugin_group_->AddCounter(
        kMetricServerFailure, 1, {xds_client_.key_, xds_server}, {});
  }

 private:
  GrpcXdsClient& xds_client_;
};

constexpr absl::string_view GrpcXdsClient::kServerKey;

namespace {

Mutex* g_mu = new Mutex;
const grpc_channel_args* g_channel_args ABSL_GUARDED_BY(*g_mu) = nullptr;

NoDestruct<std::map<absl::string_view, GrpcXdsClient*>> g_xds_client_map
    ABSL_GUARDED_BY(*g_mu);
char* g_fallback_bootstrap_config ABSL_GUARDED_BY(*g_mu) = nullptr;

absl::StatusOr<std::string> GetBootstrapContents(const char* fallback_config) {

  auto path = GetEnv("GRPC_XDS_BOOTSTRAP");
  if (path.has_value()) {
    GRPC_TRACE_LOG(xds_client, INFO)
        << "Got bootstrap file location from GRPC_XDS_BOOTSTRAP "
           "environment variable: "
        << *path;
    auto contents = LoadFile(*path, true);
    if (!contents.ok()) return contents.status();
    return std::string(contents->as_string_view());
  }

  auto env_config = GetEnv("GRPC_XDS_BOOTSTRAP_CONFIG");
  if (env_config.has_value()) {
    GRPC_TRACE_LOG(xds_client, INFO)
        << "Got bootstrap contents from GRPC_XDS_BOOTSTRAP_CONFIG "
        << "environment variable";
    return std::move(*env_config);
  }

  if (fallback_config != nullptr) {
    GRPC_TRACE_LOG(xds_client, INFO)
        << "Got bootstrap contents from fallback config";
    return fallback_config;
  }

  return absl::FailedPreconditionError(
      "Environment variables GRPC_XDS_BOOTSTRAP or GRPC_XDS_BOOTSTRAP_CONFIG "
      "not defined");
}

std::shared_ptr<GlobalStatsPluginRegistry::StatsPluginGroup>
GetStatsPluginGroupForKeyAndChannelArgs(absl::string_view key,
                                        const ChannelArgs& channel_args) {
  if (key == GrpcXdsClient::kServerKey) {
    return GlobalStatsPluginRegistry::GetStatsPluginsForServer(channel_args);
  }
  grpc_event_engine::experimental::ChannelArgsEndpointConfig endpoint_config(
      channel_args);
  std::string authority =
      channel_args.GetOwnedString(GRPC_ARG_DEFAULT_AUTHORITY)
          .value_or(
              CoreConfiguration::Get().resolver_registry().GetDefaultAuthority(
                  key));
  experimental::StatsPluginChannelScope scope(key, authority, endpoint_config);
  return GlobalStatsPluginRegistry::GetStatsPluginsForChannel(scope);
}

}

absl::StatusOr<RefCountedPtr<GrpcXdsClient>> GrpcXdsClient::GetOrCreate(
    absl::string_view key, const ChannelArgs& args, const char* reason) {

  std::optional<absl::string_view> bootstrap_config = args.GetString(
      GRPC_ARG_TEST_ONLY_DO_NOT_USE_IN_PROD_XDS_BOOTSTRAP_CONFIG);
  if (bootstrap_config.has_value()) {
    auto bootstrap = GrpcXdsBootstrap::Create(*bootstrap_config);
    if (!bootstrap.ok()) return bootstrap.status();
    grpc_channel_args* xds_channel_args = args.GetPointer<grpc_channel_args>(
        GRPC_ARG_TEST_ONLY_DO_NOT_USE_IN_PROD_XDS_CLIENT_CHANNEL_ARGS);
    auto channel_args = ChannelArgs::FromC(xds_channel_args);
    return MakeRefCounted<GrpcXdsClient>(
        key, std::move(*bootstrap), channel_args,
        MakeRefCounted<GrpcXdsTransportFactory>(channel_args),
        GetStatsPluginGroupForKeyAndChannelArgs(key, args));
  }

  MutexLock lock(g_mu);
  auto it = g_xds_client_map->find(key);
  if (it != g_xds_client_map->end()) {
    auto xds_client = it->second->RefIfNonZero(DEBUG_LOCATION, reason);
    if (xds_client != nullptr) {
      return xds_client.TakeAsSubclass<GrpcXdsClient>();
    }
  }

  auto bootstrap_contents = GetBootstrapContents(g_fallback_bootstrap_config);
  if (!bootstrap_contents.ok()) return bootstrap_contents.status();
  GRPC_TRACE_LOG(xds_client, INFO)
      << "xDS bootstrap contents: " << *bootstrap_contents;

  auto bootstrap = GrpcXdsBootstrap::Create(*bootstrap_contents);
  if (!bootstrap.ok()) return bootstrap.status();

  auto channel_args = ChannelArgs::FromC(g_channel_args);
  auto xds_client = MakeRefCounted<GrpcXdsClient>(
      key, std::move(*bootstrap), channel_args,
      MakeRefCounted<GrpcXdsTransportFactory>(channel_args),
      GetStatsPluginGroupForKeyAndChannelArgs(key, args));
  g_xds_client_map->emplace(xds_client->key(), xds_client.get());
  GRPC_TRACE_LOG(xds_client, INFO) << "[xds_client " << xds_client.get()
                                   << "] Created xDS client for key " << key;
  return xds_client;
}

namespace {

std::string UserAgentName() {
  return absl::StrCat("gRPC C-core ", GPR_PLATFORM_STRING,
                      GRPC_XDS_USER_AGENT_NAME_SUFFIX_STRING);
}

std::string UserAgentVersion() {
  return absl::StrCat("C-core ", grpc_version_string(),
                      GRPC_XDS_USER_AGENT_NAME_SUFFIX_STRING,
                      GRPC_XDS_USER_AGENT_VERSION_SUFFIX_STRING);
}

}

GrpcXdsClient::GrpcXdsClient(
    absl::string_view key, std::shared_ptr<GrpcXdsBootstrap> bootstrap,
    const ChannelArgs& args,
    RefCountedPtr<XdsTransportFactory> transport_factory,
    std::shared_ptr<GlobalStatsPluginRegistry::StatsPluginGroup>
        stats_plugin_group)
    : XdsClient(
          bootstrap, transport_factory,
          grpc_event_engine::experimental::GetDefaultEventEngine(),
          std::make_unique<MetricsReporter>(*this), UserAgentName(),
          UserAgentVersion(),
          std::max(Duration::Zero(),
                   args.GetDurationFromIntMillis(
                           GRPC_ARG_XDS_RESOURCE_DOES_NOT_EXIST_TIMEOUT_MS)
                       .value_or(Duration::Seconds(15)))),
      key_(key),
      certificate_provider_store_(MakeOrphanable<CertificateProviderStore>(
          DownCast<const GrpcXdsBootstrap&>(this->bootstrap())
              .certificate_providers())),
      stats_plugin_group_(std::move(stats_plugin_group)),
      registered_metric_callback_(stats_plugin_group_->RegisterCallback(
          [this](CallbackMetricReporter& reporter) {
            ReportCallbackMetrics(reporter);
          },
          Duration::Seconds(5), kMetricConnected, kMetricResources)),
      lrs_client_(MakeRefCounted<LrsClient>(
          std::move(bootstrap), UserAgentName(), UserAgentVersion(),
          std::move(transport_factory),
          grpc_event_engine::experimental::GetDefaultEventEngine())) {}

void GrpcXdsClient::Orphaned() {
  registered_metric_callback_.reset();
  XdsClient::Orphaned();
  lrs_client_.reset();
  MutexLock lock(g_mu);
  auto it = g_xds_client_map->find(key_);
  if (it != g_xds_client_map->end() && it->second == this) {
    g_xds_client_map->erase(it);
  }
}

void GrpcXdsClient::ResetBackoff() {
  XdsClient::ResetBackoff();
  lrs_client_->ResetBackoff();
}

grpc_pollset_set* GrpcXdsClient::interested_parties() const {
  return reinterpret_cast<GrpcXdsTransportFactory*>(transport_factory())
      ->interested_parties();
}

namespace {

std::vector<RefCountedPtr<GrpcXdsClient>> GetAllXdsClients() {
  MutexLock lock(g_mu);
  std::vector<RefCountedPtr<GrpcXdsClient>> xds_clients;
  for (const auto& [_, client] : *g_xds_client_map) {
    auto xds_client =
        client->RefIfNonZero(DEBUG_LOCATION, "DumpAllClientConfigs");
    if (xds_client != nullptr) {
      xds_clients.emplace_back(xds_client.TakeAsSubclass<GrpcXdsClient>());
    }
  }
  return xds_clients;
}

}

grpc_slice GrpcXdsClient::DumpAllClientConfigs()
    ABSL_NO_THREAD_SAFETY_ANALYSIS {
  auto xds_clients = GetAllXdsClients();
  upb::Arena arena;

  std::set<std::string> string_pool;
  auto response = envoy_service_status_v3_ClientStatusResponse_new(arena.ptr());

  for (const auto& xds_client : xds_clients) {
    auto client_config =
        envoy_service_status_v3_ClientStatusResponse_add_config(response,
                                                                arena.ptr());
    xds_client->mu()->Lock();
    xds_client->DumpClientConfig(&string_pool, arena.ptr(), client_config);
    envoy_service_status_v3_ClientConfig_set_client_scope(
        client_config, StdStringToUpbString(xds_client->key()));
  }

  size_t output_length;
  char* output = envoy_service_status_v3_ClientStatusResponse_serialize(
      response, arena.ptr(), &output_length);
  for (const auto& xds_client : xds_clients) {
    xds_client->mu()->Unlock();
  }
  return grpc_slice_from_cpp_string(std::string(output, output_length));
}

void GrpcXdsClient::ReportCallbackMetrics(CallbackMetricReporter& reporter) {
  MutexLock lock(mu());
  ReportResourceCounts([&](const ResourceCountLabels& labels, uint64_t count) {
    reporter.Report(
        kMetricResources, count,
        {key_, labels.xds_authority, labels.resource_type, labels.cache_state},
        {});
  });
  ReportServerConnections([&](absl::string_view xds_server, bool connected) {
    reporter.Report(kMetricConnected, connected, {key_, xds_server}, {});
  });
}

namespace internal {

void SetXdsChannelArgsForTest(grpc_channel_args* args) {
  MutexLock lock(g_mu);
  g_channel_args = args;
}

void UnsetGlobalXdsClientsForTest() {
  MutexLock lock(g_mu);
  g_xds_client_map->clear();
}

void SetXdsFallbackBootstrapConfig(const char* config) {
  MutexLock lock(g_mu);
  gpr_free(g_fallback_bootstrap_config);
  g_fallback_bootstrap_config = gpr_strdup(config);
}

}

}

grpc_slice grpc_dump_xds_configs(void) {
  grpc_core::ExecCtx exec_ctx;
  return grpc_core::GrpcXdsClient::DumpAllClientConfigs();
}
