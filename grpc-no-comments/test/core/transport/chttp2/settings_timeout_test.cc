
// Copyright 2017 gRPC authors.

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/slice.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/alloc.h>
#include <grpc/support/atm.h>
#include <grpc/support/sync.h>
#include <grpc/support/time.h>
#include <inttypes.h>

#include <functional>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "gtest/gtest.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_args_preconditioning.h"
#include "src/core/lib/event_engine/channel_args_endpoint_config.h"
#include "src/core/lib/event_engine/resolved_address_internal.h"
#include "src/core/lib/event_engine/shim.h"
#include "src/core/lib/event_engine/utils.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/pollset.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/lib/iomgr/resolve_address.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/iomgr/tcp_client.h"
#include "src/core/lib/resource_quota/api.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/time.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace test {
namespace {

class ServerThread {
 public:
  explicit ServerThread(const char* address) : address_(address) {}

  void Start() {

    grpc_arg a[2];
    a[0].type = GRPC_ARG_INTEGER;
    a[0].key = const_cast<char*>(GRPC_ARG_SERVER_HANDSHAKE_TIMEOUT_MS);
    a[0].value.integer = 1000;
    a[1].key = const_cast<char*>(GRPC_ARG_RESOURCE_QUOTA);
    a[1].type = GRPC_ARG_POINTER;
    a[1].value.pointer.p = grpc_resource_quota_create("test");
    a[1].value.pointer.vtable = grpc_resource_quota_arg_vtable();
    grpc_channel_args args = {2, a};
    server_ = grpc_server_create(&args, nullptr);
    grpc_server_credentials* server_creds =
        grpc_insecure_server_credentials_create();
    ASSERT_TRUE(grpc_server_add_http2_port(server_, address_, server_creds));
    grpc_server_credentials_release(server_creds);
    cq_ = grpc_completion_queue_create_for_next(nullptr);
    grpc_server_register_completion_queue(server_, cq_, nullptr);
    grpc_server_start(server_);
    thread_ =
        std::make_unique<std::thread>(std::bind(&ServerThread::Serve, this));
    grpc_resource_quota_unref(
        static_cast<grpc_resource_quota*>(a[1].value.pointer.p));
  }

  void Shutdown() {
    grpc_completion_queue* shutdown_cq =
        grpc_completion_queue_create_for_pluck(nullptr);
    grpc_server_shutdown_and_notify(server_, shutdown_cq, nullptr);
    CHECK(grpc_completion_queue_pluck(shutdown_cq, nullptr,
                                      grpc_timeout_seconds_to_deadline(1),
                                      nullptr)
              .type == GRPC_OP_COMPLETE);
    grpc_completion_queue_destroy(shutdown_cq);
    grpc_server_destroy(server_);
    grpc_completion_queue_destroy(cq_);
    thread_->join();
  }

 private:
  void Serve() {

    grpc_event ev = grpc_completion_queue_next(
        cq_, gpr_inf_future(GPR_CLOCK_MONOTONIC), nullptr);
    ASSERT_EQ(GRPC_QUEUE_SHUTDOWN, ev.type);
  }

  const char* address_;
  grpc_server* server_ = nullptr;
  grpc_completion_queue* cq_ = nullptr;
  std::unique_ptr<std::thread> thread_;
};

class Client {
 public:
  explicit Client(const char* server_address)
      : server_address_(server_address) {}

  void Connect() {
    ExecCtx exec_ctx;
    grpc_resolved_address addr;
    if (IsEventEngineDnsNonClientChannelEnabled() &&
        !grpc_event_engine::experimental::
            EventEngineExperimentDisabledForPython()) {
      auto resolver =
          grpc_event_engine::experimental::GetDefaultEventEngine()
              ->GetDNSResolver(grpc_event_engine::experimental::EventEngine::
                                   DNSResolver::ResolverOptions());
      ASSERT_TRUE(resolver.ok())
          << "Could not create resolver: " << resolver.status();
      auto addresses = grpc_event_engine::experimental::LookupHostnameBlocking(
          resolver->get(), server_address_, "80");
      ASSERT_TRUE(addresses.ok())
          << "Hostname lookup failed: " << addresses.status();
      ASSERT_GE(addresses->size(), 1)
          << "Found zero hostnames for " << server_address_ << ":80";
      addr = grpc_event_engine::experimental::CreateGRPCResolvedAddress(
          addresses->at(0));
    } else {
      absl::StatusOr<std::vector<grpc_resolved_address>> addresses_or =
          GetDNSResolver()->LookupHostnameBlocking(server_address_, "80");
      ASSERT_EQ(absl::OkStatus(), addresses_or.status())
          << addresses_or.status().ToString();
      ASSERT_GE(addresses_or->size(), 1UL);
      addr = addresses_or->at(0);
    }
    pollset_ = static_cast<grpc_pollset*>(gpr_zalloc(grpc_pollset_size()));
    grpc_pollset_init(pollset_, &mu_);
    grpc_pollset_set* pollset_set = grpc_pollset_set_create();
    grpc_pollset_set_add_pollset(pollset_set, pollset_);
    EventState state;
    auto args = CoreConfiguration::Get()
                    .channel_args_preconditioning()
                    .PreconditionChannelArgs(nullptr);
    grpc_tcp_client_connect(
        state.closure(), &endpoint_, pollset_set,
        grpc_event_engine::experimental::ChannelArgsEndpointConfig(args), &addr,
        Timestamp::Now() + Duration::Seconds(1));
    ASSERT_TRUE(PollUntilDone(&state, Timestamp::InfFuture()));
    ASSERT_EQ(absl::OkStatus(), state.error());
    grpc_pollset_set_destroy(pollset_set);
    grpc_endpoint_add_to_pollset(endpoint_, pollset_);
  }

  bool ReadUntilError() {
    ExecCtx exec_ctx;
    grpc_slice_buffer read_buffer;
    grpc_slice_buffer_init(&read_buffer);
    bool retval = true;

    Timestamp deadline = Timestamp::Now() + Duration::Seconds(3);
    while (true) {
      EventState state;
      grpc_endpoint_read(endpoint_, &read_buffer, state.closure(),
                         true, 1);
      if (!PollUntilDone(&state, deadline)) {
        retval = false;
        break;
      }
      if (state.error() != absl::OkStatus()) break;
      LOG(INFO) << "client read " << read_buffer.length << " bytes";
      grpc_slice_buffer_reset_and_unref(&read_buffer);
    }
    grpc_endpoint_destroy(endpoint_);
    endpoint_ = nullptr;
    grpc_slice_buffer_destroy(&read_buffer);
    return retval;
  }

  void Shutdown() {
    ExecCtx exec_ctx;
    if (endpoint_ != nullptr) grpc_endpoint_destroy(endpoint_);
    grpc_pollset_shutdown(pollset_,
                          GRPC_CLOSURE_CREATE(&Client::PollsetDestroy, pollset_,
                                              grpc_schedule_on_exec_ctx));
  }

 private:

  class EventState {
   public:
    EventState() {
      GRPC_CLOSURE_INIT(&closure_, &EventState::OnEventDone, this,
                        grpc_schedule_on_exec_ctx);
    }

    ~EventState() {}

    grpc_closure* closure() { return &closure_; }

    bool done() const { return gpr_atm_acq_load(&done_atm_) != 0; }

    grpc_error_handle error() const { return error_; }

   private:
    static void OnEventDone(void* arg, grpc_error_handle error) {
      LOG(INFO) << "OnEventDone(): " << StatusToString(error);
      EventState* state = static_cast<EventState*>(arg);
      state->error_ = error;
      gpr_atm_rel_store(&state->done_atm_, 1);
    }

    grpc_closure closure_;
    gpr_atm done_atm_ = 0;
    grpc_error_handle error_;
  };

  bool PollUntilDone(EventState* state, Timestamp deadline) {
    while (true) {
      grpc_pollset_worker* worker = nullptr;
      gpr_mu_lock(mu_);
      GRPC_LOG_IF_ERROR(
          "grpc_pollset_work",
          grpc_pollset_work(pollset_, &worker,
                            Timestamp::Now() + Duration::Milliseconds(100)));

      ExecCtx::Get()->Flush();
      gpr_mu_unlock(mu_);
      if (state != nullptr && state->done()) return true;
      if (Timestamp::Now() >= deadline) return false;
    }
  }

  static void PollsetDestroy(void* arg, grpc_error_handle ) {
    grpc_pollset* pollset = static_cast<grpc_pollset*>(arg);
    grpc_pollset_destroy(pollset);
    gpr_free(pollset);
  }

  const char* server_address_;
  grpc_endpoint* endpoint_;
  gpr_mu* mu_;
  grpc_pollset* pollset_;
};

TEST(SettingsTimeout, Basic) {

  const int server_port = grpc_pick_unused_port_or_die();
  std::string server_address_string = absl::StrCat("localhost:", server_port);

  LOG(INFO) << "starting server on " << server_address_string;
  ServerThread server_thread(server_address_string.c_str());
  server_thread.Start();

  LOG(INFO) << "starting client connect";
  Client client(server_address_string.c_str());
  client.Connect();

  LOG(INFO) << "starting client read";
  EXPECT_TRUE(client.ReadUntilError());

  LOG(INFO) << "shutting down client";
  client.Shutdown();

  LOG(INFO) << "shutting down server";
  server_thread.Shutdown();

}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_init();
  int result = RUN_ALL_TESTS();
  grpc_shutdown();
  return result;
}
