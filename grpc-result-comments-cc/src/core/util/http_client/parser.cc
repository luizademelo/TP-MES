Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include "src/core/util/http_client/parser.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <string.h>

#include <algorithm>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"

// Converts a buffer to a null-terminated string by allocating memory and copying
// the buffer contents. Caller is responsible for freeing the returned string.
static char* buf2str(void* buffer, size_t length) {
  char* out = static_cast<char*>(gpr_malloc(length + 1));
  memcpy(out, buffer, length);
  out[length] = 0;
  return out;
}

// Parses the HTTP response line (e.g., "HTTP/1.1 200 OK")
// Validates the format and extracts the status code.
static grpc_error_handle handle_response_line(grpc_http_parser* parser) {
  uint8_t* beg = parser->cur_line;
  uint8_t* cur = beg;
  uint8_t* end = beg + parser->cur_line_length;

  // Validate HTTP version prefix
  if (cur == end || *cur++ != 'H') {
    return GRPC_ERROR_CREATE("Expected 'H'");
  }
  if (cur == end || *cur++ != 'T') {
    return GRPC_ERROR_CREATE("Expected 'T'");
  }
  if (cur == end || *cur++ != 'T') {
    return GRPC_ERROR_CREATE("Expected 'T'");
  }
  if (cur == end || *cur++ != 'P') {
    return GRPC_ERROR_CREATE("Expected 'P'");
  }
  if (cur == end || *cur++ != '/') {
    return GRPC_ERROR_CREATE("Expected '/'");
  }
  if (cur == end || *cur++ != '1') {
    return GRPC_ERROR_CREATE("Expected '1'");
  }
  if (cur == end || *cur++ != '.') {
    return GRPC_ERROR_CREATE("Expected '.'");
  }
  // Only support HTTP/1.0 or HTTP/1.1
  if (cur == end || *cur < '0' || *cur++ > '1') {
    return GRPC_ERROR_CREATE("Expected HTTP/1.0 or HTTP/1.1");
  }
  if (cur == end || *cur++ != ' ') {
    return GRPC_ERROR_CREATE("Expected ' '");
  }
  // Parse status code (3 digits)
  if (cur == end || *cur < '1' || *cur++ > '9') {
    return GRPC_ERROR_CREATE("Expected status code");
  }
  if (cur == end || *cur < '0' || *cur++ > '9') {
    return GRPC_ERROR_CREATE("Expected status code");
  }
  if (cur == end || *cur < '0' || *cur++ > '9') {
    return GRPC_ERROR_CREATE("Expected status code");
  }
  // Calculate status code from ASCII digits
  parser->http.response->status =
      (cur[-3] - '0') * 100 + (cur[-2] - '0') * 10 + (cur[-1] - '0');
  if (cur == end || *cur++ != ' ') {
    return GRPC_ERROR_CREATE("Expected ' '");
  }

  return absl::OkStatus();
}

// Parses the HTTP request line (e.g., "GET /path HTTP/1.1")
// Extracts method, path, and HTTP version.
static grpc_error_handle handle_request_line(grpc_http_parser* parser) {
  uint8_t* beg = parser->cur_line;
  uint8_t* cur = beg;
  uint8_t* end = beg + parser->cur_line_length;
  uint8_t vers_major = 0;
  uint8_t vers_minor = 0;

  // Extract method (first token before space)
  while (cur != end && *cur++ != ' ') {
  }
  if (cur == end) {
    return GRPC_ERROR_CREATE("No method on HTTP request line");
  }
  parser->http.request->method =
      buf2str(beg, static_cast<size_t>(cur - beg - 1));

  // Extract path (next token before space)
  beg = cur;
  while (cur != end && *cur++ != ' ') {
  }
  if (cur == end) {
    return GRPC_ERROR_CREATE("No path on HTTP request line");
  }
  parser->http.request->path = buf2str(beg, static_cast<size_t>(cur - beg - 1));

  // Validate HTTP version prefix
  if (cur == end || *cur++ != 'H') {
    return GRPC_ERROR_CREATE("Expected 'H'");
  }
  if (cur == end || *cur++ != 'T') {
    return GRPC_ERROR_CREATE("Expected 'T'");
  }
  if (cur == end || *cur++ != 'T') {
    return GRPC_ERROR_CREATE("Expected 'T'");
  }
  if (cur == end || *cur++ != 'P') {
    return GRPC_ERROR_CREATE("Expected 'P'");
  }
  if (cur == end || *cur++ != '/') {
    return GRPC_ERROR_CREATE("Expected '/'");
  }
  // Parse version numbers
  vers_major = static_cast<uint8_t>(*cur++ - '1' + 1);
  ++cur;
  if (cur == end) {
    return GRPC_ERROR_CREATE("End of line in HTTP version string");
  }
  vers_minor = static_cast<uint8_t>(*cur++ - '1' + 1);

  // Set version enum based on parsed numbers
  if (vers_major == 1) {
    if (vers_minor == 0) {
      parser->http.request->version = GRPC_HTTP_HTTP10;
    } else if (vers_minor == 1) {
      parser->http.request->version = GRPC_HTTP_HTTP11;
    } else {
      return GRPC_ERROR_CREATE(
          "Expected one of HTTP/1.0, HTTP/1.1, or HTTP/2.0");
    }
  } else if (vers_major == 2) {
    if (vers_minor == 0) {
      parser->http.request->version = GRPC_HTTP_HTTP20;
    } else {
      return GRPC_ERROR_CREATE(
          "Expected one of HTTP/1.0, HTTP/1.1, or HTTP/2.0");
    }
  } else {
    return GRPC_ERROR_CREATE("Expected one of HTTP/1.0, HTTP/1.1, or HTTP/2.0");
  }

  return absl::OkStatus();
}

// Dispatches to either request or response line handler based on parser type
static grpc_error_handle handle_first_line(grpc_http_parser* parser) {
  switch (parser->type) {
    case GRPC_HTTP_REQUEST:
      return handle_request_line(parser);
    case GRPC_HTTP_RESPONSE:
      return handle_response_line(parser);
  }
  GPR_UNREACHABLE_CODE(return GRPC_ERROR_CREATE("Should never reach here"));
}

// Parses and adds a header line to the request/response
static grpc_error_handle add_header(grpc_http_parser* parser) {
  uint8_t* beg = parser->cur_line;
  uint8_t* cur = beg;
  uint8_t* end = beg + parser->cur_line_length;
  size_t* hdr_count = nullptr;
  size_t size = 0;
  grpc_http_header** hdrs = nullptr;
  grpc_http_header hdr = {nullptr, nullptr};
  grpc_error_handle error;

  CHECK(cur != end);

  // Check for header continuation (not supported)
  if (*cur == ' ' || *cur == '\t') {
    error = GRPC_ERROR_CREATE("Continued header lines not supported yet");
    goto done;
  }

  // Find header key (before colon)
  while (cur != end && *cur != ':') {
    cur++;
  }
  if (cur == end) {
    error = GRPC_ERROR_CREATE("Didn't find ':' in header string");
    goto done;
  }
  CHECK(cur >= beg);
  hdr.key = buf2str(beg, static_cast<size_t>(cur - beg));
  cur++;

  // Skip whitespace after colon
  while (cur != end && (*cur == ' ' || *cur == '\t')) {
    cur++;
  }
  CHECK((size_t)(end - cur) >= parser->cur_line_end_length);
  size = static_cast<size_t>(end - cur) - parser->cur_line_end_length;
  if ((size != 0) && (cur[size - 1] == '\r')) {
    size--;
  }
  hdr.value = buf2str(cur, size);

  // Add header to appropriate structure (request or response)
  switch (parser->type) {
    case GRPC_HTTP_RESPONSE:
      hdr_count = &parser->http.response->hdr_count;
      hdrs = &parser->http.response->hdrs;
      // Special handling for chunked transfer encoding
      if ((strcmp(hdr.key, "Transfer-Encoding") == 0) &&
          (strcmp(hdr.value, "chunked") == 0)) {
        parser->http.response->chunked_state = GRPC_HTTP_CHUNKED_LENGTH;
      }
      break;
    case GRPC_HTTP_REQUEST:
      hdr_count = &parser->http.request->hdr_count;
      hdrs = &parser->http.request->hdrs;
      break;
  }

  // Grow header array if needed
  if (*hdr_count == parser->hdr_capacity) {
    parser->hdr_capacity =
        std::max(parser->hdr_capacity + 1, parser->hdr_capacity * 3 / 2);
    *hdrs = static_cast<grpc_http_header*>(
        gpr_realloc(*hdrs, parser->hdr_capacity * sizeof(**hdrs)));
  }
  (*hdrs)[(*hdr_count)++] = hdr;

done:
  // Clean up on error
  if (!error.ok()) {
    gpr_free(hdr.key);
    gpr_free(hdr.value);
  }
  return error;
}

// Completes processing of the current line based on parser state
static grpc_error_handle finish_line(grpc_http_parser* parser,
                                     bool* found_body_start) {
  grpc_error_handle err;
  switch (parser->state) {
    case GRPC_HTTP_FIRST_LINE:
      err = handle_first_line(parser);
      if (!err.ok()) return err;
      parser->state = GRPC_HTTP_HEADERS;
      break;
    case GRPC_HTTP_HEADERS:
    case GRPC_HTTP_TRAILERS:
      // Empty line indicates end of headers/start of body
      if (parser->cur_line_length == parser->cur_line_end_length) {
        if (parser->state == GRPC_HTTP_HEADERS) {
          parser->state = GRPC_HTTP_BODY;
          *found_body_start = true;
        } else {
          parser->state = GRPC_HTTP_END;
        }
        break;
      } else {
        err = add_header(parser);
        if (!err.ok()) {
          return err;
        }
      }
      break;
    case GRPC_HTTP_BODY:
    case GRPC_HTTP_END:
      GPR_UNREACHABLE_CODE(return GRPC_ERROR_CREATE("Should never reach here"));
  }

  parser->cur_line_length = 0;
  return absl::OkStatus();
}

// Processes a byte in the body, handling chunked transfer encoding if needed
static grpc_error_handle addbyte_body(grpc_http_parser* parser, uint8_t byte) {
  size_t* body_length = nullptr;
  char** body = nullptr;

  if (parser->type == GRPC_HTTP_RESPONSE) {
    switch (parser->http.response->chunked_state) {
      case GRPC_HTTP_CHUNKED_LENGTH:
        // Parse chunk length in hexadecimal
        if ((byte == '\r') || (byte == ';')) {
          parser->http.response->chunked_state =
              GRPC_HTTP_CHUNKED_IGNORE_ALL_UNTIL_LF;
        } else if ((byte >= '0') && (byte <= '9')) {
          parser->http.response->chunk_length *= 16;
          parser->http.response->chunk_length += byte - '0';
        } else if ((byte >= 'a') && (byte <= 'f')) {
          parser->http.response->chunk_length *= 16;
          parser->http.response->chunk_length += byte - 'a' + 10;
        } else if ((byte >= 'A') && (byte <= 'F')) {
          parser->http.response->chunk_length *= 16;
          parser->http.response->chunk_length += byte - 'A' + 10;
        } else {
          return GRPC_ERROR_CREATE("Expected chunk size in hexadecimal");
        }
        return absl::OkStatus();
      case GRPC_HTTP_CHUNKED_IGNORE_ALL_UNTIL_LF:
        // Wait for LF after chunk length
        if (byte == '\n') {
          if (parser->http.response->chunk_length == 0) {
            parser->state = GRPC_HTTP_TRAILERS;
          } else {
            parser->http.response->chunked_state = GRPC_HTTP_CHUNKED_BODY;
          }
        }
        return absl::OkStatus();
      case GRPC_HTTP_CHUNKED_BODY:
        // Process chunk body bytes
        if (parser->http.response->chunk_length == 0) {
          if (byte != '\r') {
            return GRPC_ERROR_CREATE("Expected '\\r\\n' after chunk body");
          }
          parser->http.response->chunked_state = GRPC_HTTP_CHUNKED_CONSUME_LF;
          parser->http.response->chunk_length = 0;
          return absl::OkStatus();
        } else {
          parser->http.response->chunk_length--;
        }
        break;
      case GRPC_HTTP_CHUNKED_CONSUME_LF:
        // Expect LF after chunk body
        if (byte != '\n') {
          return GRPC_ERROR_CREATE("Expected '\\r\\n' after chunk body");
        }
        parser->http.response->chunked_state = GRPC_HTTP_CHUNKED_LENGTH;
        return absl::OkStatus();
      case GRPC_HTTP_CHUNKED_PLAIN:
        break;
    }
    body_length = &parser->http.response->body_length;
    body = &parser->http.response->body;
  } else if (parser->type == GRPC_HTTP_REQUEST) {
    body_length = &parser->http.request->body_length;
    body = &parser->http.request->body;
  } else {
    GPR_UNREACHABLE_CODE(return GRPC_ERROR_CREATE("Should never reach here"));
  }

  // Grow body buffer if needed
  if (*body_length == parser->body_capacity) {
    parser->body_capacity = std::max(size_t{8}, parser->body_capacity * 3 / 2);
    *body = static_cast<char*>(gpr_realloc(*body, parser->body_capacity));
  }
  (*body)[*body_length] = static_cast<char>(byte);
  (*body_length)++;

  return absl::OkStatus();
}

// Checks if current line ends with CRLF, LFCR, or LF
static bool check_line(grpc_http_parser* parser) {
  if (parser->cur_line_length >= 2 &&
      parser->cur_line[parser->cur_line_length - 2] == '\r' &&
      parser->cur_line[parser->cur_line_length - 1] == '\n') {
    return true;
  }
  else if (parser->cur_line_length >= 2 &&
           parser->cur_line[parser->cur_line_length - 2] == '\n' &&
           parser->cur_line[parser->cur_line_length - 1] == '\r') {
    return true;
  }
  else if (parser->cur_line_length >= 1 &&
           parser->cur_line[parser->cur_line_length - 1] == '\n') {
    parser->cur_line_end_length = 1;
    return true;
  }

  return false;
}

// Processes a single byte of HTTP input based on current parser state
static grpc_error_handle addbyte(grpc_http_parser* parser, uint8_t byte,
                                 bool* found_body_start) {
  switch (parser->state) {
    case GRPC_HTTP_FIRST_LINE:
    case GRPC_HTTP_HEADERS:
    case GRPC_HTTP_TRAILERS:
      // Check for max header length
      if (parser->cur_line_length >= GRPC_HTTP_PARSER_MAX_HEADER_LENGTH) {
        GRPC_TRACE_LOG(http1, ERROR)
            << "HTTP header max line length ("
            << GRPC_HTTP_PARSER_MAX_HEADER_LENGTH << ") exceeded";
        return GRPC_ERROR_CREATE("HTTP header max line length exceeded");
      }
      // Accumulate bytes until end of line
      parser->cur_line[parser->cur_line_length] = byte;
      parser->cur_line_length++;
      if (check_line(parser)) {
        return finish_line(parser, found_body_start);
      }
      return absl::OkStatus();
    case GRPC_HTTP_BODY:
      return addbyte_body(parser, byte);
    case GRPC_HTTP_END:
      return GRPC_ERROR_CREATE("Unexpected byte after end");
  }
  GPR_UNREACHABLE_CODE(return absl::OkStatus());
}

// Initializes HTTP parser for either request or response parsing
void grpc_http_parser_init(grpc_http_parser* parser, grpc_http_type type,
                           void* request_or_response) {
  memset(parser, 0, sizeof(*parser));
  parser->state = GRPC_HTTP_FIRST_LINE;
  parser->type = type