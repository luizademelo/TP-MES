
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_CALL_PLUGIN_PLUGIN_CREDENTIALS_H
#define GRPC_SRC_CORE_CREDENTIALS_CALL_PLUGIN_PLUGIN_CREDENTIALS_H

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/grpc_security_constants.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <atomic>
#include <string>
#include <utility>

#include "absl/container/inlined_vector.h"
#include "absl/status/statusor.h"
#include "src/core/credentials/call/call_credentials.h"
#include "src/core/credentials/call/call_creds_util.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/unique_type_name.h"
#include "src/core/util/useful.h"

struct grpc_plugin_credentials final : public grpc_call_credentials {
 public:
  explicit grpc_plugin_credentials(grpc_metadata_credentials_plugin plugin,
                                   grpc_security_level min_security_level);
  ~grpc_plugin_credentials() override;

  void Orphaned() override {}

  grpc_core::ArenaPromise<absl::StatusOr<grpc_core::ClientMetadataHandle>>
  GetRequestMetadata(grpc_core::ClientMetadataHandle initial_metadata,
                     const GetRequestMetadataArgs* args) override;

  std::string debug_string() override;

  grpc_core::UniqueTypeName type() const override;

 private:
  class PendingRequest : public grpc_core::RefCounted<PendingRequest> {
   public:
    PendingRequest(grpc_core::RefCountedPtr<grpc_plugin_credentials> creds,
                   grpc_core::ClientMetadataHandle initial_metadata,
                   const grpc_call_credentials::GetRequestMetadataArgs* args)
        : call_creds_(std::move(creds)),
          context_(
              grpc_core::MakePluginAuthMetadataContext(initial_metadata, args)),
          md_(std::move(initial_metadata)) {}

    ~PendingRequest() override {
      grpc_auth_metadata_context_reset(&context_);
      for (size_t i = 0; i < metadata_.size(); i++) {
        grpc_core::CSliceUnref(metadata_[i].key);
        grpc_core::CSliceUnref(metadata_[i].value);
      }
    }

    absl::StatusOr<grpc_core::ClientMetadataHandle> ProcessPluginResult(
        const grpc_metadata* md, size_t num_md, grpc_status_code status,
        const char* error_details);

    grpc_core::Poll<absl::StatusOr<grpc_core::ClientMetadataHandle>>
    PollAsyncResult();

    static void RequestMetadataReady(void* request, const grpc_metadata* md,
                                     size_t num_md, grpc_status_code status,
                                     const char* error_details);

    grpc_auth_metadata_context context() const { return context_; }
    grpc_plugin_credentials* creds() const { return call_creds_.get(); }

   private:
    std::atomic<bool> ready_{false};
    grpc_core::Waker waker_{
        grpc_core::GetContext<grpc_core::Activity>()->MakeNonOwningWaker()};
    grpc_core::RefCountedPtr<grpc_plugin_credentials> call_creds_;
    grpc_auth_metadata_context context_;
    grpc_core::ClientMetadataHandle md_;

    absl::InlinedVector<grpc_metadata, 2> metadata_;
    std::string error_details_;
    grpc_status_code status_;
  };

  int cmp_impl(const grpc_call_credentials* other) const override {

    return grpc_core::QsortCompare(
        static_cast<const grpc_call_credentials*>(this), other);
  }

  grpc_metadata_credentials_plugin plugin_;
};

#endif
