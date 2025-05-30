
// Copyright 2018 gRPC authors.

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <stdio.h>
#include <string.h>

#include "gtest/gtest.h"
#include "src/core/credentials/transport/alts/check_gcp_environment.h"
#include "src/core/util/crash.h"
#include "src/core/util/tmpfile.h"

#if GPR_LINUX

static bool check_bios_data_linux_test(const char* data) {

  char* filename = nullptr;
  FILE* fp = gpr_tmpfile("check_gcp_environment_test", &filename);
  EXPECT_NE(filename, nullptr);
  EXPECT_NE(fp, nullptr);
  EXPECT_EQ(fwrite(data, 1, strlen(data), fp), strlen(data));
  fclose(fp);
  bool result = grpc_core::internal::check_bios_data(
      reinterpret_cast<const char*>(filename));

  remove(filename);
  gpr_free(filename);
  return result;
}

TEST(CheckGcpEnvironmentLinuxTest, GcpEnvironmentCheckSuccess) {

  ASSERT_TRUE(check_bios_data_linux_test("Google"));
  ASSERT_TRUE(check_bios_data_linux_test("Google Compute Engine"));

  ASSERT_TRUE(check_bios_data_linux_test(" Google  "));
  ASSERT_TRUE(check_bios_data_linux_test("Google  "));
  ASSERT_TRUE(check_bios_data_linux_test("   Google"));
  ASSERT_TRUE(check_bios_data_linux_test("  Google Compute Engine  "));
  ASSERT_TRUE(check_bios_data_linux_test("Google Compute Engine  "));
  ASSERT_TRUE(check_bios_data_linux_test("  Google Compute Engine"));

  ASSERT_TRUE(check_bios_data_linux_test("\t\tGoogle Compute Engine\t"));
  ASSERT_TRUE(check_bios_data_linux_test("Google Compute Engine\n"));
  ASSERT_TRUE(check_bios_data_linux_test("\n\n\tGoogle Compute Engine \n\t\t"));
}

TEST(CheckGcpEnvironmentLinuxTest, GcpEnvironmentCheckFailure) {
  ASSERT_FALSE(check_bios_data_linux_test("non_existing-file"));
  ASSERT_FALSE(check_bios_data_linux_test("Google-Chrome"));
  ASSERT_FALSE(check_bios_data_linux_test("Amazon"));
  ASSERT_FALSE(check_bios_data_linux_test("Google-Chrome\t\t"));
  ASSERT_FALSE(check_bios_data_linux_test("Amazon"));
  ASSERT_FALSE(check_bios_data_linux_test("\n"));
}

#endif

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
