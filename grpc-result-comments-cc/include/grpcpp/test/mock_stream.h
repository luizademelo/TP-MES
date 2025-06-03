Here's the commented version of the code:

```c++
// Copyright 2017 gRPC authors.

#ifndef GRPCPP_TEST_MOCK_STREAM_H
#define GRPCPP_TEST_MOCK_STREAM_H

#include <grpcpp/impl/call.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/sync_stream.h>
#include <stdint.h>

#include "gmock/gmock.h"

namespace grpc {
namespace testing {

// Mock implementation of ClientReaderInterface for testing purposes.
// Template parameter R represents the response message type.
template <class R>
class MockClientReader : public grpc::ClientReaderInterface<R> {
 public:
  MockClientReader() = default;

  // Mocks the Finish method which returns final status of the RPC.
  MOCK_METHOD0_T(Finish, Status());

  // Mocks the NextMessageSize method which gets the size of the next message.
  MOCK_METHOD1_T(NextMessageSize, bool(uint32_t*));
  
  // Mocks the Read method which reads the next message.
  MOCK_METHOD1_T(Read, bool(R*));

  // Mocks the WaitForInitialMetadata method which waits for initial metadata.
  MOCK_METHOD0_T(WaitForInitialMetadata, void());
};

// Mock implementation of ClientWriterInterface for testing purposes.
// Template parameter W represents the request message type.
template <class W>
class MockClientWriter : public grpc::ClientWriterInterface<W> {
 public:
  MockClientWriter() = default;

  // Mocks the Finish method which returns final status of the RPC.
  MOCK_METHOD0_T(Finish, Status());

  // Mocks the Write method which writes a message to the stream.
  MOCK_METHOD2_T(Write, bool(const W&, const WriteOptions));

  // Mocks the WritesDone method which indicates no more writes will be made.
  MOCK_METHOD0_T(WritesDone, bool());
};

// Mock implementation of ClientReaderWriterInterface for testing purposes.
// Template parameters W and R represent request and response message types.
template <class W, class R>
class MockClientReaderWriter : public grpc::ClientReaderWriterInterface<W, R> {
 public:
  MockClientReaderWriter() = default;

  // Mocks the Finish method which returns final status of the RPC.
  MOCK_METHOD0_T(Finish, Status());

  // Mocks the NextMessageSize method which gets the size of the next message.
  MOCK_METHOD1_T(NextMessageSize, bool(uint32_t*));
  
  // Mocks the Read method which reads the next message.
  MOCK_METHOD1_T(Read, bool(R*));

  // Mocks the Write method which writes a message to the stream.
  MOCK_METHOD2_T(Write, bool(const W&, const WriteOptions));

  // Mocks the WaitForInitialMetadata method which waits for initial metadata.
  MOCK_METHOD0_T(WaitForInitialMetadata, void());
  
  // Mocks the WritesDone method which indicates no more writes will be made.
  MOCK_METHOD0_T(WritesDone, bool());
};

/// TODO: We do not support mocking an async RPC for now.

// Mock implementation of ClientAsyncResponseReaderInterface for testing purposes.
// Template parameter R represents the response message type.
template <class R>
class MockClientAsyncResponseReader
    : public grpc::ClientAsyncResponseReaderInterface<R> {
 public:
  MockClientAsyncResponseReader() = default;

  // Mocks the StartCall method which initiates the async call.
  MOCK_METHOD0_T(StartCall, void());
  
  // Mocks the ReadInitialMetadata method which reads initial metadata.
  MOCK_METHOD1_T(ReadInitialMetadata, void(void*));
  
  // Mocks the Finish method which completes the async call.
  MOCK_METHOD3_T(Finish, void(R*, Status*, void*));
};

// Mock implementation of ClientAsyncReaderInterface for testing purposes.
// Template parameter R represents the response message type.
template <class R>
class MockClientAsyncReader : public ClientAsyncReaderInterface<R> {
 public:
  MockClientAsyncReader() = default;

  // Mocks the StartCall method which initiates the async call.
  MOCK_METHOD1_T(StartCall, void(void*));
  
  // Mocks the ReadInitialMetadata method which reads initial metadata.
  MOCK_METHOD1_T(ReadInitialMetadata, void(void*));
  
  // Mocks the Finish method which completes the async call.
  MOCK_METHOD2_T(Finish, void(Status*, void*));

  // Mocks the Read method which reads the next message asynchronously.
  MOCK_METHOD2_T(Read, void(R*, void*));
};

// Mock implementation of ClientAsyncWriterInterface for testing purposes.
// Template parameter W represents the request message type.
template <class W>
class MockClientAsyncWriter : public grpc::ClientAsyncWriterInterface<W> {
 public:
  MockClientAsyncWriter() = default;

  // Mocks the StartCall method which initiates the async call.
  MOCK_METHOD1_T(StartCall, void(void*));
  
  // Mocks the ReadInitialMetadata method which reads initial metadata.
  MOCK_METHOD1_T(ReadInitialMetadata, void(void*));
  
  // Mocks the Finish method which completes the async call.
  MOCK_METHOD2_T(Finish, void(Status*, void*));

  // Mocks the Write method which writes a message asynchronously.
  MOCK_METHOD2_T(Write, void(const W&, void*));
  
  // Mocks the Write method with WriteOptions which writes a message asynchronously.
  MOCK_METHOD3_T(Write, void(const W&, grpc::WriteOptions, void*));

  // Mocks the WritesDone method which indicates no more writes will be made.
  MOCK_METHOD1_T(WritesDone, void(void*));
};

// Mock implementation of ClientAsyncReaderWriterInterface for testing purposes.
// Template parameters W and R represent request and response message types.
template <class W, class R>
class MockClientAsyncReaderWriter
    : public ClientAsyncReaderWriterInterface<W, R> {
 public:
  MockClientAsyncReaderWriter() = default;

  // Mocks the StartCall method which initiates the async call.
  MOCK_METHOD1_T(StartCall, void(void*));
  
  // Mocks the ReadInitialMetadata method which reads initial metadata.
  MOCK_METHOD1_T(ReadInitialMetadata, void(void*));
  
  // Mocks the Finish method which completes the async call.
  MOCK_METHOD2_T(Finish, void(Status*, void*));

  // Mocks the Write method which writes a message asynchronously.
  MOCK_METHOD2_T(Write, void(const W&, void*));
  
  // Mocks the Write method with WriteOptions which writes a message asynchronously.
  MOCK_METHOD3_T(Write, void(const W&, grpc::WriteOptions, void*));

  // Mocks the Read method which reads the next message asynchronously.
  MOCK_METHOD2_T(Read, void(R*, void*));

  // Mocks the WritesDone method which indicates no more writes will be made.
  MOCK_METHOD1_T(WritesDone, void(void*));
};

// Mock implementation of ServerReaderInterface for testing purposes.
// Template parameter R represents the request message type.
template <class R>
class MockServerReader : public grpc::ServerReaderInterface<R> {
 public:
  MockServerReader() = default;

  // Mocks the SendInitialMetadata method which sends initial metadata.
  MOCK_METHOD0_T(SendInitialMetadata, void());

  // Mocks the NextMessageSize method which gets the size of the next message.
  MOCK_METHOD1_T(NextMessageSize, bool(uint32_t*));
  
  // Mocks the Read method which reads the next message.
  MOCK_METHOD1_T(Read, bool(R*));
};

// Mock implementation of ServerWriterInterface for testing purposes.
// Template parameter W represents the response message type.
template <class W>
class MockServerWriter : public grpc::ServerWriterInterface<W> {
 public:
  MockServerWriter() = default;

  // Mocks the SendInitialMetadata method which sends initial metadata.
  MOCK_METHOD0_T(SendInitialMetadata, void());

  // Mocks the Write method which writes a message to the stream.
  MOCK_METHOD2_T(Write, bool(const W&, const WriteOptions));
};

// Mock implementation of ServerReaderWriterInterface for testing purposes.
// Template parameters W and R represent response and request message types.
template <class W, class R>
class MockServerReaderWriter : public grpc::ServerReaderWriterInterface<W, R> {
 public:
  MockServerReaderWriter() = default;

  // Mocks the SendInitialMetadata method which sends initial metadata.
  MOCK_METHOD0_T(SendInitialMetadata, void());

  // Mocks the NextMessageSize method which gets the size of the next message.
  MOCK_METHOD1_T(NextMessageSize, bool(uint32_t*));
  
  // Mocks the Read method which reads the next message.
  MOCK_METHOD1_T(Read, bool(R*));

  // Mocks the Write method which writes a message to the stream.
  MOCK_METHOD2_T(Write, bool(const W&, const WriteOptions));
};

}  // namespace testing
}  // namespace grpc

#endif
```