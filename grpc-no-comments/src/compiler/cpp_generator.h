
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

#ifndef GRPC_INTERNAL_COMPILER_CPP_GENERATOR_H
#define GRPC_INTERNAL_COMPILER_CPP_GENERATOR_H

#include <memory>
#include <string>
#include <vector>

#include "src/compiler/config.h"
#include "src/compiler/schema_interface.h"

#ifdef GRPC_CUSTOM_STRING
#warning GRPC_CUSTOM_STRING is no longer supported. Please use std::string.
#endif

namespace grpc {

using std::string;
using std::to_string;

}

namespace grpc_cpp_generator {

struct Parameters {

  std::string services_namespace;

  bool use_system_headers;

  std::string grpc_search_path;

  bool generate_mock_code;

  std::string gmock_search_path;

  std::vector<std::string> additional_header_includes;

  std::string message_header_extension;

  bool include_import_headers;

  bool allow_sync_server_api;

  bool allow_cq_api;

  bool allow_deprecated;
};

std::string GetHeaderPrologue(grpc_generator::File* file,
                              const Parameters& params);

std::string GetHeaderIncludes(grpc_generator::File* file,
                              const Parameters& params);

std::string GetSourceIncludes(grpc_generator::File* file,
                              const Parameters& params);

std::string GetHeaderEpilogue(grpc_generator::File* file,
                              const Parameters& params);

std::string GetSourcePrologue(grpc_generator::File* file,
                              const Parameters& params);

std::string GetHeaderServices(grpc_generator::File* file,
                              const Parameters& params);

std::string GetSourceServices(grpc_generator::File* file,
                              const Parameters& params);

std::string GetSourceEpilogue(grpc_generator::File* file,
                              const Parameters& params);

std::string GetMockPrologue(grpc_generator::File* file,
                            const Parameters& params);

std::string GetMockIncludes(grpc_generator::File* file,
                            const Parameters& params);

std::string GetMockServices(grpc_generator::File* file,
                            const Parameters& params);

std::string GetMockEpilogue(grpc_generator::File* file,
                            const Parameters& params);

std::string GetMockPrologue(grpc_generator::File* file,
                            const Parameters& params);

std::string GetMockIncludes(grpc_generator::File* file,
                            const Parameters& params);

std::string GetMockServices(grpc_generator::File* file,
                            const Parameters& params);

std::string GetMockEpilogue(grpc_generator::File* file,
                            const Parameters& params);

}

#endif
