
// Copyright 2016 gRPC authors.

#ifndef GRPC_TEST_CPP_UTIL_PROTO_REFLECTION_DESCRIPTOR_DATABASE_H
#define GRPC_TEST_CPP_UTIL_PROTO_REFLECTION_DESCRIPTOR_DATABASE_H

#include <grpcpp/grpcpp.h>
#include <grpcpp/impl/codegen/config_protobuf.h>

#include <mutex>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "src/proto/grpc/reflection/v1alpha/reflection.grpc.pb.h"

namespace grpc {

class ProtoReflectionDescriptorDatabase : public protobuf::DescriptorDatabase {
 public:
  explicit ProtoReflectionDescriptorDatabase(
      std::unique_ptr<reflection::v1alpha::ServerReflection::Stub> stub);

  explicit ProtoReflectionDescriptorDatabase(
      const std::shared_ptr<grpc::ChannelInterface>& channel);

  ~ProtoReflectionDescriptorDatabase() override;

  bool FindFileByName(const string& filename,
                      protobuf::FileDescriptorProto* output) override;

  bool FindFileContainingSymbol(const string& symbol_name,
                                protobuf::FileDescriptorProto* output) override;

  bool FindFileContainingExtension(
      const string& containing_type, int field_number,
      protobuf::FileDescriptorProto* output) override;

  bool FindAllExtensionNumbers(const string& extendee_type,
                               std::vector<int>* output) override;

  bool GetServices(std::vector<std::string>* output);

 private:
  typedef ClientReaderWriter<
      grpc::reflection::v1alpha::ServerReflectionRequest,
      grpc::reflection::v1alpha::ServerReflectionResponse>
      ClientStream;

  protobuf::FileDescriptorProto ParseFileDescriptorProtoResponse(
      const std::string& byte_fd_proto);

  void AddFileFromResponse(
      const grpc::reflection::v1alpha::FileDescriptorResponse& response);

  std::shared_ptr<ClientStream> GetStream();

  bool DoOneRequest(
      const grpc::reflection::v1alpha::ServerReflectionRequest& request,
      grpc::reflection::v1alpha::ServerReflectionResponse& response);

  std::shared_ptr<ClientStream> stream_;
  grpc::ClientContext ctx_;
  std::unique_ptr<grpc::reflection::v1alpha::ServerReflection::Stub> stub_;
  std::unordered_set<string> known_files_;
  std::unordered_set<string> missing_symbols_;
  std::unordered_map<string, std::unordered_set<int>> missing_extensions_;
  std::unordered_map<string, std::vector<int>> cached_extension_numbers_;
  std::mutex stream_mutex_;

  protobuf::SimpleDescriptorDatabase cached_db_;
};

}

#endif
