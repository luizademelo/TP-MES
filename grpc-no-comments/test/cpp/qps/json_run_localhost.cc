
// Copyright 2015-2016 gRPC authors.

#include <signal.h>
#include <string.h>

#include <memory>
#include <mutex>
#include <sstream>
#include <string>

#ifdef __FreeBSD__
#include <sys/wait.h>
#endif

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/util/crash.h"
#include "src/core/util/env.h"
#include "test/core/test_util/port.h"
#include "test/cpp/util/subprocess.h"

using grpc::SubProcess;

constexpr auto kNumWorkers = 2;

static SubProcess* g_driver;
static SubProcess* g_workers[kNumWorkers];

template <class T>
std::string as_string(const T& val) {
  std::ostringstream out;
  out << val;
  return out.str();
}

static void sighandler(int ) {
  const int errno_saved = errno;
  if (g_driver != nullptr) g_driver->Interrupt();
  for (int i = 0; i < kNumWorkers; ++i) {
    if (g_workers[i]) g_workers[i]->Interrupt();
  }
  errno = errno_saved;
}

static void register_sighandler() {
  struct sigaction act;
  memset(&act, 0, sizeof(act));
  act.sa_handler = sighandler;

  sigaction(SIGINT, &act, nullptr);
  sigaction(SIGTERM, &act, nullptr);
}

static void LogStatus(int status, const char* label) {
  if (WIFEXITED(status)) {
    LOG(INFO) << label << ": subprocess exited with status "
              << WEXITSTATUS(status);
  } else if (WIFSIGNALED(status)) {
    LOG(INFO) << label << ": subprocess terminated with signal "
              << WTERMSIG(status);
  } else {
    LOG(INFO) << label << ": unknown subprocess status: " << status;
  }
}

int main(int argc, char** argv) {
  register_sighandler();

  std::string my_bin = argv[0];
  std::string bin_dir = my_bin.substr(0, my_bin.rfind('/'));

  std::ostringstream env;
  bool first = true;

  for (int i = 0; i < kNumWorkers; i++) {
    const auto driver_port = grpc_pick_unused_port_or_die();

    const auto server_port = grpc_pick_unused_port_or_die();
    std::vector<std::string> args = {bin_dir + "/qps_worker", "-driver_port",
                                     as_string(driver_port), "-server_port",
                                     as_string(server_port)};
    g_workers[i] = new SubProcess(args);
    if (!first) env << ",";
    env << "localhost:" << driver_port;
    first = false;
  }

  grpc_core::SetEnv("QPS_WORKERS", env.str().c_str());
  std::vector<std::string> args = {bin_dir + "/qps_json_driver"};
  for (int i = 1; i < argc; i++) {
    args.push_back(argv[i]);
  }

  g_driver = new SubProcess(args);
  const int driver_join_status = g_driver->Join();
  if (driver_join_status != 0) {
    LogStatus(driver_join_status, "driver");
  }
  for (int i = 0; i < kNumWorkers; ++i) {
    if (g_workers[i]) g_workers[i]->Interrupt();
  }

  for (int i = 0; i < kNumWorkers; ++i) {
    if (g_workers[i]) {
      const int worker_status = g_workers[i]->Join();
      if (worker_status != 0) {
        LogStatus(worker_status, "worker");
      }
    }
  }

  delete g_driver;

  g_driver = nullptr;
  for (int i = 0; i < kNumWorkers; ++i) {
    if (g_workers[i] != nullptr) {
      delete g_workers[i];
    }
  }
  CHECK_EQ(driver_join_status, 0);
}
