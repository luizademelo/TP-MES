Here's the commented version of the code:

```c++
// Copyright 2017 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"
#include "src/core/util/crash.h"

#ifdef GRPC_LINUX_EPOLL
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <grpc/support/alloc.h>
#include <grpc/support/cpu.h>
#include <limits.h>
#include <poll.h>
#include <pthread.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#include <string>
#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "src/core/lib/event_engine/shim.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/block_annotate.h"
#include "src/core/lib/iomgr/ev_epoll1_linux.h"
#include "src/core/lib/iomgr/ev_posix.h"
#include "src/core/lib/iomgr/iomgr_internal.h"
#include "src/core/lib/iomgr/lockfree_event.h"
#include "src/core/lib/iomgr/wakeup_fd_posix.h"
#include "src/core/telemetry/stats.h"
#include "src/core/telemetry/stats_data.h"
#include "src/core/util/manual_constructor.h"
#include "src/core/util/strerror.h"
#include "src/core/util/string.h"
#include "src/core/util/useful.h"

// Global wakeup file descriptor and shutdown flag
static grpc_wakeup_fd global_wakeup_fd;
static bool g_is_shutdown = true;

// Constants for epoll configuration
#define MAX_EPOLL_EVENTS 100
#define MAX_EPOLL_EVENTS_HANDLED_PER_ITERATION 1

// Structure to manage epoll file descriptor and events
typedef struct epoll_set {
  int epfd;  // epoll file descriptor
  struct epoll_event events[MAX_EPOLL_EVENTS];  // Array to store events
  gpr_atm num_events;  // Number of events currently in the set (atomic)
  gpr_atm cursor;      // Current position in events array (atomic)
} epoll_set;

static epoll_set g_epoll_set;  // Global epoll set instance

// Creates an epoll file descriptor with CLOEXEC flag
static int epoll_create_and_cloexec() {
#ifdef GRPC_LINUX_EPOLL_CREATE1
  // Try to use epoll_create1 if available
  int fd = epoll_create1(EPOLL_CLOEXEC);
  if (fd < 0) {
    LOG(ERROR) << "epoll_create1 unavailable";
  }
#else
  // Fallback to epoll_create and manual CLOEXEC setting
  int fd = epoll_create(MAX_EPOLL_EVENTS);
  if (fd < 0) {
    LOG(ERROR) << "epoll_create unavailable";
  } else if (fcntl(fd, F_SETFD, FD_CLOEXEC) != 0) {
    LOG(ERROR) << "fcntl following epoll_create failed";
    return -1;
  }
#endif
  return fd;
}

// Initializes the global epoll set
static bool epoll_set_init() {
  g_epoll_set.epfd = epoll_create_and_cloexec();
  if (g_epoll_set.epfd < 0) {
    return false;
  }

  GRPC_TRACE_LOG(polling, INFO) << "grpc epoll fd: " << g_epoll_set.epfd;
  // Initialize atomic counters
  gpr_atm_no_barrier_store(&g_epoll_set.num_events, 0);
  gpr_atm_no_barrier_store(&g_epoll_set.cursor, 0);
  return true;
}

// Shuts down and cleans up the epoll set
static void epoll_set_shutdown() {
  if (g_epoll_set.epfd >= 0) {
    close(g_epoll_set.epfd);
    g_epoll_set.epfd = -1;
  }
}

// Linked list structure for tracking file descriptors during fork
struct grpc_fork_fd_list {
  grpc_fd* fd;
  grpc_fd* next;
  grpc_fd* prev;
};

// Structure representing a file descriptor in the event engine
struct grpc_fd {
  int fd;  // The actual file descriptor

  // Event closures for read, write, and error events
  grpc_core::ManualConstructor<grpc_core::LockfreeEvent> read_closure;
  grpc_core::ManualConstructor<grpc_core::LockfreeEvent> write_closure;
  grpc_core::ManualConstructor<grpc_core::LockfreeEvent> error_closure;

  struct grpc_fd* freelist_next;  // Next in freelist

  grpc_iomgr_object iomgr_object;  // For IOMGR tracking

  grpc_fork_fd_list* fork_fd_list;  // For fork handling

  bool is_pre_allocated;  // Flag for pre-allocated FDs
};

// Forward declarations
static void fd_global_init(void);
static void fd_global_shutdown(void);

// States for pollset worker kicking
typedef enum { UNKICKED, KICKED, DESIGNATED_POLLER } kick_state;

// Converts kick state to string for debugging
static const char* kick_state_string(kick_state st) {
  switch (st) {
    case UNKICKED:
      return "UNKICKED";
    case KICKED:
      return "KICKED";
    case DESIGNATED_POLLER:
      return "DESIGNATED_POLLER";
  }
  GPR_UNREACHABLE_CODE(return "UNKNOWN");
}

// Structure representing a worker in a pollset
struct grpc_pollset_worker {
  kick_state state;                // Current state of the worker
  int kick_state_mutator;          // Line number where state was last changed
  bool initialized_cv;             // Whether CV has been initialized
  grpc_pollset_worker* next;       // Next worker in circular list
  grpc_pollset_worker* prev;       // Previous worker in circular list
  gpr_cv cv;                      // Condition variable for waiting
  grpc_closure_list schedule_on_end_work;  // Closures to run after work
};

// Macro to set kick state and record where it was set
#define SET_KICK_STATE(worker, kick_state)   \
  do {                                       \
    (worker)->state = (kick_state);          \
    (worker)->kick_state_mutator = __LINE__; \
  } while (false)

// Maximum number of neighborhoods for pollset distribution
#define MAX_NEIGHBORHOODS 1024u

// Structure representing a neighborhood of pollsets
typedef struct pollset_neighborhood {
  union {
    char pad[GPR_CACHELINE_SIZE];  // Padding for cache alignment
    struct {
      gpr_mu mu;               // Mutex for this neighborhood
      grpc_pollset* active_root;  // Root of active pollsets
    };
  };
} pollset_neighborhood;

// Structure representing a pollset
struct grpc_pollset {
  gpr_mu mu;                      // Mutex for this pollset
  pollset_neighborhood* neighborhood;  // Associated neighborhood
  bool reassigning_neighborhood;  // Whether neighborhood is being reassigned
  grpc_pollset_worker* root_worker;  // Root worker in circular list
  bool kicked_without_poller;     // Whether kicked without active poller

  bool seen_inactive;            // Whether pollset is inactive
  bool shutting_down;            // Whether pollset is shutting down
  grpc_closure* shutdown_closure;  // Closure to run on shutdown

  int begin_refs;                // Reference count for workers

  grpc_pollset* next;            // Next in neighborhood list
  grpc_pollset* prev;            // Previous in neighborhood list
};

// Dummy structure for pollset sets (not fully implemented)
struct grpc_pollset_set {
  char unused;
};

// Appends an error to a composite error
static bool append_error(grpc_error_handle* composite, grpc_error_handle error,
                         const char* desc) {
  if (error.ok()) return true;
  if (composite->ok()) {
    *composite = GRPC_ERROR_CREATE(desc);
  }
  *composite = grpc_error_add_child(*composite, error);
  return false;
}

// Freelist management for file descriptors
static grpc_fd* fd_freelist = nullptr;
static gpr_mu fd_freelist_mu;

// Fork handling list management
static grpc_fd* fork_fd_list_head = nullptr;
static gpr_mu fork_fd_list_mu;

// Initializes global file descriptor state
static void fd_global_init(void) { gpr_mu_init(&fd_freelist_mu); }

// Shuts down global file descriptor state
static void fd_global_shutdown(void) {
  gpr_mu_lock(&fd_freelist_mu);
  gpr_mu_unlock(&fd_freelist_mu);
  // Free all file descriptors in the freelist
  while (fd_freelist != nullptr) {
    grpc_fd* fd = fd_freelist;
    fd_freelist = fd_freelist->freelist_next;
    gpr_free(fd);
  }
  gpr_mu_destroy(&fd_freelist_mu);
}

// Adds a file descriptor to the fork handling list
static void fork_fd_list_add_grpc_fd(grpc_fd* fd) {
  if (grpc_core::Fork::Enabled()) {
    gpr_mu_lock(&fork_fd_list_mu);
    fd->fork_fd_list =
        static_cast<grpc_fork_fd_list*>(gpr_malloc(sizeof(grpc_fork_fd_list)));
    fd->fork_fd_list->next = fork_fd_list_head;
    fd->fork_fd_list->prev = nullptr;
    if (fork_fd_list_head != nullptr) {
      fork_fd_list_head->fork_fd_list->prev = fd;
    }
    fork_fd_list_head = fd;
    gpr_mu_unlock(&fork_fd_list_mu);
  }
}

// Removes a file descriptor from the fork handling list
static void fork_fd_list_remove_grpc_fd(grpc_fd* fd) {
  if (grpc_core::Fork::Enabled()) {
    gpr_mu_lock(&fork_fd_list_mu);
    if (fork_fd_list_head == fd) {
      fork_fd_list_head = fd->fork_fd_list->next;
    }
    if (fd->fork_fd_list->prev != nullptr) {
      fd->fork_fd_list->prev->fork_fd_list->next = fd->fork_fd_list->next;
    }
    if (fd->fork_fd_list->next != nullptr) {
      fd->fork_fd_list->next->fork_fd_list->prev = fd->fork_fd_list->prev;
    }
    gpr_free(fd->fork_fd_list);
    gpr_mu_unlock(&fork_fd_list_mu);
  }
}

// Creates a new file descriptor wrapper
static grpc_fd* fd_create(int fd, const char* name, bool track_err) {
  grpc_fd* new_fd = nullptr;
  
  // Handle case where EventEngine is enabled
  if (grpc_core::IsEventEngineForAllOtherEndpointsEnabled() &&
      !grpc_event_engine::experimental::
          EventEngineExperimentDisabledForPython()) {
    grpc_fd* new_fd = static_cast<grpc_fd*>(gpr_malloc(sizeof(grpc_fd)));
    new_fd->fd = fd;
    return new_fd;
  }

  // Try to get from freelist first
  gpr_mu_lock(&fd_freelist_mu);
  if (fd_freelist != nullptr) {
    new_fd = fd_freelist;
    fd_freelist = fd_freelist->freelist_next;
  }
  gpr_mu_unlock(&fd_freelist_mu);

  // Allocate new if freelist was empty
  if (new_fd == nullptr) {
    new_fd = static_cast<grpc_fd*>(gpr_malloc(sizeof(grpc_fd)));
    new_fd->read_closure.Init();
    new_fd->write_closure.Init();
    new_fd->error_closure.Init();
  }
  
  // Initialize the file descriptor
  new_fd->fd = fd;
  new_fd->read_closure->InitEvent();
  new_fd->write_closure->InitEvent();
  new_fd->error_closure->InitEvent();

  new_fd->freelist_next = nullptr;
  new_fd->is_pre_allocated = false;

  // Register with IOMGR and fork handling
  std::string fd_name = absl::StrCat(name, " fd=", fd);
  grpc_iomgr_register_object(&new_fd->iomgr_object, fd_name.c_str());
  fork_fd_list_add_grpc_fd(new_fd);
#ifndef NDEBUG
  GRPC_TRACE_VLOG(fd_refcount, 2)
      << "FD " << fd << " " << new_fd << " create " << fd_name;
#endif

  // Add to epoll set
  struct epoll_event ev;
  ev.events = static_cast<uint32_t>(EPOLLIN | EPOLLOUT | EPOLLET);
  ev.data.ptr = reinterpret_cast<void*>(reinterpret_cast<intptr_t>(new_fd) |
                                        (track_err ? 1 : 0));
  if (epoll_ctl(g_epoll_set.epfd, EPOLL_CTL_ADD, fd, &ev) != 0) {
    LOG(ERROR) << "epoll_ctl failed: " << grpc_core::StrError(errno);
  }

  return new_fd;
}

// Returns the underlying file descriptor
static int fd_wrapped_fd(grpc_fd* fd) { return fd->fd; }

// Internal shutdown function for file descriptors
static void fd_shutdown_internal(grpc_fd* fd, grpc_error_handle why,
                                 bool releasing_fd) {
  if (fd->read_closure->SetShutdown(why)) {
    if (!releasing_fd) {
      if (!fd->is_pre_allocated) {
        shutdown(fd->fd, SHUT_RDWR);
      }
    } else {
      // Remove from epoll set if releasing the FD
      epoll_event phony_event;
      if (epoll_ctl(g_epoll_set.epfd, EPOLL_CTL_DEL, fd->fd, &phony_event) !=
          0) {
        LOG(ERROR) << "epoll_ctl failed: " << grpc_core::StrError(errno);
      }
    }
    fd->write_closure->SetShutdown(why);
    fd->error_closure->SetShutdown(why);
  }
}

// Public shutdown function for file descriptors
static void fd_shutdown(grpc_fd* fd, grpc_error_handle why) {
  fd_shutdown_internal(fd, why, false);
}

// Orphans a file descriptor (releases ownership)
static void fd_orphan(grpc_fd* fd, grpc_closure* on_done, int* release_fd,
                      const char* reason) {
  // Handle EventEngine case
  if (grpc_core::IsEventEngineForAllOtherEndpointsEnabled() &&
      !grpc_event_engine::experimental::
          EventEngineExperimentDisabledForPython()) {
    CHECK_NE(release_fd, nullptr);
    CHECK_EQ(on_done, nullptr);
    *release_fd = fd->fd;
    gpr_free(fd);
    return;
  }

  grpc_error_handle error;
  bool is_release_fd = (release_fd != nullptr);

  // Shutdown if not already shutdown
  if (!fd->read_closure->IsShutdown()) {
    fd_shutdown_internal(fd, GRPC_ERROR_CREATE(reason), is_release_fd);
  }

  // Handle FD release or close
  if (is_release_fd) {
    *release_fd = fd->fd;
  } else {
    if (!fd->is_pre_allocated) {
      close(fd->fd);
    }
  }

  // Run completion callback
  grpc_core::ExecCtx::Run(DEBUG_LOCATION, on_done, error);

  // Cleanup registration and fork handling
  grpc_iomgr_unregister_object(&fd->iomgr_object);
  fork_fd_list_remove_grpc_fd(fd);
  fd->read_closure->DestroyEvent();
  fd->write_closure->DestroyEvent();
  fd->error_closure->DestroyEvent();

  // Add to freelist for reuse
  gpr_mu_lock(&fd_freelist_mu);
  fd->freelist_next = fd_freelist;
  fd_freelist = fd;
  gpr_mu_unlock(&fd_freelist_mu);
}

// Checks if FD is shutdown
static bool fd_is_shutdown(grpc_fd* fd) {
  return fd->read_closure->IsShutdown();
}

// Registers a read notification callback
static void fd_notify_on_read(grpc_fd* fd, grpc_closure* closure) {
  fd->read_closure->NotifyOn(closure);
}

// Registers a write notification callback
static void fd_notify_on_write(grpc_fd* fd, grpc_closure* closure) {
  fd->write_closure->NotifyOn(closure);
}

// Registers an error notification callback
static void fd_notify_on_error(grpc_fd* fd, grpc_closure* closure) {