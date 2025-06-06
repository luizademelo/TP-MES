# How to write unit tests for gRPC C client.

tl;dr: [Example code](https://github.com/grpc/grpc/blob/master/test/cpp/end2end/mock_test.cc).

To unit-test client-side logic via the synchronous API, gRPC provides a mocked Stub based on googletest(googlemock) that can be programmed upon and easily incorporated in the test code.

For instance, consider an EchoService like this:

```proto
service EchoTestService {
        rpc Echo(EchoRequest) returns (EchoResponse);
        rpc BidiStream(stream EchoRequest) returns (stream EchoResponse);
}
```

The code generated would look something like this:

```c
class EchoTestService final {
  public:
  class StubInterface {
    virtual ::grpc::Status Echo(::grpc::ClientContext* context, const ::grpc::testing::EchoRequest& request, ::grpc::testing::EchoResponse* response) = 0;
  …
    std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::grpc::testing::EchoRequest, ::grpc::testing::EchoResponse>> BidiStream(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::grpc::testing::EchoRequest, ::grpc::testing::EchoResponse>>(BidiStreamRaw(context));
    }
  …
    private:
    virtual ::grpc::ClientReaderWriterInterface< ::grpc::testing::EchoRequest, ::grpc::testing::EchoResponse>* BidiStreamRaw(::grpc::ClientContext* context) = 0;
  …
  } // End StubInterface
…
} // End EchoTestService
```

If we mock the StubInterface and set expectations on the pure-virtual methods we can test client-side logic without having to make any rpcs.

A mock for this StubInterface will look like this:

```c
class MockEchoTestServiceStub : public EchoTestService::StubInterface {
 public:
  MOCK_METHOD3(Echo, ::grpc::Status(::grpc::ClientContext* context, const ::grpc::testing::EchoRequest& request, ::grpc::testing::EchoResponse* response));
  MOCK_METHOD1(BidiStreamRaw, ::grpc::ClientReaderWriterInterface< ::grpc::testing::EchoRequest, ::grpc::testing::EchoResponse>*(::grpc::ClientContext* context));
};
```

**Generating mock code:**

Such a mock can be auto-generated by:

1.  Setting flag(generate_mock_code=true) on grpc plugin for protoc, or
1.  Setting an attribute(generate_mocks) in your bazel rule.

Protoc plugin flag:

```sh
protoc -I . --grpc_out=generate_mock_code=true:. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` echo.proto
```

Bazel rule:

```py
grpc_proto_library(
  name = "echo_proto",
  srcs = ["echo.proto"],
  generate_mocks = True,
)
```

By adding such a flag now a header file `echo_mock.grpc.pb.h` containing the mocked stub will also be generated.

This header file can then be included in test files along with a gmock dependency.

**Writing tests with mocked Stub.**

Consider the following client a user might have:

```c
class FakeClient {
 public:
  explicit FakeClient(EchoTestService::StubInterface* stub) : stub_(stub) {}

  void DoEcho() {
    ClientContext context;
    EchoRequest request;
    EchoResponse response;
    request.set_message("hello world");
    Status s = stub_->Echo(&context, request, &response);
    EXPECT_EQ(request.message(), response.message());
    EXPECT_TRUE(s.ok());
  }

  void DoBidiStream() {
    EchoRequest request;
    EchoResponse response;
    ClientContext context;
    std::string msg("hello");

    std::unique_ptr<ClientReaderWriterInterface<EchoRequest, EchoResponse>>
        stream = stub_->BidiStream(&context);

    request.set_message(msg  "0");
    EXPECT_TRUE(stream->Write(request));
    EXPECT_TRUE(stream->Read(&response));
    EXPECT_EQ(response.message(), request.message());

    request.set_message(msg  "1");
    EXPECT_TRUE(stream->Write(request));
    EXPECT_TRUE(stream->Read(&response));
    EXPECT_EQ(response.message(), request.message());

    request.set_message(msg  "2");
    EXPECT_TRUE(stream->Write(request));
    EXPECT_TRUE(stream->Read(&response));
    EXPECT_EQ(response.message(), request.message());

    stream->WritesDone();
    EXPECT_FALSE(stream->Read(&response));

    Status s = stream->Finish();
    EXPECT_TRUE(s.ok());
  }

  void ResetStub(EchoTestService::StubInterface* stub) { stub_ = stub; }

 private:
  EchoTestService::StubInterface* stub_;
};
```

A test could initialize this FakeClient with a mocked stub having set expectations on it:

Unary RPC:

```c
MockEchoTestServiceStub stub;
EchoResponse resp;
resp.set_message("hello world");
EXPECT_CALL(stub, Echo(_,_,_)).Times(AtLeast(1)).WillOnce(DoAll(SetArgPointee<2>(resp), Return(Status::OK)));
FakeClient client(stub);
client.DoEcho();
```

Streaming RPC:

```c
ACTION_P(copy, msg) {
  arg0->set_message(msg->message());
}

auto rw = new MockClientReaderWriter<EchoRequest, EchoResponse>();
EchoRequest msg;
EXPECT_CALL(*rw, Write(_, _)).Times(3).WillRepeatedly(DoAll(SaveArg<0>(&msg), Return(true)));
EXPECT_CALL(*rw, Read(_)).
      WillOnce(DoAll(WithArg<0>(copy(&msg)), Return(true))).
      WillOnce(DoAll(WithArg<0>(copy(&msg)), Return(true))).
      WillOnce(DoAll(WithArg<0>(copy(&msg)), Return(true))).
      WillOnce(Return(false));

MockEchoTestServiceStub  stub;
EXPECT_CALL(stub, BidiStreamRaw(_)).Times(AtLeast(1)).WillOnce(Return(rw));

FakeClient client(stub);
client.DoBidiStream();
```
