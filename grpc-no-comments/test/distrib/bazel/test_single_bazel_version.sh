#!/usr/bin/env bash
# Copyright 2021 The gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

if [ "$#" == "0" ] ; then
    echo "Must supply bazel version to be tested." >/dev/stderr
    exit 1
fi

VERSION="$1"
shift 1

TEST_DIRECTORIES=(
  "cpp"
  "python"
)

ALL_TEST_SHARDS=("buildtest")
for TEST_DIRECTORY in "${TEST_DIRECTORIES[@]}"
do
  ALL_TEST_SHARDS+=("distribtest_${TEST_DIRECTORY}")
done

if [ "$#" != "0" ]
then

  TEST_SHARDS=("$@")
else

  TEST_SHARDS=("${ALL_TEST_SHARDS[@]}")
fi

cd "$(dirname "$0")"/../../..

EXCLUDED_TARGETS=(

  "-//src/objective-c/..."
  "-//third_party/objective_c/..."

  "-//src/proto/grpc/testing:test_gen_proto"

  "-//third_party/toolchains/rbe_windows_vs2022_bazel7/..."
  "-//third_party/toolchains:rbe_windows_default_toolchain_suite"

  "-//tools/bazelify_tests/..."

  "-//tools/artifact_gen/..."

  "-//tools/codegen/core/gen_experiments/..."
)

FAILED_TESTS=""

export OVERRIDE_BAZEL_VERSION="$VERSION"

export OVERRIDE_BAZEL_WRAPPER_DOWNLOAD_DIR=/tmp

ACTION_ENV_FLAG="--action_env=bazel_cache_invalidate=version_${VERSION}"

for TEST_SHARD in "${TEST_SHARDS[@]}"
do
  SHARD_RAN=""
  if [ "${TEST_SHARD}" == "buildtest" ] ; then
    tools/bazel version | grep "$VERSION" || { echo "Detected bazel version did not match expected value of $VERSION" >/dev/stderr; exit 1; }
    tools/bazel build "${ACTION_ENV_FLAG}" --build_tag_filters='-experiment_variation' -- //... "${EXCLUDED_TARGETS[@]}" || FAILED_TESTS="${FAILED_TESTS}buildtest "
    SHARD_RAN="true"
  fi

  for TEST_DIRECTORY in "${TEST_DIRECTORIES[@]}"
  do
    pushd "test/distrib/bazel/${TEST_DIRECTORY}/"
    if [ "${TEST_SHARD}" == "distribtest_${TEST_DIRECTORY}" ] ; then
      tools/bazel version | grep "$VERSION" || { echo "Detected bazel version did not match expected value of $VERSION" >/dev/stderr; exit 1; }
      tools/bazel test "${ACTION_ENV_FLAG}" --test_output=all //:all || FAILED_TESTS="${FAILED_TESTS}distribtest_${TEST_DIRECTORY} "
      SHARD_RAN="true"
    fi
    popd
  done

  if [ "${SHARD_RAN}" == "" ]; then
    echo "Unknown shard '${TEST_SHARD}'"
    exit 1
  fi
done

if [ "$FAILED_TESTS" != "" ]
then
  echo "Failed tests at version ${VERSION}: ${FAILED_TESTS}"
  exit 1
fi
