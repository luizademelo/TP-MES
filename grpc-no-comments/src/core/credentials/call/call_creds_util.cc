
// Copyright 2022 gRPC authors.

#include "src/core/credentials/call/call_creds_util.h"

#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>
#include <string.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/credentials/transport/security_connector.h"
#include "src/core/transport/auth_context.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

namespace {

struct ServiceUrlAndMethod {
  std::string service_url;
  absl::string_view method_name;
};

ServiceUrlAndMethod MakeServiceUrlAndMethod(
    const ClientMetadataHandle& initial_metadata,
    const grpc_call_credentials::GetRequestMetadataArgs* args) {
  DCHECK(initial_metadata->get_pointer(HttpPathMetadata()) != nullptr);
  auto service =
      initial_metadata->get_pointer(HttpPathMetadata())->as_string_view();
  auto last_slash = service.find_last_of('/');
  absl::string_view method_name;
  if (last_slash == absl::string_view::npos) {
    LOG(ERROR) << "No '/' found in fully qualified method name";
    service = "";
    method_name = "";
  } else if (last_slash == 0) {
    method_name = "";
  } else {
    method_name = service.substr(last_slash + 1);
    service = service.substr(0, last_slash);
  }
  DCHECK(initial_metadata->get_pointer(HttpAuthorityMetadata()) != nullptr);
  auto host_and_port =
      initial_metadata->get_pointer(HttpAuthorityMetadata())->as_string_view();
  absl::string_view url_scheme = args->security_connector->url_scheme();
  if (url_scheme == GRPC_SSL_URL_SCHEME) {

    auto port_delimiter = host_and_port.find_last_of(':');
    if (port_delimiter != absl::string_view::npos &&
        host_and_port.substr(port_delimiter + 1) == "443") {
      host_and_port = host_and_port.substr(0, port_delimiter);
    }
  }
  return ServiceUrlAndMethod{
      absl::StrCat(url_scheme, "://", host_and_port, service), method_name};
}

}

std::string MakeJwtServiceUrl(
    const ClientMetadataHandle& initial_metadata,
    const grpc_call_credentials::GetRequestMetadataArgs* args) {
  return MakeServiceUrlAndMethod(initial_metadata, args).service_url;
}

grpc_auth_metadata_context MakePluginAuthMetadataContext(
    const ClientMetadataHandle& initial_metadata,
    const grpc_call_credentials::GetRequestMetadataArgs* args) {
  auto fields = MakeServiceUrlAndMethod(initial_metadata, args);
  grpc_auth_metadata_context ctx;
  memset(&ctx, 0, sizeof(ctx));
  ctx.channel_auth_context = args->auth_context != nullptr
                                 ? args->auth_context->Ref().release()
                                 : nullptr;
  ctx.service_url = gpr_strdup(fields.service_url.c_str());
  ctx.method_name = gpr_strdup(std::string(fields.method_name).c_str());
  return ctx;
}

}
