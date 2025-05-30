
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_ALTS_ALTS_CREDENTIALS_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_ALTS_ALTS_CREDENTIALS_H

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>

#include "src/core/credentials/transport/security_connector.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/unique_type_name.h"
#include "src/core/util/useful.h"

class grpc_alts_credentials final : public grpc_channel_credentials {
 public:
  grpc_alts_credentials(const grpc_alts_credentials_options* options,
                        const char* handshaker_service_url);
  ~grpc_alts_credentials() override;

  grpc_core::RefCountedPtr<grpc_channel_security_connector>
  create_security_connector(
      grpc_core::RefCountedPtr<grpc_call_credentials> call_creds,
      const char* target_name, grpc_core::ChannelArgs* args) override;

  static grpc_core::UniqueTypeName Type();

  grpc_core::UniqueTypeName type() const override { return Type(); }

  const grpc_alts_credentials_options* options() const { return options_; }
  grpc_alts_credentials_options* mutable_options() { return options_; }
  const char* handshaker_service_url() const { return handshaker_service_url_; }

 private:
  int cmp_impl(const grpc_channel_credentials* other) const override {

    return grpc_core::QsortCompare(
        static_cast<const grpc_channel_credentials*>(this), other);
  }

  grpc_alts_credentials_options* options_;
  char* handshaker_service_url_;
};

class grpc_alts_server_credentials final : public grpc_server_credentials {
 public:
  grpc_alts_server_credentials(const grpc_alts_credentials_options* options,
                               const char* handshaker_service_url);
  ~grpc_alts_server_credentials() override;

  grpc_core::RefCountedPtr<grpc_server_security_connector>
  create_security_connector(const grpc_core::ChannelArgs& ) override;

  static grpc_core::UniqueTypeName Type();

  grpc_core::UniqueTypeName type() const override { return Type(); }

  const grpc_alts_credentials_options* options() const { return options_; }
  grpc_alts_credentials_options* mutable_options() { return options_; }
  const char* handshaker_service_url() const { return handshaker_service_url_; }

 private:
  grpc_alts_credentials_options* options_;
  char* handshaker_service_url_;
};

grpc_channel_credentials* grpc_alts_credentials_create_customized(
    const grpc_alts_credentials_options* options,
    const char* handshaker_service_url, bool enable_untrusted_alts);

grpc_server_credentials* grpc_alts_server_credentials_create_customized(
    const grpc_alts_credentials_options* options,
    const char* handshaker_service_url, bool enable_untrusted_alts);

#endif
