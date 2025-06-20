Here's the commented version of the code:

```python
#! /usr/bin/env python3
# Copyright 2021 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Builds the content of xds-protos package by compiling proto files to Python"""

import os
import sys

from grpc_tools import protoc  # For proto file compilation

# Handle different import methods based on Python version
if sys.version_info >= (3, 9, 0):
    from importlib import resources  # Modern resource access
else:
    import pkg_resources  # Legacy resource access

def localize_path(p: str) -> str:
    """Convert path with forward slashes to OS-specific path separator.
    Args:
        p: Path string with forward slashes
    Returns:
        Path with OS-specific separators
    """
    return os.path.join(*p.split("/"))

def _get_resource_file_name(
    package_or_requirement: str, resource_name: str
) -> str:
    """Obtain the filename for a resource on the file system.
    Args:
        package_or_requirement: Package name containing the resource
        resource_name: Name of the resource file
    Returns:
        Absolute path to the resource file
    """
    file_name = None
    if sys.version_info >= (3, 9, 0):
        # Modern Python resource access
        file_name = (
            resources.files(package_or_requirement) / resource_name
        ).resolve()
    else:
        # Legacy resource access
        file_name = pkg_resources.resource_filename(
            package_or_requirement, resource_name
        )
    return str(file_name)

# List of proto packages to exclude from compilation
EXCLUDE_PROTO_PACKAGES_LIST = tuple(
    localize_path(p)
    for p in (
        "envoy/service/metrics/v2",
        "envoy/service/metrics/v3",
        "envoy/service/metrics/v4alpha",
    )
)

# Path configuration for proto files and output
WORK_DIR = os.path.dirname(os.path.abspath(__file__))
GRPC_ROOT = os.path.abspath(os.path.join(WORK_DIR, "..", "..", "..", ".."))
ENVOY_API_PROTO_ROOT = os.path.join(GRPC_ROOT, "third_party", "envoy-api")
XDS_PROTO_ROOT = os.path.join(GRPC_ROOT, "third_party", "xds")
GOOGLEAPIS_ROOT = os.path.join(GRPC_ROOT, "third_party", "googleapis")
VALIDATE_ROOT = os.path.join(GRPC_ROOT, "third_party", "protoc-gen-validate")
OPENCENSUS_PROTO_ROOT = os.path.join(
    GRPC_ROOT, "third_party", "opencensus-proto", "src"
)
OPENTELEMETRY_PROTO_ROOT = os.path.join(GRPC_ROOT, "third_party", "opentelemetry")
WELL_KNOWN_PROTOS_INCLUDE = _get_resource_file_name("grpc_tools", "_proto")

OUTPUT_PATH = WORK_DIR  # Where to output generated files

# Test file configuration
TEST_FILE_NAME = "generated_file_import_test.py"
TEST_IMPORTS = []  # Accumulates import statements for test file

# Package initialization template for namespace packages
PKGUTIL_STYLE_INIT = (
    "__path__ = __import__('pkgutil').extend_path(__path__, __name__)\n"
)
# List of packages that should be namespace packages
NAMESPACE_PACKAGES = ["google"]

def add_test_import(proto_package_path: str, file_name: str, service: bool = False):
    """Add import statements to TEST_IMPORTS list for generated test file.
    Args:
        proto_package_path: Path to proto package
        file_name: Name of proto file
        service: Whether the proto file contains service definitions
    """
    TEST_IMPORTS.append(
        "from %s import %s\n"
        % (
            proto_package_path.replace("/", ".").replace("-", "_"),
            file_name.replace(".proto", "_pb2").replace("-", "_"),
        )
    )
    if service:
        TEST_IMPORTS.append(
            "from %s import %s\n"
            % (
                proto_package_path.replace("/", ".").replace("-", "_"),
                file_name.replace(".proto", "_pb2_grpc").replace("-", "_"),
            )
        )

# Base command for compiling proto files without gRPC services
COMPILE_PROTO_ONLY = [
    "grpc_tools.protoc",
    "--proto_path={}".format(ENVOY_API_PROTO_ROOT),
    "--proto_path={}".format(XDS_PROTO_ROOT),
    "--proto_path={}".format(GOOGLEAPIS_ROOT),
    "--proto_path={}".format(VALIDATE_ROOT),
    "--proto_path={}".format(WELL_KNOWN_PROTOS_INCLUDE),
    "--proto_path={}".format(OPENCENSUS_PROTO_ROOT),
    "--proto_path={}".format(OPENTELEMETRY_PROTO_ROOT),
    "--python_out={}".format(OUTPUT_PATH),
]
# Command for compiling proto files with gRPC services
COMPILE_BOTH = COMPILE_PROTO_ONLY + ["--grpc_python_out={}".format(OUTPUT_PATH)]

def has_grpc_service(proto_package_path: str) -> bool:
    """Check if proto package path contains gRPC service definitions.
    Args:
        proto_package_path: Path to proto package
    Returns:
        True if path is under envoy/service, False otherwise
    """
    return proto_package_path.startswith(os.path.join("envoy", "service"))

def compile_protos(proto_root: str, sub_dir: str = ".") -> None:
    """Compile all proto files in given directory tree.
    Args:
        proto_root: Root directory containing proto files
        sub_dir: Subdirectory to start compilation from
    Raises:
        Exception: If compilation fails or no proto files found
    """
    compiled_any = False
    # Walk through directory tree
    for root, _, files in os.walk(os.path.join(proto_root, sub_dir)):
        proto_package_path = os.path.relpath(root, proto_root)
        # Skip excluded packages
        if proto_package_path in EXCLUDE_PROTO_PACKAGES_LIST:
            print(f"Skipping package {proto_package_path}")
            continue
        # Process each proto file
        for file_name in files:
            if file_name.endswith(".proto"):
                compiled_any = True
                # Compile with gRPC services if needed
                if has_grpc_service(proto_package_path):
                    return_code = protoc.main(
                        COMPILE_BOTH + [os.path.join(root, file_name)]
                    )
                    add_test_import(proto_package_path, file_name, service=True)
                else:
                    return_code = protoc.main(
                        COMPILE_PROTO_ONLY + [os.path.join(root, file_name)]
                    )
                    add_test_import(proto_package_path, file_name, service=False)
                if return_code != 0:
                    raise Exception("error: {} failed".format(COMPILE_BOTH))

    # Sort imports for consistent test file generation
    TEST_IMPORTS.sort()
    if not compiled_any:
        raise Exception(
            "No proto files found at {}. Did you update git submodules?".format(
                proto_root, sub_dir
            )
        )

def create_init_file(path: str, package_path: str = "") -> None:
    """Create __init__.py file for Python package.
    Args:
        path: Directory where to create the file
        package_path: Relative package path for namespace package check
    """
    with open(os.path.join(path, "__init__.py"), "w") as f:
        # Create namespace package if needed
        if package_path in NAMESPACE_PACKAGES:
            f.write(PKGUTIL_STYLE_INIT)

def main():
    """Main function that coordinates proto compilation and package setup."""
    # Compile proto files from various sources
    compile_protos(ENVOY_API_PROTO_ROOT)
    compile_protos(XDS_PROTO_ROOT)

    # Compile specific Google API proto packages
    compile_protos(GOOGLEAPIS_ROOT, os.path.join("google", "api"))
    compile_protos(GOOGLEAPIS_ROOT, os.path.join("google", "rpc"))
    compile_protos(GOOGLEAPIS_ROOT, os.path.join("google", "longrunning"))
    compile_protos(GOOGLEAPIS_ROOT, os.path.join("google", "logging"))
    compile_protos(GOOGLEAPIS_ROOT, os.path.join("google", "type"))
    
    # Compile other third-party proto files
    compile_protos(VALIDATE_ROOT, "validate")
    compile_protos(OPENCENSUS_PROTO_ROOT)
    compile_protos(OPENTELEMETRY_PROTO_ROOT)

    # Create package __init__.py files
    create_init_file(WORK_DIR)
    for proto_root_module in [
        "envoy",
        "google",
        "opencensus",
        "udpa",
        "validate",
        "xds",
        "opentelemetry",
    ]:
        for root, _, _ in os.walk(os.path.join(WORK_DIR, proto_root_module)):
            package_path = os.path.relpath(root, WORK_DIR)
            create_init_file(root, package_path)

    # Generate test file with all imports
    with open(os.path.join(WORK_DIR, TEST_FILE_NAME), "w") as f:
        f.writelines(TEST_IMPORTS)

if __name__ == "__main__":
    main()
```