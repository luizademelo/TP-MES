#!/usr/bin/env python3

# Copyright 2024 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import os
import sys

os.chdir(os.path.join(os.path.dirname(sys.argv[0]), "../../.."))

RUBY_PHP_ALLOW_LIST = [
    "./include/grpc/support/log.h",
    "./src/core/util/log.cc",
    "./src/php/ext/grpc/call_credentials.c",
    "./src/php/ext/grpc/channel.c",
    "./src/ruby/ext/grpc/rb_call.c",
    "./src/ruby/ext/grpc/rb_call_credentials.c",
    "./src/ruby/ext/grpc/rb_channel.c",
    "./src/ruby/ext/grpc/rb_event_thread.c",
    "./src/ruby/ext/grpc/rb_grpc.c",
    "./src/ruby/ext/grpc/rb_server.c",
]

DEPRECATED_FUNCTION_TEMP_ALLOW_LIST = {

    "grpc_absl_log(": RUBY_PHP_ALLOW_LIST,
    "grpc_absl_log_int(": RUBY_PHP_ALLOW_LIST,
    "grpc_absl_log_str(": RUBY_PHP_ALLOW_LIST,

    "gpr_assertion_failed": [],
    "gpr_log(": [],
    "gpr_log_func_args": [],
    "gpr_log_message": [],
    "gpr_log_severity_string": [],
    "gpr_set_log_function": [],
    "gpr_set_log_verbosity": [],
    "gpr_should_log": [],
    "GPR_ASSERT": [],
    "GPR_DEBUG_ASSERT": [],
}

errors = 0
num_files = 0
for root, dirs, files in os.walk("."):
    for filename in files:
        num_files += 1
        path = os.path.join(root, filename)
        if os.path.splitext(path)[1] not in (".h", ".cc", ".c"):
            continue
        with open(path) as f:
            text = f.read()
        for deprecated, allowlist in list(
            DEPRECATED_FUNCTION_TEMP_ALLOW_LIST.items()
        ):
            if path in allowlist:
                continue
            if deprecated in text:
                print(
                    (
                        'Illegal use of "%s" in %s. Use absl functions instead.'
                        % (deprecated, path)
                    )
                )
                errors += 1

assert errors == 0
if errors > 0:
    print(("Number of errors : %d " % (errors)))

assert num_files > 18000
print("Number of files checked : %d " % (num_files))
