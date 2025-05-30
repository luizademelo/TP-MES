
// Copyright 2016 gRPC authors.

#include <grpc/grpc.h>

#include <memory>

#include "absl/base/thread_annotations.h"
#include "absl/strings/string_view.h"
#include "gtest/gtest.h"
#include "src/core/config/core_configuration.h"
#include "src/core/handshaker/handshaker.h"
#include "src/core/handshaker/handshaker_factory.h"
#include "src/core/handshaker/handshaker_registry.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/tcp_server.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "test/core/handshake/server_ssl_common.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {

class ReadAheadHandshaker : public Handshaker {
 public:
  absl::string_view name() const override { return "read_ahead"; }

  void DoHandshake(
      HandshakerArgs* args,
      absl::AnyInvocable<void(absl::Status)> on_handshake_done) override {
    MutexLock lock(&mu_);
    args_ = args;
    on_handshake_done_ = std::move(on_handshake_done);
    Ref().release();
    GRPC_CLOSURE_INIT(&on_read_done_, OnReadDone, this, nullptr);
    grpc_endpoint_read(args->endpoint.get(), args->read_buffer.c_slice_buffer(),
                       &on_read_done_, false,
                       1);
  }

  void Shutdown(absl::Status ) override {
    MutexLock lock(&mu_);
    if (on_handshake_done_ != nullptr) args_->endpoint.reset();
  }

 private:
  static void OnReadDone(void* arg, grpc_error_handle error) {
    auto* self = static_cast<ReadAheadHandshaker*>(arg);

    self->args_->event_engine->Run(
        [self = RefCountedPtr<ReadAheadHandshaker>(self),
         error = std::move(error)]() mutable {
          absl::AnyInvocable<void(absl::Status)> on_handshake_done;
          {
            MutexLock lock(&self->mu_);
            on_handshake_done = std::move(self->on_handshake_done_);
          }
          on_handshake_done(std::move(error));
        });
  }

  grpc_closure on_read_done_;

  Mutex mu_;

  HandshakerArgs* args_ = nullptr;
  absl::AnyInvocable<void(absl::Status)> on_handshake_done_
      ABSL_GUARDED_BY(&mu_);
};

class ReadAheadHandshakerFactory : public HandshakerFactory {
 public:
  void AddHandshakers(const ChannelArgs& ,
                      grpc_pollset_set* ,
                      HandshakeManager* handshake_mgr) override {
    handshake_mgr->Add(MakeRefCounted<ReadAheadHandshaker>());
  }
  HandshakerPriority Priority() override {
    return HandshakerPriority::kReadAheadSecurityHandshakers;
  }
  ~ReadAheadHandshakerFactory() override = default;
};

}

TEST(HandshakeServerWithReadaheadHandshakerTest, MainTest) {
  grpc_core::CoreConfiguration::WithSubstituteBuilder builder(
      [](grpc_core::CoreConfiguration::Builder* builder) {
        BuildCoreConfiguration(builder);
        builder->handshaker_registry()->RegisterHandshakerFactory(
            grpc_core::HANDSHAKER_SERVER,
            std::make_unique<grpc_core::ReadAheadHandshakerFactory>());
      });

  grpc_init();
  const char* full_alpn_list[] = {"h2"};
  ASSERT_TRUE(server_ssl_test(full_alpn_list, 1, "h2"));
  CleanupSslLibrary();
  grpc_shutdown();
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
