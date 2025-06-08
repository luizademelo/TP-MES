Here's the commented version of the code:

```c++
# Copyright 2016 gRPC authors.
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
"""Setup module for the GRPC Python package's optional reflection."""

import os
import sys

import setuptools

# Get the absolute path of the current package directory
_PACKAGE_PATH = os.path.realpath(os.path.dirname(__file__))
# Construct the path to the README file
_README_PATH = os.path.join(_PACKAGE_PATH, "README.rst")

# Ensure we're in the proper directory whether or not we're being used by pip.
os.chdir(os.path.dirname(os.path.abspath(__file__)))

# Import local modules by breaking import style to ensure we can find them
import python_version
import grpc_version


class _NoOpCommand(setuptools.Command):
    """No-op command used as a placeholder when certain build commands aren't available."""
    description = ""
    user_options = []

    def initialize_options(self):
        """Initialize options for the command (no-op)."""
        pass

    def finalize_options(self):
        """Finalize options for the command (no-op)."""
        pass

    def run(self):
        """Run the command (no-op)."""
        pass


# Define package classifiers for PyPI
CLASSIFIERS = (
    [
        "Development Status :: 5 - Production/Stable",
        "Programming Language :: Python",
        "Programming Language :: Python :: 3",
    ]
    + [
        f"Programming Language :: Python :: {x}"
        for x in python_version.SUPPORTED_PYTHON_VERSIONS  # Add all supported Python versions
    ]
    + ["License :: OSI Approved :: Apache Software License"]
)

# Package directory configuration
PACKAGE_DIRECTORIES = {
    "": ".",  # Root package directory is the current directory
}

# Package dependencies required for installation
INSTALL_REQUIRES = (
    "protobuf>=6.30.0,<7.0.0",  # Protobuf version constraint
    "grpcio>={version}".format(version=grpc_version.VERSION),  # gRPC version constraint
)

try:
    # Try to import reflection commands (only available in build environment)
    import reflection_commands as _reflection_commands

    # If successful, we're in the build environment
    SETUP_REQUIRES = (
        "grpcio-tools=={version}".format(version=grpc_version.VERSION),  # Build-time dependency
    )
    COMMAND_CLASS = {
        # Command to run preprocessing before packaging
        "preprocess": _reflection_commands.Preprocess,
        # Command to build protocol buffers
        "build_package_protos": _reflection_commands.BuildPackageProtos,
    }
except ImportError:
    # If reflection commands aren't available (normal installation case)
    SETUP_REQUIRES = ()  # No special setup requirements
    COMMAND_CLASS = {
        # Provide no-op versions of commands to maintain interface
        "preprocess": _NoOpCommand,
        "build_package_protos": _NoOpCommand,
    }

# Main setup configuration for the package
setuptools.setup(
    name="grpcio-reflection",  # Package name
    version=grpc_version.VERSION,  # Package version
    license="Apache License 2.0",  # Software license
    description="Standard Protobuf Reflection Service for gRPC",  # Short description
    long_description=open(_README_PATH, "r").read(),  # Long description from README
    author="The gRPC Authors",  # Author information
    author_email="grpc-io@googlegroups.com",  # Author email
    classifiers=CLASSIFIERS,  # Package classifiers
    url="https://grpc.io",  # Project URL
    package_dir=PACKAGE_DIRECTORIES,  # Package directory configuration
    packages=setuptools.find_packages("."),  # Automatically find packages
    python_requires=f">={python_version.MIN_PYTHON_VERSION}",  # Python version requirement
    install_requires=INSTALL_REQUIRES,  # Installation dependencies
    setup_requires=SETUP_REQUIRES,  # Setup-time dependencies
    cmdclass=COMMAND_CLASS,  # Custom commands configuration
)
```