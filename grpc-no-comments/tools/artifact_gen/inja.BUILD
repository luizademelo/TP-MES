# Copyright 2025 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

licenses(["notice"])

cc_library(
    name = "inja",
    hdrs = ["include/inja/inja.hpp"],
    visibility = ["//visibility:public"],
    deps = [":internal", "@nlohmann_json//:json"],
)

cc_library(
    name = "internal",
    includes = ["include"],
    textual_hdrs = glob(
        ["include/inja/*.hpp"],
        exclude = ["include/inja/inja.hpp"],
    ),
    deps = ["@nlohmann_json//:json"]
)
