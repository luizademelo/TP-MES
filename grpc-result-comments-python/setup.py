I'll provide a commented version of this setup.py script. The comments will explain the key components and functionality while preserving the original code structure.

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
"""A setup module for the GRPC Python package."""

# NOTE(https://github.com/grpc/grpc/issues/24028): allow setuptools to monkey
# patch distutils
import setuptools  # isort:skip

# Monkey Patch the unix compiler to accept ASM files used by boring SSL.
# This adds support for .S assembly files to the UnixCCompiler
from distutils.unixccompiler import UnixCCompiler

UnixCCompiler.src_extensions.append(".S")
del UnixCCompiler

# Standard library imports
import os
import os.path
import pathlib
import platform
import re
import shlex
import shutil
import subprocess
from subprocess import PIPE
import sys
import sysconfig

# Local imports
import _metadata
from setuptools import Extension
from setuptools.command import egg_info

# Redirect the manifest template from MANIFEST.in to PYTHON-MANIFEST.in.
# This controls which non-Python files are included in the distribution
egg_info.manifest_maker.template = "PYTHON-MANIFEST.in"

# Python version check
PY3 = sys.version_info.major == 3
# Base directory for Python source files
PYTHON_STEM = os.path.join("src", "python", "grpcio")

# Include paths for various dependencies
CORE_INCLUDE = ("include", ".")
ABSL_INCLUDE = (os.path.join("third_party", "abseil-cpp"),)
ADDRESS_SORTING_INCLUDE = (os.path.join("third_party", "address_sorting", "include"),)
CARES_INCLUDE = (
    os.path.join("third_party", "cares", "cares", "include"),
    os.path.join("third_party", "cares"),
    os.path.join("third_party", "cares", "cares"),
)
# Platform-specific care config includes
if "darwin" in sys.platform:
    CARES_INCLUDE += (os.path.join("third_party", "cares", "config_darwin"),)
if "freebsd" in sys.platform:
    CARES_INCLUDE += (os.path.join("third_party", "cares", "config_freebsd"),)
if "linux" in sys.platform:
    CARES_INCLUDE += (os.path.join("third_party", "cares", "config_linux"),)
if "openbsd" in sys.platform:
    CARES_INCLUDE += (os.path.join("third_party", "cares", "config_openbsd"),)

# Additional dependency includes
RE2_INCLUDE = (os.path.join("third_party", "re2"),)
SSL_INCLUDE = (os.path.join("third_party", "boringssl-with-bazel", "src", "include"),)
UPB_INCLUDE = (os.path.join("third_party", "upb"),)
UPB_GRPC_GENERATED_INCLUDE = (os.path.join("src", "core", "ext", "upb-gen"),)
UPBDEFS_GRPC_GENERATED_INCLUDE = (os.path.join("src", "core", "ext", "upbdefs-gen"),)
UTF8_RANGE_INCLUDE = (os.path.join("third_party", "utf8_range"),)
XXHASH_INCLUDE = (os.path.join("third_party", "xxhash"),)
ZLIB_INCLUDE = (os.path.join("third_party", "zlib"),)

# Path to README file
README = os.path.join(PYTHON_STEM, "README.rst")

# Ensure we're in the proper directory whether or not we're being used by pip.
os.chdir(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.abspath(PYTHON_STEM))

# Import local modules after setting up paths
# These modules contain patches and helper functions
import _parallel_compile_patch
import _spawn_patch
import grpc_core_dependencies
import python_version

import commands
import grpc_version

# Apply patches for parallel compilation and spawn behavior
_parallel_compile_patch.monkeypatch_compile_maybe()
_spawn_patch.monkeypatch_spawn()

# Package metadata
LICENSE = "Apache License 2.0"

# Classifiers for PyPI
CLASSIFIERS = (
    [
        "Development Status :: 5 - Production/Stable",
        "Programming Language :: Python",
        "Programming Language :: Python :: 3",
    ]
    + [
        f"Programming Language :: Python :: {x}"
        for x in python_version.SUPPORTED_PYTHON_VERSIONS
    ]
    + ["License :: OSI Approved :: Apache Software License"]
)

def _env_bool_value(env_name, default):
    """Parses a bool option from an environment variable.
    Returns True unless the environment variable is set to FALSE, 0, or empty.
    """
    return os.environ.get(env_name, default).upper() not in ["FALSE", "0", ""]

# Build configuration flags from environment variables
BUILD_WITH_BORING_SSL_ASM = _env_bool_value(
    "GRPC_BUILD_WITH_BORING_SSL_ASM", "True"
)

# Platform override for boringssl assembly optimizations
BUILD_OVERRIDE_BORING_SSL_ASM_PLATFORM = os.environ.get(
    "GRPC_BUILD_OVERRIDE_BORING_SSL_ASM_PLATFORM", ""
)

# Cython build configuration
BUILD_WITH_CYTHON = _env_bool_value("GRPC_PYTHON_BUILD_WITH_CYTHON", "False")

# System library configuration flags
BUILD_WITH_SYSTEM_OPENSSL = _env_bool_value(
    "GRPC_PYTHON_BUILD_SYSTEM_OPENSSL", "False"
)
BUILD_WITH_SYSTEM_ZLIB = _env_bool_value(
    "GRPC_PYTHON_BUILD_SYSTEM_ZLIB", "False"
)
BUILD_WITH_SYSTEM_CARES = _env_bool_value(
    "GRPC_PYTHON_BUILD_SYSTEM_CARES", "False"
)
BUILD_WITH_SYSTEM_RE2 = _env_bool_value("GRPC_PYTHON_BUILD_SYSTEM_RE2", "False")
BUILD_WITH_SYSTEM_ABSL = os.environ.get("GRPC_PYTHON_BUILD_SYSTEM_ABSL", False)

# Static linking configuration
BUILD_WITH_STATIC_LIBSTDCXX = _env_bool_value(
    "GRPC_PYTHON_BUILD_WITH_STATIC_LIBSTDCXX", "False"
)

# Prebuilt core configuration
USE_PREBUILT_GRPC_CORE = _env_bool_value(
    "GRPC_PYTHON_USE_PREBUILT_GRPC_CORE", "False"
)

# Debugging and tracing configuration
ENABLE_CYTHON_TRACING = _env_bool_value(
    "GRPC_PYTHON_ENABLE_CYTHON_TRACING", "False"
)

# Documentation build configuration
ENABLE_DOCUMENTATION_BUILD = _env_bool_value(
    "GRPC_PYTHON_ENABLE_DOCUMENTATION_BUILD", "False"
)

def check_linker_need_libatomic():
    """Test if linker on system needs libatomic.
    Compiles a small C++ program using std::atomic to check if linking succeeds.
    """
    code_test = (
        b"#include <atomic>\n"
        + b"int main() { return std::atomic<int64_t>{}; }"
    )
    cxx = shlex.split(os.environ.get("CXX", "c++"))
    cpp_test = subprocess.Popen(
        cxx + ["-x", "c++", "-std=c++17", "-"],
        stdin=PIPE,
        stdout=PIPE,
        stderr=PIPE,
    )
    cpp_test.communicate(input=code_test)
    if cpp_test.returncode == 0:
        return False
    # Double-check with -latomic
    cpp_test = subprocess.Popen(
        cxx + ["-x", "c++", "-std=c++17", "-", "-latomic"],
        stdin=PIPE,
        stdout=PIPE,
        stderr=PIPE,
    )
    cpp_test.communicate(input=code_test)
    return cpp_test.returncode == 0

# macOS deployment target configuration
if sys.platform == "darwin":
    if "MACOSX_DEPLOYMENT_TARGET" not in os.environ:
        target_ver = sysconfig.get_config_var("MACOSX_DEPLOYMENT_TARGET")
        if target_ver == "" or tuple(int(p) for p in target_ver.split(".")) < (10, 14):
            os.environ["MACOSX_DEPLOYMENT_TARGET"] = "11.0"

# Compiler and linker flags configuration
EXTRA_ENV_COMPILE_ARGS = os.environ.get("GRPC_PYTHON_CFLAGS", None)
EXTRA_ENV_LINK_ARGS = os.environ.get("GRPC_PYTHON_LDFLAGS", None)
if EXTRA_ENV_COMPILE_ARGS is None:
    EXTRA_ENV_COMPILE_ARGS = ""
    if "win32" in sys.platform:
        # Windows-specific compiler flags
        EXTRA_ENV_COMPILE_ARGS += " /std:c++17"
        EXTRA_ENV_COMPILE_ARGS += " /std:c11"
        EXTRA_ENV_COMPILE_ARGS += " /MT"  # Static linking of C++ runtime
    elif "linux" in sys.platform:
        # Linux-specific compiler flags
        EXTRA_ENV_COMPILE_ARGS += " -std=c++17"
        EXTRA_ENV_COMPILE_ARGS += " -fvisibility=hidden -fno-wrapv -fno-exceptions"
    elif "darwin" in sys.platform:
        # macOS-specific compiler flags
        EXTRA_ENV_COMPILE_ARGS += " -std=c++17"
        EXTRA_ENV_COMPILE_ARGS += (
            " -stdlib=libc++ -fvisibility=hidden -fno-wrapv -fno-exceptions"
            " -DHAVE_UNISTD_H"
        )

if EXTRA_ENV_LINK_ARGS is None:
    EXTRA_ENV_LINK_ARGS = ""
    if "linux" in sys.platform or "darwin" in sys.platform:
        EXTRA_ENV_LINK_ARGS += " -lpthread"
        if check_linker_need_libatomic():
            EXTRA_ENV_LINK_ARGS += " -latomic"
    if "linux" in sys.platform:
        EXTRA_ENV_LINK_ARGS += " -static-libgcc"

# Additional macOS framework linkage
if "darwin" in sys.platform:
    EXTRA_ENV_LINK_ARGS += " -framework CoreFoundation"

# Process compiler and linker flags
EXTRA_COMPILE_ARGS = shlex.split(EXTRA_ENV_COMPILE_ARGS)
EXTRA_LINK_ARGS = shlex.split(EXTRA_ENV_LINK_ARGS)

# Static libstdc++ configuration
if BUILD_WITH_STATIC_LIBSTDCXX:
    EXTRA_LINK_ARGS.append("-static-libstdc++")

# Cython extension configuration
CYTHON_EXTENSION_PACKAGE_NAMES = ()
CYTHON_EXTENSION_MODULE_NAMES = ("grpc._cython.cygrpc",)
CYTHON_HELPER_C_FILES = ()

# Core C files configuration
CORE_C_FILES = tuple(grpc_core_dependencies.CORE_SOURCE_FILES)
if "win32" in sys.platform:
    CORE_C_FILES = filter(lambda x: "third_party/cares" not in x, CORE_C_FILES)

# System library configuration for core files
if BUILD_WITH_SYSTEM_OPENSSL:
    CORE_C_FILES = filter(lambda x: "third_party/boringssl" not in x, CORE_C_FILES)
    CORE_C_FILES = filter(lambda x: "src/boringssl" not in x, CORE_C_FILES)
    SSL_INCLUDE = (os.path.join("/usr", "include", "openssl"),)

if BUILD_WITH_SYSTEM_ZLIB:
    CORE_C_FILES = filter(lambda x: "third_party/zlib" not in x, CORE_C_FILES)
    ZLIB_INCLUDE = (os.path.join("/usr", "include"),)

if BUILD_WITH_SYSTEM_CARES:
    CORE_C_FILES = filter(lambda x: "third_party/cares" not in x, CORE_C_FILES)
    CARES_INCLUDE = (os.path.join("/usr", "include"),)

if BUILD_WITH_SYSTEM_RE2:
    CORE_C_FILES = filter(lambda x: "third_party/re2" not in x, CORE_C_FILES)
    RE2_INCLUDE = (os.path.join("/usr", "include", "re2"),)

if BUILD_WITH_SYSTEM_ABSL:
    CORE_C_FILES = filter(lambda x: "third_party/abseil-cpp" not in x, CORE_C_FILES)
    ABSL_INCLUDE = (os.path.join("/usr", "include"),)

# Combined include directories for extensions
EXTENSION_INCLUDE_DIRECTORIES = (
    (PYTHON_STEM,)
    + CORE_INCLUDE
    + ABSL_INCLUDE
    + ADDRESS_SORTING_INCLUDE
    + CARES_INCLUDE
    + RE2_INCLUDE
    + SSL_INCLUDE
    + UPB_INCLUDE
    + UPB_GRPC_GENERATED_INCLUDE
    + UPBDEFS_GRPC_GENERATED_INCLUDE
    + UTF8_RANGE_INCLUDE
    + XXHASH_INCLUDE
    + ZLIB_INCLUDE
)

# Libraries to link against
EXTENSION_LIBRARIES = ()
if "linux" in sys.platform:
    EXTENSION_LIBRARIES += ("rt",)  # realtime library
if not "win32" in sys.platform:
    EXTENSION_LIBRARIES += ("m",)  # math library
if "win32" in sys.platform:
    EXTENSION_LIBRARIES += (
        "advapi32",
        "bcrypt",
        "dbghelp",
        "ws2_32",
    )

# System library linkage configuration
if BUILD_WITH_SYSTEM_OPENSSL:
    EXTENSION_LIBRARIES += ("ssl", "crypto")
if BUILD_WITH_SYSTEM_ZLIB:
    EXTENSION_LIBRARIES += ("z",)
if BUILD_WITH_SYSTEM_CARES:
    EXTENSION_LIBRARIES += ("cares",)
if BUILD_WITH_SYSTEM_RE2:
    EXTENSION_LIBRARIES += ("re2",)
if BUILD_WITH_SYSTEM_ABSL:
    EXTENSION_LIBRARIES += tuple(
        lib.stem[3:]
        for lib in sorted(pathlib.Path("/usr").glob("lib*/libabsl_*.so"))
    )

# Macro definitions for compilation
DEFINE_MACROS = (("_WIN32_WINNT", 0x600),)
asm_files = []

def _quote_build_define(argument):
    """Helper function to properly quote build defines for different platforms.
    Windows requires different quoting behavior than other platforms.
    """
    if "win32" in sys.platform:
        return '"\\"{}\\""'.format(argument)
    return '"{}"'.format(argument)

# Additional macro definitions
DEFINE_MACROS += (
    ("GRPC_XDS_USER_AGENT_NAME_SUFFIX", _quote_build_define("Python")),
    (
        "GRPC_XDS_USER_AGENT_VERSION_SUFFIX",
        _quote_build_define(_metadata.__version__),
    ),
)

# BoringSSL assembly configuration
asm_key = ""
if BUILD_WITH_BORING_SSL_ASM and not BUILD_WITH_SYSTEM_OPENSSL:
    boringssl_asm_platform = (
        BUILD_OVERRIDE_BORING_SSL_ASM_PLATFORM
        if BUILD_OVERRIDE_BORING_SSL_ASM_PLATFORM
        else sysconfig.get_platform()
    )
    if "i686" in boringssl_asm_platform:
        print("Enabling SSE2 on %s platform" % boringssl_asm_platform)
        EXTRA_COMPILE_ARGS.append("-msse2")
    else:
        print("SSE2 not enabled on %s platform" % boringssl_asm_platform)
    
    # Only include asm files on platforms with gas-compatible assemblers
    if not boringssl_asm_platform.startswith("win"):
        asm_key = "crypto_asm"
    else:
        print(
            "ASM Builds for BoringSSL currently not supported on:",
            boringssl_asm_platform,
        )

if asm_key:
    asm_files = grpc_core_dependencies.ASM_SOURCE_FILES[asm_key]
else:
    DEFINE_MACROS += (("OPENSSL_NO_ASM", 1),)

# Windows-specific configuration
if "win32" in sys.platform:
    DEFINE_MACROS += (
        ("WIN32_LEAN_AND_MEAN", 1),
        ("CARES_STATICLIB", 1),
        ("GRPC_ARES", 0),
        ("NTDDI_VERSION", 0x06000000),
        ("NOMINMAX", 1),
    )
    if "64bit" in platform.architecture()[0]:
        DEFINE_MACROS += (("MS_WIN64", 1),)