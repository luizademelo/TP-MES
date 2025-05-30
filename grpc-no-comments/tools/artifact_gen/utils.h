// Copyright 2025 gRPC authors.

#ifndef GRPC_TOOLS_ARTIFACT_GEN_UTILS_H
#define GRPC_TOOLS_ARTIFACT_GEN_UTILS_H

#include "include/nlohmann/json.hpp"

nlohmann::json LoadYaml(const std::string& filename);
std::vector<std::string> AllFilesInDir(const std::string& dir);
std::string LoadString(const std::string& filename);

#endif
