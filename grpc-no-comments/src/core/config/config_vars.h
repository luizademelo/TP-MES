// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_CONFIG_CONFIG_VARS_H
#define GRPC_SRC_CORE_CONFIG_CONFIG_VARS_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <atomic>
#include <optional>
#include <string>

#include "absl/strings/string_view.h"
#include "absl/types/optional.h"

namespace grpc_core {

class GPR_DLL ConfigVars {
 public:
  struct Overrides {
    absl::optional<int32_t> client_channel_backup_poll_interval_ms;
    absl::optional<int32_t> channelz_max_orphaned_nodes;
    absl::optional<bool> enable_fork_support;
    absl::optional<bool> abort_on_leaks;
    absl::optional<bool> not_use_system_ssl_roots;
    absl::optional<bool> cpp_experimental_disable_reflection;
    absl::optional<std::string> dns_resolver;
    absl::optional<std::string> verbosity;
    absl::optional<std::string> poll_strategy;
    absl::optional<std::string> system_ssl_roots_dir;
    absl::optional<std::string> default_ssl_roots_file_path;
    absl::optional<std::string> ssl_cipher_suites;
    absl::optional<std::string> experiments;
    absl::optional<std::string> trace;
  };
  ConfigVars(const ConfigVars&) = delete;
  ConfigVars& operator=(const ConfigVars&) = delete;

  static const ConfigVars& Get() {
    auto* p = config_vars_.load(std::memory_order_acquire);
    if (p != nullptr) return *p;
    return Load();
  }
  static void SetOverrides(const Overrides& overrides);

  static void Reset();
  std::string ToString() const;

  absl::string_view Experiments() const { return experiments_; }

  int32_t ClientChannelBackupPollIntervalMs() const {
    return client_channel_backup_poll_interval_ms_;
  }

  absl::string_view DnsResolver() const { return dns_resolver_; }

  absl::string_view Trace() const { return trace_; }

  absl::string_view Verbosity() const { return verbosity_; }

  bool EnableForkSupport() const { return enable_fork_support_; }

  absl::string_view PollStrategy() const { return poll_strategy_; }

  bool AbortOnLeaks() const { return abort_on_leaks_; }

  std::string SystemSslRootsDir() const;

  std::string DefaultSslRootsFilePath() const;

  bool NotUseSystemSslRoots() const { return not_use_system_ssl_roots_; }

  absl::string_view SslCipherSuites() const { return ssl_cipher_suites_; }

  bool CppExperimentalDisableReflection() const {
    return cpp_experimental_disable_reflection_;
  }

  int32_t ChannelzMaxOrphanedNodes() const {
    return channelz_max_orphaned_nodes_;
  }

 private:
  explicit ConfigVars(const Overrides& overrides);
  static const ConfigVars& Load();
  static std::atomic<ConfigVars*> config_vars_;
  int32_t client_channel_backup_poll_interval_ms_;
  int32_t channelz_max_orphaned_nodes_;
  bool enable_fork_support_;
  bool abort_on_leaks_;
  bool not_use_system_ssl_roots_;
  bool cpp_experimental_disable_reflection_;
  std::string dns_resolver_;
  std::string verbosity_;
  std::string poll_strategy_;
  std::string ssl_cipher_suites_;
  std::string experiments_;
  std::string trace_;
  absl::optional<std::string> override_system_ssl_roots_dir_;
  absl::optional<std::string> override_default_ssl_roots_file_path_;
};

}

#endif
