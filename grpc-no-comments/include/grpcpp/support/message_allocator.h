
// Copyright 2019 gRPC authors.

#ifndef GRPCPP_SUPPORT_MESSAGE_ALLOCATOR_H
#define GRPCPP_SUPPORT_MESSAGE_ALLOCATOR_H

namespace grpc {

// NOTE: This is an API for advanced users who need custom allocators.

class RpcAllocatorState {
 public:
  virtual ~RpcAllocatorState() = default;

  virtual void FreeRequest() {}
};

template <typename RequestT, typename ResponseT>
class MessageHolder : public RpcAllocatorState {
 public:

  virtual void Release() = 0;
  RequestT* request() { return request_; }
  ResponseT* response() { return response_; }

 protected:
  void set_request(RequestT* request) { request_ = request; }
  void set_response(ResponseT* response) { response_ = response; }

 private:
  // NOTE: subclasses should set these pointers.
  RequestT* request_;
  ResponseT* response_;
};

template <typename RequestT, typename ResponseT>
class MessageAllocator {
 public:
  virtual ~MessageAllocator() = default;
  virtual MessageHolder<RequestT, ResponseT>* AllocateMessages() = 0;
};

}

#endif
