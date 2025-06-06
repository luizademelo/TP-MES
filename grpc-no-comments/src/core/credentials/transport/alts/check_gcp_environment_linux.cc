
// Copyright 2018 gRPC authors.

#include <grpc/support/port_platform.h>

#ifdef GPR_LINUX

#include <grpc/support/alloc.h>
#include <grpc/support/sync.h>
#include <string.h>

#include "src/core/credentials/transport/alts/check_gcp_environment.h"

#define GRPC_ALTS_EXPECT_NAME_GOOGLE "Google"
#define GRPC_ALTS_EXPECT_NAME_GCE "Google Compute Engine"
#define GRPC_ALTS_PRODUCT_NAME_FILE "/sys/class/dmi/id/product_name"

static bool g_compute_engine_detection_done = false;
static bool g_is_on_compute_engine = false;
static gpr_mu g_mu;
static gpr_once g_once = GPR_ONCE_INIT;

namespace grpc_core {
namespace internal {

bool check_bios_data(const char* bios_data_file) {
  char* bios_data = read_bios_file(bios_data_file);
  bool result =
      bios_data && ((!strcmp(bios_data, GRPC_ALTS_EXPECT_NAME_GOOGLE)) ||
                    (!strcmp(bios_data, GRPC_ALTS_EXPECT_NAME_GCE)));
  gpr_free(bios_data);
  return result;
}

}
}

static void init_mu(void) { gpr_mu_init(&g_mu); }

bool grpc_alts_is_running_on_gcp() {
  gpr_once_init(&g_once, init_mu);
  gpr_mu_lock(&g_mu);
  if (!g_compute_engine_detection_done) {
    g_is_on_compute_engine =
        grpc_core::internal::check_bios_data(GRPC_ALTS_PRODUCT_NAME_FILE);
    g_compute_engine_detection_done = true;
  }
  gpr_mu_unlock(&g_mu);
  return g_is_on_compute_engine;
}

#endif
