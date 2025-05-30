#!/bin/bash
# Copyright 2021 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -e

readonly grpc_rootdir="$(dirname "$(readlink -f "$0")")/../.."
cd ${grpc_rootdir}

if [ "${DOCKERFILE_DIR}" == "" ]
then
    echo "You need to specify the docker image to use by setting DOCKERFILE_DIR env variable."
    echo "See docker image definitions under tools/dockerfile."
    echo ""
    echo "You likely want to set DOCKERFILE_DIR to one of these values:"
    find tools/dockerfile/test -name Dockerfile | xargs -n1 dirname
    exit 1
fi

DOCKER_NONROOT_ARGS=(

)

export DOCKER_EXTRA_ARGS="${DOCKER_NONROOT_ARGS[@]} ${DOCKER_EXTRA_ARGS}"

exec tools/run_tests/dockerize/build_and_run_docker.sh "$@"
