
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_TLS_SECURITY_CONNECTOR_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_TLS_SECURITY_CONNECTOR_H

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>

#include <map>
#include <optional>
#include <string>

#include "absl/base/thread_annotations.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "src/core/credentials/transport/security_connector.h"
#include "src/core/credentials/transport/tls/grpc_tls_certificate_distributor.h"
#include "src/core/credentials/transport/tls/ssl_utils.h"
#include "src/core/handshaker/handshaker.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/tsi/ssl/key_logging/ssl_key_logging.h"
#include "src/core/tsi/ssl_transport_security.h"
#include "src/core/tsi/transport_security_interface.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"

using TlsSessionKeyLogger = tsi::TlsSessionKeyLoggerCache::TlsSessionKeyLogger;

namespace grpc_core {

class TlsChannelSecurityConnector final
    : public grpc_channel_security_connector {
 public:

  static RefCountedPtr<grpc_channel_security_connector>
  CreateTlsChannelSecurityConnector(
      RefCountedPtr<grpc_channel_credentials> channel_creds,
      RefCountedPtr<grpc_tls_credentials_options> options,
      RefCountedPtr<grpc_call_credentials> request_metadata_creds,
      const char* target_name, const char* overridden_target_name,
      tsi_ssl_session_cache* ssl_session_cache);

  TlsChannelSecurityConnector(
      RefCountedPtr<grpc_channel_credentials> channel_creds,
      RefCountedPtr<grpc_tls_credentials_options> options,
      RefCountedPtr<grpc_call_credentials> request_metadata_creds,
      const char* target_name, const char* overridden_target_name,
      tsi_ssl_session_cache* ssl_session_cache);

  ~TlsChannelSecurityConnector() override;

  void add_handshakers(const ChannelArgs& args,
                       grpc_pollset_set* interested_parties,
                       HandshakeManager* handshake_mgr) override;

  void check_peer(tsi_peer peer, grpc_endpoint* ep, const ChannelArgs& ,
                  RefCountedPtr<grpc_auth_context>* auth_context,
                  grpc_closure* on_peer_checked) override;

  void cancel_check_peer(grpc_closure* on_peer_checked,
                         grpc_error_handle error) override;

  int cmp(const grpc_security_connector* other_sc) const override;

  ArenaPromise<absl::Status> CheckCallHost(
      absl::string_view host, grpc_auth_context* auth_context) override;

  tsi_ssl_client_handshaker_factory* ClientHandshakerFactoryForTesting() {
    MutexLock lock(&mu_);
    return client_handshaker_factory_;
  };

  std::optional<absl::string_view> RootCertsForTesting() {
    MutexLock lock(&mu_);
    return pem_root_certs_;
  }

  std::optional<PemKeyCertPairList> KeyCertPairListForTesting() {
    MutexLock lock(&mu_);
    return pem_key_cert_pair_list_;
  }

 private:

  class TlsChannelCertificateWatcher : public grpc_tls_certificate_distributor::
                                           TlsCertificatesWatcherInterface {
   public:
    explicit TlsChannelCertificateWatcher(
        TlsChannelSecurityConnector* security_connector)
        : security_connector_(security_connector) {}
    void OnCertificatesChanged(
        std::optional<absl::string_view> root_certs,
        std::optional<PemKeyCertPairList> key_cert_pairs) override;
    void OnError(grpc_error_handle root_cert_error,
                 grpc_error_handle identity_cert_error) override;

   private:
    TlsChannelSecurityConnector* security_connector_ = nullptr;
  };

  class ChannelPendingVerifierRequest {
   public:
    ChannelPendingVerifierRequest(
        RefCountedPtr<TlsChannelSecurityConnector> security_connector,
        grpc_closure* on_peer_checked, tsi_peer peer, const char* target_name);

    ~ChannelPendingVerifierRequest();

    void Start();

    grpc_tls_custom_verification_check_request* request() { return &request_; }

   private:
    void OnVerifyDone(bool run_callback_inline, absl::Status status);

    RefCountedPtr<TlsChannelSecurityConnector> security_connector_;
    grpc_tls_custom_verification_check_request request_;
    grpc_closure* on_peer_checked_;
  };

  grpc_security_status UpdateHandshakerFactoryLocked()
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

  Mutex mu_;

  Mutex verifier_request_map_mu_;
  RefCountedPtr<grpc_tls_credentials_options> options_;
  grpc_tls_certificate_distributor::TlsCertificatesWatcherInterface*
      certificate_watcher_ = nullptr;
  std::string target_name_;
  std::string overridden_target_name_;
  tsi_ssl_client_handshaker_factory* client_handshaker_factory_
      ABSL_GUARDED_BY(mu_) = nullptr;
  tsi_ssl_session_cache* ssl_session_cache_ ABSL_GUARDED_BY(mu_) = nullptr;
  RefCountedPtr<TlsSessionKeyLogger> tls_session_key_logger_;
  std::optional<absl::string_view> pem_root_certs_ ABSL_GUARDED_BY(mu_);
  std::optional<PemKeyCertPairList> pem_key_cert_pair_list_
      ABSL_GUARDED_BY(mu_);
  std::map<grpc_closure* , ChannelPendingVerifierRequest*>
      pending_verifier_requests_ ABSL_GUARDED_BY(verifier_request_map_mu_);
};

class TlsServerSecurityConnector final : public grpc_server_security_connector {
 public:

  static RefCountedPtr<grpc_server_security_connector>
  CreateTlsServerSecurityConnector(
      RefCountedPtr<grpc_server_credentials> server_creds,
      RefCountedPtr<grpc_tls_credentials_options> options);

  TlsServerSecurityConnector(
      RefCountedPtr<grpc_server_credentials> server_creds,
      RefCountedPtr<grpc_tls_credentials_options> options);
  ~TlsServerSecurityConnector() override;

  void add_handshakers(const ChannelArgs& args,
                       grpc_pollset_set* interested_parties,
                       HandshakeManager* handshake_mgr) override;

  void check_peer(tsi_peer peer, grpc_endpoint* ep, const ChannelArgs& ,
                  RefCountedPtr<grpc_auth_context>* auth_context,
                  grpc_closure* on_peer_checked) override;

  void cancel_check_peer(grpc_closure* ,
                         grpc_error_handle error) override;

  int cmp(const grpc_security_connector* other) const override;

  tsi_ssl_server_handshaker_factory* ServerHandshakerFactoryForTesting() {
    MutexLock lock(&mu_);
    return server_handshaker_factory_;
  };

  std::optional<absl::string_view> RootCertsForTesting() {
    MutexLock lock(&mu_);
    return pem_root_certs_;
  }

  std::optional<PemKeyCertPairList> KeyCertPairListForTesting() {
    MutexLock lock(&mu_);
    return pem_key_cert_pair_list_;
  }

 private:

  class TlsServerCertificateWatcher : public grpc_tls_certificate_distributor::
                                          TlsCertificatesWatcherInterface {
   public:
    explicit TlsServerCertificateWatcher(
        TlsServerSecurityConnector* security_connector)
        : security_connector_(security_connector) {}
    void OnCertificatesChanged(
        std::optional<absl::string_view> root_certs,
        std::optional<PemKeyCertPairList> key_cert_pairs) override;

    void OnError(grpc_error_handle root_cert_error,
                 grpc_error_handle identity_cert_error) override;

   private:
    TlsServerSecurityConnector* security_connector_ = nullptr;
  };

  class ServerPendingVerifierRequest {
   public:
    ServerPendingVerifierRequest(
        RefCountedPtr<TlsServerSecurityConnector> security_connector,
        grpc_closure* on_peer_checked, tsi_peer peer);

    ~ServerPendingVerifierRequest();

    void Start();

    grpc_tls_custom_verification_check_request* request() { return &request_; }

   private:
    void OnVerifyDone(bool run_callback_inline, absl::Status status);

    RefCountedPtr<TlsServerSecurityConnector> security_connector_;
    grpc_tls_custom_verification_check_request request_;
    grpc_closure* on_peer_checked_;
  };

  grpc_security_status UpdateHandshakerFactoryLocked()
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

  Mutex mu_;

  Mutex verifier_request_map_mu_;
  RefCountedPtr<grpc_tls_credentials_options> options_;
  grpc_tls_certificate_distributor::TlsCertificatesWatcherInterface*
      certificate_watcher_ = nullptr;
  tsi_ssl_server_handshaker_factory* server_handshaker_factory_
      ABSL_GUARDED_BY(mu_) = nullptr;
  std::optional<absl::string_view> pem_root_certs_ ABSL_GUARDED_BY(mu_);
  std::optional<PemKeyCertPairList> pem_key_cert_pair_list_
      ABSL_GUARDED_BY(mu_);
  RefCountedPtr<TlsSessionKeyLogger> tls_session_key_logger_;
  std::map<grpc_closure* , ServerPendingVerifierRequest*>
      pending_verifier_requests_ ABSL_GUARDED_BY(verifier_request_map_mu_);
};

}

#endif
