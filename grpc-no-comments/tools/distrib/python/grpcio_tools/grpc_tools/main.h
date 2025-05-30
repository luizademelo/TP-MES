// Copyright 2016 gRPC authors.

#include <string>
#include <utility>
#include <vector>

namespace grpc_tools {

int protoc_main(int argc, char* argv[], char* version);

struct ProtocError {
  std::string filename;
  int line;
  int column;
  std::string message;

  ProtocError() {}
  ProtocError(std::string filename, int line, int column, std::string message)
      : filename(filename), line(line), column(column), message(message) {}
};

typedef ProtocError ProtocWarning;

int protoc_get_protos(
    char* protobuf_path, const std::vector<std::string>* include_paths,
    std::vector<std::pair<std::string, std::string>>* files_out,
    std::vector<ProtocError>* errors, std::vector<ProtocWarning>* warnings);

int protoc_get_services(
    char* protobuf_path, char* version,
    const std::vector<std::string>* include_paths,
    std::vector<std::pair<std::string, std::string>>* files_out,
    std::vector<ProtocError>* errors, std::vector<ProtocWarning>* warnings);
}
