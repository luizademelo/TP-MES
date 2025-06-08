Here's the commented version of the code:

```c++
# Copyright 2015 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
"""A setup module for the gRPC Python package."""

# Import required modules
import multiprocessing  # For process-based parallelism
import os  # For OS path operations
import os.path  # For path manipulations
import sys  # For system-specific parameters and functions

# Import gRPC specific modules
import grpc_tools.command  # gRPC tools for protocol buffer compilation
import setuptools  # Package setup utilities

# Check if running under Python 3
PY3 = sys.version_info.major == 3

# Change to the directory containing this setup.py file
# Ensures consistent behavior whether run directly or via pip
os.chdir(os.path.dirname(os.path.abspath(__file__)))

# Import local modules (breaking style convention to ensure in-repo dependencies are found)
import commands  # Custom build/test commands
import grpc_version  # Version information for gRPC

# Package metadata
LICENSE = "Apache License 2.0"

# Directory structure configuration for package distribution
PACKAGE_DIRECTORIES = {
    "": ".",  # Root package directory
}

# List of required dependencies with version specifications
INSTALL_REQUIRES = (
    "coverage>=4.0",  # Code coverage tool
    "grpcio>={version}".format(version=grpc_version.VERSION),  # Core gRPC package
    "grpcio-channelz>={version}".format(version=grpc_version.VERSION),  # Channel monitoring
    "grpcio-status>={version}".format(version=grpc_version.VERSION),  # Status handling
    "grpcio-tools>={version}".format(version=grpc_version.VERSION),  # Protocol buffer tools
    "grpcio-health-checking>={version}".format(version=grpc_version.VERSION),  # Health checking
    "grpcio-observability>={version}".format(version=grpc_version.VERSION),  # Observability
    "xds-protos>={version}".format(version=grpc_version.VERSION),  # xDS protocol definitions
    "oauth2client>=1.4.7",  # OAuth2 client
    "protobuf>=6.30.0,<7.0.0",  # Protocol buffers
    "google-auth>=1.17.2",  # Google authentication
    "requests>=2.14.2",  # HTTP requests
    "absl-py>=1.4.0",  # Abseil Python utilities
)

# Custom command classes for setup.py
COMMAND_CLASS = {
    # Run `preprocess` *before* doing any packaging!
    "preprocess": commands.GatherProto,  # Gather protocol buffer files
    "build_package_protos": grpc_tools.command.BuildPackageProtos,  # Build protos
    "build_py": commands.BuildPy,  # Custom Python build
    "run_fork": commands.RunFork,  # Run tests in forked processes
    "run_interop": commands.RunInterop,  # Run interoperability tests
    "test_lite": commands.TestLite,  # Lightweight test suite
    "test_aio": commands.TestAio,  # AsyncIO tests
    "test_py3_only": commands.TestPy3Only,  # Python3-only tests
}

# Non-Python files to include in packages
PACKAGE_DATA = {
    "tests.interop": [  # Interoperability test credentials
        "credentials/ca.pem",
        "credentials/server1.key",
        "credentials/server1.pem",
    ],
    "tests.protoc_plugin.protos.invocation_testing": [  # Test protocol buffers
        "same.proto",
        "compiler.proto",
    ],
    "tests.protoc_plugin.protos.invocation_testing.split_messages": [
        "messages.proto",
    ],
    "tests.protoc_plugin.protos.invocation_testing.split_services": [
        "services.proto",
    ],
    "tests.testing.proto": [  # Testing protocol buffers
        "requests.proto",
        "services.proto",
    ],
    "tests.unit": [  # Unit test credentials
        "credentials/ca.pem",
        "credentials/server1.key",
        "credentials/server1.pem",
    ],
    "tests": ["tests.json"],  # Test configuration
}

# Test configuration
TEST_SUITE = "tests"  # Root test package
TEST_LOADER = "tests:Loader"  # Custom test loader
TEST_RUNNER = "tests:Runner"  # Custom test runner
TESTS_REQUIRE = INSTALL_REQUIRES  # Test dependencies (same as install requires)

# Find all Python packages in the project
PACKAGES = setuptools.find_packages(".")

# Main setup execution
if __name__ == "__main__":
    # Required for Windows support (freeze support for multiprocessing)
    multiprocessing.freeze_support()
    
    # Configure and run setuptools setup
    setuptools.setup(
        name="grpcio-tests",  # Package name
        version=grpc_version.VERSION,  # Version from grpc_version module
        license=LICENSE,  # License type
        packages=list(PACKAGES),  # List of all packages to include
        package_dir=PACKAGE_DIRECTORIES,  # Package directory mapping
        package_data=PACKAGE_DATA,  # Additional package data files
        install_requires=INSTALL_REQUIRES,  # Required dependencies
        cmdclass=COMMAND_CLASS,  # Custom commands
        tests_require=TESTS_REQUIRE,  # Test dependencies
        test_suite=TEST_SUITE,  # Test suite package
        test_loader=TEST_LOADER,  # Custom test loader
        test_runner=TEST_RUNNER,  # Custom test runner
    )
```