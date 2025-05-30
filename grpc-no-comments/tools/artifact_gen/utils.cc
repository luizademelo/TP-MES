// Copyright 2025 gRPC authors.

#include "utils.h"

#include <fstream>

#include "absl/log/log.h"
#include "absl/log/check.h"
#include "include/yaml-cpp/yaml.h"

namespace {

nlohmann::json YamlToJson(YAML::Node node) {
  switch (node.Type()) {
    case YAML::NodeType::Undefined:
      LOG(FATAL) << "Undefined YAML node";
    case YAML::NodeType::Null:
      return nullptr;
    case YAML::NodeType::Scalar:
      return node.Scalar();
    case YAML::NodeType::Sequence: {
      nlohmann::json result = nlohmann::json::array();
      for (const auto& element : node) {
        result.push_back(YamlToJson(element));
      }
      return result;
    }
    case YAML::NodeType::Map: {
      nlohmann::json result = nlohmann::json::object();
      for (const auto& element : node) {
        result[element.first.as<std::string>()] = YamlToJson(element.second);
      }
      return result;
    }
  }
  LOG(FATAL) << "Unknown YAML node type: " << node.Type();
}

}

nlohmann::json LoadYaml(const std::string& filename) {
  return YamlToJson(YAML::LoadFile(filename));
}

namespace {
void AddAllFilesInDir(const std::string& root_dir, const std::string& dir,
                      std::vector<std::string>* result) {
  for (const auto& entry : std::filesystem::directory_iterator(dir)) {
    if (std::filesystem::is_regular_file(entry)) {
      result->push_back(entry.path().lexically_relative(root_dir));
    } else if (std::filesystem::is_directory(entry)) {
      AddAllFilesInDir(root_dir, entry.path().string(), result);
    }
  }
}
}

std::vector<std::string> AllFilesInDir(const std::string& dir) {
  std::vector<std::string> result;
  AddAllFilesInDir(dir, dir, &result);
  return result;
}

std::string LoadString(const std::string& filename) {
  std::ifstream file(filename);
  CHECK(file.is_open()) << "Failed to open file: " << filename;
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}
