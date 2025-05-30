#!/usr/bin/env bash
# Copyright 2021 The gRPC Authors

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

readonly KEEP_HOURS="${KEEP_HOURS:-48}"

cleanup::activate_cluster() {
  activate_gke_cluster "$1"
  gcloud container clusters get-credentials "${GKE_CLUSTER_NAME}" \
    --zone "${GKE_CLUSTER_ZONE}"
  CLEANUP_KUBE_CONTEXT="$(kubectl config current-context)"
}

cleanup::activate_secondary_cluster_as_primary() {
  activate_secondary_gke_cluster "$1"
  GKE_CLUSTER_NAME="${SECONDARY_GKE_CLUSTER_NAME}"
  GKE_CLUSTER_ZONE="${SECONDARY_GKE_CLUSTER_ZONE}"
  gcloud container clusters get-credentials "${GKE_CLUSTER_NAME}" \
    --zone "${GKE_CLUSTER_ZONE}"
  CLEANUP_KUBE_CONTEXT="$(kubectl config current-context)"
}

cleanup::job::cleanup_td() {
  cleanup::run_clean "$1" --mode=td
}

cleanup::job::cleanup_td_dualstack() {
  cleanup::run_clean "$1" \
    --mode=td_no_legacy \
    --td_resource_prefixes='psm-ds' \
    --flagfile=config/common-dualstack.cfg
}

cleanup::job::cleanup_cluster_lb_primary() {
  cleanup::activate_cluster GKE_CLUSTER_PSM_LB
  cleanup::run_clean "$1" --mode=k8s
}

cleanup::job::cleanup_cluster_lb_secondary() {
  cleanup::activate_secondary_cluster_as_primary GKE_CLUSTER_PSM_LB
  cleanup::run_clean "$1" --mode=k8s --secondary
}

cleanup::job::cleanup_cluster_url_map() {
  cleanup::activate_cluster GKE_CLUSTER_PSM_BASIC
  cleanup::run_clean "$1" --mode=k8s
}

cleanup::job::cleanup_cluster_security() {
  cleanup::activate_cluster GKE_CLUSTER_PSM_SECURITY
  cleanup::run_clean "$1" --mode=k8s
}

cleanup::job::cleanup_cluster_gamma() {
  cleanup::activate_cluster GKE_CLUSTER_PSM_CSM
  cleanup::run_clean "$1" --mode=k8s
}

cleanup::job::cleanup_cluster_dualstack() {
  cleanup::activate_cluster GKE_CLUSTER_DUALSTACK
  cleanup::run_clean "$1" \
    --mode=k8s \
    --server_prefixes='psm-ds' \
    --client_prefixes='psm-ds' \
    --flagfile=config/common-dualstack.cfg
}

cleanup::run_clean() {
  local job_name="${1:?Usage: cleanup::run_clean job_name}"
  local out_dir="${TEST_XML_OUTPUT_DIR}/${job_name}"
  mkdir -pv "${out_dir}"

  python3 -m bin.cleanup.cleanup \
    --flagfile="${TEST_DRIVER_FLAGFILE}" \
    --kube_context="${CLEANUP_KUBE_CONTEXT:-unset}" \
    --keep_hours="${KEEP_HOURS}" \
    "${@:2}" \
    |& tee "${out_dir}/sponge_log.log"
}

main() {
  local script_dir
  script_dir="$(dirname "$0")"

  echo "Sourcing test driver install captured from: ${TEST_DRIVER_INSTALL_SCRIPT_URL}"
  source /dev/stdin <<< "$(curl -s "${TEST_DRIVER_INSTALL_SCRIPT_URL}")"
  set +x

  activate_gke_cluster GKE_CLUSTER_PSM_BASIC
  kokoro_setup_test_driver "${GITHUB_REPOSITORY_NAME}"

  cd "${TEST_DRIVER_FULL_DIR}"
  local failed_jobs=0
  declare -a cleanup_jobs
  cleanup_jobs=(
    "cleanup_td"
    "cleanup_td_dualstack"
    "cleanup_cluster_lb_primary"
    "cleanup_cluster_lb_secondary"
    "cleanup_cluster_security"
    "cleanup_cluster_url_map"
    "cleanup_cluster_gamma"
    "cleanup_cluster_dualstack"
  )
  for job_name in "${cleanup_jobs[@]}"; do
    echo "-------------------- Starting job ${job_name} --------------------"
    set -x
    "cleanup::job::${job_name}" "${job_name}" || (( ++failed_jobs ))
    set +x
    echo "-------------------- Finished job ${job_name} --------------------"
  done
  echo "Failed job suites: ${failed_jobs}"
  if (( failed_jobs > 0 )); then
    exit 1
  fi
}

main "$@"
