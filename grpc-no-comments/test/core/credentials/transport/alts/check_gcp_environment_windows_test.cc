
// Copyright 2018 gRPC authors.

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <stdio.h>
#include <string.h>

#include "gtest/gtest.h"
#include "src/core/credentials/transport/alts/check_gcp_environment.h"
#include "src/core/util/crash.h"
#include "src/core/util/tmpfile.h"

#ifdef GPR_WINDOWS

namespace grpc_core {
namespace internal {

bool check_windows_registry_product_name(HKEY root_key,
                                         const char* reg_key_path,
                                         const char* reg_key_name);

}
}

static bool check_bios_data_windows_test(const char* data) {
  char const reg_key_path[] = "SYSTEM\\HardwareConfig\\Current\\";
  char const reg_key_name[] = "grpcTestValueName";
  // Modify the registry for the current user to contain the
  // test value. We cannot use the system registry because the
  // user may not have privileges to change it.
  auto rc = RegSetKeyValueA(HKEY_CURRENT_USER, reg_key_path, reg_key_name,
                            REG_SZ, reinterpret_cast<const BYTE*>(data),
                            static_cast<DWORD>(strlen(data)));
  if (rc != 0) {
    return false;
  }

  auto result = grpc_core::internal::check_windows_registry_product_name(
      HKEY_CURRENT_USER, reg_key_path, reg_key_name);

  (void)RegDeleteKeyValueA(HKEY_CURRENT_USER, reg_key_path, reg_key_name);

  return result;
}

TEST(CheckGcpEnvironmentWindowsTest, GcpEnvironmentCheckSuccess) {
  // This is the only value observed in production.
  ASSERT_TRUE(check_bios_data_windows_test("Google Compute Engine"));
  // Be generous and accept other values that were accepted by the previous
  // implementation.
  ASSERT_TRUE(check_bios_data_windows_test("Google"));
  ASSERT_TRUE(check_bios_data_windows_test("Google\n"));
  ASSERT_TRUE(check_bios_data_windows_test("Google\r"));
  ASSERT_TRUE(check_bios_data_windows_test("Google\r\n"));
  ASSERT_TRUE(check_bios_data_windows_test("   Google   \r\n"));
  ASSERT_TRUE(check_bios_data_windows_test(" \t\t Google\r\n"));
  ASSERT_TRUE(check_bios_data_windows_test(" \t\t Google\t\t  \r\n"));
}

TEST(CheckGcpEnvironmentWindowsTest, GcpEnvironmentCheckFailure) {
  ASSERT_FALSE(check_bios_data_windows_test("\t\tAmazon\n"));
  ASSERT_FALSE(check_bios_data_windows_test("  Amazon\r\n"));
}

#endif  // GPR_WINDOWS

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
