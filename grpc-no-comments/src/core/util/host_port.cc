
// Copyright 2015 gRPC authors.

#include "src/core/util/host_port.h"

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include "absl/log/check.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"

namespace grpc_core {

std::string JoinHostPort(absl::string_view host, int port) {
  if (!host.empty() && host[0] != '[' && host.rfind(':') != host.npos) {

    return absl::StrFormat("[%s]:%d", host, port);
  }

  return absl::StrFormat("%s:%d", host, port);
}

namespace {
bool DoSplitHostPort(absl::string_view name, absl::string_view* host,
                     absl::string_view* port, bool* has_port) {
  *has_port = false;
  if (!name.empty() && name[0] == '[') {

    const size_t rbracket = name.find(']', 1);
    if (rbracket == absl::string_view::npos) {

      return false;
    }
    if (rbracket == name.size() - 1) {

      *port = absl::string_view();
    } else if (name[rbracket + 1] == ':') {

      *port = name.substr(rbracket + 2, name.size() - rbracket - 2);
      *has_port = true;
    } else {

      return false;
    }
    *host = name.substr(1, rbracket - 1);
    if (host->find(':') == absl::string_view::npos) {

      *host = absl::string_view();
      return false;
    }
  } else {
    size_t colon = name.find(':');
    if (colon != absl::string_view::npos &&
        name.find(':', colon + 1) == absl::string_view::npos) {

      *host = name.substr(0, colon);
      *port = name.substr(colon + 1, name.size() - colon - 1);
      *has_port = true;
    } else {

      *host = name;
      *port = absl::string_view();
    }
  }
  return true;
}
}

bool SplitHostPort(absl::string_view name, absl::string_view* host,
                   absl::string_view* port) {
  bool unused;
  return DoSplitHostPort(name, host, port, &unused);
}

bool SplitHostPort(absl::string_view name, std::string* host,
                   std::string* port) {
  DCHECK(host != nullptr);
  DCHECK(host->empty());
  DCHECK(port != nullptr);
  DCHECK(port->empty());
  absl::string_view host_view;
  absl::string_view port_view;
  bool has_port;
  const bool ret = DoSplitHostPort(name, &host_view, &port_view, &has_port);
  if (ret) {

    *host = std::string(host_view);
    if (has_port) {
      *port = std::string(port_view);
    }
  }
  return ret;
}

}
