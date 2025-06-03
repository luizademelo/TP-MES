Here's the commented version of the code:

```c++
/*
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
 */

#ifndef GRPC_INTERNAL_COMPILER_OBJECTIVE_C_GENERATOR_HELPERS_H
#define GRPC_INTERNAL_COMPILER_OBJECTIVE_C_GENERATOR_HELPERS_H

#include <google/protobuf/compiler/objectivec/names.h>
#include <map>
#include "src/compiler/config.h"
#include "src/compiler/generator_helpers.h"

namespace grpc_objective_c_generator {

using ::grpc::protobuf::FileDescriptor;
using ::grpc::protobuf::MethodDescriptor;
using ::grpc::protobuf::ServiceDescriptor;

// Returns the header file name for a protocol buffer message by combining
// the file path with the standard Objective-C protobuf header suffix
inline std::string MessageHeaderName(const FileDescriptor* file) {
  return google::protobuf::compiler::objectivec::FilePath(file) + ".pbobjc.h";
}

// Checks if a character is an uppercase ASCII letter
inline bool AsciiIsUpper(char c) { return c >= 'A' && c <= 'Z'; }

// Generates the appropriate class name for a service, considering the file's
// class prefix and service name. Handles cases where the service name might
// already start with the prefix.
inline ::std::string ServiceClassName(const ServiceDescriptor* service) {
  const FileDescriptor* file = service->file();
  ::std::string prefix =
      google::protobuf::compiler::objectivec::FileClassPrefix(file);
  ::std::string class_name(service->name());

  if (class_name.rfind(prefix, 0) == 0) {
    if (class_name.length() == prefix.length() ||
        !AsciiIsUpper(class_name[prefix.length()])) {
      return prefix + class_name;
    } else {
      return class_name;
    }
  } else {
    return prefix + class_name;
  }
}

// Generates a local import statement for Objective-C (using quotes)
inline ::std::string LocalImport(const ::std::string& import) {
  return ::std::string("#import \"" + import + "\"\n");
}

// Generates a framework import statement for Objective-C (using angle brackets)
// Extracts the filename from the full import path
inline ::std::string FrameworkImport(const ::std::string& import,
                                     const ::std::string& framework) {
  std::size_t pos = import.rfind("/");
  ::std::string filename = import.substr(pos + 1, import.size() - (pos + 1));
  return ::std::string("#import <" + framework + "/" + filename + ">\n");
}

// Generates a system import statement for Objective-C (using angle brackets)
inline ::std::string SystemImport(const ::std::string& import) {
  return ::std::string("#import <" + import + ">\n");
}

// Generates a preprocessor conditional expression
// If invert is true, creates a "not defined" condition
inline ::std::string PreprocConditional(::std::string symbol, bool invert) {
  return invert ? "!defined(" + symbol + ") || !" + symbol
                : "defined(" + symbol + ") && " + symbol;
}

// Generates a complete #if preprocessor directive block
inline ::std::string PreprocIf(const ::std::string& symbol,
                               const ::std::string& if_true) {
  return ::std::string("#if " + PreprocConditional(symbol, false) + "\n" +
                       if_true + "#endif\n");
}

// Generates a complete #if not preprocessor directive block
inline ::std::string PreprocIfNot(const ::std::string& symbol,
                                  const ::std::string& if_true) {
  return ::std::string("#if " + PreprocConditional(symbol, true) + "\n" +
                       if_true + "#endif\n");
}

// Generates a complete #if-#else preprocessor directive block
inline ::std::string PreprocIfElse(const ::std::string& symbol,
                                   const ::std::string& if_true,
                                   const ::std::string& if_false) {
  return ::std::string("#if " + PreprocConditional(symbol, false) + "\n" +
                       if_true + "#else\n" + if_false + "#endif\n");
}

// Generates a complete #if not-#else preprocessor directive block
inline ::std::string PreprocIfNotElse(const ::std::string& symbol,
                                      const ::std::string& if_true,
                                      const ::std::string& if_false) {
  return ::std::string("#if " + PreprocConditional(symbol, true) + "\n" +
                       if_true + "#else\n" + if_false + "#endif\n");
}

// Determines whether a method should be included in the generated code
// By default includes all methods, unless OBJC_SKIP_METHODS_WITHOUT_MESSAGE_PREFIX
// is defined and the method's input/output types don't have class prefixes
inline bool ShouldIncludeMethod(const MethodDescriptor* method) {
#ifdef OBJC_SKIP_METHODS_WITHOUT_MESSAGE_PREFIX
  return (method->input_type()->file()->options().has_objc_class_prefix() &&
          method->output_type()->file()->options().has_objc_class_prefix());
#else
  (void)method;
  return true;
#endif
}

}  // namespace grpc_objective_c_generator
#endif  // GRPC_INTERNAL_COMPILER_OBJECTIVE_C_GENERATOR_HELPERS_H
```

The comments explain:
1. The purpose of each function
2. The parameters they accept
3. What they return
4. Any special logic or edge cases they handle
5. Configuration options that affect behavior (like OBJC_SKIP_METHODS_WITHOUT_MESSAGE_PREFIX)
6. The overall organization of the helper functions for Objective-C code generation

The comments are concise yet informative, helping future maintainers understand the code's purpose without being overly verbose. They follow a consistent style and explain both what the code does and why it does it in key places.