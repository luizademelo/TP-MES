
// Copyright 2015 gRPC authors.

#include "src/cpp/client/secure_credentials.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security_constants.h>
#include <grpc/slice.h>
#include <grpc/support/json.h>
#include <grpc/support/string_util.h>
#include <grpc/support/time.h>
#include <grpcpp/channel.h>
#include <grpcpp/impl/grpc_library.h>
#include <grpcpp/security/tls_credentials_options.h>
#include <grpcpp/support/channel_arguments.h>
#include <grpcpp/support/config.h>
#include <grpcpp/support/slice.h>
#include <grpcpp/support/status.h>
#include <string.h>

#include <map>
#include <memory>
#include <optional>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_join.h"
#include "src/core/credentials/call/json_util.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/util/env.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_reader.h"
#include "src/core/util/load_file.h"
#include "src/cpp/common/secure_auth_context.h"
#include "src/cpp/server/thread_pool_interface.h"

namespace grpc {

namespace {
class WrappedCallCredentials : public CallCredentials {
 public:
  explicit WrappedCallCredentials(grpc_call_credentials* creds)
      : CallCredentials(creds) {}
};

std::shared_ptr<WrappedCallCredentials> WrapCallCredentials(
    grpc_call_credentials* creds) {
  return creds == nullptr ? nullptr
                          : std::make_shared<WrappedCallCredentials>(creds);
}

class WrappedChannelCredentials final : public ChannelCredentials {
 public:
  explicit WrappedChannelCredentials(grpc_channel_credentials* c_creds)
      : ChannelCredentials(c_creds) {}
};

std::shared_ptr<WrappedChannelCredentials> WrapChannelCredentials(
    grpc_channel_credentials* creds) {
  return creds == nullptr ? nullptr
                          : std::make_shared<WrappedChannelCredentials>(creds);
}

}

std::shared_ptr<ChannelCredentials> GoogleDefaultCredentials() {
  grpc::internal::GrpcLibrary init;
  return WrapChannelCredentials(
      grpc_google_default_credentials_create(nullptr));
}

std::shared_ptr<CallCredentials> ExternalAccountCredentials(
    const grpc::string& json_string, const std::vector<grpc::string>& scopes) {
  grpc::internal::GrpcLibrary init;
  return WrapCallCredentials(grpc_external_account_credentials_create(
      json_string.c_str(), absl::StrJoin(scopes, ",").c_str()));
}

std::shared_ptr<ChannelCredentials> SslCredentials(
    const SslCredentialsOptions& options) {
  grpc::internal::GrpcLibrary init;
  grpc_ssl_pem_key_cert_pair pem_key_cert_pair = {
      options.pem_private_key.c_str(), options.pem_cert_chain.c_str()};
  return WrapChannelCredentials(grpc_ssl_credentials_create(
      options.pem_root_certs.empty() ? nullptr : options.pem_root_certs.c_str(),
      options.pem_private_key.empty() ? nullptr : &pem_key_cert_pair, nullptr,
      nullptr));
}

namespace experimental {

namespace {

void ClearStsCredentialsOptions(StsCredentialsOptions* options) {
  if (options == nullptr) return;
  options->token_exchange_service_uri.clear();
  options->resource.clear();
  options->audience.clear();
  options->scope.clear();
  options->requested_token_type.clear();
  options->subject_token_path.clear();
  options->subject_token_type.clear();
  options->actor_token_path.clear();
  options->actor_token_type.clear();
}

}

grpc::Status StsCredentialsOptionsFromJson(const std::string& json_string,
                                           StsCredentialsOptions* options) {
  if (options == nullptr) {
    return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                        "options cannot be nullptr.");
  }
  ClearStsCredentialsOptions(options);
  auto json = grpc_core::JsonParse(json_string.c_str());
  if (!json.ok() || json->type() != grpc_core::Json::Type::kObject) {
    return grpc::Status(
        grpc::StatusCode::INVALID_ARGUMENT,
        absl::StrCat("Invalid json: ", json.status().ToString()));
  }

  const char* value = grpc_json_get_string_property(
      *json, "token_exchange_service_uri", nullptr);
  if (value == nullptr) {
    ClearStsCredentialsOptions(options);
    return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                        "token_exchange_service_uri must be specified.");
  }
  options->token_exchange_service_uri.assign(value);
  value = grpc_json_get_string_property(*json, "subject_token_path", nullptr);
  if (value == nullptr) {
    ClearStsCredentialsOptions(options);
    return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                        "subject_token_path must be specified.");
  }
  options->subject_token_path.assign(value);
  value = grpc_json_get_string_property(*json, "subject_token_type", nullptr);
  if (value == nullptr) {
    ClearStsCredentialsOptions(options);
    return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                        "subject_token_type must be specified.");
  }
  options->subject_token_type.assign(value);

  value = grpc_json_get_string_property(*json, "resource", nullptr);
  if (value != nullptr) options->resource.assign(value);
  value = grpc_json_get_string_property(*json, "audience", nullptr);
  if (value != nullptr) options->audience.assign(value);
  value = grpc_json_get_string_property(*json, "scope", nullptr);
  if (value != nullptr) options->scope.assign(value);
  value = grpc_json_get_string_property(*json, "requested_token_type", nullptr);
  if (value != nullptr) options->requested_token_type.assign(value);
  value = grpc_json_get_string_property(*json, "actor_token_path", nullptr);
  if (value != nullptr) options->actor_token_path.assign(value);
  value = grpc_json_get_string_property(*json, "actor_token_type", nullptr);
  if (value != nullptr) options->actor_token_type.assign(value);

  return grpc::Status();
}

grpc::Status StsCredentialsOptionsFromEnv(StsCredentialsOptions* options) {
  if (options == nullptr) {
    return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                        "options cannot be nullptr.");
  }
  ClearStsCredentialsOptions(options);
  auto sts_creds_path = grpc_core::GetEnv("STS_CREDENTIALS");
  if (!sts_creds_path.has_value()) {
    return grpc::Status(grpc::StatusCode::NOT_FOUND,
                        "STS_CREDENTIALS environment variable not set.");
  }
  auto json_slice =
      grpc_core::LoadFile(*sts_creds_path, true);
  if (!json_slice.ok()) {
    return grpc::Status(grpc::StatusCode::NOT_FOUND,
                        json_slice.status().ToString());
  }
  return StsCredentialsOptionsFromJson(json_slice->as_string_view().data(),
                                       options);
}

grpc_sts_credentials_options StsCredentialsCppToCoreOptions(
    const StsCredentialsOptions& options) {
  grpc_sts_credentials_options opts;
  memset(&opts, 0, sizeof(opts));
  opts.token_exchange_service_uri = options.token_exchange_service_uri.c_str();
  opts.resource = options.resource.c_str();
  opts.audience = options.audience.c_str();
  opts.scope = options.scope.c_str();
  opts.requested_token_type = options.requested_token_type.c_str();
  opts.subject_token_path = options.subject_token_path.c_str();
  opts.subject_token_type = options.subject_token_type.c_str();
  opts.actor_token_path = options.actor_token_path.c_str();
  opts.actor_token_type = options.actor_token_type.c_str();
  return opts;
}

std::shared_ptr<CallCredentials> StsCredentials(
    const StsCredentialsOptions& options) {
  auto opts = StsCredentialsCppToCoreOptions(options);
  return WrapCallCredentials(grpc_sts_credentials_create(&opts, nullptr));
}

std::shared_ptr<ChannelCredentials> AltsCredentials(
    const AltsCredentialsOptions& options) {
  grpc::internal::GrpcLibrary init;
  grpc_alts_credentials_options* c_options =
      grpc_alts_credentials_client_options_create();
  for (const auto& service_account : options.target_service_accounts) {
    grpc_alts_credentials_client_options_add_target_service_account(
        c_options, service_account.c_str());
  }
  grpc_channel_credentials* c_creds = grpc_alts_credentials_create(c_options);
  grpc_alts_credentials_options_destroy(c_options);
  return WrapChannelCredentials(c_creds);
}

std::shared_ptr<ChannelCredentials> LocalCredentials(
    grpc_local_connect_type type) {
  grpc::internal::GrpcLibrary init;
  return WrapChannelCredentials(grpc_local_credentials_create(type));
}

std::shared_ptr<ChannelCredentials> TlsCredentials(
    const TlsChannelCredentialsOptions& options) {
  return WrapChannelCredentials(
      grpc_tls_credentials_create(options.c_credentials_options()));
}

}

std::shared_ptr<CallCredentials> GoogleComputeEngineCredentials() {
  grpc::internal::GrpcLibrary init;
  return WrapCallCredentials(
      grpc_google_compute_engine_credentials_create(nullptr));
}

std::shared_ptr<CallCredentials> ServiceAccountJWTAccessCredentials(
    const std::string& json_key, long token_lifetime_seconds) {
  grpc::internal::GrpcLibrary init;
  if (token_lifetime_seconds <= 0) {
    LOG(ERROR) << "Trying to create JWTCredentials with non-positive lifetime";
    return WrapCallCredentials(nullptr);
  }
  gpr_timespec lifetime =
      gpr_time_from_seconds(token_lifetime_seconds, GPR_TIMESPAN);
  return WrapCallCredentials(grpc_service_account_jwt_access_credentials_create(
      json_key.c_str(), lifetime, nullptr));
}

std::shared_ptr<CallCredentials> GoogleRefreshTokenCredentials(
    const std::string& json_refresh_token) {
  grpc::internal::GrpcLibrary init;
  return WrapCallCredentials(grpc_google_refresh_token_credentials_create(
      json_refresh_token.c_str(), nullptr));
}

std::shared_ptr<CallCredentials> AccessTokenCredentials(
    const std::string& access_token) {
  grpc::internal::GrpcLibrary init;
  return WrapCallCredentials(
      grpc_access_token_credentials_create(access_token.c_str(), nullptr));
}

std::shared_ptr<CallCredentials> GoogleIAMCredentials(
    const std::string& authorization_token,
    const std::string& authority_selector) {
  grpc::internal::GrpcLibrary init;
  return WrapCallCredentials(grpc_google_iam_credentials_create(
      authorization_token.c_str(), authority_selector.c_str(), nullptr));
}

std::shared_ptr<ChannelCredentials> CompositeChannelCredentials(
    const std::shared_ptr<ChannelCredentials>& channel_creds,
    const std::shared_ptr<CallCredentials>& call_creds) {

  return channel_creds->c_creds_ == nullptr
             ? nullptr
             : WrapChannelCredentials(grpc_composite_channel_credentials_create(
                   channel_creds->c_creds_, call_creds->c_creds_, nullptr));
}

class CompositeCallCredentialsImpl : public CallCredentials {
 public:
  CompositeCallCredentialsImpl(const std::shared_ptr<CallCredentials>& creds1,
                               const std::shared_ptr<CallCredentials>& creds2)
      : CallCredentials(grpc_composite_call_credentials_create(
            creds1->c_creds_, creds2->c_creds_, nullptr)) {}
};

std::shared_ptr<CallCredentials> CompositeCallCredentials(
    const std::shared_ptr<CallCredentials>& creds1,
    const std::shared_ptr<CallCredentials>& creds2) {
  return std::make_shared<CompositeCallCredentialsImpl>(creds1, creds2);
}

namespace {

void UnrefMetadata(const std::vector<grpc_metadata>& md) {
  for (const auto& metadatum : md) {
    grpc_slice_unref(metadatum.key);
    grpc_slice_unref(metadatum.value);
  }
}

class MetadataCredentialsPluginWrapper final : private internal::GrpcLibrary {
 public:
  static void Destroy(void* wrapper) {
    if (wrapper == nullptr) return;
    grpc_event_engine::experimental::GetDefaultEventEngine()->Run([wrapper] {
      grpc_core::ExecCtx exec_ctx;
      delete static_cast<MetadataCredentialsPluginWrapper*>(wrapper);
    });
  }

  static int GetMetadata(
      void* wrapper, grpc_auth_metadata_context context,
      grpc_credentials_plugin_metadata_cb cb, void* user_data,
      grpc_metadata creds_md[GRPC_METADATA_CREDENTIALS_PLUGIN_SYNC_MAX],
      size_t* num_creds_md, grpc_status_code* status,
      const char** error_details) {
    CHECK(wrapper);
    MetadataCredentialsPluginWrapper* w =
        static_cast<MetadataCredentialsPluginWrapper*>(wrapper);
    if (!w->plugin_) {
      *num_creds_md = 0;
      *status = GRPC_STATUS_OK;
      *error_details = nullptr;
      return 1;
    }
    if (w->plugin_->IsBlocking()) {

      grpc_auth_metadata_context context_copy = grpc_auth_metadata_context();
      grpc_auth_metadata_context_copy(&context, &context_copy);

      w->thread_pool_->Add([w, context_copy, cb, user_data]() mutable {
        w->MetadataCredentialsPluginWrapper::InvokePlugin(
            context_copy, cb, user_data, nullptr, nullptr, nullptr, nullptr);
        grpc_auth_metadata_context_reset(&context_copy);
      });
      return 0;
    } else {

      w->InvokePlugin(context, cb, user_data, creds_md, num_creds_md, status,
                      error_details);
      return 1;
    }
  }

  static char* DebugString(void* wrapper) {
    CHECK(wrapper);
    MetadataCredentialsPluginWrapper* w =
        static_cast<MetadataCredentialsPluginWrapper*>(wrapper);
    return gpr_strdup(w->plugin_->DebugString().c_str());
  }

  explicit MetadataCredentialsPluginWrapper(
      std::unique_ptr<MetadataCredentialsPlugin> plugin)
      : plugin_(std::move(plugin)) {
    if (plugin_->IsBlocking()) {
      thread_pool_.reset(CreateDefaultThreadPool());
    }
  }

 private:
  void InvokePlugin(
      grpc_auth_metadata_context context,
      grpc_credentials_plugin_metadata_cb cb, void* user_data,
      grpc_metadata creds_md[GRPC_METADATA_CREDENTIALS_PLUGIN_SYNC_MAX],
      size_t* num_creds_md, grpc_status_code* status_code,
      const char** error_details) {
    std::multimap<std::string, std::string> metadata;

    SecureAuthContext cpp_channel_auth_context(
        const_cast<grpc_auth_context*>(context.channel_auth_context));

    Status status =
        plugin_->GetMetadata(context.service_url, context.method_name,
                             cpp_channel_auth_context, &metadata);
    std::vector<grpc_metadata> md;
    for (auto& metadatum : metadata) {
      grpc_metadata md_entry;
      md_entry.key = SliceFromCopiedString(metadatum.first);
      md_entry.value = SliceFromCopiedString(metadatum.second);
      md.push_back(md_entry);
    }
    if (creds_md != nullptr) {

      if (md.size() > GRPC_METADATA_CREDENTIALS_PLUGIN_SYNC_MAX) {
        *num_creds_md = 0;
        *status_code = GRPC_STATUS_INTERNAL;
        *error_details = gpr_strdup(
            "blocking plugin credentials returned too many metadata keys");
        UnrefMetadata(md);
      } else {
        for (const auto& elem : md) {
          creds_md[*num_creds_md].key = elem.key;
          creds_md[*num_creds_md].value = elem.value;
          ++(*num_creds_md);
        }
        *status_code = static_cast<grpc_status_code>(status.error_code());
        *error_details =
            status.ok() ? nullptr : gpr_strdup(status.error_message().c_str());
      }
    } else {

      cb(user_data, md.empty() ? nullptr : &md[0], md.size(),
         static_cast<grpc_status_code>(status.error_code()),
         status.error_message().c_str());
      UnrefMetadata(md);
    }
  }

  std::unique_ptr<ThreadPoolInterface> thread_pool_;
  std::unique_ptr<MetadataCredentialsPlugin> plugin_;
};

}

namespace experimental {
std::shared_ptr<CallCredentials> MetadataCredentialsFromPlugin(
    std::unique_ptr<MetadataCredentialsPlugin> plugin,
    grpc_security_level min_security_level) {
  grpc::internal::GrpcLibrary init;
  const char* type = plugin->GetType();
  MetadataCredentialsPluginWrapper* wrapper =
      new MetadataCredentialsPluginWrapper(std::move(plugin));
  grpc_metadata_credentials_plugin c_plugin = {
      MetadataCredentialsPluginWrapper::GetMetadata,
      MetadataCredentialsPluginWrapper::DebugString,
      MetadataCredentialsPluginWrapper::Destroy, wrapper, type};
  return WrapCallCredentials(grpc_metadata_credentials_create_from_plugin(
      c_plugin, min_security_level, nullptr));
}

}

std::shared_ptr<CallCredentials> MetadataCredentialsFromPlugin(
    std::unique_ptr<MetadataCredentialsPlugin> plugin) {
  return experimental::MetadataCredentialsFromPlugin(
      std::move(plugin), GRPC_PRIVACY_AND_INTEGRITY);
}

}
