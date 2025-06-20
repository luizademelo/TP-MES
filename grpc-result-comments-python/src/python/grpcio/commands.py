Here's the commented version of the code:

```c++
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Provides setuptools command classes for the GRPC Python setup process."""

import setuptools

import glob
import os
import os.path
import shutil
import subprocess
import sys
import sysconfig
import traceback

from setuptools.command import build_ext
from setuptools.command import build_py
import support

# Define root directory paths for the project
PYTHON_STEM = os.path.dirname(os.path.abspath(__file__))
GRPC_STEM = os.path.abspath(PYTHON_STEM + "../../../../")
PROTO_STEM = os.path.join(GRPC_STEM, "src", "proto")  # Protocol buffers directory
PROTO_GEN_STEM = os.path.join(GRPC_STEM, "src", "python", "gens")  # Generated protobuf files
CYTHON_STEM = os.path.join(PYTHON_STEM, "grpc", "_cython")  # Cython files directory

class CommandError(Exception):
    """Simple exception class for GRPC custom commands."""

def _get_grpc_custom_bdist(decorated_basename, target_bdist_basename):
    """Returns a string path to a bdist file for Linux to install.

    Attempts to download a pre-compiled binary distribution from a repository.
    If unavailable, falls back to building from source with a warning.

    Args:
        decorated_basename: Base name of the decorated bdist file
        target_bdist_basename: Target base name for the bdist file

    Returns:
        Path to the downloaded or built bdist file

    Raises:
        CommandError: If the bdist cannot be retrieved or written
    """
    from urllib import request

    decorated_path = decorated_basename + GRPC_CUSTOM_BDIST_EXT
    try:
        url = BINARIES_REPOSITORY + "/{target}".format(target=decorated_path)
        bdist_data = request.urlopen(url).read()
    except IOError as error:
        raise CommandError(
            "{}\n\nCould not find the bdist {}: {}".format(
                traceback.format_exc(), decorated_path, error.message
            )
        )

    bdist_path = target_bdist_basename + GRPC_CUSTOM_BDIST_EXT
    try:
        with open(bdist_path, "w") as bdist_file:
            bdist_file.write(bdist_data)
    except IOError as error:
        raise CommandError(
            "{}\n\nCould not write grpcio bdist: {}".format(
                traceback.format_exc(), error.message
            )
        )
    return bdist_path

class SphinxDocumentation(setuptools.Command):
    """Command to generate documentation via sphinx."""

    description = "generate sphinx documentation"
    user_options = []  # No additional user options for this command

    def initialize_options(self):
        """Initialize command options (no-op as there are no options)."""
        pass

    def finalize_options(self):
        """Finalize command options (no-op as there are no options)."""
        pass

    def run(self):
        """Execute the sphinx documentation generation."""
        import sphinx.cmd.build

        source_dir = os.path.join(GRPC_STEM, "doc", "python", "sphinx")
        target_dir = os.path.join(GRPC_STEM, "doc", "build")
        exit_code = sphinx.cmd.build.build_main(
            ["-b", "html", "-W", "--keep-going", source_dir, target_dir]
        )
        if exit_code != 0:
            raise CommandError(
                "Documentation generation has warnings or errors"
            )

class BuildProjectMetadata(setuptools.Command):
    """Command to generate project metadata in a module."""

    description = "build grpcio project metadata files"
    user_options = []  # No additional user options for this command

    def initialize_options(self):
        """Initialize command options (no-op as there are no options)."""
        pass

    def finalize_options(self):
        """Finalize command options (no-op as there are no options)."""
        pass

    def run(self):
        """Generate project metadata file with version information."""
        with open(
            os.path.join(PYTHON_STEM, "grpc/_grpcio_metadata.py"), "w"
        ) as module_file:
            module_file.write(
                '__version__ = """{}"""'.format(self.distribution.get_version())
            )

class BuildPy(build_py.build_py):
    """Custom project build command that includes metadata generation."""

    def run(self):
        """Execute the build process including metadata generation."""
        self.run_command("build_project_metadata")
        build_py.build_py.run(self)

def _poison_extensions(extensions, message):
    """Includes a file that will always fail to compile in all extensions.
    
    Used as a fallback when required build dependencies are missing.
    
    Args:
        extensions: List of extensions to poison
        message: Error message to include in the poison file
    """
    poison_filename = os.path.join(PYTHON_STEM, "poison.c")
    with open(poison_filename, "w") as poison:
        poison.write("#error {}".format(message))
    for extension in extensions:
        extension.sources = [poison_filename]

def check_and_update_cythonization(extensions):
    """Check for existing Cython-generated files and update extension sources.
    
    Args:
        extensions: List of extensions to check
        
    Returns:
        bool: True if all required Cython-generated files exist, False otherwise
    """
    for extension in extensions:
        generated_pyx_sources = []
        other_sources = []
        for source in extension.sources:
            base, file_ext = os.path.splitext(source)
            if file_ext == ".pyx":
                generated_pyx_source = next(
                    (
                        base + gen_ext
                        for gen_ext in (
                            ".c",
                            ".cpp",
                        )
                        if os.path.isfile(base + gen_ext)
                    ),
                    None,
                )
                if generated_pyx_source:
                    generated_pyx_sources.append(generated_pyx_source)
                else:
                    sys.stderr.write("Cython-generated files are missing...\n")
                    return False
            else:
                other_sources.append(source)
        extension.sources = generated_pyx_sources + other_sources
    sys.stderr.write("Found cython-generated files...\n")
    return True

def try_cythonize(extensions, linetracing=False, mandatory=True):
    """Attempt to cythonize the extensions.
    
    Args:
        extensions: List of setuptools.Extension objects to cythonize
        linetracing: Whether to enable line tracing for profiling/debugging
        mandatory: Whether Cython is required (will poison extensions if True and Cython missing)
        
    Returns:
        List of processed extensions
    """
    try:
        import Cython.Build
    except ImportError:
        if mandatory:
            sys.stderr.write(
                "This package needs to generate C files with Cython but it"
                " cannot. Poisoning extension sources to disallow extension"
                " commands..."
            )
            _poison_extensions(
                extensions,
                (
                    "Extensions have been poisoned due to missing"
                    " Cython-generated code."
                ),
            )
        return extensions
    
    cython_compiler_directives = {}
    if linetracing:
        additional_define_macros = [("CYTHON_TRACE_NOGIL", "1")]
        cython_compiler_directives["linetrace"] = True
        
    return Cython.Build.cythonize(
        extensions,
        include_path=[
            include_dir
            for extension in extensions
            for include_dir in extension.include_dirs
        ]
        + [CYTHON_STEM],
        compiler_directives=cython_compiler_directives,
    )

class BuildExt(build_ext.build_ext):
    """Custom build_ext command to enable compiler-specific flags and Cython support."""

    # Compiler-specific options
    C_OPTIONS = {
        "unix": ("-pthread",),  # Unix-specific compile options
        "msvc": (),  # MSVC-specific compile options
    }
    LINK_OPTIONS = {}  # Linker options

    def get_ext_filename(self, ext_name):
        """Override extension filename generation to support custom suffixes.
        
        Args:
            ext_name: Name of the extension
            
        Returns:
            Modified filename if GRPC_PYTHON_OVERRIDE_EXT_SUFFIX is set
        """
        filename = build_ext.build_ext.get_ext_filename(self, ext_name)
        orig_ext_suffix = sysconfig.get_config_var("EXT_SUFFIX")
        new_ext_suffix = os.getenv("GRPC_PYTHON_OVERRIDE_EXT_SUFFIX")
        if new_ext_suffix and filename.endswith(orig_ext_suffix):
            filename = filename[: -len(orig_ext_suffix)] + new_ext_suffix
        return filename

    def build_extensions(self):
        """Build extensions with custom compiler flags and Cython support."""
        # Monkey-patch the compiler to handle C/C++ file differences
        old_compile = self.compiler._compile

        def new_compile(obj, src, ext, cc_args, extra_postargs, pp_opts):
            if src.endswith(".c"):
                extra_postargs = [
                    arg for arg in extra_postargs if arg != "-std=c++17"
                ]
            elif src.endswith((".cc", ".cpp")):
                extra_postargs = [
                    arg for arg in extra_postargs if arg != "-std=c11"
                ]
            return old_compile(obj, src, ext, cc_args, extra_postargs, pp_opts)

        self.compiler._compile = new_compile

        # Apply compiler-specific options
        compiler = self.compiler.compiler_type
        if compiler in BuildExt.C_OPTIONS:
            for extension in self.extensions:
                extension.extra_compile_args += list(
                    BuildExt.C_OPTIONS[compiler]
                )
        if compiler in BuildExt.LINK_OPTIONS:
            for extension in self.extensions:
                extension.extra_link_args += list(
                    BuildExt.LINK_OPTIONS[compiler]
                )
                
        # Handle Cythonization
        if not check_and_update_cythonization(self.extensions):
            self.extensions = try_cythonize(self.extensions)
            
        try:
            build_ext.build_ext.build_extensions(self)
        except Exception as error:
            formatted_exception = traceback.format_exc()
            support.diagnose_build_ext_error(self, error, formatted_exception)
            raise CommandError(
                "Failed `build_ext` step:\n{}".format(formatted_exception)
            )

class Gather(setuptools.Command):
    """Command to gather project dependencies."""

    description = "gather dependencies for grpcio"
    user_options = [
        ("test", "t", "flag indicating to gather test dependencies"),
        ("install", "i", "flag indicating to gather install dependencies"),
    ]

    def initialize_options(self):
        """Initialize command options."""
        self.test = False
        self.install = False

    def finalize_options(self):
        """Finalize command options (no-op)."""
        pass

    def run(self):
        """Execute dependency gathering (currently a no-op)."""
        pass

class Clean(setuptools.Command):
    """Command to clean build artifacts."""

    description = "Clean build artifacts."
    user_options = [
        ("all", "a", "a phony flag to allow our script to continue"),
    ]

    # Patterns of files/directories to clean
    _FILE_PATTERNS = (
        "pyb",
        "src/python/grpcio/__pycache__/",
        "src/python/grpcio/grpc/_cython/cygrpc.cpp",
        "src/python/grpcio/grpc/_cython/*.so",
        "src/python/grpcio/grpcio.egg-info/",
    )
    _CURRENT_DIRECTORY = os.path.normpath(
        os.path.join(os.path.dirname(os.path.realpath(__file__)), "../../..")
    )

    def initialize_options(self):
        """Initialize command options."""
        self.all = False

    def finalize_options(self):
        """Finalize command options (no-op)."""
        pass

    def run(self):
        """Execute cleaning of build artifacts."""
        for path_spec in self._FILE_PATTERNS:
            this_glob = os.path.normpath(
                os.path.join(Clean._CURRENT_DIRECTORY, path_spec)
            )
            abs_paths = glob.glob(this_glob)
            for path in abs_paths:
                # Safety check to prevent deleting files outside project directory
                if not str(path).startswith(Clean._CURRENT_DIRECTORY):
                    raise ValueError(
                        "Cowardly refusing to delete {}.".format(path)
                    )
                print("Removing {}".format(os.path.relpath(path)))
                if os.path.isfile(path):
                    os.remove(str(path))
                else:
                    shutil.rmtree(str(path))
```