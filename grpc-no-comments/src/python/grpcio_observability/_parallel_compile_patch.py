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

try:
    BUILD_EXT_COMPILER_JOBS = int(
        os.environ["GRPC_PYTHON_BUILD_EXT_COMPILER_JOBS"]
    )
except KeyError:
    import multiprocessing

    BUILD_EXT_COMPILER_JOBS = multiprocessing.cpu_count()
except ValueError:
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

    macros, objects, extra_postargs, pp_opts, build = self._setup_compile(
        str(output_dir), macros, include_dirs, sources, depends, extra_postargs
    )
    cc_args = self._get_cc_args(pp_opts, debug, extra_preargs)

    def _compile_single_file(obj):
        try:
            src, ext = build[obj]
        except KeyError:
            return
        self._compile(obj, src, ext, cc_args, extra_postargs, pp_opts)

    import multiprocessing.pool

    multiprocessing.pool.ThreadPool(BUILD_EXT_COMPILER_JOBS).map(
        _compile_single_file, objects
    )
    return objects

def monkeypatch_compile_maybe():
    """
    Monkeypatching is dumb, but the build speed gain is worth it.
    After python 3.12, we won't find distutils if SETUPTOOLS_USE_DISTUTILS=stdlib.
    """
    use_distutils = os.environ.get("SETUPTOOLS_USE_DISTUTILS", "")
    if BUILD_EXT_COMPILER_JOBS > 1 and use_distutils != "stdlib":
        import distutils.ccompiler

        distutils.ccompiler.CCompiler.compile = _parallel_compile
