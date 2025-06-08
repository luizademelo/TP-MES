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
"""Setup module for the GRPC Python package's status mapping."""

import os

import setuptools

# Get the absolute path of the current package directory
_PACKAGE_PATH = os.path.realpath(os.path.dirname(__file__))
# Construct the path to the README file
_README_PATH = os.path.join(_PACKAGE_PATH, "README.rst")

# Change working directory to the directory containing this setup.py file
# This ensures consistent behavior whether run directly or via pip
os.chdir(os.path.dirname(os.path.abspath(__file__)))

# Import local modules (breaking typical import style to ensure we can find them)
import python_version  # Contains Python version compatibility information
import grpc_version    # Contains gRPC version information


class _NoOpCommand(setuptools.Command):
    """A no-operation command class for setuptools.
    
    This is used as a placeholder for commands we want to disable or make no-op.
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


# Define package classifiers for PyPI
CLASSIFIERS = (
    [
        "Development Status :: 5 - Production/Stable",
        "Programming Language :: Python",
        "Programming Language :: Python :: 3",
    ]
    # Add specific Python version classifiers for all supported versions
    + [
        f"Programming Language :: Python :: {x}"
        for x in python_version.SUPPORTED_PYTHON_VERSIONS
    ]
    + ["License :: OSI Approved :: Apache Software License"]
)

# Package directory configuration
PACKAGE_DIRECTORIES = {
    "": ".",  # Root package is in the current directory
}

# Package dependencies
INSTALL_REQUIRES = (
    "protobuf>=6.30.0,<7.0.0",  # Protocol Buffers dependency
    "grpcio>={version}".format(version=grpc_version.VERSION),  # gRPC core dependency
    "googleapis-common-protos>=1.5.5",  # Common Google API protos
)

try:
    # Try to import status_commands (only available in build environment)
    import status_commands as _status_commands

    # If successful, we're in the build environment - set up real commands
    COMMAND_CLASS = {
        # Run preprocessing before packaging
        "preprocess": _status_commands.Preprocess,
        # No-op for proto building (handled elsewhere)
        "build_package_protos": _NoOpCommand,
    }
except ImportError:
    # If status_commands isn't available (normal installation), use no-op commands
    COMMAND_CLASS = {
        "preprocess": _NoOpCommand,  # No-op preprocessing
        "build_package_protos": _NoOpCommand,  # No-op proto building
    }

# Main package configuration using setuptools
setuptools.setup(
    name="grpcio-status",  # Package name
    version=grpc_version.VERSION,  # Version from grpc_version module
    description="Status proto mapping for gRPC",  # Short description
    long_description=open(_README_PATH, "r").read(),  # Long description from README
    author="The gRPC Authors",
    author_email="grpc-io@googlegroups.com",
    url="https://grpc.io",  # Project URL
    license="Apache License 2.0",
    classifiers=CLASSIFIERS,  # PyPI classifiers defined above
    package_dir=PACKAGE_DIRECTORIES,  # Package directory configuration
    packages=setuptools.find_packages("."),  # Find all packages in current directory
    python_requires=f">={python_version.MIN_PYTHON_VERSION}",  # Minimum Python version
    install_requires=INSTALL_REQUIRES,  # Dependencies defined above
    cmdclass=COMMAND_CLASS,  # Command class configuration (build/no-op)
)
```