
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CORE_IOMGR_ENDPOINT_TESTS_H
#define GRPC_TEST_CORE_IOMGR_ENDPOINT_TESTS_H

#include <sys/types.h>

#include "src/core/lib/iomgr/endpoint.h"

typedef struct grpc_endpoint_test_config grpc_endpoint_test_config;
typedef struct grpc_endpoint_test_fixture grpc_endpoint_test_fixture;

struct grpc_endpoint_test_fixture {
  grpc_endpoint* client_ep;
  grpc_endpoint* server_ep;
};

struct grpc_endpoint_test_config {
  const char* name;
  grpc_endpoint_test_fixture (*create_fixture)(size_t slice_size);
  void (*clean_up)();
};

void grpc_endpoint_tests(grpc_endpoint_test_config config,
                         grpc_pollset* pollset, gpr_mu* mu);

#endif
