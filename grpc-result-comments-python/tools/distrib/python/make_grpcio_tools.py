Here's the commented version of the code:

```python
#!/usr/bin/env python3

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

from __future__ import print_function

# Import necessary standard library modules
import argparse  # For command-line argument parsing
import errno     # For system error numbers
import filecmp   # For file comparison
import glob      # For filename pattern matching
import os        # For operating system interfaces
import os.path   # For path manipulation
import pprint    # For pretty-printing data structures
import shutil    # For file operations
import subprocess  # For running subprocesses
import sys       # For system-specific parameters
import traceback # For exception handling
import uuid      # For generating UUIDs

# Template for the deps file that will be generated
DEPS_FILE_CONTENT = """
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

# AUTO-GENERATED BY make_grpcio_tools.py!
CC_FILES={cc_files}

PROTO_FILES={proto_files}

CC_INCLUDES={cc_includes}
PROTO_INCLUDE={proto_include}

{commit_hash_expr}
"""

# Constants for commit hash formatting
COMMIT_HASH_PREFIX = 'PROTOBUF_SUBMODULE_VERSION="'
COMMIT_HASH_SUFFIX = '"'

# Mapping between Bazel external references and local paths
EXTERNAL_LINKS = [
    ("@com_google_absl//", "third_party/abseil-cpp/"),
    ("@com_google_protobuf//", "third_party/protobuf/"),
    ("@utf8_range//", "third_party/protobuf/third_party/utf8_range"),
]

# Prefix for protobuf proto files in Bazel
PROTOBUF_PROTO_PREFIX = "@com_google_protobuf//src/"

# List of include directories for C++ files
CC_INCLUDES = [
    os.path.join("third_party", "abseil-cpp"),
    os.path.join("third_party", "protobuf"),
    os.path.join("third_party", "protobuf", "src"),
    os.path.join("third_party", "protobuf", "upb_generator", "cmake"),
    os.path.join("third_party", "protobuf", "upb"),
    os.path.join("third_party", "protobuf", "upb", "reflection", "cmake"),
    os.path.join("third_party", "protobuf", "third_party", "utf8_range"),
]

# Path to protobuf include directory
PROTO_INCLUDE = os.path.join("third_party", "protobuf", "src")

# Root prefix for grpcio_tools package
GRPCIO_TOOLS_ROOT_PREFIX = "tools/distrib/python/grpcio_tools/"

# List of source-target pairs for file copying operations
COPY_FILES_SOURCE_TARGET_PAIRS = [
    ("include", "grpc_root/include"),
    ("src/compiler", "grpc_root/src/compiler"),
    ("third_party/abseil-cpp/absl", "third_party/abseil-cpp/absl"),
    ("third_party/protobuf/src", "third_party/protobuf/src"),
    ("third_party/protobuf/upb", "third_party/protobuf/upb"),
    (
        "third_party/protobuf/upb_generator",
        "third_party/protobuf/upb_generator",
    ),
    (
        "third_party/protobuf/third_party/utf8_range",
        "third_party/protobuf/third_party/utf8_range",
    ),
]

# Targets to delete during cleanup
DELETE_TARGETS_ON_CLEANUP = ["third_party"]

# Absolute path to the gRPC root directory
GRPC_ROOT = os.path.abspath(
    os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "..")
)

# Path to protobuf submodule root
GRPC_PROTOBUF_SUBMODULE_ROOT = os.path.join(
    GRPC_ROOT, "third_party", "protobuf"
)

# Path to protoc library dependencies file
GRPC_PYTHON_PROTOC_LIB_DEPS = os.path.join(
    GRPC_ROOT,
    "tools",
    "distrib",
    "python",
    "grpcio_tools",
    "protoc_lib_deps.py",
)

# Path to bazel dependencies script
BAZEL_DEPS = os.path.join(
    GRPC_ROOT, "tools", "distrib", "python", "bazel_deps.sh"
)

# Bazel query for protoc library
BAZEL_DEPS_PROTOC_LIB_QUERY = "@com_google_protobuf//:protoc_lib"

# Bazel queries for common protobuf protos
BAZEL_DEPS_COMMON_PROTOS_QUERIES = [
    "@com_google_protobuf//:well_known_type_protos",
    "@com_google_protobuf//:compiler_plugin_proto",
]

def protobuf_submodule_commit_hash():
    """Gets the commit hash for the HEAD of the protobuf submodule currently
    checked out."""
    cwd = os.getcwd()
    os.chdir(GRPC_PROTOBUF_SUBMODULE_ROOT)
    output = subprocess.check_output(["git", "rev-parse", "HEAD"])
    os.chdir(cwd)
    return output.decode("ascii").splitlines()[0].strip()

def _bazel_query(query):
    """Runs 'bazel query' to collect source file info.
    
    Args:
        query: The bazel query string to execute.
        
    Returns:
        List of strings representing the query results.
    """
    print('Running "bazel query %s"' % query)
    output = subprocess.check_output([BAZEL_DEPS, query])
    return output.decode("ascii").splitlines()

def _pretty_print_list(items):
    """Pretty print python list with proper indentation.
    
    Args:
        items: The list to pretty print.
        
    Returns:
        Formatted string representation of the list.
    """
    formatted = pprint.pformat(items, indent=4)

    if formatted.startswith("["):
        formatted = formatted[0] + "\n " + formatted[1:]

    if formatted.endswith("]"):
        formatted = formatted[:-1] + "\n" + formatted[-1]
    return formatted

def _bazel_name_to_file_path(name):
    """Transform bazel reference to source file name.
    
    Args:
        name: The bazel reference to convert.
        
    Returns:
        The corresponding file path or None if conversion isn't possible.
    """
    for link in EXTERNAL_LINKS:
        if name.startswith(link[0]):
            filepath = link[1] + name[len(link[0]) :].replace(":", "/")

            # Handle special path transformations
            filepath = filepath.replace("wkt/google/protobuf/", "")

            filepath = filepath.replace(
                "/upb/reflection/stage1/", "/upb/reflection/cmake/"
            )
            filepath = filepath.replace(
                "/upb_generator/stage1/", "/upb_generator/cmake/"
            )
            # Skip certain paths
            if (
                "/upb/reflection/stage0/" in filepath
                or "/upb_generator/stage0/" in filepath
            ):
                return None

            if (
                "/upb_generator/minitable/main.cc" in filepath
                or "/upb_generator/c/generator.cc" in filepath
            ):
                return None

            return filepath
    return None

def _generate_deps_file_content():
    """Generates the content for the protoc library dependencies file.
    
    Returns:
        String containing the formatted dependencies file content.
    """
    # Get C++ source files from bazel query
    cc_files_output = _bazel_query(BAZEL_DEPS_PROTOC_LIB_QUERY)

    cc_files = []
    for name in cc_files_output:
        if name.endswith(".c") or name.endswith(".cc"):
            filepath = _bazel_name_to_file_path(name)
            if filepath:
                cc_files.append(filepath)

    # Get proto files from bazel queries
    raw_proto_files = []
    for target in BAZEL_DEPS_COMMON_PROTOS_QUERIES:
        raw_proto_files += _bazel_query(target)
    proto_files = [
        name[len(PROTOBUF_PROTO_PREFIX) :].replace(":", "/")
        for name in raw_proto_files
        if name.endswith(".proto") and name.startswith(PROTOBUF_PROTO_PREFIX)
    ]

    # Get protobuf submodule commit hash
    commit_hash = protobuf_submodule_commit_hash()
    commit_hash_expr = COMMIT_HASH_PREFIX + commit_hash + COMMIT_HASH_SUFFIX

    # Format the deps file content
    deps_file_content = DEPS_FILE_CONTENT.format(
        cc_files=_pretty_print_list(sorted(cc_files)),
        proto_files=_pretty_print_list(sorted(set(proto_files))),
        cc_includes=_pretty_print_list(CC_INCLUDES),
        proto_include=repr(PROTO_INCLUDE),
        commit_hash_expr=commit_hash_expr,
    )
    return deps_file_content

def _copy_source_tree(source, target):
    """Recursively copies source directory to target directory.
    
    Args:
        source: Path to source directory.
        target: Path to target directory.
    """
    print("Copying contents of %s to %s" % (source, target))

    for source_dir, _, files in os.walk(source):
        target_dir = os.path.abspath(
            os.path.join(target, os.path.relpath(source_dir, source))
        )
        try:
            os.makedirs(target_dir)
        except OSError as error:
            if error.errno != errno.EEXIST:
                raise
        for relative_file in files:
            source_file = os.path.abspath(
                os.path.join(source_dir, relative_file)
            )
            target_file = os.path.abspath(
                os.path.join(target_dir, relative_file)
            )
            shutil.copyfile(source_file, target_file)

def _delete_source_tree(target):
    """Deletes the specified target directory.
    
    Args:
        target: Path to directory to delete (relative to GRPCIO_TOOLS_ROOT_PREFIX).
    """
    target = GRPCIO_TOOLS_ROOT_PREFIX + target
    target_abs = os.path.join(*target.split("/"))
    print("Deleting copied folder %s" % (target_abs))
    shutil.rmtree(target_abs, ignore_errors=True)

def main():
    """Main function that orchestrates the build process."""
    # Set up command line argument parsing
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--cleanup_third_party",
        default=False,
        action="store_true",
        help="Delete the temporary third_party folder",
    )
    args = parser.parse_args()
    os.chdir(GRPC_ROOT)

    # Copy necessary source files
    for source, target in COPY_FILES_SOURCE_TARGET_PAIRS:
        source_abs = os.path.join(GRPC_ROOT, os.path.join(*source.split("/")))
        target = GRPCIO_TOOLS_ROOT_PREFIX + target
        target_abs = os.path.join(GRPC_ROOT, os.path.join(*target.split("/")))
        _copy_source_tree(source_abs, target_abs)
    print(
        "The necessary source files were copied under the grpcio_tools package"
        " root."
    )
    print()

    try:
        # Generate protobuf dependencies file
        print('Invoking "bazel query" to gather the protobuf dependencies.')
        protoc_lib_deps_content = _generate_deps_file_content()
    except Exception as error:
        sys.stderr.write("Got non-fatal error:\n")
        traceback.print_exc(file=sys.stderr)
        return

    # Write the generated dependencies file
    with open(GRPC_PYTHON_PROTOC_LIB_DEPS, "w") as deps_file:
        deps_file.write(protoc_lib_deps_content)
    print('File "%s" updated.' % GRPC_PYTHON_PROTOC_LIB_DEPS)
    
    # Clean up if requested
    if args.cleanup_third_party:
        for target in DELETE_TARGETS_ON_CLEANUP:
            _delete_source_tree(target)
    print("Done.")

if __name__ == "__main__":
    main()
```

The comments added explain:
1. The purpose of each imported module
2. The meaning of important constants and variables
3. The functionality of each function
4. The arguments and return values of functions
5. The overall flow of the program
6. Special cases and edge conditions

The comments are designed to help future developers understand:
- What the code does
- Why certain decisions were made
- How the different components interact
- Where to look for specific functionality
- How to modify or extend the code safely