
// Copyright 2017 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_HAVE_IFADDRS

#include <errno.h>
#include <grpc/support/alloc.h>
#include <ifaddrs.h>
#include <stddef.h>
#include <string.h>
#include <sys/socket.h>

#include <string>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/lib/iomgr/tcp_server_utils_posix.h"
#include "src/core/util/crash.h"

static grpc_tcp_listener* find_listener_with_addr(grpc_tcp_server* s,
                                                  grpc_resolved_address* addr) {
  grpc_tcp_listener* l;
  gpr_mu_lock(&s->mu);
  for (l = s->head; l != nullptr; l = l->next) {
    if (l->addr.len != addr->len) {
      continue;
    }
    if (memcmp(l->addr.addr, addr->addr, addr->len) == 0) {
      break;
    }
  }
  gpr_mu_unlock(&s->mu);
  return l;
}

static grpc_error_handle get_unused_port(int* port) {
  grpc_resolved_address wild;
  grpc_sockaddr_make_wildcard6(0, &wild);
  grpc_dualstack_mode dsmode;
  int fd;
  grpc_error_handle err =
      grpc_create_dualstack_socket(&wild, SOCK_STREAM, 0, &dsmode, &fd);
  if (!err.ok()) {
    return err;
  }
  if (dsmode == GRPC_DSMODE_IPV4) {
    grpc_sockaddr_make_wildcard4(0, &wild);
  }
  if (bind(fd, reinterpret_cast<const grpc_sockaddr*>(wild.addr), wild.len) !=
      0) {
    err = GRPC_OS_ERROR(errno, "bind");
    close(fd);
    return err;
  }
  if (getsockname(fd, reinterpret_cast<grpc_sockaddr*>(wild.addr), &wild.len) !=
      0) {
    err = GRPC_OS_ERROR(errno, "getsockname");
    close(fd);
    return err;
  }
  close(fd);
  *port = grpc_sockaddr_get_port(&wild);
  return *port <= 0 ? GRPC_ERROR_CREATE("Bad port") : absl::OkStatus();
}

static bool grpc_is_ipv4_available() {
  const int fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd >= 0) close(fd);
  return fd >= 0;
}

grpc_error_handle grpc_tcp_server_add_all_local_addrs(grpc_tcp_server* s,
                                                      unsigned port_index,
                                                      int requested_port,
                                                      int* out_port) {
  struct ifaddrs* ifa = nullptr;
  struct ifaddrs* ifa_it;
  unsigned fd_index = 0;
  grpc_tcp_listener* sp = nullptr;
  grpc_error_handle err;
  if (requested_port == 0) {
    // Note: There could be a race where some local addrs can listen on the

    if ((err = get_unused_port(&requested_port)) != absl::OkStatus()) {
      return err;
    } else if (requested_port <= 0) {
      return GRPC_ERROR_CREATE("Bad get_unused_port()");
    }
    VLOG(2) << "Picked unused port " << requested_port;
  }

  static bool v4_available = grpc_is_ipv4_available();

  if (getifaddrs(&ifa) != 0 || ifa == nullptr) {
    return GRPC_OS_ERROR(errno, "getifaddrs");
  }
  for (ifa_it = ifa; ifa_it != nullptr; ifa_it = ifa_it->ifa_next) {
    grpc_resolved_address addr;
    grpc_dualstack_mode dsmode;
    grpc_tcp_listener* new_sp = nullptr;
    const char* ifa_name = (ifa_it->ifa_name ? ifa_it->ifa_name : "<unknown>");
    if (ifa_it->ifa_addr == nullptr) {
      continue;
    } else if (ifa_it->ifa_addr->sa_family == AF_INET) {
      if (!v4_available) {
        continue;
      }
      addr.len = static_cast<socklen_t>(sizeof(grpc_sockaddr_in));
    } else if (ifa_it->ifa_addr->sa_family == AF_INET6) {
      addr.len = static_cast<socklen_t>(sizeof(grpc_sockaddr_in6));
    } else {
      continue;
    }
    memcpy(addr.addr, ifa_it->ifa_addr, addr.len);
    if (!grpc_sockaddr_set_port(&addr, requested_port)) {

      err = GRPC_ERROR_CREATE("Failed to set port");
      break;
    }
    auto addr_str = grpc_sockaddr_to_string(&addr, false);
    if (!addr_str.ok()) {
      return GRPC_ERROR_CREATE(addr_str.status().ToString());
    }
    VLOG(2) << absl::StrFormat(
        "Adding local addr from interface %s flags 0x%x to server: %s",
        ifa_name, ifa_it->ifa_flags, addr_str->c_str());

    if (find_listener_with_addr(s, &addr) != nullptr) {
      VLOG(2) << "Skipping duplicate addr " << *addr_str << " on interface "
              << ifa_name;
      continue;
    }
    if ((err = grpc_tcp_server_add_addr(s, &addr, port_index, fd_index, &dsmode,
                                        &new_sp)) != absl::OkStatus()) {
      grpc_error_handle root_err = GRPC_ERROR_CREATE(
          absl::StrCat("Failed to add listener: ", addr_str.value()));
      err = grpc_error_add_child(root_err, err);
      break;
    } else {
      CHECK(requested_port == new_sp->port);
      ++fd_index;
      if (sp != nullptr) {
        new_sp->is_sibling = 1;
        sp->sibling = new_sp;
      }
      sp = new_sp;
    }
  }
  freeifaddrs(ifa);
  if (!err.ok()) {
    return err;
  } else if (sp == nullptr) {
    return GRPC_ERROR_CREATE("No local addresses");
  } else {
    *out_port = sp->port;
    return absl::OkStatus();
  }
}

bool grpc_tcp_server_have_ifaddrs(void) { return true; }

#endif
