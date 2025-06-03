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

#ifndef GRPC_INTERNAL_COMPILER_GENERATOR_HELPERS_H
#define GRPC_INTERNAL_COMPILER_GENERATOR_HELPERS_H

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "src/compiler/config.h"
#include "src/compiler/proto_parser_helper.h"

namespace grpc_generator {

// Removes the given suffix from the filename if present
// Returns true if suffix was found and removed, false otherwise
inline bool StripSuffix(std::string* filename, const std::string& suffix) {
  if (filename->length() >= suffix.length()) {
    size_t suffix_pos = filename->length() - suffix.length();
    if (filename->compare(suffix_pos, std::string::npos, suffix) == 0) {
      filename->resize(filename->size() - suffix.size());
      return true;
    }
  }
  return false;
}

// Removes the given prefix from the string if present
// Returns true if prefix was found and removed, false otherwise
inline bool StripPrefix(std::string* name, const std::string& prefix) {
  if (name->length() >= prefix.length()) {
    if (name->substr(0, prefix.size()) == prefix) {
      *name = name->substr(prefix.size());
      return true;
    }
  }
  return false;
}

// Removes either ".proto" or ".protodevel" extension from filename
// Returns the stripped filename
inline std::string StripProto(std::string filename) {
  if (!StripSuffix(&filename, ".protodevel")) {
    StripSuffix(&filename, ".proto");
  }
  return filename;
}

// Replaces occurrences of 'from' with 'to' in the string 'str'
// If replace_all is false, only replaces the first occurrence
// Returns the modified string
inline std::string StringReplace(std::string str, const std::string& from,
                                 const std::string& to, bool replace_all) {
  size_t pos = 0;

  do {
    pos = str.find(from, pos);
    if (pos == std::string::npos) {
      break;
    }
    str.replace(pos, from.length(), to);
    pos += to.length();
  } while (replace_all);

  return str;
}

// Replaces all occurrences of 'from' with 'to' in the string 'str'
// Returns the modified string
inline std::string StringReplace(std::string str, const std::string& from,
                                 const std::string& to) {
  return StringReplace(str, from, to, true);
}

// Splits the input string into tokens using any of the characters in delimiters
// Returns a vector of tokens
inline std::vector<std::string> tokenize(const std::string& input,
                                         const std::string& delimiters) {
  std::vector<std::string> tokens;
  size_t pos, last_pos = 0;

  for (;;) {
    bool done = false;
    pos = input.find_first_of(delimiters, last_pos);
    if (pos == std::string::npos) {
      done = true;
      pos = input.length();
    }

    tokens.push_back(input.substr(last_pos, pos - last_pos));
    if (done) return tokens;

    last_pos = pos + 1;
  }
}

// Capitalizes the first letter of the string
// Returns the modified string
inline std::string CapitalizeFirstLetter(std::string s) {
  if (s.empty()) {
    return s;
  }
  s[0] = ::toupper(s[0]);
  return s;
}

// Lowercases the first letter of the string
// Returns the modified string
inline std::string LowercaseFirstLetter(std::string s) {
  if (s.empty()) {
    return s;
  }
  s[0] = ::tolower(s[0]);
  return s;
}

// Converts a string from lower_underscore_case to UpperCamelCase
// Returns the converted string
inline std::string LowerUnderscoreToUpperCamel(std::string str) {
  std::vector<std::string> tokens = tokenize(str, "_");
  std::string result = "";
  for (unsigned int i = 0; i < tokens.size(); i++) {
    result += CapitalizeFirstLetter(tokens[i]);
  }
  return result;
}

// Converts a proto file name to UpperCamelCase format
// include_package_path determines whether to include the full path or just the filename
// Returns the converted filename
inline std::string FileNameInUpperCamel(
    const grpc::protobuf::FileDescriptor* file, bool include_package_path) {
  std::vector<std::string> tokens =
      tokenize(StripProto(std::string(file->name())), "/");
  std::string result = "";
  if (include_package_path) {
    for (unsigned int i = 0; i < tokens.size() - 1; i++) {
      result += tokens[i] + "/";
    }
  }
  result += LowerUnderscoreToUpperCamel(tokens.back());
  return result;
}

// Converts a proto file name to UpperCamelCase format including the full path
// Returns the converted filename
inline std::string FileNameInUpperCamel(
    const grpc::protobuf::FileDescriptor* file) {
  return FileNameInUpperCamel(file, true);
}

// Enum representing different types of gRPC methods
enum MethodType {
  METHODTYPE_NO_STREAMING,         // Unary RPC
  METHODTYPE_CLIENT_STREAMING,     // Client streaming RPC
  METHODTYPE_SERVER_STREAMING,     // Server streaming RPC
  METHODTYPE_BIDI_STREAMING        // Bidirectional streaming RPC
};

// Determines the MethodType based on the method's streaming characteristics
// Returns the appropriate MethodType enum value
inline MethodType GetMethodType(
    const grpc::protobuf::MethodDescriptor* method) {
  if (method->client_streaming()) {
    if (method->server_streaming()) {
      return METHODTYPE_BIDI_STREAMING;
    } else {
      return METHODTYPE_CLIENT_STREAMING;
    }
  } else {
    if (method->server_streaming()) {
      return METHODTYPE_SERVER_STREAMING;
    } else {
      return METHODTYPE_NO_STREAMING;
    }
  }
}

// Splits a string by the specified delimiter and appends results to append_to
inline void Split(const std::string& s, char delimiter,
                  std::vector<std::string>* append_to) {
  std::istringstream iss(s);
  std::string piece;
  while (std::getline(iss, piece, delimiter)) {
    append_to->push_back(piece);
  }
}

// Enum representing different types of comments in proto files
enum CommentType {
  COMMENTTYPE_LEADING,            // Comments before the declaration
  COMMENTTYPE_TRAILING,           // Comments after the declaration
  COMMENTTYPE_LEADING_DETACHED    // Detached comments before the declaration
};

// Gets comments of the specified type from a proto descriptor
// Stores the comments line by line in the out vector
template <typename DescriptorType>
inline void GetComment(const DescriptorType* desc, CommentType type,
                       std::vector<std::string>* out) {
  grpc::protobuf::SourceLocation location;
  if (!desc->GetSourceLocation(&location)) {
    return;
  }
  if (type == COMMENTTYPE_LEADING || type == COMMENTTYPE_TRAILING) {
    const std::string& comments = type == COMMENTTYPE_LEADING
                                      ? location.leading_comments
                                      : location.trailing_comments;
    Split(comments, '\n', out);
  } else if (type == COMMENTTYPE_LEADING_DETACHED) {
    for (unsigned int i = 0; i < location.leading_detached_comments.size();
         i++) {
      Split(location.leading_detached_comments[i], '\n', out);
      out->push_back("");
    }
  } else {
    std::cerr << "Unknown comment type " << type << std::endl;
    abort();
  }
}

// Specialization of GetComment for FileDescriptor
template <>
inline void GetComment(const grpc::protobuf::FileDescriptor* desc,
                       CommentType type, std::vector<std::string>* out) {
  if (type == COMMENTTYPE_TRAILING) {
    return;
  }
  grpc::protobuf::SourceLocation location;
  std::vector<int> path;
  path.push_back(grpc::protobuf::FileDescriptorProto::kSyntaxFieldNumber);
  if (!desc->GetSourceLocation(path, &location)) {
    return;
  }
  if (type == COMMENTTYPE_LEADING) {
    Split(location.leading_comments, '\n', out);
  } else if (type == COMMENTTYPE_LEADING_DETACHED) {
    for (unsigned int i = 0; i < location.leading_detached_comments.size();
         i++) {
      Split(location.leading_detached_comments[i], '\n', out);
      out->push_back("");
    }
  } else {
    std::cerr << "Unknown comment type " << type << std::endl;
    abort();
  }
}

// Generates formatted comments with the given prefix
// Returns the formatted comments as a string
inline std::string GenerateCommentsWithPrefix(
    const std::vector<std::string>& in, const std::string& prefix) {
  std::ostringstream oss;
  for (auto it = in.begin(); it != in.end(); it++) {
    const std::string& elem = *it;
    if (elem.empty()) {
      oss << prefix << "\n";
    } else if (elem[0] == ' ') {
      oss << prefix << EscapeVariableDelimiters(elem) << "\n";
    } else {
      oss << prefix << " " << EscapeVariableDelimiters(elem) << "\n";
    }
  }
  return oss.str();
}

// Gets comments from a descriptor and formats them with the given prefix
// If leading is true, includes both leading and leading detached comments
// Returns the formatted comments as a string
template <typename DescriptorType>
inline std::string GetPrefixedComments(const DescriptorType* desc, bool leading,
                                       const std::string& prefix) {
  std::vector<std::string> out;
  if (leading) {
    grpc_generator::GetComment(
        desc, grpc_generator::COMMENTTYPE_LEADING_DETACHED, &out);
    std::vector<std::string> leading;
    grpc_generator::GetComment(desc, grpc_generator::COMMENTTYPE_LEADING,
                               &leading);
    out.insert(out.end(), leading.begin(), leading.end());
  } else {
    grpc_generator::GetComment(desc, grpc_generator::COMMENTTYPE_TRAILING,
                               &out);
  }
  return GenerateCommentsWithPrefix(out, prefix);
}

}  // namespace grpc_generator

#endif  // GRPC_INTERNAL_COMPILER_GENERATOR_HELPERS_H
```