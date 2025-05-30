// Copyright 2023 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_ARES_RESOLVER_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_ARES_RESOLVER_H

#include <grpc/support/port_platform.h>

#include <utility>

#include "absl/status/status.h"
#include "src/core/lib/debug/trace.h"

#if GRPC_ARES == 1

#include <ares.h>
#include <grpc/event_engine/event_engine.h>

#include <list>
#include <memory>

#include "absl/base/thread_annotations.h"
#include "absl/container/flat_hash_map.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/event_engine/grpc_polled_fd.h"
#include "src/core/lib/event_engine/ref_counted_dns_resolver_interface.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/sync.h"

namespace grpc_event_engine::experimental {

class AresResolver : public RefCountedDNSResolverInterface {
 public:
  static absl::StatusOr<grpc_core::OrphanablePtr<AresResolver>>
  CreateAresResolver(absl::string_view dns_server,
                     std::unique_ptr<GrpcPolledFdFactory> polled_fd_factory,
                     std::shared_ptr<EventEngine> event_engine);

  AresResolver(std::unique_ptr<GrpcPolledFdFactory> polled_fd_factory,
               std::shared_ptr<EventEngine> event_engine, ares_channel channel);
  ~AresResolver() override;
  void Orphan() override ABSL_LOCKS_EXCLUDED(mutex_);

  void LookupHostname(EventEngine::DNSResolver::LookupHostnameCallback callback,
                      absl::string_view name, absl::string_view default_port)
      ABSL_LOCKS_EXCLUDED(mutex_) override;
  void LookupSRV(EventEngine::DNSResolver::LookupSRVCallback callback,
                 absl::string_view name) ABSL_LOCKS_EXCLUDED(mutex_) override;
  void LookupTXT(EventEngine::DNSResolver::LookupTXTCallback callback,
                 absl::string_view name) ABSL_LOCKS_EXCLUDED(mutex_) override;

 private:

  struct FdNode {
    FdNode() = default;
    FdNode(ares_socket_t as, std::unique_ptr<GrpcPolledFd> pf)
        : as(as), polled_fd(std::move(pf)) {}
    ares_socket_t as;
    std::unique_ptr<GrpcPolledFd> polled_fd;

    bool readable_registered = false;

    bool writable_registered = false;
    bool already_shutdown = false;
  };
  using FdNodeList = std::list<std::unique_ptr<FdNode>>;

  using CallbackType =
      std::variant<EventEngine::DNSResolver::LookupHostnameCallback,
                   EventEngine::DNSResolver::LookupSRVCallback,
                   EventEngine::DNSResolver::LookupTXTCallback>;

  void CheckSocketsLocked() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mutex_);
  void MaybeStartTimerLocked() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mutex_);
  void OnReadable(FdNode* fd_node, absl::Status status)
      ABSL_LOCKS_EXCLUDED(mutex_);
  void OnWritable(FdNode* fd_node, absl::Status status)
      ABSL_LOCKS_EXCLUDED(mutex_);
  void OnAresBackupPollAlarm() ABSL_LOCKS_EXCLUDED(mutex_);

  static void OnHostbynameDoneLocked(void* arg, int status, int ,
                                     struct hostent* hostent)
      ABSL_NO_THREAD_SAFETY_ANALYSIS;
  static void OnSRVQueryDoneLocked(void* arg, int status, int ,
                                   unsigned char* abuf,
                                   int alen) ABSL_NO_THREAD_SAFETY_ANALYSIS;
  static void OnTXTDoneLocked(void* arg, int status, int ,
                              unsigned char* buf,
                              int len) ABSL_NO_THREAD_SAFETY_ANALYSIS;

  grpc_core::Mutex mutex_;
  bool shutting_down_ ABSL_GUARDED_BY(mutex_) = false;
  ares_channel channel_ ABSL_GUARDED_BY(mutex_);
  FdNodeList fd_node_list_ ABSL_GUARDED_BY(mutex_);
  int id_ ABSL_GUARDED_BY(mutex_) = 0;
  absl::flat_hash_map<int, CallbackType> callback_map_ ABSL_GUARDED_BY(mutex_);
  std::optional<EventEngine::TaskHandle> ares_backup_poll_alarm_handle_
      ABSL_GUARDED_BY(mutex_);
  std::unique_ptr<GrpcPolledFdFactory> polled_fd_factory_;
  std::shared_ptr<EventEngine> event_engine_;
};

}

extern void (*event_engine_grpc_ares_test_only_inject_config)(
    ares_channel* channel);

extern bool g_event_engine_grpc_ares_test_only_force_tcp;

#endif

bool ShouldUseAresDnsResolver();
absl::Status AresInit();
void AresShutdown();

#endif
