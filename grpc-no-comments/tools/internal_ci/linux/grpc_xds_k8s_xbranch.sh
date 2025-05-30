#!/usr/bin/env bash
# Copyright 2022 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -eo pipefail

readonly GITHUB_REPOSITORY_NAME="grpc"
readonly TEST_DRIVER_INSTALL_SCRIPT_URL="https://raw.githubusercontent.com/${TEST_DRIVER_REPO_OWNER:-grpc}/psm-interop/${TEST_DRIVER_BRANCH:-main}/.kokoro/psm_interop_kokoro_lib.sh"
readonly LANGS="cpp go java"
readonly MAIN_BRANCH="${MAIN_BRANCH:-master}"

main() {
  local script_dir
  script_dir="${PWD}/$(dirname "$0")"

  echo "Sourcing test driver install script from: ${TEST_DRIVER_INSTALL_SCRIPT_URL}"
  source /dev/stdin <<< "$(curl -s "${TEST_DRIVER_INSTALL_SCRIPT_URL}")"

  activate_gke_cluster GKE_CLUSTER_PSM_SECURITY

  set -x
  if [[ -n "${KOKORO_ARTIFACTS_DIR}" ]]; then
    kokoro_setup_test_driver "${GITHUB_REPOSITORY_NAME}"
    if [ "${TESTING_VERSION}" != "master" ]; then
      echo "Skipping cross branch testing for non-master branch ${TESTING_VERSION}"
      exit 0
    fi
    cd "${TEST_DRIVER_FULL_DIR}"
  else
    local_setup_test_driver "${script_dir}"
    cd "${SRC_DIR}/${TEST_DRIVER_PATH}"
  fi

  source "${script_dir}/grpc_xds_k8s_run_xtest.sh"

  local failed_tests=0
  local successful_string
  local failed_string
  LATEST_BRANCH=$(find_latest_branch "${LATEST_BRANCH}")
  OLDEST_BRANCH=$(find_oldest_branch "${OLDEST_BRANCH}" "${LATEST_BRANCH}")

  for LANG in ${LANGS}
  do
    if run_test "${LANG}" "${MAIN_BRANCH}" "${LANG}" "${LATEST_BRANCH}" "${MAIN_BRANCH}" "latest"; then
      successful_string="${successful_string} ${MAIN_BRANCH}-${LATEST_BRANCH}/${LANG}"
    else
      failed_tests=$((failed_tests + 1))
      failed_string="${failed_string} ${MAIN_BRANCH}-${LATEST_BRANCH}/${LANG}"
    fi
    if run_test "${LANG}" "${LATEST_BRANCH}" "${LANG}" "${MAIN_BRANCH}" "latest" "${MAIN_BRANCH}"; then
      successful_string="${successful_string} ${LATEST_BRANCH}-${MAIN_BRANCH}/${LANG}"
    else
      failed_tests=$((failed_tests + 1))
      failed_string="${failed_string} ${LATEST_BRANCH}-${MAIN_BRANCH}/${LANG}"
    fi
    if run_test "${LANG}" "${MAIN_BRANCH}" "${LANG}" "${OLDEST_BRANCH}" "${MAIN_BRANCH}" "oldest"; then
      successful_string="${successful_string} ${MAIN_BRANCH}-${OLDEST_BRANCH}/${LANG}"
    else
      failed_tests=$((failed_tests + 1))
      failed_string="${failed_string} ${MAIN_BRANCH}-${OLDEST_BRANCH}/${LANG}"
    fi
    if run_test "${LANG}" "${OLDEST_BRANCH}" "${LANG}" "${MAIN_BRANCH}" "oldest" "${MAIN_BRANCH}"; then
      successful_string="${successful_string} ${OLDEST_BRANCH}-${MAIN_BRANCH}/${LANG}"
    else
      failed_tests=$((failed_tests + 1))
      failed_string="${failed_string} ${OLDEST_BRANCH}-${MAIN_BRANCH}/${LANG}"
    fi
  done
  set +x
  echo "Failed test suites list: ${failed_string}"
  echo "Successful test suites list: ${successful_string}"
  if (( failed_tests > 0 )); then
    exit 1
  fi
}

main "$@"
