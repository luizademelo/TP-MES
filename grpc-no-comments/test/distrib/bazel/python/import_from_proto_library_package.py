# Copyright 2021 the gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""A trivial executable that imports Protobuf generated code where the
proto_library and py_proto_library are in different Bazel packages.
"""

import in_subpackage.subpackage_pb2
