// Copyright 2022 gRPC authors.

#include <grpc/support/port_platform.h>
#ifdef GPR_WINDOWS

#include <winsock2.h>
#include <ws2tcpip.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "src/core/lib/event_engine/windows/win_socket.h"
#include "src/core/lib/iomgr/error.h"
#include "test/core/event_engine/windows/create_sockpair.h"

namespace grpc_event_engine {
namespace experimental {

sockaddr_in GetSomeIpv4LoopbackAddress() {
  sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  addr.sin_family = AF_INET;
  return addr;
}

void CreateSockpair(SOCKET sockpair[2], DWORD flags) {
  SOCKET svr_sock = INVALID_SOCKET;
  SOCKET lst_sock = INVALID_SOCKET;
  SOCKET cli_sock = INVALID_SOCKET;
  auto addr = GetSomeIpv4LoopbackAddress();
  int addr_len = sizeof(addr);

  lst_sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, flags);
  CHECK(lst_sock != INVALID_SOCKET);

  CHECK(bind(lst_sock, (sockaddr*)&addr, sizeof(addr)) != SOCKET_ERROR);
  CHECK(listen(lst_sock, SOMAXCONN) != SOCKET_ERROR);
  CHECK(getsockname(lst_sock, (sockaddr*)&addr, &addr_len) != SOCKET_ERROR);

  cli_sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, flags);
  CHECK(cli_sock != INVALID_SOCKET);

  auto result =
      WSAConnect(cli_sock, (sockaddr*)&addr, addr_len, NULL, NULL, NULL, NULL);
  if (result != 0) {
    VLOG(2)
        << GRPC_WSA_ERROR(WSAGetLastError(), "Failed in WSAConnect").ToString();
    abort();
  }
  svr_sock = accept(lst_sock, (sockaddr*)&addr, &addr_len);
  CHECK(svr_sock != INVALID_SOCKET);
  closesocket(lst_sock);

  auto status = PrepareSocket(cli_sock);

  status = PrepareSocket(svr_sock);

  sockpair[0] = svr_sock;
  sockpair[1] = cli_sock;
}

}
}

#endif
