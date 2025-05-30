#!/usr/bin/env bash
# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
set -ex

cd $(dirname $0)/../../..

source tools/internal_ci/helper_scripts/prepare_build_linux_perf_multilang_rc

tools/run_tests/run_performance_tests.py \
    -l c++ csharp ruby java python python_asyncio go php7 php7_protobuf_c node \
    --netperf \
    --category scalable \
    --remote_worker_host grpc-kokoro-performance-server-8core grpc-kokoro-performance-client-8core grpc-kokoro-performance-client2-8core \
    -u kbuilder \
    --bq_result_table performance_test.performance_experiment \
    --xml_report run_performance_tests/8core/sponge_log.xml \
    || EXIT_CODE=1

git clean -fdxq -e reports -e run_performance_tests

tools/run_tests/run_performance_tests.py \
    -l c++ java csharp go \
    --netperf \
    --category scalable \
    --remote_worker_host grpc-kokoro-performance-server-32core grpc-kokoro-performance-client-32core grpc-kokoro-performance-client2-32core \
    -u kbuilder \
    --bq_result_table performance_test.performance_experiment_32core \
    --xml_report run_performance_tests/32core/sponge_log.xml \
    || EXIT_CODE=1

git clean -fdxq -e reports -e run_performance_tests

exit $EXIT_CODE
