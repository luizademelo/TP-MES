Here's the commented version of the code:

```c++
/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "absl/flags/flag.h"
#include "absl/log/log.h"

// Include the generated protobuf headers based on build system
#ifdef BAZEL_BUILD
#include "examples/protos/route_guide.grpc.pb.h"
#else
#include "route_guide.grpc.pb.h"
#endif

// Define the database path flag based on build system
#ifdef BAZEL_BUILD
ABSL_FLAG(std::string, db_path, "examples/cpp/route_guide/route_guide_db.json",
          "Path to db file");
#else
ABSL_FLAG(std::string, db_path, "route_guide_db.json", "Path to db file");
#endif

namespace routeguide {

// Reads and returns the content of the database file specified by the db_path flag
std::string GetDbFileContent(int argc, char** argv) {
  std::string db_path = absl::GetFlag(FLAGS_db_path);
  std::ifstream db_file(db_path);
  if (!db_file.is_open()) {
    LOG(ERROR) << "Failed to open " << db_path;
    abort();
  }
  std::stringstream db;
  db << db_file.rdbuf();
  return db.str();
}

// Parser class for parsing JSON-formatted feature data
class Parser {
 public:
  // Constructor takes the database content and verifies it starts with '['
  explicit Parser(const std::string& db) : db_(db) {
    if (!Match("[")) {
      SetFailedAndReturnFalse();
    }
  }

  // Checks if parsing has reached the end of the input
  bool Finished() { return current_ >= db_.size(); }

  // Attempts to parse one feature from the JSON input
  bool TryParseOne(Feature* feature) {
    if (failed_ || Finished() || !Match("{")) {
      return SetFailedAndReturnFalse();
    }
    // Parse location object
    if (!Match(location_) || !Match("{") || !Match(latitude_)) {
      return SetFailedAndReturnFalse();
    }
    long temp = 0;
    ReadLong(&temp);
    feature->mutable_location()->set_latitude(temp);
    if (!Match(",") || !Match(longitude_)) {
      return SetFailedAndReturnFalse();
    }
    ReadLong(&temp);
    feature->mutable_location()->set_longitude(temp);
    if (!Match("},") || !Match(name_) || !Match("\"")) {
      return SetFailedAndReturnFalse();
    }
    // Parse feature name
    size_t name_start = current_;
    while (current_ != db_.size() && db_[current_++] != '"') {
    }
    if (current_ == db_.size()) {
      return SetFailedAndReturnFalse();
    }
    feature->set_name(db_.substr(name_start, current_ - name_start - 1));
    // Check for end of feature or end of array
    if (!Match("},")) {
      if (db_[current_ - 1] == ']' && current_ == db_.size()) {
        return true;
      }
      return SetFailedAndReturnFalse();
    }
    return true;
  }

 private:
  // Helper function to mark parsing as failed
  bool SetFailedAndReturnFalse() {
    failed_ = true;
    return false;
  }

  // Checks if the input matches the given prefix and advances current position
  bool Match(const std::string& prefix) {
    bool eq = db_.substr(current_, prefix.size()) == prefix;
    current_ += prefix.size();
    return eq;
  }

  // Reads a long integer value from the input
  void ReadLong(long* l) {
    size_t start = current_;
    while (current_ != db_.size() && db_[current_] != ',' &&
           db_[current_] != '}') {
      current_++;
    }

    *l = std::stol(db_.substr(start, current_ - start));
  }

  bool failed_ = false;            // Flag indicating parsing failure
  std::string db_;                 // The database content being parsed
  size_t current_ = 0;            // Current position in the input
  const std::string location_ = "\"location\":";  // JSON location field
  const std::string latitude_ = "\"latitude\":";  // JSON latitude field
  const std::string longitude_ = "\"longitude\":"; // JSON longitude field
  const std::string name_ = "\"name\":";          // JSON name field
};

// Removes whitespace from JSON string except within quoted strings
std::string MinifyJson(const std::string& json) {
  std::regex whitespaceOutsideQuotes(R"(\s+(?=(?:(?:[^"]*"){2})*[^"]*$))");
  // Replace all matches with an empty string
  return std::regex_replace(json, whitespaceOutsideQuotes, "");
}

// Parses the database content into a vector of Features
void ParseDb(const std::string& db, std::vector<Feature>* feature_list) {
  feature_list->clear();
  // First minify the JSON to simplify parsing
  std::string db_content(MinifyJson(db));

  Parser parser(db_content);
  Feature feature;
  while (!parser.Finished()) {
    feature_list->push_back(Feature());
    if (!parser.TryParseOne(&feature_list->back())) {
      LOG(ERROR) << "Error parsing the db file";
      feature_list->clear();
      break;
    }
  }
  LOG(INFO) << "DB parsed, loaded " << feature_list->size() << " features.";
}

}  // namespace routeguide
```

Key improvements in the comments:
1. Added overview comments for each major component (class and functions)
2. Explained the purpose of conditional includes and flag definitions
3. Documented the JSON parsing logic and state management in the Parser class
4. Added comments for important implementation details
5. Clarified the purpose of helper methods
6. Explained the regex-based JSON minification
7. Added comments about error handling and logging
8. Documented the flow of the main ParseDb function

The comments are focused on explaining the why and how of the code's functionality while avoiding redundant explanations of what the code obviously does.