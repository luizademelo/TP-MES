Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header includes for gRPC core functionality and security components
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

// ABSL includes for logging and string utilities
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/statusor.h"
#include "absl/strings/match.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"

// Internal gRPC credential type includes
#include "src/core/credentials/call/external/external_account_credentials.h"
#include "src/core/credentials/call/jwt/json_token.h"
#include "src/core/credentials/call/jwt/jwt_credentials.h"
#include "src/core/credentials/call/oauth2/oauth2_credentials.h"
#include "src/core/credentials/transport/alts/check_gcp_environment.h"
#include "src/core/credentials/transport/transport_credentials.h"

// Core gRPC utility includes
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

// Load balancing related includes
#include "src/core/load_balancing/grpclb/grpclb.h"
#include "src/core/load_balancing/xds/xds_channel_args.h"

// Utility includes
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

// Constants for Google Compute Engine detection
#define GRPC_COMPUTE_ENGINE_DETECTION_HOST "metadata.google.internal."
#define GRPC_GOOGLE_CREDENTIAL_CREATION_ERROR \
  "Failed to create Google credentials"

// Global state variables for metadata server availability
static int g_metadata_server_available = 0;
static grpc_core::Mutex* g_state_mu;

// Polling related globals
static gpr_mu* g_polling_mu;
static gpr_once g_once = GPR_ONCE_INIT;
static grpc_core::internal::grpc_gce_tenancy_checker g_gce_tenancy_checker =
    grpc_alts_is_running_on_gcp;

// Initialize default credentials mutex
static void init_default_credentials(void) {
  g_state_mu = new grpc_core::Mutex();
}

// Structure for metadata server detection
struct metadata_server_detector {
  grpc_polling_entity pollent;  // Polling entity for async operations
  int is_done;                  // Flag indicating completion
  int success;                  // Flag indicating success
  grpc_http_response response;  // HTTP response from server
  grpc_core::Notification done; // Notification for completion
};

namespace {

// Checks if the given xds_cluster is a non-CFE (Google Front End) cluster
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

}  // namespace

// Creates a security connector based on the channel credentials
grpc_core::RefCountedPtr<grpc_channel_security_connector>
grpc_google_default_channel_credentials::create_security_connector(
    grpc_core::RefCountedPtr<grpc_call_credentials> call_creds,
    const char* target, grpc_core::ChannelArgs* args) {
  // Determine if we're connecting to a grpclb load balancer
  const bool is_grpclb_load_balancer =
      args->GetBool(GRPC_ARG_ADDRESS_IS_GRPCLB_LOAD_BALANCER).value_or(false);
  const bool is_backend_from_grpclb_load_balancer =
      args->GetBool(GRPC_ARG_ADDRESS_IS_BACKEND_FROM_GRPCLB_LOAD_BALANCER)
          .value_or(false);
  const bool is_xds_non_cfe_cluster =
      IsXdsNonCfeCluster(args->GetString(GRPC_ARG_XDS_CLUSTER_NAME));
  
  // Use ALTS if any of these conditions are true
  const bool use_alts = is_grpclb_load_balancer ||
                        is_backend_from_grpclb_load_balancer ||
                        is_xds_non_cfe_cluster;

  // Validate ALTS can be used if required
  if (use_alts && alts_creds_ == nullptr) {
    LOG(ERROR) << "ALTS is selected, but not running on GCE.";
    return nullptr;
  }

  // Create the appropriate security connector
  grpc_core::RefCountedPtr<grpc_channel_security_connector> sc =
      use_alts
          ? alts_creds_->create_security_connector(call_creds, target, args)
          : ssl_creds_->create_security_connector(call_creds, target, args);

  // Clean up channel args if using ALTS
  if (use_alts) {
    *args = args->Remove(GRPC_ARG_ADDRESS_IS_GRPCLB_LOAD_BALANCER)
                .Remove(GRPC_ARG_ADDRESS_IS_BACKEND_FROM_GRPCLB_LOAD_BALANCER);
  }
  return sc;
}

// Updates channel arguments with default values
grpc_core::ChannelArgs
grpc_google_default_channel_credentials::update_arguments(
    grpc_core::ChannelArgs args) {
  return args.SetIfUnset(GRPC_ARG_DNS_ENABLE_SRV_QUERIES, true);
}

// Returns the unique type name for these credentials
grpc_core::UniqueTypeName grpc_google_default_channel_credentials::Type() {
  static grpc_core::UniqueTypeName::Factory kFactory("GoogleDefault");
  return kFactory.Create();
}

// Callback for metadata server detection HTTP response
static void on_metadata_server_detection_http_response(
    void* user_data, grpc_error_handle error) {
  metadata_server_detector* detector =
      static_cast<metadata_server_detector*>(user_data);
  
  // Check for successful response with "Google" metadata flavor
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

  // Handle completion based on event engine implementation
  if (grpc_event_engine::experimental::UsePollsetAlternative()) {
    detector->done.Notify();
    return;
  }

  // Traditional pollset handling
  gpr_mu_lock(g_polling_mu);
  detector->is_done = 1;
  GRPC_LOG_IF_ERROR(
      "Pollset kick",
      grpc_pollset_kick(grpc_polling_entity_pollset(&detector->pollent),
                        nullptr));
  gpr_mu_unlock(g_polling_mu);
}

// Cleanup function for pollset
static void destroy_pollset(void* p, grpc_error_handle ) {
  grpc_pollset_destroy(static_cast<grpc_pollset*>(p));
}

// Checks if the metadata server is reachable
static int is_metadata_server_reachable() {
  metadata_server_detector detector;
  grpc_http_request request;
  grpc_closure destroy_closure;

  // Set up polling with 1 second timeout
  const auto max_detection_delay = grpc_core::Duration::Seconds(1);
  grpc_pollset* pollset =
      static_cast<grpc_pollset*>(gpr_zalloc(grpc_pollset_size()));
  grpc_pollset_init(pollset, &g_polling_mu);
  detector.pollent = grpc_polling_entity_create_from_pollset(pollset);
  detector.is_done = 0;
  detector.success = 0;
  memset(&request, 0, sizeof(grpc_http_request));

  // Create and execute HTTP request to metadata server
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

  // Wait for completion (either through event engine or traditional polling)
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

  // Clean up resources
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

// Creates default credentials from a JSON file path
static grpc_error_handle create_default_creds_from_path(
    const std::string& creds_path,
    grpc_core::RefCountedPtr<grpc_call_credentials>* creds) {
  if (creds_path.empty()) {
    return GRPC_ERROR_CREATE("creds_path unset");
  }

  // Load and parse the credentials file
  auto creds_data = grpc_core::LoadFile(creds_path, false);
  if (!creds_data.ok()) {
    return absl_status_to_grpc_error(creds_data.status());
  }

  auto json = grpc_core::JsonParse(creds_data->as_string_view());
  if (!json.ok()) {
    return absl_status_to_grpc_error(json.status());
  }

  // Validate JSON structure
  if (json->type() != Json::Type::kObject) {
    return GRPC_ERROR_CREATE(absl::StrCat("Failed to parse JSON \"",
                                          creds_data->as_string_view(), "\""));
  }

  // Try to create JWT credentials first
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

  // If not JWT, try refresh token credentials
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

  // Finally, try external account credentials
  auto external_creds =
      grpc_core::ExternalAccountCredentials::Create(*json, {});
  if (!external_creds.ok()) return external_creds.status();
  *creds = std::move(*external_creds);
  return absl::OkStatus();
}

// Updates the tenancy information (whether we're running on GCE)
static void update_tenancy() {
  gpr_once_init(&g_once, init_default_credentials);
  grpc_core::MutexLock lock(g_state_mu);

  // First try the GCE tenancy checker
  if (!g_metadata_server_available) {
    g_metadata_server_available = g_gce_tenancy_checker();
  }

  // If that fails, try directly reaching the metadata server
  if (!g_metadata_server_available) {
    g_metadata_server_available = is_metadata_server_reachable();
  }
}

// Checks if metadata server is available
static bool metadata_server_available() {
  grpc_core::MutexLock lock(g_state_mu);
  return static_cast<bool>(g_metadata_server_available);
}

// Creates default call credentials
static grpc_core::RefCountedPtr<grpc_call_credentials> make_default_call_creds(
    grpc_error_handle* error) {
  grpc_core::RefCountedPtr<grpc_call_credentials> call_creds;
  grpc_error_handle err;

  // First try getting credentials from environment variable
  auto path_from_env = grpc_core::GetEnv(GRPC_GOOGLE_CREDENTIALS_ENV_VAR);
  if (path_from_env.has_value()) {
    err = create_default_creds_from_path(*path_from_env, &call_creds);
    if (err.ok()) return call_creds;
    *error = grpc_error_add_child(*error, err);
  }

  // Then try well-known credentials file path
  err = create_default_creds_from_path(
      grpc_get_well_known_google_credentials_file_path(), &call_creds);
  if (err.ok()) return call_creds;
  *error = grpc_error_add_child(*error, err);

  // Update tenancy information
  update_tenancy();

  // Finally try getting credentials from metadata server if available
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

// Main function to create default credentials
grpc_channel_credentials* grpc_google_default_credentials_create(
    grpc_call_credentials* call_credentials) {
  grpc_channel_credentials* result = nullptr;
  grpc_core::RefCountedPtr<grpc_call_credentials> call_creds(call_credentials);
  grpc_error_handle error;
  grpc_core::ExecCtx exec_ctx;

  GRPC_TRACE_LOG(api, INFO)
      << "grpc_google_default_credentials_create(" << call_credentials << ")