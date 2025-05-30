#!/bin/bash
# Copyright 2023 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -e

ARCHIVE_WO_SUBMODULES="$1"
ARCHIVE_WITH_SUBMODULES="$2"
export ARCHIVES_DIR="$(pwd)/archives"

export ARCHIVE_FORMAT=tar

mkdir -p "${ARCHIVES_DIR}"
rm -rf "${ARCHIVES_DIR}"/*

# HACK: To be able to collect all grpc source files as an archive

FIRST_PATH_COMPONENT="$(echo $0 | sed 's|/.*||')"
ORIGINAL_BAZEL_WORKSPACE_ROOT="$(dirname $(readlink ${FIRST_PATH_COMPONENT}))"

GRPC_GIT_COMMIT_FROM_STABLE_STATUS=$(grep ^STABLE_GRPC_GIT_COMMIT bazel-out/stable-status.txt | cut -d' ' -f2)

if [ "${GRPC_GIT_COMMIT_FROM_STABLE_STATUS}" == "" ]
then
  echo "Failed to obtain info about gRPC git commit from the bazel workspace. Make sure you invoke bazel with --workspace_status_command=tools/bazelify_tests/workspace_status_cmd.sh" >&2
  exit 1
fi

GRPC_UNCOMMITTED_PATCH_CHECKSUM_FROM_STABLE_STATUS=$(grep ^STABLE_GRPC_UNCOMMITTED_PATCH_CHECKSUM bazel-out/stable-status.txt | cut -d' ' -f2)
GRPC_GIT_WORKSPACE_DIRTY_FROM_STABLE_STATUS=$(grep ^STABLE_GRPC_GIT_WORKSPACE_DIRTY bazel-out/stable-status.txt | cut -d' ' -f2)

pushd ${ORIGINAL_BAZEL_WORKSPACE_ROOT} >/dev/null

if [ "${GRPC_GIT_COMMIT_FROM_STABLE_STATUS}" != "$(git rev-parse HEAD)" ]
then
  echo "Info about gRPC commit from stable-status.txt doesn't match the commit at which the workspace root is." >&2
  echo "This is unexpected and giving up early is better than risking to end up with bogus results." >&2
  exit 1
fi

mkdir -p ${ARCHIVES_DIR}/grpc
git archive --format="${ARCHIVE_FORMAT}" HEAD >"${ARCHIVES_DIR}/grpc/$(git rev-parse HEAD).${ARCHIVE_FORMAT}"

if [ "${GRPC_UNCOMMITTED_PATCH_CHECKSUM_FROM_STABLE_STATUS}" != "" ]
then
  git diff HEAD >"${ARCHIVES_DIR}/grpc/grpc_uncommited_${GRPC_UNCOMMITTED_PATCH_CHECKSUM_FROM_STABLE_STATUS}.patch"

  echo "${GRPC_UNCOMMITTED_PATCH_CHECKSUM_FROM_STABLE_STATUS} ${ARCHIVES_DIR}/grpc/grpc_uncommited_${GRPC_UNCOMMITTED_PATCH_CHECKSUM_FROM_STABLE_STATUS}.patch" | sha256sum --quiet --check
fi

git submodule --quiet foreach 'git_commit="$(git rev-parse HEAD)"; mkdir -p ${ARCHIVES_DIR}/${name}; git archive --format=${ARCHIVE_FORMAT} HEAD >${ARCHIVES_DIR}/${name}/${git_commit}.${ARCHIVE_FORMAT}'

popd >/dev/null

mkdir grpc
tar -xopf "${ARCHIVES_DIR}/grpc/${GRPC_GIT_COMMIT_FROM_STABLE_STATUS}.${ARCHIVE_FORMAT}" -C grpc

if [ "${GRPC_UNCOMMITTED_PATCH_CHECKSUM_FROM_STABLE_STATUS}" != "" ]
then
  pushd grpc >/dev/null
  patch --quiet -p1 <"${ARCHIVES_DIR}/grpc/grpc_uncommited_${GRPC_UNCOMMITTED_PATCH_CHECKSUM_FROM_STABLE_STATUS}.patch"
  popd >/dev/null
fi

DETERMINISTIC_TAR_ARGS=(
  --sort=name

  --mtime="@1420070400"
  --owner=0
  --group=0
  --numeric-owner
  --pax-option=exthdr.name=%d/PaxHeaders/%f,delete=atime,delete=ctime
)

tar "${DETERMINISTIC_TAR_ARGS[@]}" -czf ${ARCHIVE_WO_SUBMODULES} grpc

SUBMODULE_ARCHIVE_LIST="$(grep 'STABLE_GRPC_SUBMODULE_ARCHIVES ' bazel-out/stable-status.txt | sed 's/^STABLE_GRPC_SUBMODULE_ARCHIVES //')"

for submodule_archive in ${SUBMODULE_ARCHIVE_LIST}
do
 archive_subdir="grpc/$(dirname ${submodule_archive})"
 mkdir -p $archive_subdir

 tar -xopf "${ARCHIVES_DIR}/${submodule_archive}.${ARCHIVE_FORMAT}" -C $archive_subdir
done

tar "${DETERMINISTIC_TAR_ARGS[@]}" -czf ${ARCHIVE_WITH_SUBMODULES} grpc

rm -rf "${ARCHIVES_DIR}" grpc
