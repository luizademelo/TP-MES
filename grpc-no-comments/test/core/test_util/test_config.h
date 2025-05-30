
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_TEST_CONFIG_H
#define GRPC_TEST_CORE_TEST_UTIL_TEST_CONFIG_H

#include <grpc/support/time.h>
#include <stdint.h>

extern int64_t g_fixture_slowdown_factor;
extern int64_t g_poller_slowdown_factor;

int64_t grpc_test_slowdown_factor();

gpr_timespec grpc_timeout_seconds_to_deadline(int64_t time_s);

gpr_timespec grpc_timeout_milliseconds_to_deadline(int64_t time_ms);

#if !defined(GRPC_TEST_CUSTOM_PICK_PORT) && !defined(GRPC_PORT_ISOLATED_RUNTIME)
#define GRPC_TEST_PICK_PORT
#endif

void grpc_test_init(int* argc, char** argv);

void grpc_disable_all_absl_logs(void);

bool grpc_wait_until_shutdown(int64_t time_s);

void grpc_set_absl_verbosity_debug(void);

void grpc_prewarm_os_for_tests(void);

namespace grpc {
namespace testing {

class TestEnvironment {
 public:
  TestEnvironment(int* argc, char** argv);
  ~TestEnvironment();
};

class TestGrpcScope {
 public:
  TestGrpcScope();
  ~TestGrpcScope();
};

}
}

#endif
