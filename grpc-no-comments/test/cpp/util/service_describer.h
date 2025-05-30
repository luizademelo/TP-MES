
// Copyright 2016 gRPC authors.

#ifndef GRPC_TEST_CPP_UTIL_SERVICE_DESCRIBER_H
#define GRPC_TEST_CPP_UTIL_SERVICE_DESCRIBER_H

#include <grpcpp/support/config.h>

#include "test/cpp/util/config_grpc_cli.h"

namespace grpc {
namespace testing {

std::string DescribeServiceList(std::vector<std::string> service_list,
                                grpc::protobuf::DescriptorPool& desc_pool);

std::string DescribeService(const grpc::protobuf::ServiceDescriptor* service);

std::string DescribeMethod(const grpc::protobuf::MethodDescriptor* method);

std::string SummarizeService(const grpc::protobuf::ServiceDescriptor* service);

std::string SummarizeMethod(const grpc::protobuf::MethodDescriptor* method);

}
}

#endif
