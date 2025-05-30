#!/bin/bash
# Copyright 2016 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

cd "$(dirname "$0")/../../.."
git_root=$(pwd)
cd -

DOCKER_IMAGE_NAME="$(cat "${DOCKERFILE_DIR}.current_version")"

if [[ -t 0 ]]; then
  DOCKER_TTY_ARGS=("-it")
else

  DOCKER_TTY_ARGS=()
fi

if [ "${DOCKER_RUN_SCRIPT}" != "" ]
then

  DOCKER_CMD_AND_ARGS=( bash -l "/var/local/jenkins/grpc/${DOCKER_RUN_SCRIPT}" )
  DOCKER_RUN_SCRIPT_ARGS=(

    "-e=DOCKER_RUN_SCRIPT_COMMAND=${DOCKER_RUN_SCRIPT_COMMAND}"

    "$@"
  )
else

  DOCKER_CMD_AND_ARGS=( "$@" )
  DOCKER_RUN_SCRIPT_ARGS=(

    "-w=/var/local/jenkins/grpc"
  )
fi

if [ "${KOKORO_KEYSTORE_DIR}" != "" ]
then
  MOUNT_KEYSTORE_DIR_ARGS=(
    "-v=${KOKORO_KEYSTORE_DIR}:/kokoro_keystore:ro"
    "-e=KOKORO_KEYSTORE_DIR=/kokoro_keystore"
  )
else
  MOUNT_KEYSTORE_DIR_ARGS=()
fi

if [ "${KOKORO_GFILE_DIR}" != "" ]
then
  MOUNT_GFILE_DIR_ARGS=(
    "-v=${KOKORO_GFILE_DIR}:/kokoro_gfile:ro"
    "-e=KOKORO_GFILE_DIR=/kokoro_gfile"
  )
else
  MOUNT_GFILE_DIR_ARGS=()
fi

if [ "${KOKORO_ARTIFACTS_DIR}" != "" ]
then
  MOUNT_ARTIFACTS_DIR_ARGS=(
    "-v=${KOKORO_ARTIFACTS_DIR}:/kokoro_artifacts"
    "-e=KOKORO_ARTIFACTS_DIR=/kokoro_artifacts"
  )
else
  MOUNT_ARTIFACTS_DIR_ARGS=()
fi

DOCKER_PRIVILEGED_ARGS=(

  "--cap-add=SYS_PTRACE"
)

DOCKER_PROPAGATE_ENV_ARGS=(
  "--env-file=tools/run_tests/dockerize/docker_propagate_env.list"
)

DOCKER_CLEANUP_ARGS=(

  "--rm=true"
)

DOCKER_NETWORK_ARGS=(

  "--sysctl=net.ipv6.conf.all.disable_ipv6=0"
)

DOCKER_IMAGE_IDENTITY_ARGS=(

  "-e=GRPC_TEST_DOCKER_IMAGE_IDENTITY=${DOCKER_IMAGE_NAME}"
)

# TODO: silence complaint about lack of quotes in some other way

DOCKER_EXTRA_ARGS_FROM_ENV=(

  # TODO: get rid of EXTRA_DOCKER_ARGS occurrences and replace with DOCKER_EXTRA_ARGS
  ${EXTRA_DOCKER_ARGS}
  ${DOCKER_EXTRA_ARGS}
)

EXTERNAL_GIT_ROOT=/var/local/jenkins/grpc

MOUNT_GIT_ROOT_ARGS=(
  "-v=${git_root}:${EXTERNAL_GIT_ROOT}"
  "-e=EXTERNAL_GIT_ROOT=${EXTERNAL_GIT_ROOT}"
)

TEMP_REPORT_DIR="$(mktemp -d)"

mkdir -p "${TEMP_REPORT_DIR}/reports"
mkdir -p "${git_root}/reports"

MOUNT_REPORT_DIR_ARGS=(

  "-v=${TEMP_REPORT_DIR}:/var/local/report_dir"

  "-v=${TEMP_REPORT_DIR}/reports:${EXTERNAL_GIT_ROOT}/reports"

  "-e=GRPC_TEST_REPORT_BASE_DIR=/var/local/report_dir"
)

if [ "${OUTPUT_DIR}" != "" ]
then

  TEMP_OUTPUT_DIR="$(mktemp -d)"

  mkdir -p "${TEMP_OUTPUT_DIR}/${OUTPUT_DIR}"
  mkdir -p "${git_root}/${OUTPUT_DIR}"

  MOUNT_OUTPUT_DIR_ARGS=(

    "-v=${TEMP_OUTPUT_DIR}/${OUTPUT_DIR}:${EXTERNAL_GIT_ROOT}/${OUTPUT_DIR}"
    "-e=OUTPUT_DIR=${OUTPUT_DIR}"
  )
else
  MOUNT_OUTPUT_DIR_ARGS=()
fi

DOCKER_EXIT_CODE=0

docker run \
  "${DOCKER_TTY_ARGS[@]}" \
  "${DOCKER_RUN_SCRIPT_ARGS[@]}" \
  "${MOUNT_KEYSTORE_DIR_ARGS[@]}" \
  "${MOUNT_GFILE_DIR_ARGS[@]}" \
  "${MOUNT_ARTIFACTS_DIR_ARGS[@]}" \
  "${DOCKER_PRIVILEGED_ARGS[@]}" \
  "${DOCKER_PROPAGATE_ENV_ARGS[@]}" \
  "${DOCKER_CLEANUP_ARGS[@]}" \
  "${DOCKER_NETWORK_ARGS[@]}" \
  "${DOCKER_IMAGE_IDENTITY_ARGS[@]}" \
  "${MOUNT_GIT_ROOT_ARGS[@]}" \
  "${MOUNT_REPORT_DIR_ARGS[@]}" \
  "${MOUNT_OUTPUT_DIR_ARGS[@]}" \
  "${DOCKER_EXTRA_ARGS_FROM_ENV[@]}" \
  "${DOCKER_IMAGE_NAME}" \
  "${DOCKER_CMD_AND_ARGS[@]}" || DOCKER_EXIT_CODE=$?

if [ "${GRPC_TEST_REPORT_BASE_DIR}" != "" ]
then
  mkdir -p "${GRPC_TEST_REPORT_BASE_DIR}"
  cp -r "${TEMP_REPORT_DIR}"/* "${GRPC_TEST_REPORT_BASE_DIR}" || true
else
  cp -r "${TEMP_REPORT_DIR}"/* "${git_root}" || true
fi

if [ "${OUTPUT_DIR}" != "" ]
then
  cp -r "${TEMP_OUTPUT_DIR}/${OUTPUT_DIR}" "${git_root}" || DOCKER_EXIT_CODE=$?
fi

exit $DOCKER_EXIT_CODE
