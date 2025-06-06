
// Copyright 2018 gRPC authors.

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS

#include <grpc/support/alloc.h>
#include <grpc/support/sync.h>
#include <shellapi.h>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

#include "src/core/credentials/transport/alts/check_gcp_environment.h"
#include "src/core/util/crash.h"

namespace grpc_core {
namespace internal {

bool check_bios_data(const char*) { return false; }

bool check_windows_registry_product_name(HKEY root_key,
                                         const char* reg_key_path,
                                         const char* reg_key_name) {
  const size_t kProductNameBufferSize = 256;
  char const expected_substr[] = "Google";

  DWORD buffer_size{};
  auto rc = ::RegGetValueA(
      root_key, reg_key_path, reg_key_name, RRF_RT_REG_SZ,
      nullptr,
      nullptr,
      &buffer_size);
  if (rc != 0) {
    return false;
  }

  if (buffer_size > kProductNameBufferSize) {
    return false;
  }

  char buffer[kProductNameBufferSize];
  buffer_size = kProductNameBufferSize;
  rc = ::RegGetValueA(
      root_key, reg_key_path, reg_key_name, RRF_RT_REG_SZ,
      nullptr,
      static_cast<void*>(buffer),
      &buffer_size);
  if (rc != 0) {
    return false;
  }

  return strstr(buffer, expected_substr) != nullptr;
}

}
}

static bool g_compute_engine_detection_done = false;
static bool g_is_on_compute_engine = false;
static gpr_mu g_mu;
static gpr_once g_once = GPR_ONCE_INIT;

static void init_mu(void) { gpr_mu_init(&g_mu); }

bool grpc_alts_is_running_on_gcp() {
  char const reg_key_path[] = "SYSTEM\\HardwareConfig\\Current\\";
  char const reg_key_name[] = "SystemProductName";

  gpr_once_init(&g_once, init_mu);
  gpr_mu_lock(&g_mu);
  if (!g_compute_engine_detection_done) {
    g_is_on_compute_engine =
        grpc_core::internal::check_windows_registry_product_name(
            HKEY_LOCAL_MACHINE, reg_key_path, reg_key_name);
    g_compute_engine_detection_done = true;
  }
  gpr_mu_unlock(&g_mu);
  return g_is_on_compute_engine;
}

#endif  // GPR_WINDOWS
