
// Copyright 2017 gRPC authors.

#if defined(GRPC_PORT_ISOLATED_RUNTIME)

#include <grpc/support/atm.h>
#include <grpc/support/time.h>
#include <stdlib.h>

#include "absl/log/check.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/util/crash.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"

#define MIN_PORT 1025
#define MAX_PORT 32766

static int get_random_port_offset() {
  srand(gpr_now(GPR_CLOCK_REALTIME).tv_nsec);
  double rnd = static_cast<double>(rand()) /
               (static_cast<double>(RAND_MAX) + 1.0);
  return static_cast<int>(rnd * (MAX_PORT - MIN_PORT + 1));
}

static int s_initial_offset = get_random_port_offset();
static gpr_atm s_pick_counter = 0;

static int grpc_pick_unused_port_or_die_impl(void) {
  int orig_counter_val =
      static_cast<int>(gpr_atm_full_fetch_add(&s_pick_counter, 1));
  CHECK(orig_counter_val < (MAX_PORT - MIN_PORT + 1));
  return MIN_PORT +
         (s_initial_offset + orig_counter_val) % (MAX_PORT - MIN_PORT + 1);
}

static int isolated_pick_unused_port_or_die(void) {
  while (true) {
    int port = grpc_pick_unused_port_or_die_impl();

    if (port == 5985) {
      continue;
    }
    return port;
  }
}

static void isolated_recycle_unused_port(int port) { (void)port; }

static const auto prev_fns =
    grpc_set_pick_port_functions(grpc_pick_port_functions{
        isolated_pick_unused_port_or_die, isolated_recycle_unused_port});

#endif
