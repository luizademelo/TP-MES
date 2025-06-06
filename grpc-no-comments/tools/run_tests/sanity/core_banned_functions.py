#!/usr/bin/env python3

# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Explicitly ban select functions from being used in src/core/**.

Most of these functions have internal versions that should be used instead."""

import os
import sys

os.chdir(os.path.join(os.path.dirname(sys.argv[0]), "../../.."))

BANNED_EXCEPT = {
    "grpc_slice_from_static_buffer(": [
        "src/core/lib/slice/slice.cc",
        "src/core/load_balancing/grpclb/grpclb.cc",
    ],
    "grpc_resource_quota_ref(": ["src/core/lib/resource_quota/api.cc"],
    "grpc_resource_quota_unref(": [
        "src/core/lib/resource_quota/api.cc",
        "src/core/lib/surface/server.cc",
    ],
    "grpc_error_create(": [
        "src/core/lib/iomgr/error.cc",
        "src/core/lib/iomgr/error_cfstream.cc",
    ],
    "grpc_error_ref(": ["src/core/lib/iomgr/error.cc"],
    "grpc_error_unref(": ["src/core/lib/iomgr/error.cc"],
    "grpc_os_error(": [
        "src/core/lib/iomgr/error.cc",
        "src/core/lib/iomgr/error.h",
    ],
    "grpc_wsa_error(": [
        "src/core/lib/iomgr/error.cc",
        "src/core/lib/iomgr/error.h",
    ],
    "grpc_log_if_error(": [
        "src/core/lib/iomgr/error.cc",
        "src/core/lib/iomgr/error.h",
    ],
    "grpc_slice_malloc(": [
        "src/core/lib/slice/slice.cc",
        "src/core/lib/slice/slice.h",
    ],
    "grpc_call_cancel(": ["src/core/lib/surface/call.cc"],
    "grpc_channel_destroy(": [
        "src/core/lib/surface/channel.cc",
        "src/core/lib/surface/legacy_channel.cc",
        "src/core/tsi/alts/handshaker/alts_shared_resource.cc",
    ],
    "grpc_closure_create(": [
        "src/core/lib/iomgr/closure.cc",
        "src/core/lib/iomgr/closure.h",
    ],
    "grpc_closure_init(": [
        "src/core/lib/iomgr/closure.cc",
        "src/core/lib/iomgr/closure.h",
    ],
    "grpc_closure_sched(": ["src/core/lib/iomgr/closure.cc"],
    "grpc_closure_run(": ["src/core/lib/iomgr/closure.cc"],
    "grpc_closure_list_sched(": ["src/core/lib/iomgr/closure.cc"],
    "grpc_error*": ["src/core/lib/iomgr/error.cc"],
    "grpc_error_string": ["src/core/lib/iomgr/error.cc"],

    "grpc_slice_ref(": ["src/core/lib/slice/slice.cc"],
    "grpc_slice_unref(": ["src/core/lib/slice/slice.cc"],

    "std::random_device": [
        "src/core/load_balancing/rls/rls.cc",
        "src/core/resolver/google_c2p/google_c2p_resolver.cc",
    ],

    "GPR_ASSERT": [],

    "absl::exchange": [],

    "absl::make_unique": [],

    "ABSL_FALLTHROUGH_INTENDED": [],

    "ABSL_MUST_USE_RESULT": [],

    "absl::variant": [],
    "absl::get": [],
    "absl::get_if": [],
    "absl::has_alternative": [],

    "absl::optional": [

        "src/core/config/config_vars.cc",
        "src/core/config/config_vars.h",
        "src/core/config/load_config.cc",
        "src/core/config/load_config.h",
    ],
    "absl::nullopt": [],
    "absl::make_optional": [],
    "std::make_pair": [],
    "std::make_tuple": [
        "src/core/call/filter_fusion.h",
    ],
}

errors = 0
num_files = 0
for root, dirs, files in os.walk("src/core"):
    if root.startswith("src/core/tsi"):
        continue
    for filename in files:
        num_files += 1
        path = os.path.join(root, filename)
        if os.path.splitext(path)[1] not in (".h", ".cc"):
            continue
        with open(path) as f:
            text = f.read()
        for banned, exceptions in list(BANNED_EXCEPT.items()):
            if path in exceptions:
                continue
            if banned in text:
                print(('Illegal use of "%s" in %s' % (banned, path)))
                errors += 1

assert errors == 0
if errors > 0:
    print(("Number of errors : %d " % (errors)))

assert num_files > 1900
