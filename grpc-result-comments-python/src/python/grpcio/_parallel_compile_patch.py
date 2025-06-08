Here's the commented version of the code:

```c++
# Copyright 2023 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

"""Patches the compile() to enable parallel compilation of C/C++.

build_ext has lots of C/C++ files and normally them one by one.
Enabling parallel build helps a lot.
"""

import os

# Try to get the number of parallel jobs from environment variable.
# If not set, default to number of CPU cores.
# If invalid value, default to 1 (sequential compilation)
try:
    BUILD_EXT_COMPILER_JOBS = int(
        os.environ["GRPC_PYTHON_BUILD_EXT_COMPILER_JOBS"]
    )
except KeyError:
    import multiprocessing
    # Default to number of available CPU cores
    BUILD_EXT_COMPILER_JOBS = multiprocessing.cpu_count()
except ValueError:
    # Fallback to sequential compilation if invalid value provided
    BUILD_EXT_COMPILER_JOBS = 1

def _parallel_compile(
    self,
    sources,
    output_dir=None,
    macros=None,
    include_dirs=None,
    debug=0,
    extra_preargs=None,
    extra_postargs=None,
    depends=None,
):
    """Compiles source files in parallel using multiple threads.
    
    Args:
        self: Compiler instance
        sources: List of source files to compile
        output_dir: Directory for output objects
        macros: Preprocessor macros
        include_dirs: Include directories
        debug: Debug level
        extra_preargs: Extra pre-arguments
        extra_postargs: Extra post-arguments
        depends: Dependency files
    
    Returns:
        List of compiled object files
    """
    # Setup compilation parameters and get the list of objects to build
    macros, objects, extra_postargs, pp_opts, build = self._setup_compile(
        str(output_dir), macros, include_dirs, sources, depends, extra_postargs
    )
    # Get compiler arguments
    cc_args = self._get_cc_args(pp_opts, debug, extra_preargs)

    def _compile_single_file(obj):
        """Helper function to compile a single source file.
        
        Args:
            obj: The object file to build
        """
        try:
            src, ext = build[obj]
        except KeyError:
            return
        self._compile(obj, src, ext, cc_args, extra_postargs, pp_opts)

    # Create a thread pool and compile files in parallel
    import multiprocessing.pool
    multiprocessing.pool.ThreadPool(BUILD_EXT_COMPILER_JOBS).map(
        _compile_single_file, objects
    )
    return objects

def monkeypatch_compile_maybe():
    """Conditionally monkeypatches the compile() function for parallel compilation.
    
    This function checks if parallel compilation should be enabled (more than 1 job)
    and if distutils is available (not using stdlib version in Python 3.12+).
    If conditions are met, it replaces the standard compile() with our parallel version.
    """
    use_distutils = os.environ.get("SETUPTOOLS_USE_DISTUTILS", "")
    # Only patch if we want parallel compilation and distutils is available
    if BUILD_EXT_COMPILER_JOBS > 1 and use_distutils != "stdlib":
        import distutils.ccompiler
        # Replace standard compile with our parallel version
        distutils.ccompiler.CCompiler.compile = _parallel_compile
```