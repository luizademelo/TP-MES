#!/bin/bash
# Copyright 2021 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

cd "$(dirname "$0")/../../.."

export DOCKERFILE_DIR=tools/dockerfile/test/bazel

APPLICATION_DEFAULT_CREDENTIALS_DIR="$HOME/.config/gcloud"
export DOCKER_EXTRA_ARGS="-v=${APPLICATION_DEFAULT_CREDENTIALS_DIR}:/application_default_credentials:ro -e=GOOGLE_APPLICATION_CREDENTIALS=/application_default_credentials/application_default_credentials.json"

tools/docker_runners/run_in_docker.sh bazel "$@"
