
// Copyright 2018 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_FAKE_UDP_AND_TCP_SERVER_H
#define GRPC_TEST_CORE_TEST_UTIL_FAKE_UDP_AND_TCP_SERVER_H

#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>

#include <functional>
#include <memory>
#include <string>
#include <thread>

namespace grpc_core {
namespace testing {

class FakeUdpAndTcpServer {
 public:
  enum class ProcessReadResult {
    kContinueReading = 0,
    kCloseSocket,
  };

  enum class AcceptMode {
    kWaitForClientToSendFirstBytes,

    kEagerlySendSettings,

  };

  explicit FakeUdpAndTcpServer(
      AcceptMode accept_mode,
      std::function<ProcessReadResult(int, int, int)> process_read_cb);

  ~FakeUdpAndTcpServer();

  const char* address() { return address_.c_str(); }

  int port() { return port_; };

  static ProcessReadResult CloseSocketUponReceivingBytesFromPeer(
      int bytes_received_size, int read_error, int s);

  static ProcessReadResult CloseSocketUponCloseFromPeer(int bytes_received_size,
                                                        int read_error, int s);

  static ProcessReadResult SendThreeAllZeroBytes(int bytes_received_size,
                                                 int read_error, int s);

  void ReadFromUdpSocket();

  void RunServerLoop();

 private:
  class FakeUdpAndTcpServerPeer {
   public:
    explicit FakeUdpAndTcpServerPeer(int fd);

    ~FakeUdpAndTcpServerPeer();

    void MaybeContinueSendingSettings();

    int fd() { return fd_; }

   private:
    int fd_;
    int total_bytes_sent_ = 0;
  };

  int accept_socket_;
  int udp_socket_;
  int port_;
  gpr_event stop_ev_;
  std::string address_;
  std::unique_ptr<std::thread> run_server_loop_thd_;
  const AcceptMode accept_mode_;
  std::function<ProcessReadResult(int, int, int)> process_read_cb_;
};

}
}

#endif
