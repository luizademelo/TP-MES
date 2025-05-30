
// Copyright 2015 gRPC authors.

#include <grpcpp/support/config.h>

#include <fstream>
#include <functional>
#include <iostream>

#include "absl/flags/flag.h"
#include "test/cpp/util/cli_credentials.h"
#include "test/cpp/util/grpc_tool.h"
#include "test/cpp/util/test_config.h"

ABSL_FLAG(std::string, outfile, "", "Output file (default is stdout)");

static bool SimplePrint(const std::string& outfile, const std::string& output) {
  if (outfile.empty()) {
    std::cout << output << std::flush;
  } else {
    std::ofstream output_file(outfile, std::ios::app | std::ios::binary);
    output_file << output << std::flush;
    output_file.close();
  }
  return true;
}

int main(int argc, char** argv) {
  grpc::testing::InitTest(&argc, &argv, true);

  return grpc::testing::GrpcToolMainLib(
      argc, const_cast<const char**>(argv), grpc::testing::CliCredentials(),
      std::bind(SimplePrint, absl::GetFlag(FLAGS_outfile),
                std::placeholders::_1));
}
