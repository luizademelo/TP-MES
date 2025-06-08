Here's the commented version of the code:

```c++
# Copyright 2018 The gRPC Authors
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
"""Setup module for the GRPC Python package's Channelz."""

import os
import sys

import setuptools

# Get the absolute path of the current package directory
_PACKAGE_PATH = os.path.realpath(os.path.dirname(__file__))
# Construct the path to the README file
_README_PATH = os.path.join(_PACKAGE_PATH, "README.rst")

# Change working directory to the directory containing this setup.py file
# This ensures consistent behavior whether run directly or via pip
os.chdir(os.path.dirname(os.path.abspath(__file__)))

# Import local modules by breaking typical import style
# This is done to ensure we can find our local modules regardless of how the script is run
import python_version
import grpc_version


class _NoOpCommand(setuptools.Command):
    """A no-operation command class for setuptools.
    
    This is used as a fallback when certain build commands aren't available
    in the current environment, preventing build failures while maintaining
    compatibility with external dependencies.
    """
    description = ""
    user_options = []

    def initialize_options(self):
        """Initialize command options (no-op)."""
        pass

    def finalize_options(self):
        """Finalize command options (no-op)."""
        pass

    def run(self):
        """Execute the command (no-op)."""
        pass


# Package metadata classifiers for PyPI
CLASSIFIERS = (
    [
        "Development Status :: 5 - Production/Stable",
        "Programming Language :: Python",
        "Programming Language :: Python :: 3",
    ]
    + [
        # Add classifiers for each supported Python version
        f"Programming Language :: Python :: {x}"
        for x in python_version.SUPPORTED_PYTHON_VERSIONS
    ]
    + ["License :: OSI Approved :: Apache Software License"]
)

# Package directory configuration
PACKAGE_DIRECTORIES = {
    "": ".",  # Root package is in the current directory
}

# Package dependencies required for installation
INSTALL_REQUIRES = (
    "protobuf>=6.30.0,<7.0.0",  # Protocol Buffers dependency
    "grpcio>={version}".format(version=grpc_version.VERSION),  # gRPC core dependency
)

try:
    # Try to import build-specific commands
    import channelz_commands as _channelz_commands

    # If successful, we're in the build environment
    # Set up build-time dependencies
    SETUP_REQUIRES = (
        "grpcio-tools=={version}".format(version=grpc_version.VERSION),
    )
    # Configure custom build commands
    COMMAND_CLASS = {
        # Preprocess step runs before packaging
        "preprocess": _channelz_commands.Preprocess,
        # Protobuf compilation step
        "build_package_protos": _channelz_commands.BuildPackageProtos,
    }
except ImportError:
    # If we're not in the build environment (e.g., during user installation)
    # Use no-op commands and no additional setup requirements
    SETUP_REQUIRES = ()
    COMMAND_CLASS = {
        # Replace build commands with no-op versions
        "preprocess": _NoOpCommand,
        "build_package_protos": _NoOpCommand,
    }


# Main package configuration using setuptools
setuptools.setup(
    name="grpcio-channelz",  # Package name
    version=grpc_version.VERSION,  # Version from grpc_version module
    license="Apache License 2.0",
    description="Channel Level Live Debug Information Service for gRPC",
    long_description=open(_README_PATH, "r").read(),  # Read long description from README
    author="The gRPC Authors",
    author_email="grpc-io@googlegroups.com",
    classifiers=CLASSIFIERS,  # Package metadata classifiers
    url="https://grpc.io",  # Project URL
    package_dir=PACKAGE_DIRECTORIES,  # Package directory configuration
    packages=setuptools.find_packages("."),  # Auto-discover packages in current directory
    python_requires=f">={python_version.MIN_PYTHON_VERSION}",  # Minimum Python version
    install_requires=INSTALL_REQUIRES,  # Runtime dependencies
    setup_requires=SETUP_REQUIRES,  # Build-time dependencies
    cmdclass=COMMAND_CLASS,  # Custom build commands
)
```