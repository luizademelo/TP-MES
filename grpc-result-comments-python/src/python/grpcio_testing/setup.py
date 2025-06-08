Here's the commented version of the code:

```c++
# Copyright 2017 gRPC authors.
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
"""Setup module for gRPC Python's testing package."""

# Import required standard library modules
import os
import sys

# Import setuptools for package setup functionality
import setuptools

# Define paths for package directory and README file
_PACKAGE_PATH = os.path.realpath(os.path.dirname(__file__))
_README_PATH = os.path.join(_PACKAGE_PATH, "README.rst")

# Change working directory to the directory containing this setup file
# This ensures consistent behavior whether run directly or via pip
os.chdir(os.path.dirname(os.path.abspath(__file__)))

# Import grpc_version module from the same directory
# Breaking normal import style to ensure local module can be found
import grpc_version


class _NoOpCommand(setuptools.Command):
    """A dummy setuptools command that does nothing.
    
    This is used as a fallback when certain commands aren't available
    in the current environment.
    """
    description = ""
    user_options = []

    def initialize_options(self):
        """Required by setuptools but does nothing in this no-op implementation."""
        pass

    def finalize_options(self):
        """Required by setuptools but does nothing in this no-op implementation."""
        pass

    def run(self):
        """Required by setuptools but does nothing in this no-op implementation."""
        pass


# Package directory configuration
PACKAGE_DIRECTORIES = {
    "": ".",  # Root package is in the current directory
}

# Package dependencies specification
INSTALL_REQUIRES = (
    # Required protobuf version range
    "protobuf>=6.30.0,<7.0.0",
    # Required grpcio version matching current package version
    "grpcio>={version}".format(version=grpc_version.VERSION),
)

# Try to import testing-specific commands if available
try:
    import testing_commands as _testing_commands

    # If we're in a build environment (import succeeded), set up the preprocess command
    COMMAND_CLASS = {
        # Run preprocessing step before packaging
        "preprocess": _testing_commands.Preprocess,
    }
except ImportError:
    # If not in build environment (import failed), use no-op commands instead
    COMMAND_CLASS = {
        # Provide dummy preprocess command to maintain interface
        "preprocess": _NoOpCommand,
    }

# Main package configuration using setuptools
setuptools.setup(
    name="grpcio-testing",  # Package name
    version=grpc_version.VERSION,  # Version from grpc_version module
    license="Apache License 2.0",  # Software license
    description="Testing utilities for gRPC Python",  # Short description
    # Long description from README file
    long_description=open(_README_PATH, "r").read(),
    author="The gRPC Authors",  # Author information
    author_email="grpc-io@googlegroups.com",
    url="https://grpc.io",  # Project URL
    package_dir=PACKAGE_DIRECTORIES,  # Package directory configuration
    packages=setuptools.find_packages("."),  # Auto-discover packages
    install_requires=INSTALL_REQUIRES,  # Dependencies
    cmdclass=COMMAND_CLASS,  # Custom commands configuration
)
```