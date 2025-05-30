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
    -l c++ csharp ruby java python python_asyncio go php7 php7_protobuf_c \
    --netperf \
    --category smoketest \
    -u kbuilder \
    --bq_result_table performance_test.performance_experiment_singlevm \
    --xml_report run_performance_tests/singlemachine/sponge_log.xml
