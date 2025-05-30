# Copyright 2021 the gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

"""
Includes default copts.
"""

GRPC_LLVM_WARNING_FLAGS = [

    "-Wall",
    "-Wextra",

    "-Wimplicit-fallthrough",

    "-Werror",

    "-Wno-unknown-warning-option",

    "-Wc++20-extensions",
    "-Wctad-maybe-unsupported",
    "-Wdeprecated-increment-bool",
    "-Wfloat-overflow-conversion",
    "-Wfloat-zero-conversion",
    "-Wfor-loop-analysis",
    "-Wformat-security",
    "-Wgnu-redeclared-enum",
    "-Winfinite-recursion",
    "-Wliteral-conversion",
    "-Wnon-virtual-dtor",
    "-Woverloaded-virtual",
    "-Wself-assign",
    "-Wstring-conversion",
    "-Wtautological-overlap-compare",
    "-Wthread-safety-analysis",
    "-Wthread-safety-beta",
    "-Wunused-but-set-variable",
    "-Wunused-comparison",
    "-Wvla",

    "-Wtype-limits",

    "-Wno-string-concatenation",

    "-Wno-deprecated-declarations",
    "-Wno-unused-function",

    "-Walign-mismatch",
    "-Wover-aligned",
    "-Wunaligned-access",
]

GRPC_LLVM_WINDOWS_WARNING_FLAGS = GRPC_LLVM_WARNING_FLAGS + [

    "-Wthread-safety",
    "-Wreorder-ctor",

    "-Wno-c++98-compat-pedantic",
    "-Wno-missing-prototypes",
    "-Wno-thread-safety-precise",

    "-Wno-comma",
    "-Wno-deprecated-redundant-constexpr-static-def",
    "-Wno-deprecated",
    "-Wno-float-equal",
    "-Wno-gcc-compat",
    "-Wno-reserved-identifier",
    "-Wno-thread-safety-negative",
    "-Wno-sign-compare",

    "-Wno-zero-as-null-pointer-constant",

    "-Wno-macro-redefined",

    "-Wno-cast-align",
    "-Wno-format-nonliteral",
    "-Wno-inconsistent-missing-destructor-override",
    "-Wno-language-extension-token",

    "-Wno-disabled-macro-expansion",

    "-Wno-shift-sign-overflow",

    "-Wno-c++17-attribute-extensions",

    "-Wno-missing-variable-declarations",

    # TODO: delete iomgr
    "-Wno-old-style-cast",
    "-Wno-cast-qual",
    "-Wno-unused-member-function",
    "-Wno-unused-template",

    "-Wno-global-constructors",

    "-Wno-missing-field-initializers",
    "-Wno-non-virtual-dtor",
    "-Wno-thread-safety-reference-return",

    "-Wno-sign-conversion",
    "-Wno-shorten-64-to-32",

    # TODO: general cleanup required. Maybe new developer or rainy day projects.
    "-Wno-unreachable-code-break",
    "-Wno-unreachable-code-return",
    "-Wno-unreachable-code",
    "-Wno-used-but-marked-unused",
    "-Wno-newline-eof",
    "-Wno-unused-const-variable",
    "-Wno-extra-semi",
    "-Wno-extra-semi-stmt",
    "-Wno-suggest-destructor-override",
    "-Wno-shadow",
    "-Wno-missing-noreturn",
    "-Wno-nested-anon-types",
    "-Wno-gnu-anonymous-struct",
    "-Wno-nonportable-system-include-path",
    "-Wno-microsoft-cast",
    "-Wno-exit-time-destructors",
    "-Wno-undef",
    "-Wno-unused-macros",
    "-Wno-redundant-parens",
    "-Wno-undefined-func-template",
    "-Wno-gnu-zero-variadic-macro-arguments",
    "-Wno-double-promotion",
    "-Wno-implicit-float-conversion",
    "-Wno-implicit-int-conversion",
    "-Wno-float-conversion",
    "-Wno-unused-parameter",
    "-Wno-suggest-override",
    "-Wno-documentation",
    "-Wno-documentation-unknown-command",
    "-Wno-unsafe-buffer-usage",

    "-Wno-covered-switch-default",
    "-Wno-switch-default",
    "-Wno-switch-enum",
    "-Wno-c99-extensions",
    "-Wno-unused-private-field",
]

GRPC_DEFAULT_COPTS = select({
    "//:use_strict_warning": GRPC_LLVM_WARNING_FLAGS + ["-DUSE_STRICT_WARNING=1"],
    "//:use_strict_warning_windows": GRPC_LLVM_WINDOWS_WARNING_FLAGS + ["-DUSE_STRICT_WARNING=1"],
    "//conditions:default": [],
})
