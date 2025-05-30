#!/bin/bash
# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# NOTE: These images are not intended to be used by gRPC end users,

set -e

cd $(dirname $0)/../..

if [ "${CHECK_MODE}" == "" ]
then

  docker run --rm -it debian:11 bash -c 'echo "sudoless docker run works!"' || \
      (echo "Error: docker not installed or sudoless docker doesn't work?" && exit 1)

  if [ "${HOST_ARCH_ONLY}" == "" ]; then

    docker run --rm --platform=linux/arm64 -it arm64v8/debian:11 bash -c 'echo "able to run arm64 docker images with an emulator!"' || \
        (echo "Error: can't run arm64 images under an emulator. Have you run 'sudo apt-get install qemu-user-static'?" && exit 1)
  fi
fi

ARTIFACT_REGISTRY_PREFIX=us-docker.pkg.dev/grpc-testing/testing-images-public

ALL_DOCKERFILE_DIRS=(
  tools/dockerfile/test/*
  tools/dockerfile/grpc_artifact_*
  tools/dockerfile/interoptest/*
  tools/dockerfile/distribtest/*
  third_party/rake-compiler-dock/*
)

EXCLUDE_DIRS=(
  tools/dockerfile/interoptest/grpc_interop_go1.8
)

ARM_DOCKERFILE_DIRS=(
  tools/dockerfile/distribtest/python_alpine_aarch64
  tools/dockerfile/distribtest/python_python39_buster_aarch64
  tools/dockerfile/grpc_artifact_python_musllinux_1_1_aarch64
  tools/dockerfile/test/bazel_arm64
  tools/dockerfile/test/csharp_debian11_arm64
  tools/dockerfile/test/php8_debian12_arm64
  tools/dockerfile/test/python_debian11_default_arm64
  tools/dockerfile/test/ruby_debian11_arm64
)

CHECK_FAILED=""

if [ "${CHECK_MODE}" != "" ]
then

  for CURRENTVERSION_FILE in $(find tools/ third_party/rake-compiler-dock -name '*.current_version')
  do
    DOCKERFILE_DIR="$(echo ${CURRENTVERSION_FILE} | sed 's/.current_version$//')"
    if [ ! -e "${DOCKERFILE_DIR}/Dockerfile" ]
    then
       echo "Found that ${DOCKERFILE_DIR} has '.current_version' file but there is no corresponding Dockerfile."
       echo "Should the ${CURRENTVERSION_FILE} file be deleted?"
       CHECK_FAILED=true
    fi
  done
fi

for DOCKERFILE_DIR in "${ALL_DOCKERFILE_DIRS[@]}"
do

  DOCKER_IMAGE_NAME=$(basename $DOCKERFILE_DIR)

  if [ ! -e "$DOCKERFILE_DIR/Dockerfile" ]; then
    continue
  else
    DOCKER_IMAGE_TAG=$(sha1sum $DOCKERFILE_DIR/Dockerfile | cut -f1 -d\ )
  fi

  exclude=false
  for exclude_dir in "${EXCLUDE_DIRS[@]}"; do
    if [[ "$DOCKERFILE_DIR" == "$exclude_dir" ]]; then
      exclude=true
      break
    fi
  done
  if $exclude; then
    continue
  fi

  echo "* Visiting ${DOCKERFILE_DIR}"

  if [ "${HOST_ARCH_ONLY}" != "" ]; then
    [[ "$(uname -m)" == aarch64 ]] && is_host_arm=1 || is_host_arm=0
    is_docker_for_arm=0
    for ARM_DOCKERFILE_DIR in "${ARM_DOCKERFILE_DIRS[@]}"; do
      if [ "$DOCKERFILE_DIR" == "$ARM_DOCKERFILE_DIR" ]; then
        is_docker_for_arm=1
        break
      fi
    done
    if [ "$is_host_arm" != "$is_docker_for_arm" ]; then
      echo "Skipped due to the different architecture:" ${DOCKER_IMAGE_NAME}
      continue
    fi
  fi

  if [[ -z "${LOCAL_ONLY_MODE}" && -z "${ALWAYS_BUILD}" ]]
  then

    DOCKER_IMAGE_DIGEST_REMOTE=$(gcloud artifacts docker images describe "${ARTIFACT_REGISTRY_PREFIX}/${DOCKER_IMAGE_NAME}:${DOCKER_IMAGE_TAG}" --format=json | jq -r '.image_summary.digest')

    if [ "${DOCKER_IMAGE_DIGEST_REMOTE}" != "" ]
    then

      echo "Docker image ${DOCKER_IMAGE_NAME} already exists in artifact registry at the right version (tag ${DOCKER_IMAGE_TAG})."

      VERSION_FILE_OUT_OF_DATE=""
      grep "^${ARTIFACT_REGISTRY_PREFIX}/${DOCKER_IMAGE_NAME}:${DOCKER_IMAGE_TAG}@${DOCKER_IMAGE_DIGEST_REMOTE}$" ${DOCKERFILE_DIR}.current_version >/dev/null || VERSION_FILE_OUT_OF_DATE="true"

      if [ "${VERSION_FILE_OUT_OF_DATE}" == "" ]
      then
        echo "Version file for ${DOCKER_IMAGE_NAME} is in sync with info from artifact registry."
        continue
      fi

      if [ "${CHECK_MODE}" != "" ]
      then
        echo "CHECK FAILED: Version file ${DOCKERFILE_DIR}.current_version is not in sync with info from artifact registry."
        CHECK_FAILED=true
        continue
      fi

      echo -n "${ARTIFACT_REGISTRY_PREFIX}/${DOCKER_IMAGE_NAME}:${DOCKER_IMAGE_TAG}@${DOCKER_IMAGE_DIGEST_REMOTE}" >${DOCKERFILE_DIR}.current_version

      continue
    fi

    if [ "${CHECK_MODE}" != "" ]
    then
      echo "CHECK FAILED: Docker image ${DOCKER_IMAGE_NAME} not found in artifact registry."
      CHECK_FAILED=true
      continue
    fi

  else
    echo "Skipped querying artifact registry (running in local-only mode)."
  fi

  LOCAL_BUILD_REQUIRED=""
  grep "^${ARTIFACT_REGISTRY_PREFIX}/${DOCKER_IMAGE_NAME}:${DOCKER_IMAGE_TAG}@sha256:.*$" ${DOCKERFILE_DIR}.current_version >/dev/null || LOCAL_BUILD_REQUIRED=true

  DIGEST_MISSING_IN_CURRENT_VERSION_FILE=""
  grep "^${ARTIFACT_REGISTRY_PREFIX}/${DOCKER_IMAGE_NAME}:${DOCKER_IMAGE_TAG}$" ${DOCKERFILE_DIR}.current_version >/dev/null && DIGEST_MISSING_IN_CURRENT_VERSION_FILE=true

  if [ "${LOCAL_BUILD_REQUIRED}" == "" ]
  then
    if [ "${ALWAYS_BUILD}" == "" ]; then
      echo "Dockerfile for ${DOCKER_IMAGE_NAME} hasn't changed. Will skip 'docker build'."
      continue
    else
      echo "Dockerfile for ${DOCKER_IMAGE_NAME} hasn't changed but will do 'docker build' anyway."
    fi
  fi

  if [ "${CHECK_MODE}" != "" ] && [ "${DIGEST_MISSING_IN_CURRENT_VERSION_FILE}" != "" ]
  then
    echo "CHECK FAILED: Dockerfile for ${DOCKER_IMAGE_NAME} has changed and was built locally, but looks like it hasn't been pushed."
    CHECK_FAILED=true
    continue
  fi
  if [ "${CHECK_MODE}" != "" ]
  then
    echo "CHECK FAILED: Dockerfile for ${DOCKER_IMAGE_NAME} has changed, but the ${DOCKERFILE_DIR}.current_version is not up to date."
    CHECK_FAILED=true
    continue
  fi

  echo "Running 'docker build' for ${DOCKER_IMAGE_NAME}"
  echo "=========="

  docker build \
    ${ALWAYS_BUILD:+--no-cache --pull} \
    -t ${ARTIFACT_REGISTRY_PREFIX}/${DOCKER_IMAGE_NAME}:${DOCKER_IMAGE_TAG} \
    -t ${ARTIFACT_REGISTRY_PREFIX}/${DOCKER_IMAGE_NAME}:infrastructure-public-image-${DOCKER_IMAGE_TAG} \
    ${DOCKERFILE_DIR}
  echo "=========="

  echo -n "${ARTIFACT_REGISTRY_PREFIX}/${DOCKER_IMAGE_NAME}:${DOCKER_IMAGE_TAG}" >${DOCKERFILE_DIR}.current_version

  if [ "${SKIP_UPLOAD}" == "" ] && [ "${LOCAL_ONLY_MODE}" == "" ]
  then
    docker push ${ARTIFACT_REGISTRY_PREFIX}/${DOCKER_IMAGE_NAME}:${DOCKER_IMAGE_TAG}
    docker push ${ARTIFACT_REGISTRY_PREFIX}/${DOCKER_IMAGE_NAME}:infrastructure-public-image-${DOCKER_IMAGE_TAG}

    DOCKER_IMAGE_DIGEST_REMOTE=$(docker image inspect "${ARTIFACT_REGISTRY_PREFIX}/${DOCKER_IMAGE_NAME}:${DOCKER_IMAGE_TAG}" | jq -e -r ".[0].RepoDigests[] | select(contains(\"${ARTIFACT_REGISTRY_PREFIX}/${DOCKER_IMAGE_NAME}@\"))" | sed 's/^.*@sha256:/sha256:/')
    echo -n "${ARTIFACT_REGISTRY_PREFIX}/${DOCKER_IMAGE_NAME}:${DOCKER_IMAGE_TAG}@${DOCKER_IMAGE_DIGEST_REMOTE}" >${DOCKERFILE_DIR}.current_version
  fi
done

if [ "${CHECK_MODE}" != "" ]
then

    CHECK_MODE="${CHECK_MODE}" tools/bazelify_tests/generate_dockerimage_current_versions_bzl.sh || CHECK_FAILED=true
else

    tools/bazelify_tests/generate_dockerimage_current_versions_bzl.sh
fi

if [ "${CHECK_FAILED}" != "" ]
then
  echo "ERROR: Some checks have failed."
  exit 1
fi

echo "All done."
