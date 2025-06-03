Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Include necessary gRPC core headers
#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

// Only compile this code if using POSIX socket event engine
#ifdef GRPC_POSIX_SOCKET_EV

// Standard and gRPC support headers
#include <grpc/support/alloc.h>
#include <grpc/support/string_util.h>
#include <string.h>

// Abseil logging and string utilities
#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_split.h"

// gRPC core configuration and utilities
#include "src/core/config/config_vars.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/ev_epoll1_linux.h"
#include "src/core/lib/iomgr/ev_poll_posix.h"
#include "src/core/lib/iomgr/ev_posix.h"
#include "src/core/lib/iomgr/internal_errqueue.h"
#include "src/core/util/crash.h"
#include "src/core/util/useful.h"

// Define poll function based on platform
#ifndef GPR_AIX
// Standard poll function for most platforms
grpc_poll_function_type grpc_poll_function = poll;
#else
// Special implementation for AIX platform
int aix_poll(struct pollfd fds[], nfds_t nfds, int timeout) {
  return poll(fds, nfds, timeout);
}
grpc_poll_function_type grpc_poll_function = aix_poll;
#endif

// Global wakeup file descriptor
grpc_wakeup_fd grpc_global_wakeup_fd;

// Current event engine implementation
static const grpc_event_engine_vtable* g_event_engine = nullptr;
// One-time initialization control
static gpr_once g_choose_engine = GPR_ONCE_INIT;

// Array of available event engine implementations
static const grpc_event_engine_vtable* g_vtables[] = {
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    &grpc_ev_epoll1_posix,  // epoll1 engine
    &grpc_ev_poll_posix,    // poll engine
    &grpc_ev_none_posix,    // none engine
    nullptr,
    nullptr,
    nullptr,
    nullptr,
};

// Helper function to compare engine names
static bool is(absl::string_view want, absl::string_view have) {
  return want == "all" || want == have;
}

// Try to initialize a specific event engine
static void try_engine(absl::string_view engine) {
  for (size_t i = 0; i < GPR_ARRAY_SIZE(g_vtables); i++) {
    if (g_vtables[i] != nullptr && is(engine, g_vtables[i]->name) &&
        g_vtables[i]->check_engine_available(engine == g_vtables[i]->name)) {
      g_event_engine = g_vtables[i];
      GRPC_TRACE_VLOG(polling_api, 2)
          << "Using polling engine: " << g_event_engine->name;
      return;
    }
  }
}

// Register a new event engine factory
void grpc_register_event_engine_factory(const grpc_event_engine_vtable* vtable,
                                        bool add_at_head) {
  const grpc_event_engine_vtable** first_null = nullptr;
  const grpc_event_engine_vtable** last_null = nullptr;

  // Find first and last null slots in the vtables array
  for (size_t i = 0; i < GPR_ARRAY_SIZE(g_vtables); i++) {
    if (g_vtables[i] == nullptr) {
      if (first_null == nullptr) first_null = &g_vtables[i];
      last_null = &g_vtables[i];
    } else if (0 == strcmp(g_vtables[i]->name, vtable->name)) {
      // Replace existing engine with same name
      g_vtables[i] = vtable;
      return;
    }
  }

  // Add new engine at head or tail of available slots
  *(add_at_head ? first_null : last_null) = vtable;
}

// Get the name of the current polling strategy
const char* grpc_get_poll_strategy_name() { return g_event_engine->name; }

// Initialize the event engine
void grpc_event_engine_init(void) {
  gpr_once_init(&g_choose_engine, []() {
    // Get configured polling strategy from config vars
    auto value = grpc_core::ConfigVars::Get().PollStrategy();
    // Try each engine in the comma-separated list
    for (auto trial : absl::StrSplit(value, ',')) {
      try_engine(trial);
      if (g_event_engine != nullptr) return;
    }

    // Crash if no engine could be initialized
    if (g_event_engine == nullptr) {
      grpc_core::Crash(
          absl::StrFormat("No event engine could be initialized from %s",
                          std::string(value).c_str()));
    }
  });
  // Initialize the selected engine
  g_event_engine->init_engine();
}

// Shutdown the event engine
void grpc_event_engine_shutdown(void) { g_event_engine->shutdown_engine(); }

// Check if the engine can track errors
bool grpc_event_engine_can_track_errors(void) {
  return grpc_core::KernelSupportsErrqueue() && g_event_engine->can_track_err;
}

// Check if the engine runs in background
bool grpc_event_engine_run_in_background(void) {
  return g_event_engine != nullptr && g_event_engine->run_in_background;
}

// Create a new file descriptor wrapper
grpc_fd* grpc_fd_create(int fd, const char* name, bool track_err) {
  GRPC_TRACE_DLOG(polling_api, INFO) << "(polling-api) fd_create(" << fd << ", "
                                     << name << ", " << track_err << ")";
  GRPC_TRACE_LOG(fd_trace, INFO) << "(fd-trace) fd_create(" << fd << ", "
                                 << name << ", " << track_err << ")";
  return g_event_engine->fd_create(
      fd, name, track_err && grpc_event_engine_can_track_errors());
}

// Get the underlying file descriptor
int grpc_fd_wrapped_fd(grpc_fd* fd) {
  return g_event_engine->fd_wrapped_fd(fd);
}

// Orphan a file descriptor (release ownership)
void grpc_fd_orphan(grpc_fd* fd, grpc_closure* on_done, int* release_fd,
                    const char* reason) {
  GRPC_TRACE_DLOG(polling_api, INFO)
      << "(polling-api) fd_orphan(" << grpc_fd_wrapped_fd(fd) << ", " << on_done
      << ", " << release_fd << ", " << reason << ")";
  GRPC_TRACE_LOG(fd_trace, INFO)
      << "(fd-trace) grpc_fd_orphan, fd:" << grpc_fd_wrapped_fd(fd)
      << " closed";

  g_event_engine->fd_orphan(fd, on_done, release_fd, reason);
}

// Mark a file descriptor as pre-allocated
void grpc_fd_set_pre_allocated(grpc_fd* fd) {
  GRPC_TRACE_DLOG(polling_api, INFO)
      << "(polling-api) fd_set_pre_allocated(" << grpc_fd_wrapped_fd(fd) << ")";
  GRPC_TRACE_LOG(fd_trace, INFO)
      << "(fd-trace) fd_set_pre_allocated(" << grpc_fd_wrapped_fd(fd) << ")";
  g_event_engine->fd_set_pre_allocated(fd);
}

// Shutdown a file descriptor
void grpc_fd_shutdown(grpc_fd* fd, grpc_error_handle why) {
  GRPC_TRACE_LOG(polling_api, INFO)
      << "(polling-api) fd_shutdown(" << grpc_fd_wrapped_fd(fd) << ")";
  GRPC_TRACE_LOG(fd_trace, INFO)
      << "(fd-trace) fd_shutdown(" << grpc_fd_wrapped_fd(fd) << ")";
  g_event_engine->fd_shutdown(fd, why);
}

// Check if a file descriptor is shutdown
bool grpc_fd_is_shutdown(grpc_fd* fd) {
  return g_event_engine->fd_is_shutdown(fd);
}

// Set up a read notification callback
void grpc_fd_notify_on_read(grpc_fd* fd, grpc_closure* closure) {
  g_event_engine->fd_notify_on_read(fd, closure);
}

// Set up a write notification callback
void grpc_fd_notify_on_write(grpc_fd* fd, grpc_closure* closure) {
  g_event_engine->fd_notify_on_write(fd, closure);
}

// Set up an error notification callback
void grpc_fd_notify_on_error(grpc_fd* fd, grpc_closure* closure) {
  g_event_engine->fd_notify_on_error(fd, closure);
}

// Mark file descriptor as readable
void grpc_fd_set_readable(grpc_fd* fd) { g_event_engine->fd_set_readable(fd); }

// Mark file descriptor as writable
void grpc_fd_set_writable(grpc_fd* fd) { g_event_engine->fd_set_writable(fd); }

// Mark file descriptor as in error state
void grpc_fd_set_error(grpc_fd* fd) { g_event_engine->fd_set_error(fd); }

// Get pollset size
static size_t pollset_size(void) { return g_event_engine->pollset_size; }

// Initialize a pollset
static void pollset_init(grpc_pollset* pollset, gpr_mu** mu) {
  GRPC_TRACE_DLOG(polling_api, INFO)
      << "(polling-api) pollset_init(" << pollset << ")";
  g_event_engine->pollset_init(pollset, mu);
}

// Shutdown a pollset
static void pollset_shutdown(grpc_pollset* pollset, grpc_closure* closure) {
  GRPC_TRACE_DLOG(polling_api, INFO)
      << "(polling-api) pollset_shutdown(" << pollset << ")";
  g_event_engine->pollset_shutdown(pollset, closure);
}

// Destroy a pollset
static void pollset_destroy(grpc_pollset* pollset) {
  GRPC_TRACE_DLOG(polling_api, INFO)
      << "(polling-api) pollset_destroy(" << pollset << ")";
  g_event_engine->pollset_destroy(pollset);
}

// Do pollset work (wait for events)
static grpc_error_handle pollset_work(grpc_pollset* pollset,
                                      grpc_pollset_worker** worker,
                                      grpc_core::Timestamp deadline) {
  GRPC_TRACE_DLOG(polling_api, INFO)
      << "(polling-api) pollset_work(" << pollset << ", "
      << deadline.milliseconds_after_process_epoch() << ") begin";
  grpc_error_handle err =
      g_event_engine->pollset_work(pollset, worker, deadline);
  GRPC_TRACE_DLOG(polling_api, INFO)
      << "(polling-api) pollset_work(" << pollset << ", "
      << deadline.milliseconds_after_process_epoch() << ") end";
  return err;
}

// Kick a worker in the pollset
static grpc_error_handle pollset_kick(grpc_pollset* pollset,
                                      grpc_pollset_worker* specific_worker) {
  GRPC_TRACE_DLOG(polling_api, INFO) << "(polling-api) pollset_kick(" << pollset
                                     << ", " << specific_worker << ")";
  return g_event_engine->pollset_kick(pollset, specific_worker);
}

// Add a file descriptor to a pollset
void grpc_pollset_add_fd(grpc_pollset* pollset, struct grpc_fd* fd) {
  GRPC_TRACE_DLOG(polling_api, INFO)
      << "(polling-api) pollset_add_fd(" << pollset << ", "
      << grpc_fd_wrapped_fd(fd) << ")";
  g_event_engine->pollset_add_fd(pollset, fd);
}

// Empty global init/shutdown functions for pollset
void pollset_global_init() {}
void pollset_global_shutdown() {}

// Pollset virtual function table
grpc_pollset_vtable grpc_posix_pollset_vtable = {
    pollset_global_init, pollset_global_shutdown,
    pollset_init,        pollset_shutdown,
    pollset_destroy,     pollset_work,
    pollset_kick,        pollset_size};

// Create a new pollset set
static grpc_pollset_set* pollset_set_create(void) {
  grpc_pollset_set* pss = g_event_engine->pollset_set_create();
  GRPC_TRACE_DLOG(polling_api, INFO)
      << "(polling-api) pollset_set_create(" << pss << ")";
  return pss;
}

// Destroy a pollset set
static void pollset_set_destroy(grpc_pollset_set* pollset_set) {
  GRPC_TRACE_DLOG(polling_api, INFO)
      << "(polling-api) pollset_set_destroy(" << pollset_set << ")";
  g_event_engine->pollset_set_destroy(pollset_set);
}

// Add a pollset to a pollset set
static void pollset_set_add_pollset(grpc_pollset_set* pollset_set,
                                    grpc_pollset* pollset) {
  GRPC_TRACE_DLOG(polling_api, INFO) << "(polling-api) pollset_set_add_pollset("
                                     << pollset_set << ", " << pollset << ")";
  g_event_engine->pollset_set_add_pollset(pollset_set, pollset);
}

// Remove a pollset from a pollset set
static void pollset_set_del_pollset(grpc_pollset_set* pollset_set,
                                    grpc_pollset* pollset) {
  GRPC_TRACE_DLOG(polling_api, INFO) << "(polling-api) pollset_set_del_pollset("
                                     << pollset_set << ", " << pollset << ")";
  g_event_engine->pollset_set_del_pollset(pollset_set, pollset);
}

// Add a pollset set to another pollset set
static void pollset_set_add_pollset_set(grpc_pollset_set* bag,
                                        grpc_pollset_set* item) {
  GRPC_TRACE_DLOG(polling_api, INFO)
      << "(polling-api) pollset_set_add_pollset_set(" << bag << ", " << item
      << ")";
  g_event_engine->pollset_set_add_pollset_set(bag, item);
}

// Remove a pollset set from another pollset set
static void pollset_set_del_pollset_set(grpc_pollset_set* bag,
                                        grpc_pollset_set* item) {
  GRPC_TRACE_DLOG(polling_api, INFO)
      << "(polling-api) pollset_set_del_pollset_set(" << bag << ", " << item
      << ")";
  g_event_engine->pollset_set_del_pollset_set(bag, item);
}

// Pollset set virtual function table
grpc_pollset_set_vtable grpc_posix_pollset_set_vtable = {
    pollset_set_create,          pollset_set_destroy,
    pollset_set_add_pollset,     pollset_set_del_pollset,
    pollset_set_add_pollset_set, pollset_set_del_pollset_set};

// Add a file descriptor to a pollset set
void grpc_pollset_set_add_fd(grpc_pollset_set* pollset_set, grpc_fd* fd) {
  GRPC_TRACE_DLOG(polling_api, INFO)
      << "(polling-api) pollset_set_add_fd(" << pollset_set << ", "
      << grpc_fd_wrapped_fd(fd) << ")";
  g_event_engine->pollset_set_add_fd(pollset_set, fd);
}

// Remove a file descriptor from a pollset set
void grpc_pollset_set_del_fd(grpc_pollset_set* pollset_set, grpc_fd* fd) {
  GRPC_TRACE_DLOG(polling_api, INFO)
      << "(polling-api) pollset_set_del_fd(" << pollset_set << ", "
      << grpc_fd_wrapped_fd(fd) << ")";
  g_event_engine->pollset_set_del_fd(pollset_set, fd);
}

// Check if current thread is a background poller thread
bool grpc_is_any_background_poller_thread(void) {
  return g_event_engine->is_any_background_poller_thread();
}

// Add closure to background poller
bool grpc_add_closure_to_background_poller(grpc_closure* closure,
                                           grpc_error_handle error) {
  return g_event_engine->add_closure_to_background_poller(closure, error);
}

// Shutdown background closure
void grpc_shutdown_background_closure(void) {
  g_event_engine->shutdown_background_closure();
}

#else  // GRPC_POSIX_SOCKET_EV not defined

// Empty implementation when POSIX socket event engine is not available
const char* grpc_get_poll_strategy_name() { return ""; }

#endif
```