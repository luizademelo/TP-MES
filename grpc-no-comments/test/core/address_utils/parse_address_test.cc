
// Copyright 2017 gRPC authors.

#include "src/core/lib/address_utils/parse_address.h"
#ifdef GRPC_HAVE_UNIX_SOCKET
#ifdef GPR_WINDOWS

#include <ws2def.h>
#include <afunix.h>

#else
#include <sys/un.h>
#endif
#endif

#ifdef GRPC_HAVE_VSOCK
#include <linux/vm_sockets.h>
#endif

#include <grpc/grpc.h>

#include <string>

#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/match.h"
#include "gtest/gtest.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/lib/iomgr/socket_utils.h"
#include "test/core/test_util/test_config.h"

#ifdef GRPC_HAVE_UNIX_SOCKET

static void test_grpc_parse_unix(const char* uri_text, const char* pathname) {
  grpc_core::ExecCtx exec_ctx;
  absl::StatusOr<grpc_core::URI> uri = grpc_core::URI::Parse(uri_text);
  if (!uri.ok()) {
    LOG(ERROR) << uri.status();
    ASSERT_TRUE(uri.ok());
  }
  grpc_resolved_address addr;

  ASSERT_TRUE(grpc_parse_uri(*uri, &addr));
  struct sockaddr_un* addr_un =
      reinterpret_cast<struct sockaddr_un*>(addr.addr);
  ASSERT_EQ(AF_UNIX, addr_un->sun_family);
  ASSERT_STREQ(addr_un->sun_path, pathname);
}

static void test_grpc_parse_unix_abstract(const char* uri_text,
                                          const char* pathname) {
  grpc_core::ExecCtx exec_ctx;
  absl::StatusOr<grpc_core::URI> uri = grpc_core::URI::Parse(uri_text);
  if (!uri.ok()) {
    LOG(ERROR) << uri.status();
    ASSERT_TRUE(uri.ok());
  }
  grpc_resolved_address addr;

  ASSERT_TRUE(grpc_parse_uri(*uri, &addr));
  struct sockaddr_un* addr_un =
      reinterpret_cast<struct sockaddr_un*>(addr.addr);
  ASSERT_EQ(AF_UNIX, addr_un->sun_family);
  ASSERT_EQ('\0', addr_un->sun_path[0]);
  ASSERT_TRUE(absl::StartsWith(addr_un->sun_path + 1, pathname));
}

#else

static void test_grpc_parse_unix(const char* uri_text, const char* pathname) {}
static void test_grpc_parse_unix_abstract(const char* uri_text,
                                          const char* pathname) {}

#endif

#ifdef GRPC_HAVE_VSOCK

static void test_grpc_parse_vsock(const char* uri_text, uint32_t cid,
                                  uint32_t port) {
  grpc_core::ExecCtx exec_ctx;
  absl::StatusOr<grpc_core::URI> uri = grpc_core::URI::Parse(uri_text);
  if (!uri.ok()) {
    LOG(ERROR) << uri.status();
    ASSERT_TRUE(uri.ok());
  }
  grpc_resolved_address addr;

  ASSERT_TRUE(grpc_parse_uri(*uri, &addr));
  struct sockaddr_vm* addr_vm =
      reinterpret_cast<struct sockaddr_vm*>(addr.addr);
  ASSERT_EQ(AF_VSOCK, addr_vm->svm_family);
  ASSERT_EQ(grpc_ntohl(addr_vm->svm_cid), cid);
  ASSERT_EQ(addr_vm->svm_port, port);
}

#else

static void test_grpc_parse_vsock(const char* , ...) {}

#endif

static void test_grpc_parse_ipv4(const char* uri_text, const char* host,
                                 unsigned short port) {
  grpc_core::ExecCtx exec_ctx;
  absl::StatusOr<grpc_core::URI> uri = grpc_core::URI::Parse(uri_text);
  if (!uri.ok()) {
    LOG(ERROR) << uri.status();
    ASSERT_TRUE(uri.ok());
  }
  grpc_resolved_address addr;
  char ntop_buf[GRPC_INET_ADDRSTRLEN];

  ASSERT_TRUE(grpc_parse_ipv4(*uri, &addr));
  grpc_sockaddr_in* addr_in = reinterpret_cast<grpc_sockaddr_in*>(addr.addr);
  ASSERT_EQ(GRPC_AF_INET, addr_in->sin_family);
  ASSERT_NE(nullptr, grpc_inet_ntop(GRPC_AF_INET, &addr_in->sin_addr, ntop_buf,
                                    sizeof(ntop_buf)));
  ASSERT_STREQ(ntop_buf, host);
  ASSERT_EQ(grpc_ntohs(addr_in->sin_port), port);
}

static void test_grpc_parse_ipv6(const char* uri_text, const char* host,
                                 unsigned short port, uint32_t scope_id) {
  grpc_core::ExecCtx exec_ctx;
  absl::StatusOr<grpc_core::URI> uri = grpc_core::URI::Parse(uri_text);
  if (!uri.ok()) {
    LOG(ERROR) << uri.status();
    ASSERT_TRUE(uri.ok());
  }
  grpc_resolved_address addr;
  char ntop_buf[GRPC_INET6_ADDRSTRLEN];
  ASSERT_TRUE(grpc_parse_ipv6(*uri, &addr));
  grpc_sockaddr_in6* addr_in6 = reinterpret_cast<grpc_sockaddr_in6*>(addr.addr);
  ASSERT_EQ(GRPC_AF_INET6, addr_in6->sin6_family);
  ASSERT_NE(nullptr, grpc_inet_ntop(GRPC_AF_INET6, &addr_in6->sin6_addr,
                                    ntop_buf, sizeof(ntop_buf)));
  ASSERT_STREQ(ntop_buf, host);
  ASSERT_EQ(grpc_ntohs(addr_in6->sin6_port), port);
  ASSERT_EQ(addr_in6->sin6_scope_id, scope_id);
}

static void test_grpc_parse_ipv6_invalid(const char* uri_text) {
  grpc_core::ExecCtx exec_ctx;
  absl::StatusOr<grpc_core::URI> uri = grpc_core::URI::Parse(uri_text);
  if (!uri.ok()) {
    LOG(ERROR) << uri.status();
    ASSERT_TRUE(uri.ok());
  }
  grpc_resolved_address addr;
  ASSERT_FALSE(grpc_parse_ipv6(*uri, &addr));
}

TEST(ParseAddressTest, MainTest) {
  grpc_init();

  test_grpc_parse_unix("unix:/path/name", "/path/name");
  test_grpc_parse_unix_abstract("unix-abstract:foobar", "foobar");
  test_grpc_parse_vsock("vsock:-1:12345", -1, 12345);
  test_grpc_parse_ipv4("ipv4:192.0.2.1:12345", "192.0.2.1", 12345);
  test_grpc_parse_ipv6("ipv6:[2001:db8::1]:12345", "2001:db8::1", 12345, 0);
  test_grpc_parse_ipv6("ipv6:[2001:db8::1%252]:12345", "2001:db8::1", 12345, 2);

  test_grpc_parse_ipv6_invalid(
      "ipv6:WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW45%"
      "25v6:45%25x$1*");

  grpc_shutdown();
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
