Here's the commented version of the code:

```c++
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Provides setuptools command classes for the GRPC Python setup process."""

import os
import shutil

import setuptools

# Root directory of the project
ROOT_DIR = os.path.abspath(os.path.dirname(os.path.abspath(__file__)))
# Path to the health proto file in the source tree
HEALTH_PROTO = os.path.join(ROOT_DIR, "../../proto/grpc/health/v1/health.proto")
# Path to the project LICENSE file
LICENSE = os.path.join(ROOT_DIR, "../../../LICENSE")

class Preprocess(setuptools.Command):
    """Command to copy proto modules from grpc/src/proto and LICENSE from
    the root directory"""

    # Brief description of the command
    description = ""
    # No user-configurable options for this command
    user_options = []

    def initialize_options(self):
        """Initialize command options (no-op as there are no options)"""
        pass

    def finalize_options(self):
        """Finalize command options (no-op as there are no options)"""
        pass

    def run(self):
        """Execute the preprocessing command:
        1. Copies health.proto file to package directory if it exists
        2. Copies LICENSE file to package directory if it exists
        """
        # TODO: Can skip copy proto part.
        # Copy health proto file if it exists
        if os.path.isfile(HEALTH_PROTO):
            shutil.copyfile(
                HEALTH_PROTO,
                os.path.join(ROOT_DIR, "grpc_health/v1/health.proto"),
            )
        # Copy LICENSE file if it exists
        if os.path.isfile(LICENSE):
            shutil.copyfile(LICENSE, os.path.join(ROOT_DIR, "LICENSE"))

class BuildPackageProtos(setuptools.Command):
    """Command to generate project *_pb2.py modules from proto files."""

    # Brief description of the command
    description = "build grpc protobuf modules"
    # No user-configurable options for this command
    user_options = []

    def initialize_options(self):
        """Initialize command options (no-op as there are no options)"""
        pass

    def finalize_options(self):
        """Finalize command options (no-op as there are no options)"""
        pass

    def run(self):
        """Execute the protobuf building command:
        Uses grpc_tools to compile all proto files into Python protobuf modules
        """
        from grpc_tools import command

        # Build all protobuf modules in the package directory
        command.build_package_protos(self.distribution.package_dir[""])
```