#!/bin/bash
# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
set -ex

GEM_PLATFORM="$1"

SYSTEM=$(uname | cut -f 1 -d_)

cd "$(dirname "$0")/../../.."

if [ "$SYSTEM" == "MSYS" ] ; then
  SYSTEM=MINGW32
fi
if [ "$SYSTEM" == "MINGW64" ] ; then
  SYSTEM=MINGW32
fi

if [ "$SYSTEM" == "MINGW32" ] ; then
  echo "Need Linux to build the Windows ruby gem."
  exit 1
fi

ruby --version

gem list || true

export BUNDLE_PATH=bundle_local_gems
tools/run_tests/helper_scripts/bundle_install_wrapper.sh

bundle exec rake "gem:native[${GEM_PLATFORM}]"

if [ "$SYSTEM" == "Darwin" ] ; then
  # TODO: consider rewriting this to pass shellcheck

  rm $(ls pkg/*.gem | grep -v darwin)
fi

mkdir -p "${ARTIFACTS_OUT}"

cp pkg/*.gem "${ARTIFACTS_OUT}"/
