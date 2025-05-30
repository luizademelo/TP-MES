#!/bin/bash
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

source tools/internal_ci/helper_scripts/prepare_build_linux_rc

SUBMODULE_NAME="${RUN_TESTS_FLAGS}"

SUBMODULE_BRANCH_NAME="${BAZEL_FLAGS:-master}"

(cd "third_party/${SUBMODULE_NAME}" && git fetch origin && git checkout "origin/${SUBMODULE_BRANCH_NAME}")

echo "This suite tests whether gRPC HEAD builds with HEAD of submodule '${SUBMODULE_NAME}'"
echo "If a test breaks, either"
echo "1) some change in the grpc repository has caused the failure"
echo "2) some change that was just merged in the submodule head has caused the failure."
echo ""
echo "submodule '${SUBMODULE_NAME}' is at commit: $(cd third_party/${SUBMODULE_NAME}; git rev-parse --verify HEAD)"
echo ""

case "$SUBMODULE_NAME" in
  abseil-cpp)
    BAZEL_DEP_NAME="com_google_absl"
    ;;
  boringssl)
    BAZEL_DEP_NAME="boringssl"
    ;;
  protobuf)
    BAZEL_DEP_NAME="com_google_protobuf"
    ;;
esac
if [ -z "$BAZEL_DEP_NAME" ]
then
   echo "No bazel dependency is specified so skipping bazel reconfiguration."
else
   BAZEL_DEP_PATH="$(pwd)/third_party/${SUBMODULE_NAME}"
   echo "bazel override_repository is set for ${BAZEL_DEP_NAME} to ${BAZEL_DEP_PATH}"
   echo "build --override_repository=${BAZEL_DEP_NAME}=${BAZEL_DEP_PATH}" >> "tools/bazel.rc"
   echo "query --override_repository=${BAZEL_DEP_NAME}=${BAZEL_DEP_PATH}" >> "tools/bazel.rc"
fi
echo ""

if [ "${SUBMODULE_NAME}" == "abseil-cpp" ]
then
  src/abseil-cpp/preprocessed_builds.yaml.gen.py
fi

if [ "${SUBMODULE_NAME}" == "protobuf" ]
then

  rm -rf third_party/upb/upb
  cp -r third_party/protobuf/upb third_party/upb

  export CC=gcc
  tools/codegen/core/gen_upb_api.sh

  rm -rf third_party/utf8_range
  cp -r third_party/protobuf/third_party/utf8_range third_party/utf8_range/
fi

tools/buildgen/generate_projects.sh

git add -A
git -c user.name='foo' -c user.email='foo@google.com' commit -m 'Update submodule' --allow-empty

tools/run_tests/run_tests_matrix.py -f linux --exclude c sanity basictests_arm64 openssl dbg --inner_jobs 16 -j 2 --build_only
