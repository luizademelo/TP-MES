
// Copyright 2016 gRPC authors.

#ifndef GRPC_TEST_CPP_UTIL_CONFIG_GRPC_CLI_H
#define GRPC_TEST_CPP_UTIL_CONFIG_GRPC_CLI_H

#include <grpcpp/impl/codegen/config_protobuf.h>

#ifndef GRPC_CUSTOM_DYNAMICMESSAGEFACTORY
#include <google/protobuf/dynamic_message.h>
#define GRPC_CUSTOM_DYNAMICMESSAGEFACTORY \
  ::google::protobuf::DynamicMessageFactory
#endif

#ifndef GRPC_CUSTOM_DESCRIPTORPOOLDATABASE
#include <google/protobuf/descriptor.h>
#define GRPC_CUSTOM_DESCRIPTORPOOLDATABASE \
  ::google::protobuf::DescriptorPoolDatabase
#define GRPC_CUSTOM_MERGEDDESCRIPTORDATABASE \
  ::google::protobuf::MergedDescriptorDatabase
#endif

#ifndef GRPC_CUSTOM_TEXTFORMAT
#include <google/protobuf/text_format.h>
#define GRPC_CUSTOM_TEXTFORMAT ::google::protobuf::TextFormat
#endif

#ifndef GRPC_CUSTOM_DISKSOURCETREE
#include <google/protobuf/compiler/importer.h>
#define GRPC_CUSTOM_DISKSOURCETREE ::google::protobuf::compiler::DiskSourceTree
#define GRPC_CUSTOM_IMPORTER ::google::protobuf::compiler::Importer
#define GRPC_CUSTOM_MULTIFILEERRORCOLLECTOR \
  ::google::protobuf::compiler::MultiFileErrorCollector
#endif

namespace grpc {
namespace protobuf {

typedef GRPC_CUSTOM_DYNAMICMESSAGEFACTORY DynamicMessageFactory;

typedef GRPC_CUSTOM_DESCRIPTORPOOLDATABASE DescriptorPoolDatabase;
typedef GRPC_CUSTOM_MERGEDDESCRIPTORDATABASE MergedDescriptorDatabase;

typedef GRPC_CUSTOM_TEXTFORMAT TextFormat;

namespace compiler {
typedef GRPC_CUSTOM_DISKSOURCETREE DiskSourceTree;
typedef GRPC_CUSTOM_IMPORTER Importer;
typedef GRPC_CUSTOM_MULTIFILEERRORCOLLECTOR MultiFileErrorCollector;
}

}
}

#endif
