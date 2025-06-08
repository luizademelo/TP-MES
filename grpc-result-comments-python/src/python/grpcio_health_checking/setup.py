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
"""Setup module for the GRPC Python package's optional health checking."""

import os
import setuptools

# Get the absolute path of the current package directory
_PACKAGE_PATH = os.path.realpath(os.path.dirname(__file__))
# Construct the path to the README file
_README_PATH = os.path.join(_PACKAGE_PATH, "README.rst")

# Ensure the working directory is set to the directory containing this setup file
os.chdir(os.path.dirname(os.path.abspath(__file__)))

# Import local modules (breaking typical import style to ensure they can be found)
import python_version  # Contains Python version compatibility information
import grpc_version    # Contains gRPC version information


class _NoOpCommand(setuptools.Command):
    """A no-operation command class for setuptools.
    
    This is used as a fallback when certain build commands aren't available
    in the current environment.
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
    # Add classifiers for each supported Python version
    + [
        f"Programming Language :: Python :: {x}"
        for x in python_version.SUPPORTED_PYTHON_VERSIONS
    ]
    + ["License :: OSI Approved :: Apache Software License"]
)

# Package directory configuration
PACKAGE_DIRECTORIES = {
    "": ".",  # Look for packages in the current directory
}

# Required dependencies for installation
INSTALL_REQUIRES = (
    "protobuf>=6.30.0,<7.0.0",  # Protocol Buffers dependency
    "grpcio>={version}".format(version=grpc_version.VERSION),  # gRPC core dependency
)

try:
    # Try to import health_commands which contains build-time commands
    import health_commands as _health_commands

    # If successful, we're in a build environment
    # Specify build-time dependencies
    SETUP_REQUIRES = (
        "grpcio-tools=={version}".format(version=grpc_version.VERSION),
    )
    # Configure custom build commands
    COMMAND_CLASS = {
        # Preprocess step before packaging
        "preprocess": _health_commands.Preprocess,
        # Build protocol buffers
        "build_package_protos": _health_commands.BuildPackageProtos,
    }
except ImportError:
    # If health_commands isn't available (normal installation environment)
    SETUP_REQUIRES = ()  # No special setup requirements
    COMMAND_CLASS = {
        # Provide no-op versions of the commands
        "preprocess": _NoOpCommand,
        "build_package_protos": _NoOpCommand,
    }

# Main setup configuration for the package
setuptools.setup(
    name="grpcio-health-checking",  # Package name
    version=grpc_version.VERSION,    # Version from grpc_version module
    description="Standard Health Checking Service for gRPC",
    long_description=open(_README_PATH, "r").read(),  # Read long description from README
    author="The gRPC Authors",
    author_email="grpc-io@googlegroups.com",
    url="https://grpc.io",  # Project homepage
    license="Apache License 2.0",
    classifiers=CLASSIFIERS,  # PyPI classifiers
    package_dir=PACKAGE_DIRECTORIES,  # Where to find packages
    packages=setuptools.find_packages("."),  # Auto-discover packages in current dir
    python_requires=f">={python_version.MIN_PYTHON_VERSION}",  # Python version requirement
    install_requires=INSTALL_REQUIRES,  # Runtime dependencies
    setup_requires=SETUP_REQUIRES,     # Build-time dependencies
    cmdclass=COMMAND_CLASS,            # Custom build commands
)
```