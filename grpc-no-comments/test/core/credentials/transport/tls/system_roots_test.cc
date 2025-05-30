
// Copyright 2018 gRPC authors.

#include <grpc/support/port_platform.h>
#include <stdio.h>

#if defined(GPR_LINUX) || defined(GPR_FREEBSD) || defined(GPR_APPLE) || \
    defined(GPR_WINDOWS)
#include <string.h>
#if defined(GPR_LINUX) || defined(GPR_FREEBSD) || defined(GPR_APPLE)
#include <sys/param.h>
#endif

#include <grpc/grpc_security.h>
#include <grpc/support/alloc.h>
#include <grpc/support/string_util.h>

#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "gtest/gtest.h"
#include "src/core/credentials/transport/security_connector.h"
#include "src/core/credentials/transport/tls/load_system_roots.h"
#include "src/core/credentials/transport/tls/load_system_roots_supported.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_string_helpers.h"
#include "src/core/tsi/ssl_transport_security.h"
#include "src/core/tsi/transport_security.h"
#include "src/core/util/crash.h"
#include "src/core/util/env.h"
#include "src/core/util/load_file.h"
#include "src/core/util/tmpfile.h"
#include "test/core/test_util/test_config.h"

namespace grpc {
namespace {

#if defined(GPR_LINUX) || defined(GPR_FREEBSD) || defined(GPR_APPLE)
TEST(AbsoluteFilePathTest, ConcatenatesCorrectly) {
  const char* directory = "nonexistent/test/directory";
  const char* filename = "doesnotexist.txt";
  char result_path[MAXPATHLEN];
  grpc_core::GetAbsoluteFilePath(directory, filename, result_path);
  EXPECT_STREQ(result_path, "nonexistent/test/directory/doesnotexist.txt");
}

TEST(CreateRootCertsBundleTest, ReturnsEmpty) {

  grpc_slice result_slice = grpc_core::CreateRootCertsBundle(nullptr);
  EXPECT_TRUE(GRPC_SLICE_IS_EMPTY(result_slice));
  grpc_slice_unref(result_slice);
  result_slice = grpc_core::CreateRootCertsBundle("does/not/exist");
  EXPECT_TRUE(GRPC_SLICE_IS_EMPTY(result_slice));
  grpc_slice_unref(result_slice);
}

TEST(CreateRootCertsBundleTest, BundlesCorrectly) {

  constexpr absl::string_view kTestPathPrefix =
      "test/core/credentials/transport/tls/test_data/";
  absl::string_view roots_bundle_str;
  auto roots_bundle =
      grpc_core::LoadFile(absl::StrCat(kTestPathPrefix, "bundle.pem"),
                          false);
  if (roots_bundle.ok()) roots_bundle_str = roots_bundle->as_string_view();

  grpc_core::Slice result_slice(grpc_core::CreateRootCertsBundle(
      (absl::StrCat(kTestPathPrefix, "test_roots")).c_str()));
  EXPECT_EQ(result_slice.as_string_view(), roots_bundle_str)
      << "Expected: \"" << result_slice.as_string_view() << "\"\n"
      << "Actual:   \"" << roots_bundle_str << "\"";
}
#endif

#if defined(GPR_WINDOWS)
TEST(LoadSystemRootCertsTest, Success) {
  grpc_slice roots_slice = grpc_core::LoadSystemRootCerts();
  EXPECT_FALSE(GRPC_SLICE_IS_EMPTY(roots_slice));
  grpc_slice_unref(roots_slice);
}
#endif

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#else
int main() {
  printf(
      "*** WARNING: this test is only supported on Linux, FreeBSD, and MacOS"
      "systems ***\n");
  return 0;
}
#endif
