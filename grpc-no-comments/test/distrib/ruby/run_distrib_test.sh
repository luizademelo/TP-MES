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

cd "$(dirname "$0")"

function die {
  echo "$1"
  exit 1
}

ARCH="$1"
PLATFORM="$2"
PACKAGE_TYPE="$3"
PROTOBUF_VERSION="$4"

echo "$EXTERNAL_GIT_ROOT"
GRPC_VERSION="$(ruby -e 'require ENV["EXTERNAL_GIT_ROOT"] + "/src/ruby/lib/grpc/version.rb"; puts GRPC::VERSION')"
if [[ "$PACKAGE_TYPE" == "source" ]]; then
  GEM_NAME="grpc-${GRPC_VERSION}.gem"
else
  [[ "$PACKAGE_TYPE" == "binary" ]] || die "unexpeced package type: $PACKAGE_TYPE"
  GEM_NAME="grpc-${GRPC_VERSION}-${ARCH}-${PLATFORM}.gem"
fi

GEM_SOURCE=../../../gem_source
mkdir -p "${GEM_SOURCE}/gems"
cp "${EXTERNAL_GIT_ROOT}/input_artifacts/${GEM_NAME}" "${GEM_SOURCE}/gems"
# TODO: rewrite the following line to be shellcheck-compliant

if [[ "$(ls "${GEM_SOURCE}/gems" | grep -c grpc)" != 1 ]]; then
  echo "Sanity check failed. Copied over more than one grpc gem into the gem source directory."
  exit 1
fi;
gem install builder
gem generate_index --directory "${GEM_SOURCE}"

if [[ -n "$PROTOBUF_VERSION" ]]; then
  bundle add google-protobuf --version "~> $PROTOBUF_VERSION"
fi;

bundle install

bundle exec ./distribtest.rb

[[ "$PACKAGE_TYPE" == "source" ]] && exit 0

INSTALLATION_DIR="$(gem env | grep '\- INSTALLATION DIRECTORY' | awk '{ print $4 }')"
if [[ "$(find "$INSTALLATION_DIR" -name 'grpc_c.so' | wc -l)" == 0 ]]; then
  echo "Sanity check failed. The gRPC package is not installed in $INSTALLATION_DIR."
  exit 1
fi
LIBRUBY_DEPENDENCY_EXISTS="$(find "$INSTALLATION_DIR" -name 'grpc_c.so' -exec ldd {} \; | grep -c 'libruby')" || true
if [[ "$LIBRUBY_DEPENDENCY_EXISTS" != 0 ]]; then
  echo "A grpc_c.so file in this binary gRPC package is dynamically linked to libruby."
fi
DEPENDENCY_NOT_FOUND="$(find "$INSTALLATION_DIR" -name 'grpc_c.so' -exec ldd {} \; | grep -c 'not found')" || true
if [[ "$DEPENDENCY_NOT_FOUND" != 0 ]]; then
  echo "A grpc_c.so file in this binary gRPC package has an non-portable dependency."
fi
if [ "$LIBRUBY_DEPENDENCY_EXISTS" != 0 ] || [ "$DEPENDENCY_NOT_FOUND" != 0 ]; then
  exit 1
fi
