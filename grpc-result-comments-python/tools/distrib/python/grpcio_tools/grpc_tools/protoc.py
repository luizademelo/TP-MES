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

import os
import sys

from grpc_tools import _protoc_compiler

# Use importlib.resources for Python 3.9+, fallback to pkg_resources for older versions
if sys.version_info >= (3, 9, 0):
    from importlib import resources
else:
    import pkg_resources

# Suffixes for generated proto and service modules
_PROTO_MODULE_SUFFIX = "_pb2"
_SERVICE_MODULE_SUFFIX = "_pb2_grpc"

# Environment variable to disable dynamic stubs generation
_DISABLE_DYNAMIC_STUBS = "GRPC_PYTHON_DISABLE_DYNAMIC_STUBS"

def main(command_arguments):
    """Run the protocol buffer compiler with the given command-line arguments.

    Args:
      command_arguments: a list of strings representing command line arguments to
          `protoc`.
    """
    # Encode all arguments to bytes before passing to protoc compiler
    command_arguments = [argument.encode() for argument in command_arguments]
    return _protoc_compiler.run_main(command_arguments)

def _get_resource_file_name(
    package_or_requirement: str, resource_name: str
) -> str:
    """Obtain the filename for a resource on the file system.
    
    Args:
        package_or_requirement: Package name or requirement string
        resource_name: Name of the resource to locate
        
    Returns:
        Absolute path to the resource file as a string
    """
    file_name = None
    if sys.version_info >= (3, 9, 0):
        # Modern path-based resource access
        file_name = (
            resources.files(package_or_requirement) / resource_name
        ).resolve()
    else:
        # Legacy resource access using pkg_resources
        file_name = pkg_resources.resource_filename(
            package_or_requirement, resource_name
        )
    return str(file_name)

# Dynamic module loading functionality (Python 3.5+ only)
if sys.version_info >= (3, 5, 0):
    import contextlib
    import importlib
    import importlib.abc
    import importlib.machinery
    import threading

    # Global flag and lock for thread-safe finder installation
    _FINDERS_INSTALLED = False
    _FINDERS_INSTALLED_LOCK = threading.Lock()

    def _maybe_install_proto_finders():
        """Install proto finders in sys.meta_path if not already installed."""
        global _FINDERS_INSTALLED
        with _FINDERS_INSTALLED_LOCK:
            if not _FINDERS_INSTALLED:
                # Add finders for both proto and service modules
                sys.meta_path.extend(
                    [
                        ProtoFinder(
                            _PROTO_MODULE_SUFFIX, _protoc_compiler.get_protos
                        ),
                        ProtoFinder(
                            _SERVICE_MODULE_SUFFIX,
                            _protoc_compiler.get_services,
                        ),
                    ]
                )

                # Add proto include directory to sys.path
                proto_include = _get_resource_file_name("grpc_tools", "_proto")
                sys.path.append(proto_include)

                _FINDERS_INSTALLED = True

    def _module_name_to_proto_file(suffix, module_name):
        """Convert a module name back to its original proto file path.
        
        Args:
            suffix: Module suffix (_pb2 or _pb2_grpc)
            module_name: Full module name (e.g., package.module_pb2)
            
        Returns:
            Corresponding proto file path (e.g., package/module.proto)
        """
        components = module_name.split(".")
        proto_name = components[-1][: -1 * len(suffix)]
        return "/".join(components[:-1] + [proto_name + ".proto"])

    def _proto_file_to_module_name(suffix, proto_file):
        """Convert a proto file path to its generated module name.
        
        Args:
            suffix: Module suffix to append (_pb2 or _pb2_grpc)
            proto_file: Path to proto file (e.g., package/module.proto)
            
        Returns:
            Generated module name (e.g., package.module_pb2)
        """
        components = proto_file.split(os.path.sep)
        proto_base_name = os.path.splitext(components[-1])[0]
        return ".".join(components[:-1] + [proto_base_name + suffix])

    def _protos(protobuf_path):
        """Returns a gRPC module generated from the indicated proto file.
        
        Args:
            protobuf_path: Path to the proto file
            
        Returns:
            Imported module containing generated proto classes
        """
        _maybe_install_proto_finders()
        module_name = _proto_file_to_module_name(
            _PROTO_MODULE_SUFFIX, protobuf_path
        )
        module = importlib.import_module(module_name)
        return module

    def _services(protobuf_path):
        """Returns a module generated from the indicated proto file.
        
        Args:
            protobuf_path: Path to the proto file
            
        Returns:
            Imported module containing generated gRPC service classes
        """
        _maybe_install_proto_finders()
        _protos(protobuf_path)  # Ensure proto module is generated first
        module_name = _proto_file_to_module_name(
            _SERVICE_MODULE_SUFFIX, protobuf_path
        )
        module = importlib.import_module(module_name)
        return module

    def _protos_and_services(protobuf_path):
        """Returns two modules, corresponding to _pb2.py and _pb2_grpc.py files.
        
        Args:
            protobuf_path: Path to the proto file
            
        Returns:
            Tuple of (proto_module, service_module)
        """
        return (_protos(protobuf_path), _services(protobuf_path))

    # Cache for generated proto code with thread-safe access
    _proto_code_cache = {}
    _proto_code_cache_lock = threading.RLock()

    class ProtoLoader(importlib.abc.Loader):
        """Custom loader for dynamically generated proto modules."""
        
        def __init__(
            self, suffix, codegen_fn, module_name, protobuf_path, proto_root
        ):
            """Initialize the loader.
            
            Args:
                suffix: Module suffix (_pb2 or _pb2_grpc)
                codegen_fn: Function to generate code from proto files
                module_name: Full name of module to load
                protobuf_path: Path to proto file
                proto_root: Root directory for proto imports
            """
            self._suffix = suffix
            self._codegen_fn = codegen_fn
            self._module_name = module_name
            self._protobuf_path = protobuf_path
            self._proto_root = proto_root

        def create_module(self, spec):
            """Create a new module (returns None to use default module creation)."""
            return None

        def _generated_file_to_module_name(self, filepath):
            """Convert generated file path back to module name."""
            components = filepath.split(os.path.sep)
            return ".".join(
                components[:-1] + [os.path.splitext(components[-1])[0]]
            )

        def exec_module(self, module):
            """Execute the module in its own namespace.
            
            Args:
                module: The module object to execute
            """
            assert module.__name__ == self._module_name
            code = None
            with _proto_code_cache_lock:
                if self._module_name in _proto_code_cache:
                    # Use cached code if available
                    code = _proto_code_cache[self._module_name]
                    exec(code, module.__dict__)
                else:
                    # Generate code for the proto file and its dependencies
                    files = self._codegen_fn(
                        self._protobuf_path.encode("ascii"),
                        [path.encode("ascii") for path in sys.path],
                    )
                    # Process dependencies first (files are in topological order)
                    for f in files[:-1]:
                        module_name = self._generated_file_to_module_name(
                            f[0].decode("ascii")
                        )
                        if module_name not in sys.modules:
                            if module_name not in _proto_code_cache:
                                _proto_code_cache[module_name] = f[1]
                            importlib.import_module(module_name)
                    # Execute the main module code
                    exec(files[-1][1], module.__dict__)

    class ProtoFinder(importlib.abc.MetaPathFinder):
        """Meta path finder for proto-generated modules."""
        
        def __init__(self, suffix, codegen_fn):
            """Initialize the finder.
            
            Args:
                suffix: Module suffix to look for (_pb2 or _pb2_grpc)
                codegen_fn: Function to generate code if module not found
            """
            self._suffix = suffix
            self._codegen_fn = codegen_fn

        def find_spec(self, fullname, path, target=None):
            """Find the spec for a module if it matches our suffix.
            
            Args:
                fullname: Full module name
                path: Import path
                target: Target module (unused)
                
            Returns:
                ModuleSpec if this is a proto module, None otherwise
            """
            if not fullname.endswith(self._suffix):
                return None
            filepath = _module_name_to_proto_file(self._suffix, fullname)
            # Search sys.path for the corresponding proto file
            for search_path in sys.path:
                try:
                    prospective_path = os.path.join(search_path, filepath)
                    os.stat(prospective_path)
                except (FileNotFoundError, NotADirectoryError, OSError):
                    continue
                else:
                    # Found matching proto file - return spec with our loader
                    return importlib.machinery.ModuleSpec(
                        fullname,
                        ProtoLoader(
                            self._suffix,
                            self._codegen_fn,
                            fullname,
                            filepath,
                            search_path,
                        ),
                    )

    # Install finders unless disabled by environment variable
    if not os.getenv(_DISABLE_DYNAMIC_STUBS):
        _maybe_install_proto_finders()

def entrypoint() -> None:
    """Main entry point for the protoc compiler tool.
    
    Adds the proto include directory to the arguments and invokes the compiler.
    """
    proto_include = _get_resource_file_name("grpc_tools", "_proto")
    sys.exit(main(sys.argv + ["-I{}".format(proto_include)]))

if __name__ == "__main__":
    entrypoint()
```