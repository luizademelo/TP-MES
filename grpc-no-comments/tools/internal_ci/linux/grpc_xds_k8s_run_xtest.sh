#!/usr/bin/env bash
# Copyright 2022 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

readonly IMAGE_REPO="us-docker.pkg.dev/grpc-testing/psm-interop"

find_latest() {
  gcloud container images list-tags --filter='tags~v1\.\d+\.x' "${IMAGE_REPO}/${1}-${2}" --flatten='tags[]' --format='value(tags)' | sort --version-sort | tail -n 1
}

find_latest_branch() {
  local latest_branch=$1
  if [ "${latest_branch}" == "" ]; then
    cpp_server=$(find_latest cpp server)
    cpp_client=$(find_latest cpp client)
    go_server=$(find_latest go server)
    go_client=$(find_latest go client)
    java_server=$(find_latest java server)
    java_client=$(find_latest java client)
    latest_branch=$( (printf "%s\n" "${cpp_server}" "${cpp_client}" "${go_server}" "${go_client}" "${java_server}" "${java_client}") | sort --version-sort | head -1)
  fi
  echo ${latest_branch}
}

find_oldest_branch() {
  local oldest_branch=$1
  local latest_branch=$2
  if [ "${oldest_branch}" == "" ]; then
    major_branch=$( echo "${latest_branch}" | cut -f 2 -d.)
    oldest_branch="v1.$(( major_branch - 9)).x"
  fi
  echo ${oldest_branch}
}

run_test() {
  if [ "$#" -ne 6 ]; then
    echo "Usage: run_test client_lang client_branch server_lang server_branch cl-branch-fixed srv-branch-fixed" >&2
    exit 1
  fi

  local client_lang="$1"
  local client_branch="$2"
  local server_lang="$3"
  local server_branch="$4"
  local client_branch_fixed="$5"
  local server_branch_fixed="$6"
  local server_image_name="${IMAGE_REPO}/${server_lang}-server"
  local client_image_name="${IMAGE_REPO}/${client_lang}-client"

  server_tags="$(gcloud_gcr_list_image_tags "${server_image_name}" "${server_branch}")"
  echo "${server_tags:?Server image not found}"

  client_tags="$(gcloud_gcr_list_image_tags "${client_image_name}" "${client_branch}")"
  echo "${client_tags:?Client image not found}"

  local server_image_name_tag="${server_image_name}:${server_branch}"
  local client_image_name_tag="${client_image_name}:${client_branch}"

  local out_dir="${TEST_XML_OUTPUT_DIR}/${client_branch_fixed}-${server_branch_fixed}/${client_lang}-${server_lang}"
  mkdir -pv "${out_dir}"
  set -x
  echo "Client branch='${client_branch}', Server branch='${server_branch}'" > ${out_dir}/sponge_log.log
  python -m "tests.security_test" \
    --flagfile="${TEST_DRIVER_FLAGFILE}" \
    --kube_context="${KUBE_CONTEXT}" \
    --server_image="${server_image_name_tag}" \
    --client_image="${client_image_name_tag}" \
    --testing_version="${TESTING_VERSION}" \
    --nocheck_local_certs \
    --force_cleanup \
    --collect_app_logs \
    --log_dir="${out_dir}" \
    --xml_output_file="${out_dir}/sponge_log.xml" \
    |& tee -a "${out_dir}/sponge_log.log"
}
