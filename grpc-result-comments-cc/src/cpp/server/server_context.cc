Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Standard C/C++ headers
#include <assert.h>
#include <atomic>
#include <cstdlib>
#include <functional>
#include <map>
#include <memory>
#include <new>
#include <string>
#include <utility>
#include <vector>

// gRPC core headers
#include <grpc/compression.h>
#include <grpc/grpc.h>
#include <grpc/impl/compression_types.h>
#include <grpc/load_reporting.h>
#include <grpc/status.h>
#include <grpc/support/alloc.h>
#include <grpc/support/time.h>

// gRPC C++ headers
#include <grpcpp/completion_queue.h>
#include <grpcpp/ext/call_metric_recorder.h>
#include <grpcpp/ext/server_metric_recorder.h>
#include <grpcpp/impl/call.h>
#include <grpcpp/impl/call_op_set.h>
#include <grpcpp/impl/call_op_set_interface.h>
#include <grpcpp/impl/completion_queue_tag.h>
#include <grpcpp/impl/interceptor_common.h>
#include <grpcpp/impl/metadata_map.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/callback_common.h>
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/support/server_interceptor.h>
#include <grpcpp/support/string_ref.h>

// Other dependencies
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/surface/call.h"
#include "src/core/util/crash.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/sync.h"
#include "src/cpp/server/backend_metric_recorder.h"

namespace grpc {

// Implementation of CompletionOp for ServerContextBase
// This class handles completion operations for server-side RPC calls
class ServerContextBase::CompletionOp final
    : public internal::CallOpSetInterface {
 public:
  // Constructor initializes the completion operation
  CompletionOp(internal::Call* call,
               grpc::internal::ServerCallbackCall* callback_controller)
      : call_(*call),
        callback_controller_(callback_controller),
        has_tag_(false),
        tag_(nullptr),
        core_cq_tag_(this),
        refs_(2),  // Initial refcount of 2 (one for call, one for completion queue)
        finalized_(false),
        cancelled_(0),
        done_intercepting_(false) {}

  // Disable copy and move operations
  CompletionOp(const CompletionOp&) = delete;
  CompletionOp& operator=(const CompletionOp&) = delete;
  CompletionOp(CompletionOp&&) = delete;
  CompletionOp& operator=(CompletionOp&&) = delete;

  // Destructor cleans up RPC info if present
  ~CompletionOp() override {
    if (call_.server_rpc_info()) {
      call_.server_rpc_info()->Unref();
    }
  }

  // Interface methods
  void FillOps(internal::Call* call) override;

  // Custom memory management operators
  static void operator delete(void* , std::size_t size) {
    (void)size;
    assert(size == sizeof(CompletionOp));
  }

  static void operator delete(void*, void*) { assert(0); }

  bool FinalizeResult(void** tag, bool* status) override;

  // Methods to check cancellation status
  bool CheckCancelled(CompletionQueue* cq) {
    cq->TryPluck(this);
    return CheckCancelledNoPluck();
  }
  bool CheckCancelledAsync() { return CheckCancelledNoPluck(); }

  // Tag management methods
  void set_tag(void* tag) {
    has_tag_ = true;
    tag_ = tag;
  }

  void set_core_cq_tag(void* core_cq_tag) { core_cq_tag_ = core_cq_tag; }

  void* core_cq_tag() override { return core_cq_tag_; }

  // Reference counting management
  void Unref();

  // Interception handling methods
  void SetHijackingState() override {
    grpc_core::Crash("unreachable");
  }

  void ContinueFillOpsAfterInterception() override {}

  void ContinueFinalizeResultAfterInterception() override {
    done_intercepting_ = true;
    if (!has_tag_) {
      // No tag means we can release our reference immediately
      Unref();
      return;
    }

    // Start a batch with no ops just to trigger the completion
    CHECK(grpc_call_start_batch(call_.call(), nullptr, 0, core_cq_tag_,
                                nullptr) == GRPC_CALL_OK);
  }

 private:
  // Internal method to check cancellation status without plucking from queue
  bool CheckCancelledNoPluck() {
    grpc_core::MutexLock lock(&mu_);
    return finalized_ ? (cancelled_ != 0) : false;
  }

  // Member variables
  internal::Call call_;  // The associated call object
  grpc::internal::ServerCallbackCall* const callback_controller_;  // Callback controller if present
  bool has_tag_;         // Whether a completion tag is set
  void* tag_;            // The completion tag
  void* core_cq_tag_;    // Core completion queue tag
  grpc_core::RefCount refs_;  // Reference count
  grpc_core::Mutex mu_;  // Mutex for thread safety
  bool finalized_;       // Whether the operation is finalized
  int cancelled_;        // Cancellation status (0 = not cancelled)
  bool done_intercepting_;  // Whether interception is complete
  internal::InterceptorBatchMethodsImpl interceptor_methods_;  // Interceptor methods
};

// Releases a reference to the completion operation
void ServerContextBase::CompletionOp::Unref() {
  if (refs_.Unref()) {
    // If refcount reaches zero, clean up
    grpc_call* call = call_.call();
    delete this;
    grpc_call_unref(call);
  }
}

// Fills the operations needed for completion handling
void ServerContextBase::CompletionOp::FillOps(internal::Call* call) {
  grpc_op ops;
  ops.op = GRPC_OP_RECV_CLOSE_ON_SERVER;  // Operation to detect client close
  ops.data.recv_close_on_server.cancelled = &cancelled_;
  ops.flags = 0;
  ops.reserved = nullptr;
  
  // Set up interceptor methods
  interceptor_methods_.SetCall(&call_);
  interceptor_methods_.SetReverse();
  interceptor_methods_.SetCallOpSetInterface(this);

  // Start the batch operation
  CHECK(grpc_call_start_batch(call->call(), &ops, 1, core_cq_tag_, nullptr) ==
        GRPC_CALL_OK);
}

// Finalizes the result of the completion operation
bool ServerContextBase::CompletionOp::FinalizeResult(void** tag, bool* status) {
  bool do_unref = false;
  bool has_tag = false;
  bool call_cancel = false;

  {
    // Lock-protected section for thread safety
    grpc_core::MutexLock lock(&mu_);
    if (done_intercepting_) {
      // If done intercepting, just return the tag if present
      has_tag = has_tag_;
      if (has_tag) {
        *tag = tag_;
      }
      do_unref = true;
    } else {
      finalized_ = true;
      // If status is false, mark as cancelled
      if (!*status) {
        cancelled_ = 1;
      }
      call_cancel = (cancelled_ != 0);
    }
  }

  if (do_unref) {
    Unref();
    return has_tag;
  }
  
  // If call was cancelled and we have a callback controller, notify it
  if (call_cancel && callback_controller_ != nullptr) {
    callback_controller_->MaybeCallOnCancel();
  }

  // Run post-receive close interception points
  interceptor_methods_.AddInterceptionHookPoint(
      experimental::InterceptionHookPoints::POST_RECV_CLOSE);
  if (interceptor_methods_.RunInterceptors()) {
    // If interceptors ran, return the tag if present
    bool has_tag = has_tag_;
    if (has_tag) {
      *tag = tag_;
    }
    Unref();
    return has_tag;
  }

  return false;
}

// ServerContextBase implementation

// Constructors
ServerContextBase::ServerContextBase()
    : deadline_(gpr_inf_future(GPR_CLOCK_REALTIME)) {}  // Default to infinite deadline

ServerContextBase::ServerContextBase(gpr_timespec deadline,
                                     grpc_metadata_array* arr)
    : deadline_(deadline) {
  // Swap in client metadata
  std::swap(*client_metadata_.arr(), *arr);
}

// Binds deadline and metadata to the context
void ServerContextBase::BindDeadlineAndMetadata(gpr_timespec deadline,
                                                grpc_metadata_array* arr) {
  deadline_ = deadline;
  std::swap(*client_metadata_.arr(), *arr);
}

// Destructor cleans up resources
ServerContextBase::~ServerContextBase() {
  if (completion_op_) {
    completion_op_->Unref();
  }
  if (rpc_info_) {
    rpc_info_->Unref();
  }
  if (default_reactor_used_.load(std::memory_order_relaxed)) {
    reinterpret_cast<Reactor*>(&default_reactor_)->~Reactor();
  }
  if (call_metric_recorder_ != nullptr) {
    call_metric_recorder_->~CallMetricRecorder();
  }
}

// CallWrapper destructor
ServerContextBase::CallWrapper::~CallWrapper() {
  if (call) {
    grpc_call_unref(call);
  }
}

// Begins a completion operation for the call
void ServerContextBase::BeginCompletionOp(
    internal::Call* call, std::function<void(bool)> callback,
    grpc::internal::ServerCallbackCall* callback_controller) {
  CHECK(!completion_op_);
  if (rpc_info_) {
    rpc_info_->Ref();
  }
  grpc_call_ref(call->call());
  // Allocate and construct new CompletionOp in the call arena
  completion_op_ =
      new (grpc_call_arena_alloc(call->call(), sizeof(CompletionOp)))
          CompletionOp(call, callback_controller);
  
  // Set up completion tag based on whether we have a callback controller
  if (callback_controller != nullptr) {
    completion_tag_.Set(call->call(), std::move(callback), completion_op_,
                        true);
    completion_op_->set_core_cq_tag(&completion_tag_);
    completion_op_->set_tag(completion_op_);
  } else if (has_notify_when_done_tag_) {
    completion_op_->set_tag(async_notify_when_done_tag_);
  }
  call->PerformOps(completion_op_);
}

// Gets the completion queue tag for this context
internal::CompletionQueueTag* ServerContextBase::GetCompletionOpTag() {
  return static_cast<internal::CompletionQueueTag*>(completion_op_);
}

// Adds metadata to be sent with initial response
void ServerContextBase::AddInitialMetadata(const std::string& key,
                                           const std::string& value) {
  initial_metadata_.insert(std::pair(key, value));
}

// Adds metadata to be sent with trailing response
void ServerContextBase::AddTrailingMetadata(const std::string& key,
                                            const std::string& value) {
  trailing_metadata_.insert(std::pair(key, value));
}

// Attempts to cancel the RPC
void ServerContextBase::TryCancel() const {
  internal::CancelInterceptorBatchMethods cancel_methods;
  if (rpc_info_) {
    // Run cancellation interceptors if present
    for (size_t i = 0; i < rpc_info_->interceptors_.size(); i++) {
      rpc_info_->RunInterceptor(&cancel_methods, i);
    }
  }
  // Actually cancel the call
  grpc_call_error err =
      grpc_call_cancel_with_status(call_.call, GRPC_STATUS_CANCELLED,
                                   "Cancelled on the server side", nullptr);
  if (err != GRPC_CALL_OK) {
    LOG(ERROR) << "TryCancel failed with: " << err;
  }
}

// Checks if the RPC has been cancelled
bool ServerContextBase::IsCancelled() const {
  if (completion_tag_) {
    // For callback API
    return marked_cancelled_.load(std::memory_order_acquire) ||
           completion_op_->CheckCancelledAsync();
  } else if (has_notify_when_done_tag_) {
    // For async API
    return completion_op_ && completion_op_->CheckCancelledAsync();
  } else {
    // For sync API
    return marked_cancelled_.load(std::memory_order_acquire) ||
           (completion_op_ && completion_op_->CheckCancelled(cq_));
  }
}

// Sets the compression algorithm for the response
void ServerContextBase::set_compression_algorithm(
    grpc_compression_algorithm algorithm) {
  compression_algorithm_ = algorithm;
  const char* algorithm_name = nullptr;
  if (!grpc_compression_algorithm_name(algorithm, &algorithm_name)) {
    grpc_core::Crash(absl::StrFormat(
        "Name for compression algorithm '%d' unknown.", algorithm));
  }
  CHECK_NE(algorithm_name, nullptr);
  AddInitialMetadata(GRPC_COMPRESSION_REQUEST_ALGORITHM_MD_KEY, algorithm_name);
}

// Gets the peer address
std::string ServerContextBase::peer() const {
  std::string peer;
  if (call_.call) {
    char* c_peer = grpc_call_get_peer(call_.call);
    peer = c_peer;
    gpr_free(c_peer);
  }
  return peer;
}

// Gets the census context if available
const struct census_context* ServerContextBase::census_context() const {
  return call_.call == nullptr ? nullptr
                               : grpc_census_call_get_context(call_.call);
}

// Sets load reporting costs
void ServerContextBase::SetLoadReportingCosts(
    const std::vector<std::string>& cost_data) {
  if (call_.call == nullptr) return;
  for (const auto& cost_datum : cost_data) {
    AddTrailingMetadata(GRPC_LB_COST_MD_KEY, cost_datum);
  }
}

// Creates a call metric recorder
void ServerContextBase::CreateCallMetricRecorder(
    experimental::ServerMetricRecorder* server_metric_recorder) {
  if (call_.call == nullptr) return;
  CHECK_EQ(call_metric_recorder_, nullptr);
  grpc_core::Arena* arena = grpc_call_get_arena(call_.call);
  auto* backend_metric_state =
      arena->New<BackendMetricState>(server_metric_recorder);
  call_metric_recorder_ = backend_metric_state;
  arena->SetContext<grpc_core::BackendMetricProvider>(backend_metric_state);
}

// Experimental method to get authority
grpc::string_ref ServerContextBase::ExperimentalGetAuthority() const {
  absl::string_view authority = grpc_call_server_authority(call_.call);
  return grpc::string_ref(authority.data(), authority.size());
}

}  // namespace grpc
```