
// Copyright 2017 gRPC authors.

#include <grpc/support/alloc.h>
#include <inttypes.h>
#include <net/if.h>
#include <netdb.h>
#include <string.h>
#ifdef GRPC_HAVE_UNIX_SOCKET
#include <sys/un.h>
#endif

#include <grpc/grpc.h>

#include <string>

#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_format.h"
#include "gtest/gtest.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/util/crash.h"
#include "src/core/util/host_port.h"
#include "src/core/util/uri.h"
#include "test/core/test_util/test_config.h"

static void test_grpc_parse_ipv6_parity_with_getaddrinfo(
    const char* target, const struct sockaddr_in6 result_from_getaddrinfo) {

  grpc_core::ExecCtx exec_ctx;
  absl::StatusOr<grpc_core::URI> uri = grpc_core::URI::Parse(target);
  if (!uri.ok()) {
    LOG(ERROR) << uri.status();
    ASSERT_TRUE(uri.ok());
  }
  grpc_resolved_address addr;
  ASSERT_TRUE(grpc_parse_ipv6(*uri, &addr));
  grpc_sockaddr_in6* result_from_grpc_parser =
      reinterpret_cast<grpc_sockaddr_in6*>(addr.addr);

  ASSERT_EQ(result_from_grpc_parser->sin6_family, AF_INET6);
  ASSERT_EQ(result_from_getaddrinfo.sin6_family, AF_INET6);
  ASSERT_EQ(memcmp(&result_from_grpc_parser->sin6_addr,
                   &result_from_getaddrinfo.sin6_addr, sizeof(in6_addr)),
            0);
  ASSERT_EQ(result_from_grpc_parser->sin6_scope_id,
            result_from_getaddrinfo.sin6_scope_id);
  ASSERT_NE(result_from_grpc_parser->sin6_scope_id, 0);

}

struct sockaddr_in6 resolve_with_gettaddrinfo(const char* uri_text) {
  absl::StatusOr<grpc_core::URI> uri = grpc_core::URI::Parse(uri_text);
  if (!uri.ok()) {
    LOG(ERROR) << uri.status();
    EXPECT_TRUE(uri.ok());
  }
  std::string host;
  std::string port;
  grpc_core::SplitHostPort(uri->path(), &host, &port);
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET6;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_NUMERICHOST;
  struct addrinfo* result;
  int res = getaddrinfo(host.c_str(), port.c_str(), &hints, &result);
  if (res != 0) {
    grpc_core::Crash(absl::StrFormat(
        "getaddrinfo failed to resolve host:%s port:%s. Error: %d.",
        host.c_str(), port.c_str(), res));
  }
  size_t num_addrs_from_getaddrinfo = 0;
  for (struct addrinfo* resp = result; resp != nullptr; resp = resp->ai_next) {
    num_addrs_from_getaddrinfo++;
  }
  EXPECT_EQ(num_addrs_from_getaddrinfo, 1);
  EXPECT_EQ(result->ai_family, AF_INET6);
  struct sockaddr_in6 out =
      *reinterpret_cast<struct sockaddr_in6*>(result->ai_addr);

  freeaddrinfo(result);
  return out;
}

TEST(ParseAddressWithNamedScopeIdTest, MainTest) {
  grpc_init();
  char* arbitrary_interface_name = static_cast<char*>(gpr_zalloc(IF_NAMESIZE));

  for (size_t i = 1; i < 65536; i++) {
    if (if_indextoname(i, arbitrary_interface_name) != nullptr) {
      VLOG(2) << "Found interface at index " << i << " named "
              << arbitrary_interface_name << ". Will use this for the test";
      break;
    }
  }
  ASSERT_GT(strlen(arbitrary_interface_name), 0);
  std::string target =
      absl::StrFormat("ipv6:[fe80::1234%%%s]:12345", arbitrary_interface_name);
  struct sockaddr_in6 result_from_getaddrinfo =
      resolve_with_gettaddrinfo(target.c_str());

  VLOG(2) << "Run test_grpc_parse_ipv6_parity_with_getaddrinfo with target: "
          << target;
  test_grpc_parse_ipv6_parity_with_getaddrinfo(target.c_str(),
                                               result_from_getaddrinfo);

  gpr_free(arbitrary_interface_name);
  grpc_shutdown();
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
