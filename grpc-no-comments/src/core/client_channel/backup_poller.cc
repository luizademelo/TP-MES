
// Copyright 2017 gRPC authors.

#include "src/core/client_channel/backup_poller.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>
#include <inttypes.h>

#include "absl/log/log.h"
#include "absl/status/status.h"
#include "src/core/config/config_vars.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/iomgr.h"
#include "src/core/lib/iomgr/pollset.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/lib/iomgr/timer.h"
#include "src/core/util/memory.h"
#include "src/core/util/time.h"

#define DEFAULT_POLL_INTERVAL_MS 5000

namespace {
struct backup_poller {
  grpc_timer polling_timer;
  grpc_closure run_poller_closure;
  grpc_closure shutdown_closure;
  gpr_mu* pollset_mu;
  grpc_pollset* pollset;
  bool shutting_down;
  gpr_refcount refs;
  gpr_refcount shutdown_refs;
};
}

static gpr_mu g_poller_mu;
static backup_poller* g_poller = nullptr;

static grpc_core::Duration g_poll_interval =
    grpc_core::Duration::Milliseconds(DEFAULT_POLL_INTERVAL_MS);

static bool g_backup_polling_disabled;

void grpc_client_channel_global_init_backup_polling() {

  g_backup_polling_disabled = grpc_core::IsEventEngineClientEnabled() &&
                              grpc_core::IsEventEngineListenerEnabled() &&
                              grpc_core::IsEventEngineDnsEnabled();
  if (g_backup_polling_disabled) {
    return;
  }

  gpr_mu_init(&g_poller_mu);
  int32_t poll_interval_ms =
      grpc_core::ConfigVars::Get().ClientChannelBackupPollIntervalMs();
  if (poll_interval_ms < 0) {
    LOG(ERROR) << "Invalid GRPC_CLIENT_CHANNEL_BACKUP_POLL_INTERVAL_MS: "
               << poll_interval_ms << ", default value "
               << g_poll_interval.millis() << " will be used.";
  } else {
    g_poll_interval = grpc_core::Duration::Milliseconds(poll_interval_ms);
  }
}

static void backup_poller_shutdown_unref(backup_poller* p) {
  if (gpr_unref(&p->shutdown_refs)) {
    grpc_pollset_destroy(p->pollset);
    gpr_free(p->pollset);
    gpr_free(p);
  }
}

static void done_poller(void* arg, grpc_error_handle ) {
  backup_poller_shutdown_unref(static_cast<backup_poller*>(arg));
}

static void g_poller_unref() {
  gpr_mu_lock(&g_poller_mu);
  if (gpr_unref(&g_poller->refs)) {
    backup_poller* p = g_poller;
    g_poller = nullptr;
    gpr_mu_unlock(&g_poller_mu);
    gpr_mu_lock(p->pollset_mu);
    p->shutting_down = true;
    grpc_pollset_shutdown(
        p->pollset, GRPC_CLOSURE_INIT(&p->shutdown_closure, done_poller, p,
                                      grpc_schedule_on_exec_ctx));
    gpr_mu_unlock(p->pollset_mu);
    grpc_timer_cancel(&p->polling_timer);
    backup_poller_shutdown_unref(p);
  } else {
    gpr_mu_unlock(&g_poller_mu);
  }
}

static void run_poller(void* arg, grpc_error_handle error) {
  backup_poller* p = static_cast<backup_poller*>(arg);
  if (!error.ok()) {
    if (error != absl::CancelledError()) {
      GRPC_LOG_IF_ERROR("run_poller", error);
    }
    backup_poller_shutdown_unref(p);
    return;
  }
  gpr_mu_lock(p->pollset_mu);
  if (p->shutting_down) {
    gpr_mu_unlock(p->pollset_mu);
    backup_poller_shutdown_unref(p);
    return;
  }
  grpc_error_handle err =
      grpc_pollset_work(p->pollset, nullptr, grpc_core::Timestamp::Now());
  gpr_mu_unlock(p->pollset_mu);
  GRPC_LOG_IF_ERROR("Run client channel backup poller", err);
  grpc_timer_init(&p->polling_timer,
                  grpc_core::Timestamp::Now() + g_poll_interval,
                  &p->run_poller_closure);
}

static void g_poller_init_locked() {
  if (g_poller == nullptr) {
    g_poller = grpc_core::Zalloc<backup_poller>();
    g_poller->pollset =
        static_cast<grpc_pollset*>(gpr_zalloc(grpc_pollset_size()));
    g_poller->shutting_down = false;
    grpc_pollset_init(g_poller->pollset, &g_poller->pollset_mu);
    gpr_ref_init(&g_poller->refs, 0);

    gpr_ref_init(&g_poller->shutdown_refs, 3);
    GRPC_CLOSURE_INIT(&g_poller->run_poller_closure, run_poller, g_poller,
                      grpc_schedule_on_exec_ctx);
    grpc_timer_init(&g_poller->polling_timer,
                    grpc_core::Timestamp::Now() + g_poll_interval,
                    &g_poller->run_poller_closure);
  }
}

void grpc_client_channel_start_backup_polling(
    grpc_pollset_set* interested_parties) {
  if (g_backup_polling_disabled ||
      g_poll_interval == grpc_core::Duration::Zero() ||
      grpc_iomgr_run_in_background()) {
    return;
  }
  gpr_mu_lock(&g_poller_mu);
  g_poller_init_locked();
  gpr_ref(&g_poller->refs);

  grpc_pollset* pollset = g_poller->pollset;
  gpr_mu_unlock(&g_poller_mu);

  grpc_pollset_set_add_pollset(interested_parties, pollset);
}

void grpc_client_channel_stop_backup_polling(
    grpc_pollset_set* interested_parties) {
  if (g_backup_polling_disabled ||
      g_poll_interval == grpc_core::Duration::Zero() ||
      grpc_iomgr_run_in_background()) {
    return;
  }
  grpc_pollset_set_del_pollset(interested_parties, g_poller->pollset);
  g_poller_unref();
}
