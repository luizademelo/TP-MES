Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions
#ifndef GRPCPP_SUPPORT_INTERCEPTOR_H
#define GRPCPP_SUPPORT_INTERCEPTOR_H

// Include necessary headers
#include <grpc/impl/grpc_types.h>
#include <grpcpp/impl/metadata_map.h>
#include <grpcpp/support/byte_buffer.h>
#include <grpcpp/support/config.h>
#include <grpcpp/support/string_ref.h>

#include <map>
#include <memory>
#include <string>

namespace grpc {

// Forward declarations
class ChannelInterface;
class Status;

namespace experimental {

// Enumeration defining all possible points where interception can occur
// during gRPC call processing
enum class InterceptionHookPoints {
  // Hook points for sending operations
  PRE_SEND_INITIAL_METADATA,  // Before sending initial metadata
  PRE_SEND_MESSAGE,           // Before sending a message
  POST_SEND_MESSAGE,          // After sending a message
  PRE_SEND_STATUS,            // Before sending status
  PRE_SEND_CLOSE,             // Before sending close

  // Hook points for receiving operations
  PRE_RECV_INITIAL_METADATA,  // Before receiving initial metadata
  PRE_RECV_MESSAGE,           // Before receiving a message
  PRE_RECV_STATUS,            // Before receiving status

  POST_RECV_INITIAL_METADATA, // After receiving initial metadata
  POST_RECV_MESSAGE,          // After receiving a message
  POST_RECV_STATUS,           // After receiving status
  POST_RECV_CLOSE,            // After receiving close

  PRE_SEND_CANCEL,            // Before sending cancellation
  NUM_INTERCEPTION_HOOKS      // Total count of interception points
};

// Abstract base class defining methods that interceptors can use to
// interact with and modify gRPC call processing
class InterceptorBatchMethods {
 public:
  virtual ~InterceptorBatchMethods() {}

  // Check if this batch contains a specific interception hook point
  virtual bool QueryInterceptionHookPoint(InterceptionHookPoints type) = 0;

  // Continue processing to the next interceptor or the actual RPC call
  virtual void Proceed() = 0;

  // Take control of the call processing (hijack the call)
  virtual void Hijack() = 0;

  // Message handling methods
  virtual ByteBuffer* GetSerializedSendMessage() = 0;  // Get serialized outgoing message
  virtual const void* GetSendMessage() = 0;           // Get outgoing message
  virtual void ModifySendMessage(const void* message) = 0;  // Modify outgoing message
  virtual bool GetSendMessageStatus() = 0;            // Get send message status

  // Metadata handling methods
  virtual std::multimap<std::string, std::string>* GetSendInitialMetadata() = 0;
  virtual std::multimap<std::string, std::string>* GetSendTrailingMetadata() = 0;

  // Status handling methods
  virtual Status GetSendStatus() = 0;                 // Get current send status
  virtual void ModifySendStatus(const Status& status) = 0;  // Modify send status

  // Receive-side methods
  virtual void* GetRecvMessage() = 0;                 // Get received message
  virtual std::multimap<grpc::string_ref, grpc::string_ref>* GetRecvInitialMetadata() = 0;
  virtual Status* GetRecvStatus() = 0;                // Get received status
  virtual std::multimap<grpc::string_ref, grpc::string_ref>* GetRecvTrailingMetadata() = 0;

  // Channel access method
  virtual std::unique_ptr<ChannelInterface> GetInterceptedChannel() = 0;

  // Error handling for hijacked operations
  virtual void FailHijackedRecvMessage() = 0;         // Fail hijacked receive
  virtual void FailHijackedSendMessage() = 0;         // Fail hijacked send
};

// Abstract base class for all gRPC interceptors
class Interceptor {
 public:
  virtual ~Interceptor() {}

  // Main interception point - called when interception is needed
  virtual void Intercept(InterceptorBatchMethods* methods) = 0;
};

}  // namespace experimental
}  // namespace grpc

#endif  // GRPCPP_SUPPORT_INTERCEPTOR_H
```