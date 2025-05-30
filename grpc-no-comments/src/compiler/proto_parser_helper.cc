// Copyright 2023 The gRPC Authors

#include <string>

namespace grpc_generator {

std::string EscapeVariableDelimiters(const std::string& original) {
  std::string mut_str = original;
  size_t index = 0;
  while ((index = mut_str.find('$', index)) != std::string::npos) {
    mut_str.replace(index, 1, "$$");
    index += 2;
  }
  return mut_str;
}

}
