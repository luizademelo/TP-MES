Here's the commented version of the code:

```c++
// Copyright 2020 gRPC authors.

#include "src/core/credentials/transport/tls/grpc_tls_certificate_provider.h"

#include <grpc/credentials.h>
#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>
#include <stdint.h>
#include <time.h>

#include <algorithm>
#include <utility>
#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "src/core/credentials/transport/tls/ssl_utils.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/tsi/ssl_transport_security_utils.h"
#include "src/core/util/load_file.h"
#include "src/core/util/stat.h"
#include "src/core/util/status_helper.h"

namespace grpc_core {
namespace {

// Validates root certificates in PEM format
// Returns OK status if validation succeeds or if root_certificates is empty
// Returns error status if parsing fails
absl::Status ValidateRootCertificates(absl::string_view root_certificates) {
  if (root_certificates.empty()) return absl::OkStatus();
  absl::StatusOr<std::vector<X509*>> parsed_roots =
      ParsePemCertificateChain(root_certificates);
  if (!parsed_roots.ok()) {
    return absl::Status(
        parsed_roots.status().code(),
        absl::StrCat("Failed to parse root certificates as PEM: ",
                     parsed_roots.status().message()));
  }
  // Clean up parsed certificates
  for (X509* x509 : *parsed_roots) {
    X509_free(x509);
  }
  return absl::OkStatus();
}

// Validates a PEM key-certificate pair
// Returns OK status if validation succeeds or if both inputs are empty
// Returns error status if either cert_chain or private_key fails to parse
absl::Status ValidatePemKeyCertPair(absl::string_view cert_chain,
                                    absl::string_view private_key) {
  if (cert_chain.empty() && private_key.empty()) return absl::OkStatus();

  // Parse and validate certificate chain
  absl::StatusOr<std::vector<X509*>> parsed_certs =
      ParsePemCertificateChain(cert_chain);
  if (!parsed_certs.ok()) {
    return absl::Status(
        parsed_certs.status().code(),
        absl::StrCat("Failed to parse certificate chain as PEM: ",
                     parsed_certs.status().message()));
  }
  // Clean up parsed certificates
  for (X509* x509 : *parsed_certs) {
    X509_free(x509);
  }

  // Parse and validate private key
  absl::StatusOr<EVP_PKEY*> parsed_private_key =
      ParsePemPrivateKey(private_key);
  if (!parsed_private_key.ok()) {
    return absl::Status(parsed_private_key.status().code(),
                        absl::StrCat("Failed to parse private key as PEM: ",
                                     parsed_private_key.status().message()));
  }
  EVP_PKEY_free(*parsed_private_key);
  return absl::OkStatus();
}

}  // namespace

// StaticDataCertificateProvider implementation

// Constructor for static certificate provider
// Takes root certificate and list of key-cert pairs
// Initializes distributor and sets up watch status callback
StaticDataCertificateProvider::StaticDataCertificateProvider(
    std::string root_certificate, PemKeyCertPairList pem_key_cert_pairs)
    : distributor_(MakeRefCounted<grpc_tls_certificate_distributor>()),
      root_certificate_(std::move(root_certificate)),
      pem_key_cert_pairs_(std::move(pem_key_cert_pairs)) {
  // Set up callback for when certificates are being watched
  distributor_->SetWatchStatusCallback([this](std::string cert_name,
                                              bool root_being_watched,
                                              bool identity_being_watched) {
    MutexLock lock(&mu_);
    std::optional<std::string> root_certificate;
    std::optional<PemKeyCertPairList> pem_key_cert_pairs;
    StaticDataCertificateProvider::WatcherInfo& info = watcher_info_[cert_name];
    
    // Handle root certificate watching
    if (!info.root_being_watched && root_being_watched &&
        !root_certificate_.empty()) {
      root_certificate = root_certificate_;
    }
    info.root_being_watched = root_being_watched;
    
    // Handle identity certificate watching
    if (!info.identity_being_watched && identity_being_watched &&
        !pem_key_cert_pairs_.empty()) {
      pem_key_cert_pairs = pem_key_cert_pairs_;
    }
    info.identity_being_watched = identity_being_watched;
    
    // Clean up if no longer being watched
    if (!info.root_being_watched && !info.identity_being_watched) {
      watcher_info_.erase(cert_name);
    }
    
    const bool root_has_update = root_certificate.has_value();
    const bool identity_has_update = pem_key_cert_pairs.has_value();
    
    // Update materials if needed
    if (root_has_update || identity_has_update) {
      distributor_->SetKeyMaterials(cert_name, std::move(root_certificate),
                                    std::move(pem_key_cert_pairs));
    }
    
    // Handle errors for missing certificates
    grpc_error_handle root_cert_error;
    grpc_error_handle identity_cert_error;
    if (root_being_watched && !root_has_update) {
      root_cert_error =
          GRPC_ERROR_CREATE("Unable to get latest root certificates.");
    }
    if (identity_being_watched && !identity_has_update) {
      identity_cert_error =
          GRPC_ERROR_CREATE("Unable to get latest identity certificates.");
    }
    if (!root_cert_error.ok() || !identity_cert_error.ok()) {
      distributor_->SetErrorForCert(cert_name, root_cert_error,
                                    identity_cert_error);
    }
  });
}

// Destructor - clears watch status callback
StaticDataCertificateProvider::~StaticDataCertificateProvider() {
  distributor_->SetWatchStatusCallback(nullptr);
}

// Returns the type name for this certificate provider
UniqueTypeName StaticDataCertificateProvider::type() const {
  static UniqueTypeName::Factory kFactory("StaticData");
  return kFactory.Create();
}

// Validates all stored credentials
// Returns OK if all credentials are valid
// Returns first error encountered if validation fails
absl::Status StaticDataCertificateProvider::ValidateCredentials() const {
  absl::Status status = ValidateRootCertificates(root_certificate_);
  if (!status.ok()) {
    return status;
  }
  for (const PemKeyCertPair& pair : pem_key_cert_pairs_) {
    absl::Status status =
        ValidatePemKeyCertPair(pair.cert_chain(), pair.private_key());
    if (!status.ok()) {
      return status;
    }
  }
  return absl::OkStatus();
}

namespace {

// Helper function to convert timeout in seconds to deadline
gpr_timespec TimeoutSecondsToDeadline(int64_t seconds) {
  return gpr_time_add(gpr_now(GPR_CLOCK_MONOTONIC),
                      gpr_time_from_seconds(seconds, GPR_TIMESPAN));
}

}  // namespace

// Minimum refresh interval for file watcher (1 second)
static constexpr int64_t kMinimumFileWatcherRefreshIntervalSeconds = 1;

// FileWatcherCertificateProvider implementation

// Constructor for file watcher certificate provider
// Takes paths to private key, identity cert, root cert, and refresh interval
FileWatcherCertificateProvider::FileWatcherCertificateProvider(
    std::string private_key_path, std::string identity_certificate_path,
    std::string root_cert_path, int64_t refresh_interval_sec)
    : private_key_path_(std::move(private_key_path)),
      identity_certificate_path_(std::move(identity_certificate_path)),
      root_cert_path_(std::move(root_cert_path)),
      refresh_interval_sec_(refresh_interval_sec),
      distributor_(MakeRefCounted<grpc_tls_certificate_distributor>()) {
  // Enforce minimum refresh interval
  if (refresh_interval_sec_ < kMinimumFileWatcherRefreshIntervalSeconds) {
    VLOG(2) << "FileWatcherCertificateProvider refresh_interval_sec_ set to "
               "value less than minimum. Overriding configured value to "
               "minimum.";
    refresh_interval_sec_ = kMinimumFileWatcherRefreshIntervalSeconds;
  }

  // Validate that private key and identity cert are both present or both absent
  CHECK(private_key_path_.empty() == identity_certificate_path_.empty());

  // Must have at least one of private key or root cert
  CHECK(!private_key_path_.empty() || !root_cert_path_.empty());
  
  // Initialize shutdown event and force first update
  gpr_event_init(&shutdown_event_);
  ForceUpdate();
  
  // Set up refresh thread
  auto thread_lambda = [](void* arg) {
    FileWatcherCertificateProvider* provider =
        static_cast<FileWatcherCertificateProvider*>(arg);
    CHECK_NE(provider, nullptr);
    while (true) {
      void* value = gpr_event_wait(
          &provider->shutdown_event_,
          TimeoutSecondsToDeadline(provider->refresh_interval_sec_));
      if (value != nullptr) {
        return;
      };
      provider->ForceUpdate();
    }
  };
  refresh_thread_ = Thread("FileWatcherCertificateProvider_refreshing_thread",
                           thread_lambda, this);
  refresh_thread_.Start();
  
  // Set up watch status callback similar to StaticDataCertificateProvider
  distributor_->SetWatchStatusCallback([this](std::string cert_name,
                                              bool root_being_watched,
                                              bool identity_being_watched) {
    MutexLock lock(&mu_);
    std::optional<std::string> root_certificate;
    std::optional<PemKeyCertPairList> pem_key_cert_pairs;
    FileWatcherCertificateProvider::WatcherInfo& info =
        watcher_info_[cert_name];
    if (!info.root_being_watched && root_being_watched &&
        !root_certificate_.empty()) {
      root_certificate = root_certificate_;
    }
    info.root_being_watched = root_being_watched;
    if (!info.identity_being_watched && identity_being_watched &&
        !pem_key_cert_pairs_.empty()) {
      pem_key_cert_pairs = pem_key_cert_pairs_;
    }
    info.identity_being_watched = identity_being_watched;
    if (!info.root_being_watched && !info.identity_being_watched) {
      watcher_info_.erase(cert_name);
    }
    ExecCtx exec_ctx;
    if (root_certificate.has_value() || pem_key_cert_pairs.has_value()) {
      distributor_->SetKeyMaterials(cert_name, root_certificate,
                                    pem_key_cert_pairs);
    }
    grpc_error_handle root_cert_error;
    grpc_error_handle identity_cert_error;
    if (root_being_watched && !root_certificate.has_value()) {
      root_cert_error =
          GRPC_ERROR_CREATE("Unable to get latest root certificates.");
    }
    if (identity_being_watched && !pem_key_cert_pairs.has_value()) {
      identity_cert_error =
          GRPC_ERROR_CREATE("Unable to get latest identity certificates.");
    }
    if (!root_cert_error.ok() || !identity_cert_error.ok()) {
      distributor_->SetErrorForCert(cert_name, root_cert_error,
                                    identity_cert_error);
    }
  });
}

// Destructor - stops refresh thread and clears callback
FileWatcherCertificateProvider::~FileWatcherCertificateProvider() {
  distributor_->SetWatchStatusCallback(nullptr);
  gpr_event_set(&shutdown_event_, reinterpret_cast<void*>(1));
  refresh_thread_.Join();
}

// Returns the type name for this certificate provider
UniqueTypeName FileWatcherCertificateProvider::type() const {
  static UniqueTypeName::Factory kFactory("FileWatcher");
  return kFactory.Create();
}

// Validates all stored credentials
// Returns OK if all credentials are valid
// Returns first error encountered if validation fails
absl::Status FileWatcherCertificateProvider::ValidateCredentials() const {
  MutexLock lock(&mu_);
  absl::Status status = ValidateRootCertificates(root_certificate_);
  if (!status.ok()) {
    return status;
  }
  for (const PemKeyCertPair& pair : pem_key_cert_pairs_) {
    absl::Status status =
        ValidatePemKeyCertPair(pair.cert_chain(), pair.private_key());
    if (!status.ok()) {
      return status;
    }
  }
  return absl::OkStatus();
}

// Forces an immediate refresh of certificates from files
void FileWatcherCertificateProvider::ForceUpdate() {
  std::optional<std::string> root_certificate;
  std::optional<PemKeyCertPairList> pem_key_cert_pairs;
  
  // Read root cert if path is configured
  if (!root_cert_path_.empty()) {
    root_certificate = ReadRootCertificatesFromFile(root_cert_path_);
  }
  
  // Read identity cert if path is configured
  if (!private_key_path_.empty()) {
    pem_key_cert_pairs = ReadIdentityKeyCertPairFromFiles(
        private_key_path_, identity_certificate_path_);
  }
  
  MutexLock lock(&mu_);
  
  // Check if root cert changed
  const bool root_cert_changed =
      (!root_certificate.has_value() && !root_certificate_.empty()) ||
      (root_certificate.has_value() && root_certificate_ != *root_certificate);
  if (root_cert_changed) {
    if (root_certificate.has_value()) {
      root_certificate_ = std::move(*root_certificate);
    } else {
      root_certificate_ = "";
    }
  }
  
  // Check if identity cert changed
  const bool identity_cert_changed =
      (!pem_key_cert_pairs.has_value() && !pem_key_cert_pairs_.empty()) ||
      (pem_key_cert_pairs.has_value() &&
       pem_key_cert_pairs_ != *pem_key_cert_pairs);
  if (identity_cert_changed) {
    if (pem_key_cert_pairs.has_value()) {
      pem_key_cert_pairs_ = std::move(*pem_key_cert_pairs);
    } else {
      pem_key_cert_pairs_ = {};
    }
  }
  
  // Notify watchers if anything changed
  if (root_cert_changed || identity_cert_changed) {
    ExecCtx exec_ctx;
    grpc_error_handle root_cert_error =
        GRPC_ERROR_CREATE("Unable to get latest root certificates.");
    grpc_error_handle identity_cert_error =
        GRPC_ERROR_CREATE("Unable to get latest identity certificates.");
    for (const auto& p : watcher_info_) {
      const std::string& cert_name = p.first;
      const WatcherInfo& info = p.second;
      std::optional<std::string> root_to_report;
      std::optional<PemKeyCertPairList> identity_to_report;

      if (info.root_being_watched && !root_certificate_.empty() &&
          root_cert_changed) {
        root_to_report = root_certificate_;
      }
      if (info.identity_being_watched && !pem_key_cert_pairs_.empty() &&
          identity_cert_changed) {
        identity_to_report = pem_key_cert_pairs_;
      }
      if (root_to_report.has_value() || identity_to_report.has_value()) {
        distributor_->SetKeyMaterials(cert_name, std::move(root_to_report),
                                      std::move(identity_to_report));
      }

      const bool report_root_error =
          info.root_being_watched && root_certificate_.empty();
      const bool report_identity_error =
          info.identity_being_watched && pem_key_cert_pairs_.empty();
      if (report_root_error || report_identity_error) {
        distributor_->SetErrorForCert(
            cert_name, report_root_error ? root_cert_error : absl::OkStatus(),
            report_identity_error ? identity_cert_error : absl::OkStatus());
      }
    }
  }
}

// Reads root certificates from file
// Returns contents as string if successful, nullopt if failed
std::optional<std::string>
FileWatcherCertificateProvider::ReadRootCertificatesFromFile(
    const std::string& root_cert_full_path) {
  auto root_slice = LoadFile(root_cert_full_path, false);
  if (!root_slice.ok()) {
    LOG(ERROR) << "Reading file " << root_cert_full_path
               << " failed: " << root_slice.status();
    return std::nullopt;
  }
  return std::string(root_slice->as_string_view());
}

namespace {

// Gets modification time of a file
// Returns 0 if failed to get modification time
time_t GetModificationTime(const char* filename) {
  time_t ts = 0;
  (void)GetFileModificationTime(filename, &ts);
  return ts;
}

}  // namespace

// Reads identity key-cert pair from files with retry logic
// Returns pair if successful, nullopt if failed after retries
std::optional<PemKeyCertPairList>
FileWatcherCertificateProvider::ReadIdentityKeyCertPairFromFiles(
    const std::string& private_key_path,
    const std::string& identity_certificate_path) {
  const int kNumRetryAttempts = 3;
  for (int i = 0; i < kNumRetryAttempts; ++i) {
    // Get modification times before reading
    time_t identity_key_ts_before =
        GetModificationTime(private_key_path.c_str());
    if (identity_key_ts_before == 0) {
      LOG(ERROR) << "Failed to get the file's modification time