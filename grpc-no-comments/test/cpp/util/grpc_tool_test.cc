
// Copyright 2016 gRPC authors.

#include "test/cpp/util/grpc_tool.h"

#include <gmock/gmock-matchers.h>
#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include <chrono>
#include <sstream>

#include "absl/flags/declare.h"
#include "absl/flags/flag.h"
#include "absl/strings/str_split.h"
#include "gtest/gtest.h"
#include "src/core/util/env.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "src/proto/grpc/testing/echo.pb.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/core/test_util/tls_utils.h"
#include "test/cpp/util/cli_credentials.h"
#include "test/cpp/util/string_ref_helper.h"
#include "test/cpp/util/test_config.h"

#define CA_CERT_PATH "src/core/tsi/test_creds/ca.pem"
#define SERVER_CERT_PATH "src/core/tsi/test_creds/server1.pem"
#define SERVER_KEY_PATH "src/core/tsi/test_creds/server1.key"

using grpc::testing::EchoRequest;
using grpc::testing::EchoResponse;

#define USAGE_REGEX "(  grpc_cli .+\n){2,10}"

#define ECHO_TEST_SERVICE_SUMMARY \
  "Echo\n"                        \
  "Echo1\n"                       \
  "Echo2\n"                       \
  "CheckDeadlineUpperBound\n"     \
  "CheckDeadlineSet\n"            \
  "CheckClientInitialMetadata\n"  \
  "RequestStream\n"               \
  "ResponseStream\n"              \
  "BidiStream\n"                  \
  "Unimplemented\n"               \
  "UnimplementedBidi\n"

#define ECHO_TEST_SERVICE_DESCRIPTION                                          \
  "filename: src/proto/grpc/testing/echo.proto\n"                              \
  "package: grpc.testing;\n"                                                   \
  "service EchoTestService {\n"                                                \
  "  rpc Echo(grpc.testing.EchoRequest) returns (grpc.testing.EchoResponse) "  \
  "{}\n"                                                                       \
  "  rpc Echo1(grpc.testing.EchoRequest) returns (grpc.testing.EchoResponse) " \
  "{}\n"                                                                       \
  "  rpc Echo2(grpc.testing.EchoRequest) returns (grpc.testing.EchoResponse) " \
  "{}\n"                                                                       \
  "  rpc CheckDeadlineUpperBound(grpc.testing.SimpleRequest) returns "         \
  "(grpc.testing.StringValue) {}\n"                                            \
  "  rpc CheckDeadlineSet(grpc.testing.SimpleRequest) returns "                \
  "(grpc.testing.StringValue) {}\n"                                            \
  "  rpc CheckClientInitialMetadata(grpc.testing.SimpleRequest) returns "      \
  "(grpc.testing.SimpleResponse) {}\n"                                         \
  "  rpc RequestStream(stream grpc.testing.EchoRequest) returns "              \
  "(grpc.testing.EchoResponse) {}\n"                                           \
  "  rpc ResponseStream(grpc.testing.EchoRequest) returns (stream "            \
  "grpc.testing.EchoResponse) {}\n"                                            \
  "  rpc BidiStream(stream grpc.testing.EchoRequest) returns (stream "         \
  "grpc.testing.EchoResponse) {}\n"                                            \
  "  rpc Unimplemented(grpc.testing.EchoRequest) returns "                     \
  "(grpc.testing.EchoResponse) {}\n"                                           \
  "  rpc UnimplementedBidi(stream grpc.testing.EchoRequest) returns (stream "  \
  "grpc.testing.EchoResponse) {}\n"                                            \
  "}\n"                                                                        \
  "\n"

#define ECHO_METHOD_DESCRIPTION                                               \
  "  rpc Echo(grpc.testing.EchoRequest) returns (grpc.testing.EchoResponse) " \
  "{}\n"

#define ECHO_RESPONSE_MESSAGE_TEXT_FORMAT \
  "message: \"echo\"\n"                   \
  "param {\n"                             \
  "  host: \"localhost\"\n"               \
  "  peer: \"peer\"\n"                    \
  "}\n\n"

#define ECHO_RESPONSE_MESSAGE_JSON_FORMAT \
  "{\n"                                   \
  " \"message\": \"echo\",\n"             \
  " \"param\": {\n"                       \
  "  \"host\": \"localhost\",\n"          \
  "  \"peer\": \"peer\"\n"                \
  " }\n"                                  \
  "}\n\n"

ABSL_DECLARE_FLAG(std::string, channel_creds_type);
ABSL_DECLARE_FLAG(std::string, ssl_target);
ABSL_DECLARE_FLAG(bool, binary_input);
ABSL_DECLARE_FLAG(bool, binary_output);
ABSL_DECLARE_FLAG(bool, json_input);
ABSL_DECLARE_FLAG(bool, json_output);
ABSL_DECLARE_FLAG(bool, l);
ABSL_DECLARE_FLAG(bool, batch);
ABSL_DECLARE_FLAG(std::string, metadata);
ABSL_DECLARE_FLAG(std::string, protofiles);
ABSL_DECLARE_FLAG(std::string, proto_path);
ABSL_DECLARE_FLAG(std::string, default_service_config);
ABSL_DECLARE_FLAG(double, timeout);
ABSL_DECLARE_FLAG(int, max_recv_msg_size);
ABSL_DECLARE_FLAG(std::string, channel_args);

namespace grpc {
namespace testing {
namespace {

const int kServerDefaultResponseStreamsToSend = 3;

class TestCliCredentials final : public grpc::testing::CliCredentials {
 public:
  explicit TestCliCredentials(bool secure = false) : secure_(secure) {}
  std::shared_ptr<grpc::ChannelCredentials> GetChannelCredentials()
      const override {
    if (!secure_) {
      return InsecureChannelCredentials();
    }
    std::string test_root_cert =
        grpc_core::testing::GetFileContents(CA_CERT_PATH);
    SslCredentialsOptions ssl_opts = {test_root_cert, "", ""};
    return grpc::SslCredentials(grpc::SslCredentialsOptions(ssl_opts));
  }
  std::string GetCredentialUsage() const override { return ""; }

 private:
  const bool secure_;
};

bool PrintStream(std::stringstream* ss, const std::string& output) {
  (*ss) << output;
  return true;
}

template <typename T>
size_t ArraySize(T& a) {
  return ((sizeof(a) / sizeof(*(a))) /
          static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))));
}

class TestServiceImpl : public grpc::testing::EchoTestService::Service {
 public:
  Status Echo(ServerContext* context, const EchoRequest* request,
              EchoResponse* response) override {
    if (!context->client_metadata().empty()) {
      for (std::multimap<grpc::string_ref, grpc::string_ref>::const_iterator
               iter = context->client_metadata().begin();
           iter != context->client_metadata().end(); ++iter) {
        context->AddInitialMetadata(ToString(iter->first),
                                    ToString(iter->second));
      }
    }
    context->AddTrailingMetadata("trailing_key", "trailing_value");
    response->set_message(request->message());
    return Status::OK;
  }

  Status CheckDeadlineSet(ServerContext* context,
                          const SimpleRequest* ,
                          StringValue* response) override {
    response->set_message(context->deadline() !=
                                  std::chrono::system_clock::time_point::max()
                              ? "true"
                              : "false");
    return Status::OK;
  }

  Status CheckDeadlineUpperBound(ServerContext* context,
                                 const SimpleRequest* ,
                                 StringValue* response) override {
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(
        context->deadline() - std::chrono::system_clock::now());

    response->set_message(
        seconds.count() <= absl::GetFlag(FLAGS_timeout) ? "true" : "false");
    return Status::OK;
  }

  Status RequestStream(ServerContext* context,
                       ServerReader<EchoRequest>* reader,
                       EchoResponse* response) override {
    EchoRequest request;
    response->set_message("");
    if (!context->client_metadata().empty()) {
      for (std::multimap<grpc::string_ref, grpc::string_ref>::const_iterator
               iter = context->client_metadata().begin();
           iter != context->client_metadata().end(); ++iter) {
        context->AddInitialMetadata(ToString(iter->first),
                                    ToString(iter->second));
      }
    }
    context->AddTrailingMetadata("trailing_key", "trailing_value");
    while (reader->Read(&request)) {
      response->mutable_message()->append(request.message());
    }

    return Status::OK;
  }

  Status ResponseStream(ServerContext* context, const EchoRequest* request,
                        ServerWriter<EchoResponse>* writer) override {
    if (!context->client_metadata().empty()) {
      for (std::multimap<grpc::string_ref, grpc::string_ref>::const_iterator
               iter = context->client_metadata().begin();
           iter != context->client_metadata().end(); ++iter) {
        context->AddInitialMetadata(ToString(iter->first),
                                    ToString(iter->second));
      }
    }
    context->AddTrailingMetadata("trailing_key", "trailing_value");

    EchoResponse response;
    for (int i = 0; i < kServerDefaultResponseStreamsToSend; i++) {
      response.set_message(request->message() + std::to_string(i));
      writer->Write(response);
    }

    return Status::OK;
  }

  Status BidiStream(
      ServerContext* context,
      ServerReaderWriter<EchoResponse, EchoRequest>* stream) override {
    EchoRequest request;
    EchoResponse response;
    if (!context->client_metadata().empty()) {
      for (std::multimap<grpc::string_ref, grpc::string_ref>::const_iterator
               iter = context->client_metadata().begin();
           iter != context->client_metadata().end(); ++iter) {
        context->AddInitialMetadata(ToString(iter->first),
                                    ToString(iter->second));
      }
    }
    context->AddTrailingMetadata("trailing_key", "trailing_value");

    while (stream->Read(&request)) {
      response.set_message(request.message());
      stream->Write(response);
    }

    return Status::OK;
  }
};

}

class GrpcToolTest : public ::testing::Test {
 protected:
  GrpcToolTest() {}

  std::string SetUpServer(bool secure = false) {
    std::ostringstream server_address;
    int port = grpc_pick_unused_port_or_die();
    server_address << "localhost:" << port;

    ServerBuilder builder;
    std::shared_ptr<grpc::ServerCredentials> creds;
    std::string server_cert =
        grpc_core::testing::GetFileContents(SERVER_CERT_PATH);
    std::string server_key =
        grpc_core::testing::GetFileContents(SERVER_KEY_PATH);
    SslServerCredentialsOptions::PemKeyCertPair pkcp = {server_key,
                                                        server_cert};
    if (secure) {
      SslServerCredentialsOptions ssl_opts;
      ssl_opts.pem_root_certs = "";
      ssl_opts.pem_key_cert_pairs.push_back(pkcp);
      creds = SslServerCredentials(ssl_opts);
    } else {
      creds = InsecureServerCredentials();
    }
    builder.AddListeningPort(server_address.str(), creds);
    builder.RegisterService(&service_);
    server_ = builder.BuildAndStart();
    return server_address.str();
  }

  void ShutdownServer() { server_->Shutdown(); }

  std::unique_ptr<Server> server_;
  TestServiceImpl service_;
  reflection::ProtoServerReflectionPlugin plugin_;
};

TEST_F(GrpcToolTest, NoCommand) {

  std::stringstream output_stream;
  const char* argv[] = {"grpc_cli"};

  EXPECT_EXIT(
      GrpcToolMainLib(
          ArraySize(argv), argv, TestCliCredentials(),
          std::bind(PrintStream, &output_stream, std::placeholders::_1)),
      ::testing::ExitedWithCode(1), "No command specified\n" USAGE_REGEX);

  EXPECT_TRUE(0 == output_stream.tellp());
}

TEST_F(GrpcToolTest, InvalidCommand) {

  std::stringstream output_stream;
  const char* argv[] = {"grpc_cli", "abc"};

  EXPECT_EXIT(
      GrpcToolMainLib(
          ArraySize(argv), argv, TestCliCredentials(),
          std::bind(PrintStream, &output_stream, std::placeholders::_1)),
      ::testing::ExitedWithCode(1), "Invalid command 'abc'\n" USAGE_REGEX);

  EXPECT_TRUE(0 == output_stream.tellp());
}

TEST_F(GrpcToolTest, HelpCommand) {

  std::stringstream output_stream;
  const char* argv[] = {"grpc_cli", "help"};

  EXPECT_EXIT(GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                              std::bind(PrintStream, &output_stream,
                                        std::placeholders::_1)),
              ::testing::ExitedWithCode(1), USAGE_REGEX);

  EXPECT_TRUE(0 == output_stream.tellp());
}

TEST_F(GrpcToolTest, ListCommand) {

  std::stringstream output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "ls", server_address.c_str()};

  absl::SetFlag(&FLAGS_l, false);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  EXPECT_THAT(absl::StrSplit(output_stream.str(), "\n"),
              ::testing::UnorderedElementsAre(
                  "grpc.testing.EchoTestService",
                  "grpc.reflection.v1alpha.ServerReflection",
                  "grpc.reflection.v1.ServerReflection", ""));

  ShutdownServer();
}

TEST_F(GrpcToolTest, ListOneService) {

  std::stringstream output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "ls", server_address.c_str(),
                        "grpc.testing.EchoTestService"};

  absl::SetFlag(&FLAGS_l, false);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));

  EXPECT_TRUE(0 ==
              strcmp(output_stream.str().c_str(), ECHO_TEST_SERVICE_SUMMARY));

  output_stream.str(std::string());
  output_stream.clear();
  absl::SetFlag(&FLAGS_l, true);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));

  EXPECT_TRUE(
      0 == strcmp(output_stream.str().c_str(), ECHO_TEST_SERVICE_DESCRIPTION));

  ShutdownServer();
}

TEST_F(GrpcToolTest, TypeCommand) {

  std::stringstream output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "type", server_address.c_str(),
                        "grpc.testing.EchoRequest"};

  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  const grpc::protobuf::Descriptor* desc =
      grpc::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(
          "grpc.testing.EchoRequest");

  EXPECT_TRUE(0 ==
              strcmp(output_stream.str().c_str(), desc->DebugString().c_str()));

  ShutdownServer();
}

TEST_F(GrpcToolTest, ListOneMethod) {

  std::stringstream output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "ls", server_address.c_str(),
                        "grpc.testing.EchoTestService.Echo"};

  absl::SetFlag(&FLAGS_l, false);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));

  EXPECT_TRUE(0 == strcmp(output_stream.str().c_str(), "Echo\n"));

  output_stream.str(std::string());
  output_stream.clear();
  absl::SetFlag(&FLAGS_l, true);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));

  EXPECT_TRUE(0 ==
              strcmp(output_stream.str().c_str(), ECHO_METHOD_DESCRIPTION));

  ShutdownServer();
}

TEST_F(GrpcToolTest, TypeNotFound) {

  std::stringstream output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "type", server_address.c_str(),
                        "grpc.testing.PhonyRequest"};

  EXPECT_TRUE(1 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  ShutdownServer();
}

TEST_F(GrpcToolTest, CallCommand) {

  std::stringstream output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "call", server_address.c_str(), "Echo",
                        "message: 'Hello'"};

  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));

  EXPECT_TRUE(nullptr !=
              strstr(output_stream.str().c_str(), "message: \"Hello\""));

  output_stream.str(std::string());
  output_stream.clear();

  absl::SetFlag(&FLAGS_json_output, true);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  absl::SetFlag(&FLAGS_json_output, false);

  EXPECT_TRUE(nullptr != strstr(output_stream.str().c_str(),
                                "{\n \"message\": \"Hello\"\n}"));

  ShutdownServer();
}

TEST_F(GrpcToolTest, CallCommandJsonInput) {

  std::stringstream output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "call", server_address.c_str(), "Echo",
                        "{ \"message\": \"Hello\"}"};

  absl::SetFlag(&FLAGS_json_input, true);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));

  EXPECT_TRUE(nullptr !=
              strstr(output_stream.str().c_str(), "message: \"Hello\""));

  output_stream.str(std::string());
  output_stream.clear();

  absl::SetFlag(&FLAGS_json_output, true);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  absl::SetFlag(&FLAGS_json_output, false);
  absl::SetFlag(&FLAGS_json_input, false);

  EXPECT_TRUE(nullptr != strstr(output_stream.str().c_str(),
                                "{\n \"message\": \"Hello\"\n}"));

  ShutdownServer();
}

TEST_F(GrpcToolTest, CallCommandBatch) {

  std::stringstream output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "call", server_address.c_str(), "Echo",
                        "message: 'Hello0'"};

  std::streambuf* orig = std::cin.rdbuf();
  std::istringstream ss("message: 'Hello1'\n\n message: 'Hello2'\n\n");
  std::cin.rdbuf(ss.rdbuf());

  absl::SetFlag(&FLAGS_batch, true);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  absl::SetFlag(&FLAGS_batch, false);

  EXPECT_TRUE(nullptr != strstr(output_stream.str().c_str(),
                                "message: \"Hello0\"\nmessage: "
                                "\"Hello1\"\nmessage: \"Hello2\"\n"));

  output_stream.str(std::string());
  output_stream.clear();
  ss.clear();
  ss.seekg(0);
  std::cin.rdbuf(ss.rdbuf());

  absl::SetFlag(&FLAGS_batch, true);
  absl::SetFlag(&FLAGS_json_output, true);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  absl::SetFlag(&FLAGS_json_output, false);
  absl::SetFlag(&FLAGS_batch, false);

  EXPECT_TRUE(nullptr != strstr(output_stream.str().c_str(),
                                "{\n \"message\": \"Hello0\"\n}\n"
                                "{\n \"message\": \"Hello1\"\n}\n"
                                "{\n \"message\": \"Hello2\"\n}\n"));

  std::cin.rdbuf(orig);
  ShutdownServer();
}

TEST_F(GrpcToolTest, CallCommandBatchJsonInput) {

  std::stringstream output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "call", server_address.c_str(), "Echo",
                        "{\"message\": \"Hello0\"}"};

  std::streambuf* orig = std::cin.rdbuf();
  std::istringstream ss(
      "{\"message\": \"Hello1\"}\n\n{\"message\": \"Hello2\" }\n\n");
  std::cin.rdbuf(ss.rdbuf());

  absl::SetFlag(&FLAGS_json_input, true);
  absl::SetFlag(&FLAGS_batch, true);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  absl::SetFlag(&FLAGS_batch, false);

  EXPECT_TRUE(nullptr != strstr(output_stream.str().c_str(),
                                "message: \"Hello0\"\nmessage: "
                                "\"Hello1\"\nmessage: \"Hello2\"\n"));

  output_stream.str(std::string());
  output_stream.clear();
  ss.clear();
  ss.seekg(0);
  std::cin.rdbuf(ss.rdbuf());

  absl::SetFlag(&FLAGS_batch, true);
  absl::SetFlag(&FLAGS_json_output, true);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  absl::SetFlag(&FLAGS_json_output, false);
  absl::SetFlag(&FLAGS_batch, false);
  absl::SetFlag(&FLAGS_json_input, false);

  EXPECT_TRUE(nullptr != strstr(output_stream.str().c_str(),
                                "{\n \"message\": \"Hello0\"\n}\n"
                                "{\n \"message\": \"Hello1\"\n}\n"
                                "{\n \"message\": \"Hello2\"\n}\n"));

  std::cin.rdbuf(orig);
  ShutdownServer();
}

TEST_F(GrpcToolTest, CallCommandBatchWithBadRequest) {

  std::stringstream output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "call", server_address.c_str(), "Echo",
                        "message: 'Hello0'"};

  std::streambuf* orig = std::cin.rdbuf();
  std::istringstream ss("message: 1\n\n message: 'Hello2'\n\n");
  std::cin.rdbuf(ss.rdbuf());

  absl::SetFlag(&FLAGS_batch, true);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  absl::SetFlag(&FLAGS_batch, false);

  EXPECT_TRUE(nullptr != strstr(output_stream.str().c_str(),
                                "message: \"Hello0\"\nmessage: \"Hello2\"\n"));

  output_stream.str(std::string());
  output_stream.clear();
  ss.clear();
  ss.seekg(0);
  std::cin.rdbuf(ss.rdbuf());

  absl::SetFlag(&FLAGS_batch, true);
  absl::SetFlag(&FLAGS_json_output, true);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  absl::SetFlag(&FLAGS_json_output, false);
  absl::SetFlag(&FLAGS_batch, false);

  EXPECT_TRUE(nullptr != strstr(output_stream.str().c_str(),
                                "{\n \"message\": \"Hello0\"\n}\n"
                                "{\n \"message\": \"Hello2\"\n}\n"));

  std::cin.rdbuf(orig);
  ShutdownServer();
}

TEST_F(GrpcToolTest, CallCommandBatchJsonInputWithBadRequest) {

  std::stringstream output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "call", server_address.c_str(), "Echo",
                        "{ \"message\": \"Hello0\"}"};

  std::streambuf* orig = std::cin.rdbuf();
  std::istringstream ss(
      "{ \"message\": 1 }\n\n { \"message\": \"Hello2\" }\n\n");
  std::cin.rdbuf(ss.rdbuf());

  absl::SetFlag(&FLAGS_batch, true);
  absl::SetFlag(&FLAGS_json_input, true);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  absl::SetFlag(&FLAGS_json_input, false);
  absl::SetFlag(&FLAGS_batch, false);

  EXPECT_TRUE(nullptr != strstr(output_stream.str().c_str(),
                                "message: \"Hello0\"\nmessage: \"Hello2\"\n"));

  output_stream.str(std::string());
  output_stream.clear();
  ss.clear();
  ss.seekg(0);
  std::cin.rdbuf(ss.rdbuf());

  absl::SetFlag(&FLAGS_batch, true);
  absl::SetFlag(&FLAGS_json_input, true);
  absl::SetFlag(&FLAGS_json_output, true);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  absl::SetFlag(&FLAGS_json_output, false);
  absl::SetFlag(&FLAGS_json_input, false);
  absl::SetFlag(&FLAGS_batch, false);

  EXPECT_TRUE(nullptr != strstr(output_stream.str().c_str(),
                                "{\n \"message\": \"Hello0\"\n}\n"
                                "{\n \"message\": \"Hello2\"\n}\n"));

  std::cin.rdbuf(orig);
  ShutdownServer();
}

TEST_F(GrpcToolTest, CallCommandRequestStream) {

  std::stringstream output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "call", server_address.c_str(),
                        "RequestStream", "message: 'Hello0'"};

  std::streambuf* orig = std::cin.rdbuf();
  std::istringstream ss("message: 'Hello1'\n\n message: 'Hello2'\n\n");
  std::cin.rdbuf(ss.rdbuf());

  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));

  EXPECT_TRUE(nullptr != strstr(output_stream.str().c_str(),
                                "message: \"Hello0Hello1Hello2\""));
  std::cin.rdbuf(orig);
  ShutdownServer();
}

TEST_F(GrpcToolTest, CallCommandRequestStreamJsonInput) {

  std::stringstream output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "call", server_address.c_str(),
                        "RequestStream", "{ \"message\": \"Hello0\" }"};

  std::streambuf* orig = std::cin.rdbuf();
  std::istringstream ss(
      "{ \"message\": \"Hello1\" }\n\n{ \"message\": \"Hello2\" }\n\n");
  std::cin.rdbuf(ss.rdbuf());

  absl::SetFlag(&FLAGS_json_input, true);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  absl::SetFlag(&FLAGS_json_input, false);

  EXPECT_TRUE(nullptr != strstr(output_stream.str().c_str(),
                                "message: \"Hello0Hello1Hello2\""));
  std::cin.rdbuf(orig);
  ShutdownServer();
}

TEST_F(GrpcToolTest, CallCommandRequestStreamWithBadRequest) {

  std::stringstream output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "call", server_address.c_str(),
                        "RequestStream", "message: 'Hello0'"};

  std::streambuf* orig = std::cin.rdbuf();
  std::istringstream ss("bad_field: 'Hello1'\n\n message: 'Hello2'\n\n");
  std::cin.rdbuf(ss.rdbuf());

  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));

  EXPECT_TRUE(nullptr !=
              strstr(output_stream.str().c_str(), "message: \"Hello0Hello2\""));
  std::cin.rdbuf(orig);
  ShutdownServer();
}

TEST_F(GrpcToolTest, CallCommandRequestStreamWithBadRequestJsonInput) {

  std::stringstream output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "call", server_address.c_str(),
                        "RequestStream", "{ \"message\": \"Hello0\" }"};

  std::streambuf* orig = std::cin.rdbuf();
  std::istringstream ss(
      "{ \"bad_field\": \"Hello1\" }\n\n{ \"message\": \"Hello2\" }\n\n");
  std::cin.rdbuf(ss.rdbuf());

  absl::SetFlag(&FLAGS_json_input, true);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  absl::SetFlag(&FLAGS_json_input, false);

  EXPECT_TRUE(nullptr !=
              strstr(output_stream.str().c_str(), "message: \"Hello0Hello2\""));
  std::cin.rdbuf(orig);
  ShutdownServer();
}

TEST_F(GrpcToolTest, CallCommandWithTimeoutDeadlineSet) {

  std::stringstream output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "call", server_address.c_str(),
                        "CheckDeadlineSet"};

  absl::SetFlag(&FLAGS_timeout, 5000.25);

  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));

  EXPECT_TRUE(nullptr !=
              strstr(output_stream.str().c_str(), "message: \"true\""));
  ShutdownServer();
}

TEST_F(GrpcToolTest, CallCommandWithTimeoutDeadlineUpperBound) {

  std::stringstream output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "call", server_address.c_str(),
                        "CheckDeadlineUpperBound"};

  absl::SetFlag(&FLAGS_timeout, 900);

  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));

  std::string output = output_stream.str();

  EXPECT_TRUE(nullptr != strstr(output.c_str(), "message: \"true\"")) << output;
  ShutdownServer();
}

TEST_F(GrpcToolTest, CallCommandWithNegativeTimeoutValue) {

  std::stringstream output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "call", server_address.c_str(),
                        "CheckDeadlineSet"};

  absl::SetFlag(&FLAGS_timeout, -5);

  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));

  EXPECT_TRUE(nullptr !=
              strstr(output_stream.str().c_str(), "message: \"false\""));

  ShutdownServer();
}

TEST_F(GrpcToolTest, CallCommandWithDefaultTimeoutValue) {

  std::stringstream output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "call", server_address.c_str(),
                        "CheckDeadlineSet"};

  absl::SetFlag(&FLAGS_timeout, -1);

  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));

  EXPECT_TRUE(nullptr !=
              strstr(output_stream.str().c_str(), "message: \"false\""));

  ShutdownServer();
}

TEST_F(GrpcToolTest, CallCommandResponseStream) {

  std::stringstream output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "call", server_address.c_str(),
                        "ResponseStream", "message: 'Hello'"};

  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));

  for (int i = 0; i < kServerDefaultResponseStreamsToSend; i++) {
    std::string expected_response_text =
        "message: \"Hello" + std::to_string(i) + "\"\n";
    EXPECT_TRUE(nullptr != strstr(output_stream.str().c_str(),
                                  expected_response_text.c_str()));
  }

  output_stream.str(std::string());
  output_stream.clear();

  absl::SetFlag(&FLAGS_json_output, true);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  absl::SetFlag(&FLAGS_json_output, false);

  for (int i = 0; i < kServerDefaultResponseStreamsToSend; i++) {
    std::string expected_response_text =
        "{\n \"message\": \"Hello" + std::to_string(i) + "\"\n}\n";
    EXPECT_TRUE(nullptr != strstr(output_stream.str().c_str(),
                                  expected_response_text.c_str()));
  }

  ShutdownServer();
}

TEST_F(GrpcToolTest, CallCommandBidiStream) {

  std::stringstream output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "call", server_address.c_str(),
                        "BidiStream", "message: 'Hello0'"};

  std::streambuf* orig = std::cin.rdbuf();
  std::istringstream ss("message: 'Hello1'\n\n message: 'Hello2'\n\n");
  std::cin.rdbuf(ss.rdbuf());

  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));

  EXPECT_TRUE(nullptr != strstr(output_stream.str().c_str(),
                                "message: \"Hello0\"\nmessage: "
                                "\"Hello1\"\nmessage: \"Hello2\"\n"));
  std::cin.rdbuf(orig);
  ShutdownServer();
}

TEST_F(GrpcToolTest, CallCommandBidiStreamWithBadRequest) {

  std::stringstream output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "call", server_address.c_str(),
                        "BidiStream", "message: 'Hello0'"};

  std::streambuf* orig = std::cin.rdbuf();
  std::istringstream ss("message: 1.0\n\n message: 'Hello2'\n\n");
  std::cin.rdbuf(ss.rdbuf());

  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));

  EXPECT_TRUE(nullptr != strstr(output_stream.str().c_str(),
                                "message: \"Hello0\"\nmessage: \"Hello2\"\n"));
  std::cin.rdbuf(orig);

  ShutdownServer();
}

TEST_F(GrpcToolTest, ParseCommand) {

  std::stringstream output_stream;
  std::stringstream binary_output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "parse", server_address.c_str(),
                        "grpc.testing.EchoResponse",
                        ECHO_RESPONSE_MESSAGE_TEXT_FORMAT};

  absl::SetFlag(&FLAGS_binary_input, false);
  absl::SetFlag(&FLAGS_binary_output, false);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));

  EXPECT_TRUE(0 == strcmp(output_stream.str().c_str(),
                          ECHO_RESPONSE_MESSAGE_TEXT_FORMAT));

  output_stream.str(std::string());
  output_stream.clear();

  absl::SetFlag(&FLAGS_json_output, true);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  absl::SetFlag(&FLAGS_json_output, false);

  EXPECT_TRUE(0 == strcmp(output_stream.str().c_str(),
                          ECHO_RESPONSE_MESSAGE_JSON_FORMAT));

  output_stream.str(std::string());
  output_stream.clear();
  absl::SetFlag(&FLAGS_binary_output, true);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  std::string binary_data = output_stream.str();
  output_stream.str(std::string());
  output_stream.clear();
  argv[4] = binary_data.c_str();
  absl::SetFlag(&FLAGS_binary_input, true);
  absl::SetFlag(&FLAGS_binary_output, false);
  EXPECT_TRUE(0 == GrpcToolMainLib(5, argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));

  EXPECT_TRUE(0 == strcmp(output_stream.str().c_str(),
                          ECHO_RESPONSE_MESSAGE_TEXT_FORMAT));

  absl::SetFlag(&FLAGS_binary_input, false);
  absl::SetFlag(&FLAGS_binary_output, false);
  ShutdownServer();
}

TEST_F(GrpcToolTest, ParseCommandJsonFormat) {

  std::stringstream output_stream;
  std::stringstream binary_output_stream;

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "parse", server_address.c_str(),
                        "grpc.testing.EchoResponse",
                        ECHO_RESPONSE_MESSAGE_JSON_FORMAT};

  absl::SetFlag(&FLAGS_json_input, true);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));

  EXPECT_TRUE(0 == strcmp(output_stream.str().c_str(),
                          ECHO_RESPONSE_MESSAGE_TEXT_FORMAT));

  output_stream.str(std::string());
  output_stream.clear();

  absl::SetFlag(&FLAGS_json_output, true);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  absl::SetFlag(&FLAGS_json_output, false);
  absl::SetFlag(&FLAGS_json_input, false);

  EXPECT_TRUE(0 == strcmp(output_stream.str().c_str(),
                          ECHO_RESPONSE_MESSAGE_JSON_FORMAT));

  ShutdownServer();
}

TEST_F(GrpcToolTest, TooFewArguments) {

  std::stringstream output_stream;
  const char* argv[] = {"grpc_cli", "call", "Echo"};

  EXPECT_EXIT(
      GrpcToolMainLib(
          ArraySize(argv), argv, TestCliCredentials(),
          std::bind(PrintStream, &output_stream, std::placeholders::_1)),
      ::testing::ExitedWithCode(1), ".*Wrong number of arguments for call.*");

  EXPECT_TRUE(0 == output_stream.tellp());
}

TEST_F(GrpcToolTest, TooManyArguments) {

  std::stringstream output_stream;
  const char* argv[] = {"grpc_cli", "call", "localhost:10000",
                        "Echo",     "Echo", "message: 'Hello'"};

  EXPECT_EXIT(
      GrpcToolMainLib(
          ArraySize(argv), argv, TestCliCredentials(),
          std::bind(PrintStream, &output_stream, std::placeholders::_1)),
      ::testing::ExitedWithCode(1), ".*Wrong number of arguments for call.*");

  EXPECT_TRUE(0 == output_stream.tellp());
}

TEST_F(GrpcToolTest, CallCommandWithMetadata) {

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "call", server_address.c_str(), "Echo",
                        "message: 'Hello'"};

  {
    std::stringstream output_stream;
    absl::SetFlag(&FLAGS_metadata, "key0:val0:key1:valq:key2:val2");
    EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv,
                                     TestCliCredentials(),
                                     std::bind(PrintStream, &output_stream,
                                               std::placeholders::_1)));

    EXPECT_TRUE(nullptr !=
                strstr(output_stream.str().c_str(), "message: \"Hello\""));
  }

  {
    std::stringstream output_stream;
    absl::SetFlag(&FLAGS_metadata, "key:val\\:val");
    EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv,
                                     TestCliCredentials(),
                                     std::bind(PrintStream, &output_stream,
                                               std::placeholders::_1)));

    EXPECT_TRUE(nullptr !=
                strstr(output_stream.str().c_str(), "message: \"Hello\""));
  }

  {
    std::stringstream output_stream;
    absl::SetFlag(&FLAGS_metadata, "key:val\\\\val");
    EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv,
                                     TestCliCredentials(),
                                     std::bind(PrintStream, &output_stream,
                                               std::placeholders::_1)));

    EXPECT_TRUE(nullptr !=
                strstr(output_stream.str().c_str(), "message: \"Hello\""));
  }

  absl::SetFlag(&FLAGS_metadata, "");
  ShutdownServer();
}

TEST_F(GrpcToolTest, CallCommandWithBadMetadata) {

  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "call", server_address.c_str(),
                        "grpc.testing.EchoTestService.Echo",
                        "message: 'Hello'"};

  {
    std::stringstream output_stream;
    absl::SetFlag(&FLAGS_metadata, "key0:val0:key1");

    EXPECT_EXIT(
        GrpcToolMainLib(
            ArraySize(argv), argv, TestCliCredentials(),
            std::bind(PrintStream, &output_stream, std::placeholders::_1)),
        ::testing::ExitedWithCode(1), ".*Failed to parse metadata flag.*");
  }

  {
    std::stringstream output_stream;
    absl::SetFlag(&FLAGS_metadata, "key:val\\val");

    EXPECT_EXIT(
        GrpcToolMainLib(
            ArraySize(argv), argv, TestCliCredentials(),
            std::bind(PrintStream, &output_stream, std::placeholders::_1)),
        ::testing::ExitedWithCode(1), ".*Failed to parse metadata flag.*");
  }

  absl::SetFlag(&FLAGS_metadata, "");
  ShutdownServer();
}

TEST_F(GrpcToolTest, CallMaxRecvMessageSizeSmall) {
  std::stringstream output_stream;
  const std::string server_address = SetUpServer();

  const char* argv[] = {"grpc_cli", "call", server_address.c_str(),
                        "grpc.testing.EchoTestService.Echo",
                        "message: 'Hello'"};

  absl::SetFlag(&FLAGS_max_recv_msg_size, 4);
  EXPECT_FALSE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                    std::bind(PrintStream, &output_stream,
                                              std::placeholders::_1)));
  absl::SetFlag(&FLAGS_max_recv_msg_size, 0);

  EXPECT_TRUE(0 == output_stream.tellp());
  ShutdownServer();
}

TEST_F(GrpcToolTest, CallMaxRecvMessageSizeEnough) {
  std::stringstream output_stream;
  const std::string server_address = SetUpServer();

  const char* argv[] = {"grpc_cli", "call", server_address.c_str(),
                        "grpc.testing.EchoTestService.Echo",
                        "message: 'Hello'"};

  absl::SetFlag(&FLAGS_max_recv_msg_size, 1024 * 1024);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  absl::SetFlag(&FLAGS_max_recv_msg_size, 0);

  EXPECT_TRUE(nullptr !=
              strstr(output_stream.str().c_str(), "message: \"Hello\""));
  ShutdownServer();
}

TEST_F(GrpcToolTest, CallMaxRecvMessageSizeDefault) {
  std::stringstream output_stream;
  const std::string server_address = SetUpServer();

  const char* argv[] = {"grpc_cli", "call", server_address.c_str(),
                        "grpc.testing.EchoTestService.Echo",
                        "message: 'Hello'"};

  absl::SetFlag(&FLAGS_max_recv_msg_size, 0);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));

  EXPECT_TRUE(nullptr !=
              strstr(output_stream.str().c_str(), "message: \"Hello\""));
  ShutdownServer();
}

TEST_F(GrpcToolTest, CallMaxRecvMessageSizeUnlimited) {
  std::stringstream output_stream;
  const std::string server_address = SetUpServer();

  const char* argv[] = {"grpc_cli", "call", server_address.c_str(),
                        "grpc.testing.EchoTestService.Echo",
                        "message: 'Hello'"};

  absl::SetFlag(&FLAGS_max_recv_msg_size, -1);
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  absl::SetFlag(&FLAGS_max_recv_msg_size, 0);

  EXPECT_TRUE(nullptr !=
              strstr(output_stream.str().c_str(), "message: \"Hello\""));
  ShutdownServer();
}

TEST_F(GrpcToolTest, CallWithChannelArgs) {
  std::stringstream output_stream;
  const std::string server_address = SetUpServer();

  const char* argv[] = {"grpc_cli", "call", server_address.c_str(),
                        "grpc.testing.EchoTestService.Echo",
                        "message: 'Hello'"};

  absl::SetFlag(&FLAGS_channel_args,
                "x=y,grpc.max_receive_message_length=4,z=1");
  EXPECT_FALSE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                    std::bind(PrintStream, &output_stream,
                                              std::placeholders::_1)));
  absl::SetFlag(&FLAGS_channel_args, "");

  absl::SetFlag(&FLAGS_channel_args,
                ",grpc.max_receive_message_length=1000000,");
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  absl::SetFlag(&FLAGS_channel_args, "");

  ShutdownServer();
}

TEST_F(GrpcToolTest, ListCommandOverrideSslHostName) {
  const std::string server_address = SetUpServer(true);

  std::stringstream output_stream;
  const char* argv[] = {"grpc_cli", "ls", server_address.c_str()};
  absl::SetFlag(&FLAGS_l, false);
  absl::SetFlag(&FLAGS_channel_creds_type, "ssl");
  absl::SetFlag(&FLAGS_ssl_target, "z.test.google.fr");
  EXPECT_TRUE(
      0 == GrpcToolMainLib(
               ArraySize(argv), argv, TestCliCredentials(true),
               std::bind(PrintStream, &output_stream, std::placeholders::_1)));
  EXPECT_THAT(
      absl::StrSplit(output_stream.str(), '\n'),
      ::testing::UnorderedElementsAre(
          "grpc.testing.EchoTestService", "grpc.reflection.v1.ServerReflection",
          "grpc.reflection.v1alpha.ServerReflection", ""));

  absl::SetFlag(&FLAGS_channel_creds_type, "");
  absl::SetFlag(&FLAGS_ssl_target, "");
  ShutdownServer();
}

TEST_F(GrpcToolTest, ConfiguringDefaultServiceConfig) {

  std::stringstream output_stream;
  const std::string server_address = SetUpServer();
  const char* argv[] = {"grpc_cli", "ls", server_address.c_str()};

  absl::SetFlag(&FLAGS_l, false);
  absl::SetFlag(&FLAGS_default_service_config,
                "{\"loadBalancingConfig\":[{\"pick_first\":{}}]}");
  EXPECT_TRUE(0 == GrpcToolMainLib(ArraySize(argv), argv, TestCliCredentials(),
                                   std::bind(PrintStream, &output_stream,
                                             std::placeholders::_1)));
  absl::SetFlag(&FLAGS_default_service_config, "");
  EXPECT_THAT(
      absl::StrSplit(output_stream.str().c_str(), '\n'),
      ::testing::UnorderedElementsAre(
          "grpc.testing.EchoTestService", "grpc.reflection.v1.ServerReflection",
          "grpc.reflection.v1alpha.ServerReflection", ""));
  ShutdownServer();
}

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  GTEST_FLAG_SET(death_test_style, "threadsafe");
  return RUN_ALL_TESTS();
}
