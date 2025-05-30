# Copyright 2023 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

from libcpp cimport bool

cdef extern from "absl/debugging/failure_signal_handler.h" namespace "absl":
    ctypedef struct FailureSignalHandlerOptions "::absl::FailureSignalHandlerOptions":
        bool symbolize_stacktrace
        bool use_alternate_stack
        int alarm_on_failure_secs
        bool call_previous_handler
        void (*writerfn)(const char*)

    void InstallFailureSignalHandler(const FailureSignalHandlerOptions& options)

def install_failure_signal_handler(**kwargs):
    cdef FailureSignalHandlerOptions opts = FailureSignalHandlerOptions(
        True, False, -1, False, NULL
    )

    InstallFailureSignalHandler(opts)
