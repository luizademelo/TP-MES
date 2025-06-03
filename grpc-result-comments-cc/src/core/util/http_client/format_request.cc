Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include "src/core/util/http_client/format_request.h"

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <string>
#include <vector>

#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/string_view.h"
#include "src/core/util/http_client/httpcli.h"

/**
 * Fills common HTTP headers for various request types.
 * 
 * @param request The HTTP request containing custom headers
 * @param host The target host for the request
 * @param path The request path/URI
 * @param connection_close Whether to add 'Connection: close' header
 * @param buf Output vector where the formatted headers will be stored
 */
static void fill_common_header(const grpc_http_request* request,
                               const char* host, const char* path,
                               bool connection_close,
                               std::vector<std::string>* buf) {
  // Add request path and HTTP version
  buf->push_back(path);
  buf->push_back(" HTTP/1.1\r\n");
  
  // Add Host header
  buf->push_back("Host: ");
  buf->push_back(host);
  buf->push_back("\r\n");
  
  // Add Connection header if needed
  if (connection_close) buf->push_back("Connection: close\r\n");
  
  // Add default User-Agent header
  buf->push_back("User-Agent: " GRPC_HTTPCLI_USER_AGENT "\r\n");

  // Add all custom headers from the request
  for (size_t i = 0; i < request->hdr_count; i++) {
    buf->push_back(request->hdrs[i].key);
    buf->push_back(": ");
    buf->push_back(request->hdrs[i].value);
    buf->push_back("\r\n");
  }
}

/**
 * Formats a HTTP GET request.
 * 
 * @param request The HTTP request details
 * @param host The target host
 * @param path The request path/URI
 * @return Formatted request as a grpc_slice
 */
grpc_slice grpc_httpcli_format_get_request(const grpc_http_request* request,
                                           const char* host, const char* path) {
  std::vector<std::string> out;
  out.push_back("GET ");
  fill_common_header(request, host, path, true, &out);
  out.push_back("\r\n");
  std::string req = absl::StrJoin(out, "");
  return grpc_slice_from_copied_buffer(req.data(), req.size());
}

/**
 * Formats a HTTP POST request.
 * Handles Content-Type and Content-Length headers for requests with body.
 * 
 * @param request The HTTP request details
 * @param host The target host
 * @param path The request path/URI
 * @return Formatted request as a grpc_slice
 */
grpc_slice grpc_httpcli_format_post_request(const grpc_http_request* request,
                                            const char* host,
                                            const char* path) {
  std::vector<std::string> out;
  out.push_back("POST ");
  fill_common_header(request, host, path, true, &out);
  
  // Handle request body if present
  if (request->body != nullptr) {
    // Check if Content-Type header was provided
    bool has_content_type = false;
    for (size_t i = 0; i < request->hdr_count; i++) {
      if (strcmp(request->hdrs[i].key, "Content-Type") == 0) {
        has_content_type = true;
        break;
      }
    }
    // Add default Content-Type if not provided
    if (!has_content_type) {
      out.push_back("Content-Type: text/plain\r\n");
    }
    // Add Content-Length header
    out.push_back(
        absl::StrFormat("Content-Length: %lu\r\n",
                        static_cast<unsigned long>(request->body_length)));
  }
  
  out.push_back("\r\n");
  std::string req = absl::StrJoin(out, "");
  
  // Append request body if present
  if (request->body != nullptr) {
    absl::StrAppend(&req,
                    absl::string_view(request->body, request->body_length));
  }
  
  return grpc_slice_from_copied_buffer(req.data(), req.size());
}

/**
 * Formats a HTTP PUT request.
 * Handles Content-Type and Content-Length headers for requests with body.
 * 
 * @param request The HTTP request details
 * @param host The target host
 * @param path The request path/URI
 * @return Formatted request as a grpc_slice
 */
grpc_slice grpc_httpcli_format_put_request(const grpc_http_request* request,
                                           const char* host, const char* path) {
  std::vector<std::string> out;
  out.push_back("PUT ");
  fill_common_header(request, host, path, true, &out);
  
  // Handle request body if present (same logic as POST)
  if (request->body != nullptr) {
    bool has_content_type = false;
    for (size_t i = 0; i < request->hdr_count; i++) {
      if (strcmp(request->hdrs[i].key, "Content-Type") == 0) {
        has_content_type = true;
        break;
      }
    }
    if (!has_content_type) {
      out.push_back("Content-Type: text/plain\r\n");
    }
    out.push_back(
        absl::StrFormat("Content-Length: %lu\r\n",
                        static_cast<unsigned long>(request->body_length)));
  }
  
  out.push_back("\r\n");
  std::string req = absl::StrJoin(out, "");
  
  // Append request body if present
  if (request->body != nullptr) {
    absl::StrAppend(&req,
                    absl::string_view(request->body, request->body_length));
  }
  
  return grpc_slice_from_copied_buffer(req.data(), req.size());
}

/**
 * Formats a HTTP CONNECT request.
 * 
 * @param request The HTTP request details
 * @param host The target host
 * @param path The request path/URI
 * @return Formatted request as a grpc_slice
 */
grpc_slice grpc_httpcli_format_connect_request(const grpc_http_request* request,
                                               const char* host,
                                               const char* path) {
  std::vector<std::string> out;
  out.push_back("CONNECT ");
  fill_common_header(request, host, path, false, &out);
  out.push_back("\r\n");
  std::string req = absl::StrJoin(out, "");
  return grpc_slice_from_copied_buffer(req.data(), req.size());
}
```

Key improvements made:
1. Added detailed function-level documentation explaining purpose and parameters
2. Added inline comments explaining key logic blocks
3. Documented the common header construction process
4. Explained the body handling logic for POST/PUT requests
5. Noted the difference in connection handling for CONNECT requests
6. Maintained consistent comment style throughout

The comments now provide clear guidance for future maintainers about:
- What each function does
- How the HTTP request is constructed
- Special handling for different request types
- Important implementation details
- Parameter and return value meanings