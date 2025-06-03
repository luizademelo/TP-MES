Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions
#ifndef GRPCPP_IMPL_CODEGEN_CONFIG_PROTOBUF_H
#define GRPCPP_IMPL_CODEGEN_CONFIG_PROTOBUF_H

// Define a macro to enable Protobuf Cord support
#define GRPC_PROTOBUF_CORD_SUPPORT_ENABLED

// Configuration for custom message types
#ifndef GRPC_CUSTOM_MESSAGE
// Check if using lite version of protobuf
#ifdef GRPC_USE_PROTO_LITE
#include <google/protobuf/message_lite.h>
// Define message types for lite version
#define GRPC_CUSTOM_MESSAGE ::google::protobuf::MessageLite
#define GRPC_CUSTOM_MESSAGELITE ::google::protobuf::MessageLite
#else
// Default to full protobuf version
#include <google/protobuf/message.h>
#define GRPC_CUSTOM_MESSAGE ::google::protobuf::Message
#define GRPC_CUSTOM_MESSAGELITE ::google::protobuf::MessageLite
#endif
#endif

// Configuration for descriptor-related types
#ifndef GRPC_CUSTOM_DESCRIPTOR
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
// Check for protobuf version >= 4.25.0 for edition support
#if !defined(GOOGLE_PROTOBUF_VERSION) || GOOGLE_PROTOBUF_VERSION >= 4025000
#define GRPC_PROTOBUF_EDITION_SUPPORT
#endif
// Define various descriptor-related types
#define GRPC_CUSTOM_DESCRIPTOR ::google::protobuf::Descriptor
#define GRPC_CUSTOM_DESCRIPTORPOOL ::google::protobuf::DescriptorPool
#ifdef GRPC_PROTOBUF_EDITION_SUPPORT
#define GRPC_CUSTOM_EDITION ::google::protobuf::Edition
#endif
#define GRPC_CUSTOM_FIELDDESCRIPTOR ::google::protobuf::FieldDescriptor
#define GRPC_CUSTOM_FILEDESCRIPTOR ::google::protobuf::FileDescriptor
#define GRPC_CUSTOM_FILEDESCRIPTORPROTO ::google::protobuf::FileDescriptorProto
#define GRPC_CUSTOM_METHODDESCRIPTOR ::google::protobuf::MethodDescriptor
#define GRPC_CUSTOM_SERVICEDESCRIPTOR ::google::protobuf::ServiceDescriptor
#define GRPC_CUSTOM_SOURCELOCATION ::google::protobuf::SourceLocation
#endif

// Configuration for descriptor database types
#ifndef GRPC_CUSTOM_DESCRIPTORDATABASE
#include <google/protobuf/descriptor_database.h>
#define GRPC_CUSTOM_DESCRIPTORDATABASE ::google::protobuf::DescriptorDatabase
#define GRPC_CUSTOM_SIMPLEDESCRIPTORDATABASE \
  ::google::protobuf::SimpleDescriptorDatabase
#endif

// Configuration for zero-copy stream types
#ifndef GRPC_CUSTOM_ZEROCOPYOUTPUTSTREAM
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream.h>
#define GRPC_CUSTOM_ZEROCOPYOUTPUTSTREAM \
  ::google::protobuf::io::ZeroCopyOutputStream
#define GRPC_CUSTOM_ZEROCOPYINPUTSTREAM \
  ::google::protobuf::io::ZeroCopyInputStream
#define GRPC_CUSTOM_CODEDINPUTSTREAM ::google::protobuf::io::CodedInputStream
#define GRPC_CUSTOM_CODEDOUTPUTSTREAM ::google::protobuf::io::CodedOutputStream
#endif

// Configuration for JSON utility types
#ifndef GRPC_CUSTOM_JSONUTIL
#include <google/protobuf/util/json_util.h>
#include <google/protobuf/util/type_resolver_util.h>
#include "absl/status/status.h"
#define GRPC_CUSTOM_JSONUTIL ::google::protobuf::util
#define GRPC_CUSTOM_UTIL_STATUS ::absl::Status
#endif

// gRPC protobuf namespace definitions
namespace grpc {
namespace protobuf {

// Type aliases for protobuf message types
typedef GRPC_CUSTOM_MESSAGE Message;
typedef GRPC_CUSTOM_MESSAGELITE MessageLite;

// Type aliases for descriptor-related types
typedef GRPC_CUSTOM_DESCRIPTOR Descriptor;
typedef GRPC_CUSTOM_DESCRIPTORPOOL DescriptorPool;
typedef GRPC_CUSTOM_DESCRIPTORDATABASE DescriptorDatabase;
#ifdef GRPC_PROTOBUF_EDITION_SUPPORT
typedef GRPC_CUSTOM_EDITION Edition;
#endif
typedef GRPC_CUSTOM_FIELDDESCRIPTOR FieldDescriptor;
typedef GRPC_CUSTOM_FILEDESCRIPTOR FileDescriptor;
typedef GRPC_CUSTOM_FILEDESCRIPTORPROTO FileDescriptorProto;
typedef GRPC_CUSTOM_METHODDESCRIPTOR MethodDescriptor;
typedef GRPC_CUSTOM_SERVICEDESCRIPTOR ServiceDescriptor;
typedef GRPC_CUSTOM_SIMPLEDESCRIPTORDATABASE SimpleDescriptorDatabase;
typedef GRPC_CUSTOM_SOURCELOCATION SourceLocation;

// Utility namespace for status types
namespace util {
typedef GRPC_CUSTOM_UTIL_STATUS Status;
}

// JSON utility namespace alias
namespace json = GRPC_CUSTOM_JSONUTIL;

// I/O namespace for stream types
namespace io {
typedef GRPC_CUSTOM_ZEROCOPYOUTPUTSTREAM ZeroCopyOutputStream;
typedef GRPC_CUSTOM_ZEROCOPYINPUTSTREAM ZeroCopyInputStream;
typedef GRPC_CUSTOM_CODEDINPUTSTREAM CodedInputStream;
typedef GRPC_CUSTOM_CODEDOUTPUTSTREAM CodedOutputStream;
}

}  // namespace protobuf
}  // namespace grpc

#endif  // GRPCPP_IMPL_CODEGEN_CONFIG_PROTOBUF_H
```

The comments explain:
1. The purpose of header guards and configuration macros
2. The conditional inclusion of different Protobuf versions (lite vs full)
3. The various type definitions and their purposes
4. The namespace organization
5. The version-specific features (like edition support)
6. The different components (messages, descriptors, I/O, JSON utilities)

The comments are placed to help future developers understand:
- Why certain decisions were made (like version checks)
- What each section of the configuration does
- How the types are organized in namespaces
- The relationships between different components