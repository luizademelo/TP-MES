# Copyright 2021 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Custom rules for gRPC Python"""

def pyx_library(name, deps = [], py_deps = [], srcs = [], **kwargs):
    """Compiles a group of .pyx / .pxd / .py files.

    First runs Cython to create .cpp files for each input .pyx or .py + .pxd
    pair. Then builds a shared object for each, passing "deps" to each cc_binary
    rule (includes Python headers by default). Finally, creates a py_library rule
    with the shared objects and any pure Python "srcs", with py_deps as its
    dependencies; the shared objects can be imported like normal Python files.

    Args:
        name: Name for the rule.
        deps: C/C++ dependencies of the Cython (e.g. Numpy headers).
        py_deps: Pure Python dependencies of the final library.
        srcs: .py, .pyx, or .pxd files to either compile or pass through.
        **kwargs: Extra keyword arguments passed to the py_library.
    """

    py_srcs = []
    pyx_srcs = []
    pxd_srcs = []
    for src in srcs:
        if src.endswith(".pyx") or (src.endswith(".py") and
                                    src[:-3] + ".pxd" in srcs):
            pyx_srcs.append(src)
        elif src.endswith(".py"):
            py_srcs.append(src)
        else:
            pxd_srcs.append(src)
        if src.endswith("__init__.py"):
            pxd_srcs.append(src)

    for filename in pyx_srcs:
        native.genrule(
            name = filename + "_cython_translation",
            srcs = [filename],
            outs = [filename.split(".")[0] + ".cpp"],

            cmd =
                "PYTHONHASHSEED=0 $(location @cython//:cython_binary) --cplus $(SRCS) --output-file $(OUTS)",
            tools = ["@cython//:cython_binary"] + pxd_srcs,
        )

    shared_objects = []
    defines = kwargs.pop("defines", [])
    for src in pyx_srcs:
        stem = src.split(".")[0]
        shared_object_name = stem + ".so"
        native.cc_binary(
            name = shared_object_name,
            srcs = [stem + ".cpp"],
            deps = deps + ["@local_config_python//:python_headers"],
            defines = defines,
            linkshared = 1,
        )
        shared_objects.append(shared_object_name)

    data = shared_objects[:]
    data += kwargs.pop("data", [])

    native.py_library(
        name = name,
        srcs = py_srcs,
        deps = py_deps,
        srcs_version = "PY2AND3",
        data = data,
        **kwargs
    )
