#!/bin/bash
# Copyright 2016 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -e

if [ "${RELATIVE_COPY_PATH}" == "" ]
then
  mkdir -p /var/local/git
  git clone "${EXTERNAL_GIT_ROOT}" /var/local/git/grpc

  # TODO: figure out a way to eliminate this following shellcheck suppressions

  (cd "${EXTERNAL_GIT_ROOT}" && git submodule foreach 'git clone ${EXTERNAL_GIT_ROOT}/${name} /var/local/git/grpc/${name}')
  (cd /var/local/git/grpc && git submodule init)
else
  mkdir -p "/var/local/git/grpc/${RELATIVE_COPY_PATH}"
  cp -r "${EXTERNAL_GIT_ROOT}/${RELATIVE_COPY_PATH}"/* "/var/local/git/grpc/${RELATIVE_COPY_PATH}"
fi

cd /var/local/git/grpc

ln -s "${EXTERNAL_GIT_ROOT}/reports" reports

if [ "${OUTPUT_DIR}" != "" ]
then
  ln -s "${EXTERNAL_GIT_ROOT}/${OUTPUT_DIR}" "${OUTPUT_DIR}"
fi

exit_code=0
${DOCKER_RUN_SCRIPT_COMMAND} || exit_code=$?

if [ -x "$(command -v ccache)" ]
then
  ccache --show-stats || true
fi

exit $exit_code
