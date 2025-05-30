
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/slice.h>
#include <stdint.h>
#include <string.h>

#include <cstdint>

#include "fuzztest/fuzztest.h"
#include "gtest/gtest.h"
#include "src/core/util/http_client/parser.h"

void RequestTest(std::vector<uint8_t> buffer) {
  grpc_http_parser parser;
  grpc_http_request request;
  grpc_init();
  memset(&request, 0, sizeof(request));
  grpc_http_parser_init(&parser, GRPC_HTTP_REQUEST, &request);
  grpc_slice slice =
      grpc_slice_from_copied_buffer((const char*)buffer.data(), buffer.size());
  (void)grpc_http_parser_parse(&parser, slice, nullptr);
  (void)grpc_http_parser_eof(&parser);
  grpc_slice_unref(slice);
  grpc_http_parser_destroy(&parser);
  grpc_http_request_destroy(&request);
  grpc_shutdown();
}
FUZZ_TEST(HttpClient, RequestTest);

void ResponseTest(std::vector<uint8_t> buffer) {
  grpc_http_parser parser;
  grpc_http_response response;
  grpc_init();
  response = {};
  grpc_http_parser_init(&parser, GRPC_HTTP_RESPONSE, &response);
  grpc_slice slice =
      grpc_slice_from_copied_buffer((const char*)buffer.data(), buffer.size());
  (void)grpc_http_parser_parse(&parser, slice, nullptr);
  (void)grpc_http_parser_eof(&parser);
  grpc_slice_unref(slice);
  grpc_http_parser_destroy(&parser);
  grpc_http_response_destroy(&response);
  grpc_shutdown();
}
FUZZ_TEST(HttpClient, ResponseTest);
