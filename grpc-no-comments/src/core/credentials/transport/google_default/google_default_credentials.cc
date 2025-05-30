
// Copyright 2015 gRPC authors.

#include "src/core/credentials/transport/google_default/google_default_credentials.h"

#include <grpc/credentials.h>
#include <grpc/grpc_security.h>
#include <grpc/grpc_security_constants.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/slice.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>
#include <string.h>

#include <memory>
#include <optional>
#include <string>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/statusor.h"
#include "absl/strings/match.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "src/core/credentials/call/external/external_account_credentials.h"
#include "src/core/credentials/call/jwt/json_token.h"
#include "src/core/credentials/call/jwt/jwt_credentials.h"
#include "src/core/credentials/call/oauth2/oauth2_credentials.h"
#include "src/core/credentials/transport/alts/check_gcp_environment.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/event_engine/shim.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/polling_entity.h"
#include "src/core/lib/iomgr/pollset.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/transport/error_utils.h"
#include "src/core/load_balancing/grpclb/grpclb.h"
#include "src/core/load_balancing/xds/xds_channel_args.h"
#include "src/core/util/env.h"
#include "src/core/util/http_client/httpcli.h"
#include "src/core/util/http_client/parser.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_reader.h"
#include "src/core/util/load_file.h"
#include "src/core/util/notification.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"
#include "src/core/util/uri.h"

using grpc_core::Json;

#define GRPC_COMPUTE_ENGINE_DETECTION_HOST "metadata.google.internal."
#define GRPC_GOOGLE_CREDENTIAL_CREATION_ERROR \
  "Failed to create Google credentials"

static int g_metadata_server_available = 0;
static grpc_core::Mutex* g_state_mu;

static gpr_mu* g_polling_mu;
static gpr_once g_once = GPR_ONCE_INIT;
static grpc_core::internal::grpc_gce_tenancy_checker g_gce_tenancy_checker =
    grpc_alts_is_running_on_gcp;

static void init_default_credentials(void) {
  g_state_mu = new grpc_core::Mutex();
}

struct metadata_server_detector {
  grpc_polling_entity pollent;
  int is_done;
  int success;
  grpc_http_response response;
  grpc_core::Notification done;
};

namespace {

bool IsXdsNonCfeCluster(std::optional<absl::string_view> xds_cluster) {
  if (!xds_cluster.has_value()) return false;
  if (absl::StartsWith(*xds_cluster, "google_cfe_")) return false;
  if (!absl::StartsWith(*xds_cluster, "xdstp:")) return true;
  auto uri = grpc_core::URI::Parse(*xds_cluster);
  if (!uri.ok()) return true;
  return uri->authority() != "traffic-director-c2p.xds.googleapis.com" ||
         !absl::StartsWith(uri->path(),
                           "/envoy.config.cluster.v3.Cluster/google_cfe_");
}

}

grpc_core::RefCountedPtr<grpc_channel_security_connector>
grpc_google_default_channel_credentials::create_security_connector(
    grpc_core::RefCountedPtr<grpc_call_credentials> call_creds,
    const char* target, grpc_core::ChannelArgs* args) {
  const bool is_grpclb_load_balancer =
      args->GetBool(GRPC_ARG_ADDRESS_IS_GRPCLB_LOAD_BALANCER).value_or(false);
  const bool is_backend_from_grpclb_load_balancer =
      args->GetBool(GRPC_ARG_ADDRESS_IS_BACKEND_FROM_GRPCLB_LOAD_BALANCER)
          .value_or(false);
  const bool is_xds_non_cfe_cluster =
      IsXdsNonCfeCluster(args->GetString(GRPC_ARG_XDS_CLUSTER_NAME));
  const bool use_alts = is_grpclb_load_balancer ||
                        is_backend_from_grpclb_load_balancer ||
                        is_xds_non_cfe_cluster;

  if (use_alts && alts_creds_ == nullptr) {
    LOG(ERROR) << "ALTS is selected, but not running on GCE.";
    return nullptr;
  }
  grpc_core::RefCountedPtr<grpc_channel_security_connector> sc =
      use_alts
          ? alts_creds_->create_security_connector(call_creds, target, args)
          : ssl_creds_->create_security_connector(call_creds, target, args);

  if (use_alts) {
    *args = args->Remove(GRPC_ARG_ADDRESS_IS_GRPCLB_LOAD_BALANCER)
                .Remove(GRPC_ARG_ADDRESS_IS_BACKEND_FROM_GRPCLB_LOAD_BALANCER);
  }
  return sc;
}

grpc_core::ChannelArgs
grpc_google_default_channel_credentials::update_arguments(
    grpc_core::ChannelArgs args) {
  return args.SetIfUnset(GRPC_ARG_DNS_ENABLE_SRV_QUERIES, true);
}

grpc_core::UniqueTypeName grpc_google_default_channel_credentials::Type() {
  static grpc_core::UniqueTypeName::Factory kFactory("GoogleDefault");
  return kFactory.Create();
}

static void on_metadata_server_detection_http_response(
    void* user_data, grpc_error_handle error) {
  metadata_server_detector* detector =
      static_cast<metadata_server_detector*>(user_data);
  if (error.ok() && detector->response.status == 200 &&
      detector->response.hdr_count > 0) {

    size_t i;
    for (i = 0; i < detector->response.hdr_count; i++) {
      grpc_http_header* header = &detector->response.hdrs[i];
      if (strcmp(header->key, "Metadata-Flavor") == 0 &&
          strcmp(header->value, "Google") == 0) {
        detector->success = 1;
        break;
      }
    }
  }
  if (grpc_event_engine::experimental::UsePollsetAlternative()) {
    detector->done.Notify();
    return;
  }
  gpr_mu_lock(g_polling_mu);
  detector->is_done = 1;
  GRPC_LOG_IF_ERROR(
      "Pollset kick",
      grpc_pollset_kick(grpc_polling_entity_pollset(&detector->pollent),
                        nullptr));
  gpr_mu_unlock(g_polling_mu);
}

static void destroy_pollset(void* p, grpc_error_handle ) {
  grpc_pollset_destroy(static_cast<grpc_pollset*>(p));
}

static int is_metadata_server_reachable() {
  metadata_server_detector detector;
  grpc_http_request request;
  grpc_closure destroy_closure;

  const auto max_detection_delay = grpc_core::Duration::Seconds(1);
  grpc_pollset* pollset =
      static_cast<grpc_pollset*>(gpr_zalloc(grpc_pollset_size()));
  grpc_pollset_init(pollset, &g_polling_mu);
  detector.pollent = grpc_polling_entity_create_from_pollset(pollset);
  detector.is_done = 0;
  detector.success = 0;
  memset(&request, 0, sizeof(grpc_http_request));
  auto uri = grpc_core::URI::Create("http", "",
                                    GRPC_COMPUTE_ENGINE_DETECTION_HOST, "/",
                                    {} , "" );
  CHECK(uri.ok());
  auto http_request = grpc_core::HttpRequest::Get(
      std::move(*uri), nullptr , &detector.pollent, &request,
      grpc_core::Timestamp::Now() + max_detection_delay,
      GRPC_CLOSURE_CREATE(on_metadata_server_detection_http_response, &detector,
                          grpc_schedule_on_exec_ctx),
      &detector.response,
      grpc_core::RefCountedPtr<grpc_channel_credentials>(
          grpc_insecure_credentials_create()));
  http_request->Start();
  grpc_core::ExecCtx::Get()->Flush();
  if (grpc_event_engine::experimental::UsePollsetAlternative()) {
    detector.done.WaitForNotification();
  } else {

    gpr_mu_lock(g_polling_mu);
    while (!detector.is_done) {
      grpc_pollset_worker* worker = nullptr;
      if (!GRPC_LOG_IF_ERROR(
              "pollset_work",
              grpc_pollset_work(grpc_polling_entity_pollset(&detector.pollent),
                                &worker, grpc_core::Timestamp::InfFuture()))) {
        detector.is_done = 1;
        detector.success = 0;
      }
    }
    gpr_mu_unlock(g_polling_mu);
  }
  http_request.reset();
  GRPC_CLOSURE_INIT(&destroy_closure, destroy_pollset,
                    grpc_polling_entity_pollset(&detector.pollent),
                    grpc_schedule_on_exec_ctx);
  grpc_pollset_shutdown(grpc_polling_entity_pollset(&detector.pollent),
                        &destroy_closure);
  g_polling_mu = nullptr;
  grpc_core::ExecCtx::Get()->Flush();
  gpr_free(grpc_polling_entity_pollset(&detector.pollent));
  grpc_http_response_destroy(&detector.response);
  return detector.success;
}

static grpc_error_handle create_default_creds_from_path(
    const std::string& creds_path,
    grpc_core::RefCountedPtr<grpc_call_credentials>* creds) {
  if (creds_path.empty()) {
    return GRPC_ERROR_CREATE("creds_path unset");
  }
  auto creds_data =
      grpc_core::LoadFile(creds_path, false);
  if (!creds_data.ok()) {
    return absl_status_to_grpc_error(creds_data.status());
  }
  auto json = grpc_core::JsonParse(creds_data->as_string_view());
  if (!json.ok()) {
    return absl_status_to_grpc_error(json.status());
  }
  if (json->type() != Json::Type::kObject) {
    return GRPC_ERROR_CREATE(absl::StrCat("Failed to parse JSON \"",
                                          creds_data->as_string_view(), "\""));
  }

  grpc_auth_json_key key = grpc_auth_json_key_create_from_json(*json);
  if (grpc_auth_json_key_is_valid(&key)) {
    *creds =
        grpc_service_account_jwt_access_credentials_create_from_auth_json_key(
            key, grpc_max_auth_token_lifetime());
    if (*creds == nullptr) {
      return GRPC_ERROR_CREATE(
          "grpc_service_account_jwt_access_credentials_create_from_auth_json_"
          "key failed");
    }
    return absl::OkStatus();
  }

  grpc_auth_refresh_token token =
      grpc_auth_refresh_token_create_from_json(*json);
  if (grpc_auth_refresh_token_is_valid(&token)) {
    *creds =
        grpc_refresh_token_credentials_create_from_auth_refresh_token(token);
    if (*creds == nullptr) {
      return GRPC_ERROR_CREATE(
          "grpc_refresh_token_credentials_create_from_auth_refresh_token "
          "failed");
    }
    return absl::OkStatus();
  }

  auto external_creds =
      grpc_core::ExternalAccountCredentials::Create(*json, {});
  if (!external_creds.ok()) return external_creds.status();
  *creds = std::move(*external_creds);
  return absl::OkStatus();
}

static void update_tenancy() {
  gpr_once_init(&g_once, init_default_credentials);
  grpc_core::MutexLock lock(g_state_mu);

  if (!g_metadata_server_available) {
    g_metadata_server_available = g_gce_tenancy_checker();
  }

  if (!g_metadata_server_available) {
    g_metadata_server_available = is_metadata_server_reachable();
  }
}

static bool metadata_server_available() {
  grpc_core::MutexLock lock(g_state_mu);
  return static_cast<bool>(g_metadata_server_available);
}

static grpc_core::RefCountedPtr<grpc_call_credentials> make_default_call_creds(
    grpc_error_handle* error) {
  grpc_core::RefCountedPtr<grpc_call_credentials> call_creds;
  grpc_error_handle err;

  auto path_from_env = grpc_core::GetEnv(GRPC_GOOGLE_CREDENTIALS_ENV_VAR);
  if (path_from_env.has_value()) {
    err = create_default_creds_from_path(*path_from_env, &call_creds);
    if (err.ok()) return call_creds;
    *error = grpc_error_add_child(*error, err);
  }

  err = create_default_creds_from_path(
      grpc_get_well_known_google_credentials_file_path(), &call_creds);
  if (err.ok()) return call_creds;
  *error = grpc_error_add_child(*error, err);

  update_tenancy();

  if (metadata_server_available()) {
    call_creds = grpc_core::RefCountedPtr<grpc_call_credentials>(
        grpc_google_compute_engine_credentials_create(nullptr));
    if (call_creds == nullptr) {
      *error = GRPC_ERROR_CREATE(GRPC_GOOGLE_CREDENTIAL_CREATION_ERROR);
      *error = grpc_error_add_child(
          *error, GRPC_ERROR_CREATE("Failed to get credentials from network"));
    }
  }

  return call_creds;
}

grpc_channel_credentials* grpc_google_default_credentials_create(
    grpc_call_credentials* call_credentials) {
  grpc_channel_credentials* result = nullptr;
  grpc_core::RefCountedPtr<grpc_call_credentials> call_creds(call_credentials);
  grpc_error_handle error;
  grpc_core::ExecCtx exec_ctx;

  GRPC_TRACE_LOG(api, INFO)
      << "grpc_google_default_credentials_create(" << call_credentials << ")";

  if (call_creds == nullptr) {
    call_creds = make_default_call_creds(&error);
  }

  if (call_creds != nullptr) {

    grpc_channel_credentials* ssl_creds =
        grpc_ssl_credentials_create(nullptr, nullptr, nullptr, nullptr);
    CHECK_NE(ssl_creds, nullptr);
    grpc_alts_credentials_options* options =
        grpc_alts_credentials_client_options_create();
    grpc_channel_credentials* alts_creds =
        grpc_alts_credentials_create(options);
    grpc_alts_credentials_options_destroy(options);
    auto creds =
        grpc_core::MakeRefCounted<grpc_google_default_channel_credentials>(
            grpc_core::RefCountedPtr<grpc_channel_credentials>(alts_creds),
            grpc_core::RefCountedPtr<grpc_channel_credentials>(ssl_creds));
    result = grpc_composite_channel_credentials_create(
        creds.get(), call_creds.get(), nullptr);
    CHECK_NE(result, nullptr);
  } else {
    LOG(ERROR) << "Could not create google default credentials: "
               << grpc_core::StatusToString(error);
  }
  return result;
}

namespace grpc_core {
namespace internal {

void set_gce_tenancy_checker_for_testing(grpc_gce_tenancy_checker checker) {
  g_gce_tenancy_checker = checker;
}

void grpc_flush_cached_google_default_credentials(void) {
  ExecCtx exec_ctx;
  gpr_once_init(&g_once, init_default_credentials);
  MutexLock lock(g_state_mu);
  g_metadata_server_available = 0;
}

}
}

static grpc_well_known_credentials_path_getter creds_path_getter = nullptr;

std::string grpc_get_well_known_google_credentials_file_path(void) {
  if (creds_path_getter != nullptr) return creds_path_getter();
  return grpc_get_well_known_google_credentials_file_path_impl();
}

void grpc_override_well_known_credentials_path_getter(
    grpc_well_known_credentials_path_getter getter) {
  creds_path_getter = getter;
}
