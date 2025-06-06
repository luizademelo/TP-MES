#! /bin/bash
# Copyright 2019 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -e

BUILDIFIER_VERSION="8.0.0"
TEMP_BUILDIFIER_PATH="/tmp/buildifier"
EXTRA_BUILDIFIER_FLAGS="$*"

function error_handling() {
    error=$1
    if [[ -n "$error" ]]; then
        echo "${error}"
        exit 1
    fi
}

function download_buildifier() {
    platform="$(uname -sm)"
    case "${platform}" in
        "Linux x86_64")  download_link="https://github.com/bazelbuild/buildtools/releases/download/v${BUILDIFIER_VERSION}/buildifier-linux-amd64";;
        "Linux aarch64") download_link="https://github.com/bazelbuild/buildtools/releases/download/v${BUILDIFIER_VERSION}/buildifier-linux-arm64";;
        "Darwin x86_64") download_link="https://github.com/bazelbuild/buildtools/releases/download/v${BUILDIFIER_VERSION}/buildifier-darwin-amd64";;
        "Darwin arm64")  download_link="https://github.com/bazelbuild/buildtools/releases/download/v${BUILDIFIER_VERSION}/buildifier-darwin-arm64";;
        *)               error_handling "Unsupported platform: ${platform}";;
    esac

    if [ -x "$(command -v curl)" ]; then
        curl -L -o ${TEMP_BUILDIFIER_PATH} ${download_link}
    elif [ -x "$(command -v wget)" ]; then
        wget -O ${TEMP_BUILDIFIER_PATH} ${download_link}
    else
        error_handling "Download failed: curl and wget not available"
    fi

    chmod +x ${TEMP_BUILDIFIER_PATH}
}

if [ -x "$(command -v buildifier)" ]; then
    existing_buildifier_version="$(buildifier -version 2>&1 | head -n1 | cut -d" " -f3)"
    if [[ "${existing_buildifier_version}" != "${BUILDIFIER_VERSION}" ]]; then
        download_buildifier
        buildifier_bin="${TEMP_BUILDIFIER_PATH}"
    else
        buildifier_bin="buildifier"
    fi
else
    download_buildifier
    buildifier_bin="${TEMP_BUILDIFIER_PATH}"
fi

dir=$(dirname "${0}")
cd "${dir}/../.."

bazel_files=$(find . \( -iname 'BUILD' -o -iname '*.bzl' -o -iname '*.bazel' -o -iname 'WORKSPACE' \) -type f -not -path "./third_party/*")

${buildifier_bin} ${EXTRA_BUILDIFIER_FLAGS[@]} -v ${bazel_files}
