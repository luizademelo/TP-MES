Here's the commented version of the code:

```c++
# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import os
import sys

from grpc_tools import protoc
import setuptools

# Handle different import paths for resources based on Python version
if sys.version_info >= (3, 9, 0):
    from importlib import resources
else:
    import pkg_resources

def _get_resource_file_name(
    package_or_requirement: str, resource_name: str
) -> str:
    """Obtain the filename for a resource on the file system.
    
    Args:
        package_or_requirement: The package name or requirement string
        resource_name: The name of the resource within the package
        
    Returns:
        str: The absolute filesystem path to the resource
    """
    file_name = None
    # Use importlib.resources for Python 3.9+ (modern approach)
    if sys.version_info >= (3, 9, 0):
        file_name = (
            resources.files(package_or_requirement) / resource_name
        ).resolve()
    # Fall back to pkg_resources for older Python versions
    else:
        file_name = pkg_resources.resource_filename(
            package_or_requirement, resource_name
        )
    return str(file_name)

def build_package_protos(package_root, strict_mode=False):
    """Build protobuf modules by compiling .proto files.
    
    Args:
        package_root: Root directory containing .proto files
        strict_mode: If True, raises exception on compilation failure.
                     If False, only prints warning.
    """
    # Find all .proto files recursively in package_root
    proto_files = []
    inclusion_root = os.path.abspath(package_root)
    for root, _, files in os.walk(inclusion_root):
        for filename in files:
            if filename.endswith(".proto"):
                proto_files.append(
                    os.path.abspath(os.path.join(root, filename))
                )

    # Get include path for well-known protobuf types
    well_known_protos_include = _get_resource_file_name("grpc_tools", "_proto")

    # Compile each proto file
    for proto_file in proto_files:
        command = [
            "grpc_tools.protoc",
            "--proto_path={}".format(inclusion_root),  # Proto file search path
            "--proto_path={}".format(well_known_protos_include),  # Well-known types path
            "--python_out={}".format(inclusion_root),  # Output directory for _pb2.py
            "--pyi_out={}".format(inclusion_root),  # Output directory for .pyi
            "--grpc_python_out={}".format(inclusion_root),  # Output directory for _pb2_grpc.py
        ] + [proto_file]  # The proto file to compile
        
        # Run protoc compiler and handle result
        if protoc.main(command) != 0:
            if strict_mode:
                raise Exception("error: {} failed".format(command))
            else:
                sys.stderr.write("warning: {} failed".format(command))

class BuildPackageProtos(setuptools.Command):
    """Command to generate project *_pb2.py modules from proto files.
    
    This is a setuptools Command class that can be used in setup.py to
    add a custom command for compiling protobuf files during package setup.
    """

    description = "build grpc protobuf modules"
    user_options = [
        (
            "strict-mode",
            "s",
            "exit with non-zero value if the proto compiling fails.",
        )
    ]

    def initialize_options(self):
        """Initialize command options."""
        self.strict_mode = False

    def finalize_options(self):
        """Finalize command options (no-op in this implementation)."""
        pass

    def run(self):
        """Execute the command by compiling all proto files."""
        build_package_protos(
            self.distribution.package_dir[""], self.strict_mode
        )
```