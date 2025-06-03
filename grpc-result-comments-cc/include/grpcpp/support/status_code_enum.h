Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_SUPPORT_STATUS_CODE_ENUM_H
#define GRPCPP_SUPPORT_STATUS_CODE_ENUM_H

namespace grpc {

// Enumeration defining various gRPC status codes that can be returned by RPC calls.
// These codes are used to indicate success or various types of failures.
enum StatusCode {
  // The operation completed successfully
  OK = 0,

  // The operation was cancelled (typically by the caller)
  CANCELLED = 1,

  // Unknown error. An example of where this error may be returned is if a Status
  // value received from another address space belongs to an error-space that is
  // not known in this address space.
  UNKNOWN = 2,

  // Client specified an invalid argument. Note that this differs from FAILED_PRECONDITION.
  INVALID_ARGUMENT = 3,

  // Deadline expired before operation could complete.
  DEADLINE_EXCEEDED = 4,

  // Some requested entity (e.g., file or directory) was not found.
  NOT_FOUND = 5,

  // Some entity that we attempted to create (e.g., file or directory) already exists.
  ALREADY_EXISTS = 6,

  // The caller does not have permission to execute the specified operation.
  PERMISSION_DENIED = 7,

  // The request does not have valid authentication credentials for the operation.
  UNAUTHENTICATED = 16,

  // Some resource has been exhausted, perhaps a per-user quota, or perhaps the
  // entire file system is out of space.
  RESOURCE_EXHAUSTED = 8,

  // Operation was rejected because the system is not in a state required for the
  // operation's execution.
  FAILED_PRECONDITION = 9,

  // The operation was aborted, typically due to a concurrency issue like sequencer
  // check failures, transaction aborts, etc.
  ABORTED = 10,

  // Operation was attempted past the valid range. E.g., seeking or reading past end of file.
  OUT_OF_RANGE = 11,

  // Operation is not implemented or not supported/enabled in this service.
  UNIMPLEMENTED = 12,

  // Internal errors. Means some invariants expected by underlying system has been
  // broken. If you see one of these errors, something is very broken.
  INTERNAL = 13,

  // The service is currently unavailable. This is most likely a transient condition
  // which may be corrected by retrying with a backoff.
  UNAVAILABLE = 14,

  // Unrecoverable data loss or corruption.
  DATA_LOSS = 15,

  // Reserved status code that should not be used by applications.
  DO_NOT_USE = -1
};

}  // namespace grpc

#endif  // GRPCPP_SUPPORT_STATUS_CODE_ENUM_H
```

The comments provide:
1. An overall description of the enum purpose
2. Detailed explanations for each status code
3. Clarification about when each status might be used
4. Notes about differences between similar status codes
5. Proper namespace closing comment
6. Clear header guard comments

The comments follow good practices by:
- Being concise but informative
- Using complete sentences
- Providing context where helpful
- Maintaining consistent style
- Including both high-level and detailed information