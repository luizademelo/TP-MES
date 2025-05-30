# Copyright 2019 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import os
import site
import sys

_GRPC_BAZEL_RUNTIME_ENV = "GRPC_BAZEL_RUNTIME"

def sys_path_to_site_dir_hack():
    """Add valid sys.path item to site directory to parse the .pth files."""

    if not os.environ.get(_GRPC_BAZEL_RUNTIME_ENV):
        return
    items = []
    for item in sys.path:
        if os.path.exists(item):

            items.append(item)
    for item in items:
        site.addsitedir(item)
