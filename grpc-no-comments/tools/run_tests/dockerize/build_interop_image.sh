#!/bin/bash
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

cd "$(dirname "$0")/../../.."
echo "GRPC_ROOT: ${GRPC_ROOT:=$(pwd)}"
MOUNT_ARGS="-v $GRPC_ROOT:/var/local/jenkins/grpc:ro"

echo "GRPC_JAVA_ROOT: ${GRPC_JAVA_ROOT:=$(cd ../grpc-java && pwd)}"
if [ -n "$GRPC_JAVA_ROOT" ]
then
  MOUNT_ARGS+=" -v $GRPC_JAVA_ROOT:/var/local/jenkins/grpc-java:ro"
else
  echo "WARNING: grpc-java not found, it won't be mounted to the docker container."
fi

echo "GRPC_GO_ROOT: ${GRPC_GO_ROOT:=$(cd ../grpc-go && pwd)}"
if [ -n "$GRPC_GO_ROOT" ]
then
  MOUNT_ARGS+=" -v $GRPC_GO_ROOT:/var/local/jenkins/grpc-go:ro"
else
  echo "WARNING: grpc-go not found, it won't be mounted to the docker container."
fi

echo "GRPC_DART_ROOT: ${GRPC_DART_ROOT:=$(cd ../grpc-dart && pwd)}"
if [ -n "$GRPC_DART_ROOT" ]
then
  MOUNT_ARGS+=" -v $GRPC_DART_ROOT:/var/local/jenkins/grpc-dart:ro"
else
  echo "WARNING: grpc-dart not found, it won't be mounted to the docker container."
fi

echo "GRPC_NODE_ROOT: ${GRPC_NODE_ROOT:=$(cd ../grpc-node && pwd)}"
if [ -n "$GRPC_NODE_ROOT" ]
then
  MOUNT_ARGS+=" -v $GRPC_NODE_ROOT:/var/local/jenkins/grpc-node:ro"
else
  echo "WARNING: grpc-node not found, it won't be mounted to the docker container."
fi

echo "GRPC_DOTNET_ROOT: ${GRPC_DOTNET_ROOT:=$(cd ../grpc-dotnet && pwd)}"
if [ -n "$GRPC_DOTNET_ROOT" ]
then
  MOUNT_ARGS+=" -v $GRPC_DOTNET_ROOT:/var/local/jenkins/grpc-dotnet:ro"
else
  echo "WARNING: grpc-dotnet not found, it won't be mounted to the docker container."
fi

if [ -e "$HOME/service_account" ]
then
  MOUNT_ARGS+=" -v $HOME/service_account:/var/local/jenkins/service_account:ro"
fi

BASE_IMAGE_DIR="tools/dockerfile/interoptest/$BASE_NAME"

BASE_IMAGE="$(cat "${BASE_IMAGE_DIR}.current_version")"

if [[ -t 0 ]]; then
  DOCKER_TTY_ARGS=("-it")
else

  DOCKER_TTY_ARGS=()
fi

CONTAINER_NAME="build_${BASE_NAME}_$(uuidgen)"

# TODO: Figure out if is safe to eliminate the suppression. It's currently here

(docker run \
  --cap-add SYS_PTRACE \
  --env-file "tools/run_tests/dockerize/docker_propagate_env.list" \
  "${DOCKER_TTY_ARGS[@]}" \
  $MOUNT_ARGS \
  $BUILD_INTEROP_DOCKER_EXTRA_ARGS \
  --name="$CONTAINER_NAME" \
  "$BASE_IMAGE" \
  bash -l "/var/local/jenkins/grpc/tools/dockerfile/interoptest/$BASE_NAME/build_interop.sh" \
  && docker commit "$CONTAINER_NAME" "$INTEROP_IMAGE" \
  && echo "Successfully built image $INTEROP_IMAGE")
EXITCODE=$?

docker rm -f "$CONTAINER_NAME"

exit $EXITCODE
