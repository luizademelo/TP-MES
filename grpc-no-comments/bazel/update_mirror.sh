#!/bin/bash
# Copyright 2020 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -e

cd $(dirname $0)/..

tmpdir="$(mktemp -d)"
function cleanup {
  rm -rf "$tmpdir"
}
trap cleanup EXIT

function upload {
  local file="$1"

  if gsutil stat "gs://grpc-bazel-mirror/${file}" > /dev/null
  then
    echo "Skipping ${file}"
  else
    echo "Downloading https://${file}"
    curl -L --fail --output "${tmpdir}/archive" "https://${file}"

    echo "Uploading https://${file} to https://storage.googleapis.com/grpc-bazel-mirror/${file}"
    gsutil cp "${tmpdir}/archive" "gs://grpc-bazel-mirror/${file}"

    rm -rf "${tmpdir}/archive"
  fi
}

upload github.com/bazelbuild/bazel/releases/download/7.4.1/bazel-7.4.1-linux-arm64
upload github.com/bazelbuild/bazel/releases/download/7.4.1/bazel-7.4.1-linux-x86_64
upload github.com/bazelbuild/bazel/releases/download/7.4.1/bazel-7.4.1-darwin-x86_64
upload github.com/bazelbuild/bazel/releases/download/7.4.1/bazel-7.4.1-windows-x86_64.exe
upload github.com/bazelbuild/bazel/releases/download/8.0.1/bazel-8.0.1-linux-arm64
upload github.com/bazelbuild/bazel/releases/download/8.0.1/bazel-8.0.1-linux-x86_64
upload github.com/bazelbuild/bazel/releases/download/8.0.1/bazel-8.0.1-darwin-x86_64
upload github.com/bazelbuild/bazel/releases/download/8.0.1/bazel-8.0.1-windows-x86_64.exe

grep -o '"https://github.com/[^"]*"' bazel/grpc_deps.bzl | sed 's/^"https:\/\///' | sed 's/"$//' | while read -r line ; do
    echo "Updating mirror for ${line}"
    upload "${line}"
done
