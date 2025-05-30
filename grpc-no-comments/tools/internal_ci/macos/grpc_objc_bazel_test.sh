#!/usr/bin/env bash
# Copyright 2022 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

source $(dirname $0)/../../../tools/internal_ci/helper_scripts/move_src_tree_and_respawn_itself_rc

cd $(dirname $0)/../../..

source tools/internal_ci/helper_scripts/prepare_build_macos_rc

sudo ln -s $(which python3) /usr/bin/python3 || true

tools/bazel version

KOKORO_IMAGE_VERSION="$(cat /VERSION)"

BAZEL_REMOTE_CACHE_ARGS=(

  --remote_upload_local_results=true

  --remote_default_exec_properties="grpc_cache_silo_key1=83d8e488-1ca9-40fd-929e-d37d13529c99"

  --remote_default_exec_properties="grpc_cache_silo_key2=${KOKORO_IMAGE_VERSION}"
)

EXAMPLE_TARGETS=(

  //src/objective-c/examples:Sample
  //src/objective-c/examples:tvOS-sample
)

TEST_TARGETS=(

  //src/objective-c/tests:InteropTestsLocalCleartext
  //src/objective-c/tests:InteropTestsLocalSSL
  //src/objective-c/tests:InteropTestsRemote
  //src/objective-c/tests:MacTests
  //src/objective-c/tests:UnitTests

  //src/objective-c/tests:CFStreamTests

  //src/objective-c/tests:EventEngineClientTests
  //src/objective-c/tests:tvtests_build_test

  //src/objective-c/tests:objc_codegen_plugin_test
  //src/objective-c/tests:objc_codegen_plugin_option_test
)

python3 tools/run_tests/python_utils/bazel_report_helper.py --report_path build_interop_server
build_interop_server/bazel_wrapper \
  --output_base=.bazel_rbe \
  --bazelrc=tools/remote_build/mac.bazelrc \
  build \
  --google_credentials="${KOKORO_GFILE_DIR}/GrpcTesting-d0eeee2db331.json" \
  "${BAZEL_REMOTE_CACHE_ARGS[@]}" \
  -- \
  //test/cpp/interop:interop_server

python3 tools/run_tests/start_port_server.py

PLAIN_PORT=$(curl localhost:32766/get)
TLS_PORT=$(curl localhost:32766/get)

INTEROP_SERVER_BINARY=bazel-bin/test/cpp/interop/interop_server

"${INTEROP_SERVER_BINARY}" --port=$PLAIN_PORT --max_send_message_size=8388608 &
"${INTEROP_SERVER_BINARY}" --port=$TLS_PORT --max_send_message_size=8388608 --use_tls &

trap 'echo "KILLING interop_server binaries running on the background"; kill -9 $(jobs -p)' EXIT

OBJC_TEST_ENV_ARGS=(
  --test_env=HOST_PORT_LOCAL=localhost:$PLAIN_PORT
  --test_env=HOST_PORT_LOCALSSL=localhost:$TLS_PORT
)

python3 tools/run_tests/python_utils/bazel_report_helper.py --report_path objc_bazel_tests

# NOTE: When using bazel to run the tests, test env variables like GRPC_VERBOSITY or GRPC_TRACE

objc_bazel_tests/bazel_wrapper \
  --bazelrc=tools/remote_build/include/test_locally_with_resultstore_results.bazelrc \
  test \
  --google_credentials="${KOKORO_GFILE_DIR}/GrpcTesting-d0eeee2db331.json" \
  "${BAZEL_REMOTE_CACHE_ARGS[@]}" \
  $BAZEL_FLAGS \
  --cxxopt=-DGRPC_IOS_EVENT_ENGINE_CLIENT=0 \
  --test_env=GRPC_VERBOSITY=debug --test_env=GRPC_TRACE=event_engine*,api \
  "${OBJC_TEST_ENV_ARGS[@]}" \
  -- \
  "${EXAMPLE_TARGETS[@]}" \
  "${TEST_TARGETS[@]}"

EVENT_ENGINE_TEST_TARGETS=(
  //src/objective-c/tests:InteropTestsLocalCleartext
  //src/objective-c/tests:InteropTestsLocalSSL
  //src/objective-c/tests:InteropTestsRemote
  //src/objective-c/tests:MacTests
  //src/objective-c/tests:UnitTests
  //src/objective-c/tests:EventEngineUnitTests
  //src/objective-c/tests:CFStreamTests
  //src/objective-c/tests:tvtests_build_test
)

python3 tools/run_tests/python_utils/bazel_report_helper.py --report_path objc_event_engine_bazel_tests

objc_event_engine_bazel_tests/bazel_wrapper \
  --bazelrc=tools/remote_build/include/test_locally_with_resultstore_results.bazelrc \
  test \
  --google_credentials="${KOKORO_GFILE_DIR}/GrpcTesting-d0eeee2db331.json" \
  "${BAZEL_REMOTE_CACHE_ARGS[@]}" \
  $BAZEL_FLAGS \
  --test_env=GRPC_EXPERIMENTS=event_engine_client \
  --test_env=GRPC_VERBOSITY=debug --test_env=GRPC_TRACE=event_engine*,api \
  "${OBJC_TEST_ENV_ARGS[@]}" \
  -- \
  "${EXAMPLE_TARGETS[@]}" \
  "${EVENT_ENGINE_TEST_TARGETS[@]}"
