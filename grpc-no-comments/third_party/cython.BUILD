
py_library(
    name="cython_lib",
    srcs=glob(
        ["Cython/**/*.py"],
        exclude=[
            "**/Tests/*.py",
        ],
    ) + ["cython.py"],
    data=glob([
        "Cython/**/*.pyx",
        "Cython/Utility/*.*",
        "Cython/Includes/**/*.pxd",
    ]),
    srcs_version="PY2AND3",
    visibility=["//visibility:public"],
)

py_binary(
    name="cython_binary",
    srcs=["cython.py"],
    main="cython.py",
    srcs_version="PY2AND3",
    visibility=["//visibility:public"],
    deps=["cython_lib"],
)
