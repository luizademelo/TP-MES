
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SUPPORT_INTERCEPTOR_H
#define GRPCPP_SUPPORT_INTERCEPTOR_H

#include <grpc/impl/grpc_types.h>
#include <grpcpp/impl/metadata_map.h>
#include <grpcpp/support/byte_buffer.h>
#include <grpcpp/support/config.h>
#include <grpcpp/support/string_ref.h>

#include <map>
#include <memory>
#include <string>

namespace grpc {

class ChannelInterface;
class Status;

namespace experimental {

enum class InterceptionHookPoints {

  PRE_SEND_INITIAL_METADATA,
  PRE_SEND_MESSAGE,
  POST_SEND_MESSAGE,
  PRE_SEND_STATUS,
  PRE_SEND_CLOSE,

  PRE_RECV_INITIAL_METADATA,
  PRE_RECV_MESSAGE,
  PRE_RECV_STATUS,

  POST_RECV_INITIAL_METADATA,
  POST_RECV_MESSAGE,
  POST_RECV_STATUS,
  POST_RECV_CLOSE,

  PRE_SEND_CANCEL,
  NUM_INTERCEPTION_HOOKS
};

class InterceptorBatchMethods {
 public:
  virtual ~InterceptorBatchMethods() {}

  virtual bool QueryInterceptionHookPoint(InterceptionHookPoints type) = 0;

  virtual void Proceed() = 0;

  virtual void Hijack() = 0;

  virtual ByteBuffer* GetSerializedSendMessage() = 0;

  virtual const void* GetSendMessage() = 0;

  virtual void ModifySendMessage(const void* message) = 0;

  virtual bool GetSendMessageStatus() = 0;

  virtual std::multimap<std::string, std::string>* GetSendInitialMetadata() = 0;

  virtual Status GetSendStatus() = 0;

  virtual void ModifySendStatus(const Status& status) = 0;

  virtual std::multimap<std::string, std::string>*
  GetSendTrailingMetadata() = 0;

  virtual void* GetRecvMessage() = 0;

  virtual std::multimap<grpc::string_ref, grpc::string_ref>*
  GetRecvInitialMetadata() = 0;

  virtual Status* GetRecvStatus() = 0;

  virtual std::multimap<grpc::string_ref, grpc::string_ref>*
  GetRecvTrailingMetadata() = 0;

  virtual std::unique_ptr<ChannelInterface> GetInterceptedChannel() = 0;

  virtual void FailHijackedRecvMessage() = 0;

  virtual void FailHijackedSendMessage() = 0;
};

class Interceptor {
 public:
  virtual ~Interceptor() {}

  virtual void Intercept(InterceptorBatchMethods* methods) = 0;
};

}
}

#endif
