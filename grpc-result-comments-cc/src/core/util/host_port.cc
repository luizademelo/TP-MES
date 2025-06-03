Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include "src/core/util/host_port.h"

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include "absl/log/check.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"

namespace grpc_core {

// Combines a host and port into a single string in the format "host:port".
// Handles IPv6 addresses by enclosing them in square brackets if necessary.
// Parameters:
//   host: The hostname or IP address (can be IPv4 or IPv6)
//   port: The port number
// Returns:
//   Formatted string combining host and port
std::string JoinHostPort(absl::string_view host, int port) {
  // If host is not empty, not already in brackets, and contains a colon (IPv6),
  // enclose it in square brackets
  if (!host.empty() && host[0] != '[' && host.rfind(':') != host.npos) {
    return absl::StrFormat("[%s]:%d", host, port);
  }

  // Standard host:port format for IPv4 or already-bracketed IPv6
  return absl::StrFormat("%s:%d", host, port);
}

namespace {
// Internal helper function to split a host:port string into its components.
// Handles both IPv4 and IPv6 addresses.
// Parameters:
//   name: The input string to parse (e.g., "example.com:80" or "[::1]:8080")
//   host: Output parameter for the host portion
//   port: Output parameter for the port portion
//   has_port: Output parameter indicating whether a port was found
// Returns:
//   true if parsing was successful, false otherwise
bool DoSplitHostPort(absl::string_view name, absl::string_view* host,
                     absl::string_view* port, bool* has_port) {
  *has_port = false;
  // Handle IPv6 addresses enclosed in square brackets
  if (!name.empty() && name[0] == '[') {
    // Find the closing bracket
    const size_t rbracket = name.find(']', 1);
    if (rbracket == absl::string_view::npos) {
      // No matching closing bracket found - invalid format
      return false;
    }
    if (rbracket == name.size() - 1) {
      // No port after the closing bracket
      *port = absl::string_view();
    } else if (name[rbracket + 1] == ':') {
      // Port is specified after the colon following the closing bracket
      *port = name.substr(rbracket + 2, name.size() - rbracket - 2);
      *has_port = true;
    } else {
      // Invalid character after closing bracket
      return false;
    }
    // Extract the host (inside the brackets)
    *host = name.substr(1, rbracket - 1);
    // Validate the host contains a colon (IPv6 requirement)
    if (host->find(':') == absl::string_view::npos) {
      *host = absl::string_view();
      return false;
    }
  } else {
    // Handle IPv4 addresses or hostnames
    size_t colon = name.find(':');
    // If there's exactly one colon, split at that point
    if (colon != absl::string_view::npos &&
        name.find(':', colon + 1) == absl::string_view::npos) {
      *host = name.substr(0, colon);
      *port = name.substr(colon + 1, name.size() - colon - 1);
      *has_port = true;
    } else {
      // No port specified or invalid format (multiple colons)
      *host = name;
      *port = absl::string_view();
    }
  }
  return true;
}
}

// Public version of SplitHostPort that doesn't track whether a port was found.
// Parameters:
//   name: The input string to parse
//   host: Output parameter for host portion
//   port: Output parameter for port portion
// Returns:
//   true if parsing was successful, false otherwise
bool SplitHostPort(absl::string_view name, absl::string_view* host,
                   absl::string_view* port) {
  bool unused;
  return DoSplitHostPort(name, host, port, &unused);
}

// Public version of SplitHostPort that returns host and port as std::strings.
// Parameters:
//   name: The input string to parse
//   host: Output parameter for host portion (will be empty if parsing fails)
//   port: Output parameter for port portion (will be empty if no port or if parsing fails)
// Returns:
//   true if parsing was successful, false otherwise
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
    // Convert string_view results to std::string
    *host = std::string(host_view);
    if (has_port) {
      *port = std::string(port_view);
    }
  }
  return ret;
}

}
```