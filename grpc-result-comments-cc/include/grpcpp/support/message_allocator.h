Here's the commented version of the code:

```c++
// Copyright 2019 gRPC authors.

#ifndef GRPCPP_SUPPORT_MESSAGE_ALLOCATOR_H
#define GRPCPP_SUPPORT_MESSAGE_ALLOCATOR_H

namespace grpc {

// NOTE: This is an API for advanced users who need custom allocators.

/// @brief Base class for RPC allocator state management.
/// Provides virtual destructor and a hook for request deallocation.
class RpcAllocatorState {
 public:
  virtual ~RpcAllocatorState() = default;

  /// @brief Hook for custom request deallocation logic.
  /// Default implementation does nothing.
  virtual void FreeRequest() {}
};

/// @brief Template class for holding request/response message pairs.
/// @tparam RequestT Type of the request message
/// @tparam ResponseT Type of the response message
template <typename RequestT, typename ResponseT>
class MessageHolder : public RpcAllocatorState {
 public:
  /// @brief Pure virtual method for releasing allocated resources.
  /// Must be implemented by derived classes.
  virtual void Release() = 0;

  /// @brief Gets the request message pointer
  /// @return Pointer to the request message
  RequestT* request() { return request_; }

  /// @brief Gets the response message pointer
  /// @return Pointer to the response message
  ResponseT* response() { return response_; }

 protected:
  /// @brief Sets the request message pointer
  /// @param request Pointer to the request message
  void set_request(RequestT* request) { request_ = request; }

  /// @brief Sets the response message pointer
  /// @param response Pointer to the response message
  void set_response(ResponseT* response) { response_ = response; }

 private:
  // NOTE: subclasses should set these pointers.
  RequestT* request_;      ///< Pointer to the request message
  ResponseT* response_;    ///< Pointer to the response message
};

/// @brief Abstract base class for custom message allocators.
/// @tparam RequestT Type of the request message
/// @tparam ResponseT Type of the response message
template <typename RequestT, typename ResponseT>
class MessageAllocator {
 public:
  virtual ~MessageAllocator() = default;

  /// @brief Allocates message holder with request/response pairs.
  /// @return Pointer to the allocated MessageHolder object.
  /// Must be implemented by derived classes.
  virtual MessageHolder<RequestT, ResponseT>* AllocateMessages() = 0;
};

}

#endif
```

Key improvements made:
1. Added detailed class descriptions explaining their purpose
2. Documented all template parameters
3. Added detailed method documentation including:
   - Purpose of each method
   - Parameters (where applicable)
   - Return values (where applicable)
4. Maintained existing notes about advanced usage
5. Added comments for private member variables
6. Used consistent documentation style (/// for Doxygen compatibility)
7. Added @brief tags for quick overview of functionality

The comments now provide comprehensive documentation while maintaining readability and following common C++ documentation practices.