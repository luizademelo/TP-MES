Here's the commented version of the code:

```c++
// Copyright 2020 gRPC authors.

#include "src/core/credentials/transport/tls/grpc_tls_certificate_distributor.h"

#include <grpc/credentials.h>
#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>

#include "absl/log/check.h"
#include "absl/status/status.h"

// Sets key materials (root certs and/or identity cert pairs) for a given certificate name
// and notifies all relevant watchers about the change.
void grpc_tls_certificate_distributor::SetKeyMaterials(
    const std::string& cert_name, std::optional<std::string> pem_root_certs,
    std::optional<grpc_core::PemKeyCertPairList> pem_key_cert_pairs) {
  // At least one of root certs or key pairs must be provided
  CHECK(pem_root_certs.has_value() || pem_key_cert_pairs.has_value());
  grpc_core::MutexLock lock(&mu_);
  auto& cert_info = certificate_info_map_[cert_name];
  
  // Handle root certificates update if provided
  if (pem_root_certs.has_value()) {
    // Clear any previous root cert error
    cert_info.SetRootError(absl::OkStatus());
    
    // Notify all watchers monitoring this root certificate
    for (auto* watcher_ptr : cert_info.root_cert_watchers) {
      CHECK_NE(watcher_ptr, nullptr);
      const auto watcher_it = watchers_.find(watcher_ptr);
      CHECK(watcher_it != watchers_.end());
      CHECK(watcher_it->second.root_cert_name.has_value());
      
      // Determine which identity certs to report with these root certs
      std::optional<grpc_core::PemKeyCertPairList> pem_key_cert_pairs_to_report;
      if (pem_key_cert_pairs.has_value() &&
          watcher_it->second.identity_cert_name == cert_name) {
        // If watcher is watching both root and identity on same cert name
        pem_key_cert_pairs_to_report = pem_key_cert_pairs;
      } else if (watcher_it->second.identity_cert_name.has_value()) {
        // If watcher is watching identity on different cert name
        auto& identity_cert_info =
            certificate_info_map_[*watcher_it->second.identity_cert_name];
        if (!identity_cert_info.pem_key_cert_pairs.empty()) {
          pem_key_cert_pairs_to_report = identity_cert_info.pem_key_cert_pairs;
        }
      }
      // Notify watcher with updated certificates
      watcher_ptr->OnCertificatesChanged(
          pem_root_certs, std::move(pem_key_cert_pairs_to_report));
    }
    // Store the new root certificates
    cert_info.pem_root_certs = std::move(*pem_root_certs);
  }
  
  // Handle identity key-cert pairs update if provided
  if (pem_key_cert_pairs.has_value()) {
    // Clear any previous identity cert error
    cert_info.SetIdentityError(absl::OkStatus());
    
    // Notify all watchers monitoring this identity certificate
    for (const auto watcher_ptr : cert_info.identity_cert_watchers) {
      CHECK_NE(watcher_ptr, nullptr);
      const auto watcher_it = watchers_.find(watcher_ptr);
      CHECK(watcher_it != watchers_.end());
      CHECK(watcher_it->second.identity_cert_name.has_value());
      
      // Determine which root certs to report with these identity certs
      std::optional<absl::string_view> pem_root_certs_to_report;
      if (pem_root_certs.has_value() &&
          watcher_it->second.root_cert_name == cert_name) {
        // Skip if we already notified this watcher in root certs section
        continue;
      } else if (watcher_it->second.root_cert_name.has_value()) {
        // If watcher is watching root on different cert name
        auto& root_cert_info =
            certificate_info_map_[*watcher_it->second.root_cert_name];
        if (!root_cert_info.pem_root_certs.empty()) {
          pem_root_certs_to_report = root_cert_info.pem_root_certs;
        }
      }
      // Notify watcher with updated certificates
      watcher_ptr->OnCertificatesChanged(pem_root_certs_to_report,
                                         pem_key_cert_pairs);
    }
    // Store the new identity key-cert pairs
    cert_info.pem_key_cert_pairs = std::move(*pem_key_cert_pairs);
  }
}

// Checks if root certificates exist for the given certificate name
bool grpc_tls_certificate_distributor::HasRootCerts(
    const std::string& root_cert_name) {
  grpc_core::MutexLock lock(&mu_);
  const auto it = certificate_info_map_.find(root_cert_name);
  return it != certificate_info_map_.end() &&
         !it->second.pem_root_certs.empty();
};

// Checks if identity key-cert pairs exist for the given certificate name
bool grpc_tls_certificate_distributor::HasKeyCertPairs(
    const std::string& identity_cert_name) {
  grpc_core::MutexLock lock(&mu_);
  const auto it = certificate_info_map_.find(identity_cert_name);
  return it != certificate_info_map_.end() &&
         !it->second.pem_key_cert_pairs.empty();
};

// Sets error status for a certificate and notifies all relevant watchers
void grpc_tls_certificate_distributor::SetErrorForCert(
    const std::string& cert_name,
    std::optional<grpc_error_handle> root_cert_error,
    std::optional<grpc_error_handle> identity_cert_error) {
  // At least one error must be provided
  CHECK(root_cert_error.has_value() || identity_cert_error.has_value());
  grpc_core::MutexLock lock(&mu_);
  CertificateInfo& cert_info = certificate_info_map_[cert_name];
  
  // Handle root certificate error if provided
  if (root_cert_error.has_value()) {
    // Notify all watchers monitoring this root certificate
    for (auto* watcher_ptr : cert_info.root_cert_watchers) {
      CHECK_NE(watcher_ptr, nullptr);
      const auto watcher_it = watchers_.find(watcher_ptr);
      CHECK(watcher_it != watchers_.end());

      // Determine which identity error to report with this root error
      grpc_error_handle identity_cert_error_to_report;
      if (identity_cert_error.has_value() &&
          watcher_it->second.identity_cert_name == cert_name) {
        // If watcher is watching both root and identity on same cert name
        identity_cert_error_to_report = *identity_cert_error;
      } else if (watcher_it->second.identity_cert_name.has_value()) {
        // If watcher is watching identity on different cert name
        auto& identity_cert_info =
            certificate_info_map_[*watcher_it->second.identity_cert_name];
        identity_cert_error_to_report = identity_cert_info.identity_cert_error;
      }
      // Notify watcher with the errors
      watcher_ptr->OnError(*root_cert_error, identity_cert_error_to_report);
    }
    // Store the root certificate error
    cert_info.SetRootError(*root_cert_error);
  }
  
  // Handle identity certificate error if provided
  if (identity_cert_error.has_value()) {
    // Notify all watchers monitoring this identity certificate
    for (auto* watcher_ptr : cert_info.identity_cert_watchers) {
      CHECK_NE(watcher_ptr, nullptr);
      const auto watcher_it = watchers_.find(watcher_ptr);
      CHECK(watcher_it != watchers_.end());

      // Determine which root error to report with this identity error
      grpc_error_handle root_cert_error_to_report;
      if (root_cert_error.has_value() &&
          watcher_it->second.root_cert_name == cert_name) {
        // Skip if we already notified this watcher in root error section
        continue;
      } else if (watcher_it->second.root_cert_name.has_value()) {
        // If watcher is watching root on different cert name
        auto& root_cert_info =
            certificate_info_map_[*watcher_it->second.root_cert_name];
        root_cert_error_to_report = root_cert_info.root_cert_error;
      }
      // Notify watcher with the errors
      watcher_ptr->OnError(root_cert_error_to_report, *identity_cert_error);
    }
    // Store the identity certificate error
    cert_info.SetIdentityError(*identity_cert_error);
  }
};

// Sets a global error status for all certificates and notifies all watchers
void grpc_tls_certificate_distributor::SetError(grpc_error_handle error) {
  CHECK(!error.ok());
  grpc_core::MutexLock lock(&mu_);
  
  // Notify all watchers with appropriate errors
  for (const auto& watcher : watchers_) {
    const auto watcher_ptr = watcher.first;
    CHECK_NE(watcher_ptr, nullptr);
    const auto& watcher_info = watcher.second;
    watcher_ptr->OnError(
        watcher_info.root_cert_name.has_value() ? error : absl::OkStatus(),
        watcher_info.identity_cert_name.has_value() ? error : absl::OkStatus());
  }
  
  // Set error status for all certificates
  for (auto& cert_info_entry : certificate_info_map_) {
    auto& cert_info = cert_info_entry.second;
    cert_info.SetRootError(error);
    cert_info.SetIdentityError(error);
  }
};

// Registers a new watcher for certificate updates
void grpc_tls_certificate_distributor::WatchTlsCertificates(
    std::unique_ptr<TlsCertificatesWatcherInterface> watcher,
    std::optional<std::string> root_cert_name,
    std::optional<std::string> identity_cert_name) {
  bool start_watching_root_cert = false;
  bool already_watching_identity_for_root_cert = false;
  bool start_watching_identity_cert = false;
  bool already_watching_root_for_identity_cert = false;
  
  // At least one of root or identity cert name must be provided
  CHECK(root_cert_name.has_value() || identity_cert_name.has_value());
  TlsCertificatesWatcherInterface* watcher_ptr = watcher.get();
  CHECK_NE(watcher_ptr, nullptr);

  {
    grpc_core::MutexLock lock(&mu_);
    const auto watcher_it = watchers_.find(watcher_ptr);

    // Watcher must not already exist
    CHECK(watcher_it == watchers_.end());
    
    // Store the watcher information
    watchers_[watcher_ptr] = {std::move(watcher), root_cert_name,
                              identity_cert_name};
    std::optional<absl::string_view> updated_root_certs;
    std::optional<grpc_core::PemKeyCertPairList> updated_identity_pairs;
    grpc_error_handle root_error;
    grpc_error_handle identity_error;
    
    // Handle root certificate watching
    if (root_cert_name.has_value()) {
      CertificateInfo& cert_info = certificate_info_map_[*root_cert_name];
      start_watching_root_cert = cert_info.root_cert_watchers.empty();
      already_watching_identity_for_root_cert =
          !cert_info.identity_cert_watchers.empty();
      cert_info.root_cert_watchers.insert(watcher_ptr);
      root_error = cert_info.root_cert_error;

      // If root certs already exist, prepare to notify watcher
      if (!cert_info.pem_root_certs.empty()) {
        updated_root_certs = cert_info.pem_root_certs;
      }
    }
    
    // Handle identity certificate watching
    if (identity_cert_name.has_value()) {
      CertificateInfo& cert_info = certificate_info_map_[*identity_cert_name];
      start_watching_identity_cert = cert_info.identity_cert_watchers.empty();
      already_watching_root_for_identity_cert =
          !cert_info.root_cert_watchers.empty();
      cert_info.identity_cert_watchers.insert(watcher_ptr);
      identity_error = cert_info.identity_cert_error;

      // If identity certs already exist, prepare to notify watcher
      if (!cert_info.pem_key_cert_pairs.empty()) {
        updated_identity_pairs = cert_info.pem_key_cert_pairs;
      }
    }

    // Notify watcher immediately if certs are already available
    if (updated_root_certs.has_value() || updated_identity_pairs.has_value()) {
      watcher_ptr->OnCertificatesChanged(updated_root_certs,
                                         std::move(updated_identity_pairs));
    }

    // Notify watcher immediately if errors exist
    if (!root_error.ok() || !identity_error.ok()) {
      watcher_ptr->OnError(root_error, identity_error);
    }
  }

  // Notify callback about watch status changes
  {
    grpc_core::MutexLock lock(&callback_mu_);
    if (watch_status_callback_ != nullptr) {
      if (root_cert_name == identity_cert_name &&
          (start_watching_root_cert || start_watching_identity_cert)) {
        // Special case when watching same cert name for both types
        watch_status_callback_(*root_cert_name, start_watching_root_cert,
                               start_watching_identity_cert);
      } else {
        // Normal case for different cert names
        if (start_watching_root_cert) {
          watch_status_callback_(*root_cert_name, true,
                                 already_watching_identity_for_root_cert);
        }
        if (start_watching_identity_cert) {
          watch_status_callback_(*identity_cert_name,
                                 already_watching_root_for_identity_cert, true);
        }
      }
    }
  }
};

// Unregisters a watcher and cleans up if no more watchers exist
void grpc_tls_certificate_distributor::CancelTlsCertificatesWatch(
    TlsCertificatesWatcherInterface* watcher) {
  std::optional<std::string> root_cert_name;
  std::optional<std::string> identity_cert_name;
  bool stop_watching_root_cert = false;
  bool already_watching_identity_for_root_cert = false;
  bool stop_watching_identity_cert = false;
  bool already_watching_root_for_identity_cert = false;

  {
    grpc_core::MutexLock lock(&mu_);
    auto it = watchers_.find(watcher);
    if (it == watchers_.end()) return;
    
    // Get watcher information before removing it
    WatcherInfo& watcher_info = it->second;
    root_cert_name = std::move(watcher_info.root_cert_name);
    identity_cert_name = std::move(watcher_info.identity_cert_name);
    watchers_.erase(it);
    
    // Handle root certificate unwatching
    if (root_cert_name.has_value()) {
      auto it = certificate_info_map_.find(*root_cert_name);
      CHECK(it != certificate_info_map_.end());
      CertificateInfo& cert_info = it->second;
      cert_info.root_cert_watchers.erase(watcher);
      stop_watching_root_cert = cert_info.root_cert_watchers.empty();
      already_watching_identity_for_root_cert =
          !cert_info.identity_cert_watchers.empty();
      // Clean up if no more watchers for this certificate
      if (stop_watching_root_cert && !already_watching_identity_for_root_cert) {
        certificate_info_map_.erase(it);
      }
    }
    
    // Handle identity certificate unwatching
    if (identity_cert_name.has_value()) {
      auto it = certificate_info_map_.find(*identity_cert_name);
      CHECK(it != certificate_info_map_.end());
      CertificateInfo& cert_info = it->second;
      cert_info.identity_cert_watchers.erase(watcher);
      stop_watching_identity_cert = cert_info.identity_cert_watchers.empty();
      already_watching_root_for_identity_cert =
          !cert_info.root_cert_watchers.empty();
      // Clean up if no more watchers for this certificate
      if (stop_watching_identity_cert &&
          !already_watching_root_for_identity_cert) {
        certificate_info_map_.erase(it);
      }
    }
  }

  // Notify callback about watch status changes
  {
    grpc_core::MutexLock lock(&callback_mu_);
    if (watch_status_callback_ != nullptr) {
      if (root_cert_name == identity_cert_name &&
          (stop_watching_root_cert || stop_watching_identity_cert)) {
        // Special case when unwatching same cert name for both types
        watch_status_callback_(*root_cert_name, !stop_watching_root_cert,
                               !stop_watching_identity_cert);
      } else {
        // Normal case for different cert names
        if (stop_watching_root_cert) {
          watch_status_callback_(*root_cert_name, false,
                                 already_watching_identity_for_root_cert);
        }
        if (stop_watching_identity_cert) {
          watch_status_callback_(*identity_cert_name,
                                 already_watching_root_for_identity_cert,
                                 false);
        }
      }
    }
  }
};

// Creates a new TLS identity pairs container
grpc_tls_identity_pairs* grpc_tls_identity_pairs_create() {
  return new grpc_tls_identity_pairs();
}

// Adds a key-cert pair to a TLS identity pairs container
void grpc_tls_identity_pairs_add_pair(grpc_tls_identity_pairs* pairs,
                                      const char* private_key,
                                      const char* cert_chain) {
  CHECK_NE(pairs, nullptr);
  CHECK_NE(private_key, nullptr);
  CHECK_NE(cert_chain, nullptr);
  pairs->pem_key_cert_pairs.emplace_back(private_key, cert_chain);
}

// Destroys a TLS identity pairs container
void grpc_tls_identity_pairs_destroy(grpc_tls_identity_pairs* pairs) {
  CHECK_NE(pairs, nullptr);
  delete pairs;
}
```