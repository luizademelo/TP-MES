
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_HTTP_CLIENT_PARSER_H
#define GRPC_SRC_CORE_UTIL_HTTP_CLIENT_PARSER_H

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <stdint.h>

#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/error.h"

#define GRPC_HTTP_PARSER_MAX_HEADER_LENGTH 4096

typedef struct grpc_http_header {
  char* key;
  char* value;
} grpc_http_header;

typedef enum {
  GRPC_HTTP_FIRST_LINE,
  GRPC_HTTP_HEADERS,
  GRPC_HTTP_BODY,
  GRPC_HTTP_TRAILERS,
  GRPC_HTTP_END,
} grpc_http_parser_state;

typedef enum {
  GRPC_HTTP_CHUNKED_PLAIN,
  GRPC_HTTP_CHUNKED_LENGTH,
  GRPC_HTTP_CHUNKED_IGNORE_ALL_UNTIL_LF,
  GRPC_HTTP_CHUNKED_BODY,
  GRPC_HTTP_CHUNKED_CONSUME_LF,
} grpc_http_parser_chunked_state;

typedef enum {
  GRPC_HTTP_HTTP10,
  GRPC_HTTP_HTTP11,
  GRPC_HTTP_HTTP20,
} grpc_http_version;

typedef enum {
  GRPC_HTTP_RESPONSE,
  GRPC_HTTP_REQUEST,
} grpc_http_type;

typedef struct grpc_http_request {

  char* method;

  char* path;

  grpc_http_version version;

  size_t hdr_count;
  grpc_http_header* hdrs;

  size_t body_length;
  char* body;
} grpc_http_request;

typedef struct grpc_http_response {

  int status = 0;

  size_t hdr_count = 0;
  grpc_http_header* hdrs = nullptr;

  size_t body_length = 0;

  grpc_http_parser_chunked_state chunked_state = GRPC_HTTP_CHUNKED_PLAIN;
  size_t chunk_length = 0;
  char* body = nullptr;
} grpc_http_response;

struct grpc_http_parser {
  grpc_http_parser_state state;
  grpc_http_type type;

  union {
    grpc_http_response* response;
    grpc_http_request* request;
    void* request_or_response;
  } http;
  size_t body_capacity;
  size_t hdr_capacity;

  uint8_t cur_line[GRPC_HTTP_PARSER_MAX_HEADER_LENGTH];
  size_t cur_line_length;
  size_t cur_line_end_length;
};
void grpc_http_parser_init(grpc_http_parser* parser, grpc_http_type type,
                           void* request_or_response);
void grpc_http_parser_destroy(grpc_http_parser* parser);

grpc_error_handle grpc_http_parser_parse(grpc_http_parser* parser,
                                         const grpc_slice& slice,
                                         size_t* start_of_body);
grpc_error_handle grpc_http_parser_eof(grpc_http_parser* parser);

void grpc_http_request_destroy(grpc_http_request* request);
void grpc_http_response_destroy(grpc_http_response* response);

#endif
