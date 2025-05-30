#!/usr/bin/env bash
# Copyright 2023 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
set -ex

declare -a GRPC_EXPERIMENTS=(
  "event_engine_listener"
  "event_engine_client"
  "event_engine_client,event_engine_listener"
)

cd "$(dirname "$0")/../../.."

source tools/internal_ci/helper_scripts/prepare_build_linux_rc

GRPC_CORE_REPO=grpc/grpc
GRPC_CORE_GITREF=master
TEST_INFRA_REPO=grpc/test-infra
TEST_INFRA_GITREF=master

LOAD_TEST_PREFIX="${KOKORO_BUILD_INITIATOR}"

if [[ "${KOKORO_BUILD_INITIATOR%%-*}" == kokoro ]]; then
  LOAD_TEST_PREFIX=kokoro
fi

BIGQUERY_TABLE_8CORE=e2e_benchmark_cxx_experiments.results_8core
BIGQUERY_TABLE_32CORE=e2e_benchmark_cxx_experiments.results_32core

CLOUD_LOGGING_URL="https://source.cloud.google.com/results/invocations/${KOKORO_BUILD_ID}"
PREBUILT_IMAGE_PREFIX="us-docker.pkg.dev/grpc-testing/e2etest-prebuilt"
UNIQUE_IDENTIFIER="cxx-experiment-$(date +%Y%m%d%H%M%S)"
ROOT_DIRECTORY_OF_DOCKERFILES="../test-infra/containers/pre_built_workers/"

GRPC_COMMIT="$(git show --format="%H" --no-patch)"

if [[ "${KOKORO_GITHUB_COMMIT_URL%/*}" == "https://github.com/grpc/grpc/commit" ]]; then
  GRPC_CORE_COMMIT="${KOKORO_GIT_COMMIT}"
else
  GRPC_CORE_COMMIT="$(git ls-remote -h "https://github.com/${GRPC_CORE_REPO}.git" "${GRPC_CORE_GITREF}" | cut -f1)"
fi

DRIVER_POOL=drivers-ci
WORKER_POOL_8CORE=workers-c2-8core-ci

WORKER_POOL_32CORE=workers-c2-30core-ci

LOG_URL_PREFIX="http://cnsviewer/placer/prod/home/kokoro-dedicated/build_artifacts/${KOKORO_BUILD_ARTIFACTS_SUBDIR}/github/grpc/"

gcloud auth configure-docker --quiet
gcloud auth configure-docker "${PREBUILT_IMAGE_PREFIX%%/*}" --quiet

gcloud config set project grpc-testing
gcloud container clusters get-credentials benchmarks-prod2 \
  --zone us-central1-b --project grpc-testing

mkdir ../test-infra
pushd ../test-infra
git clone "https://github.com/${TEST_INFRA_REPO}.git" .
git checkout "${TEST_INFRA_GITREF}"
make all-tools
popd

declare -a loadtest_files=()

buildConfigs() {
  local -r pool="$1"
  local -r base_table="$2"
  local -r experiment="$3"
  shift 3

  SANITIZED_EXPERIMENT="${experiment//,/__}"
  OUTFILE="loadtest_with_prebuilt_workers_${pool}_${SANITIZED_EXPERIMENT}.yaml"
  tools/run_tests/performance/loadtest_config.py "$@" \
    -t ./tools/run_tests/performance/templates/loadtest_template_prebuilt_cxx_experiments.yaml \
    -s driver_pool="${DRIVER_POOL}" -s driver_image= \
    -s client_pool="${pool}" -s server_pool="${pool}" \
    -s big_query_table="${base_table}_${SANITIZED_EXPERIMENT}" -s timeout_seconds=900 \
    -s prebuilt_image_prefix="${PREBUILT_IMAGE_PREFIX}" \
    -s prebuilt_image_tag="${UNIQUE_IDENTIFIER}" \
    -s grpc_experiment="${experiment}" \
    -a ci_buildNumber="${KOKORO_BUILD_NUMBER}" \
    -a ci_buildUrl="${CLOUD_LOGGING_URL}" \
    -a ci_jobName="${KOKORO_JOB_NAME}" \
    -a ci_gitCommit="${GRPC_COMMIT}" \
    -a ci_gitCommit_core="${GRPC_CORE_COMMIT}" \
    -a ci_gitActualCommit="${KOKORO_GIT_COMMIT}" \
    --prefix="${LOAD_TEST_PREFIX}" -u "${UNIQUE_IDENTIFIER}" -u "${pool}" \
    -a pool="${pool}" --category=dashboard \
    --allow_client_language=c++ --allow_server_language=c++ \
    --allow_server_language=node \
    -o "${OUTFILE}"

  loadtest_files+=(-i "${OUTFILE}")
}

for experiment in "${GRPC_EXPERIMENTS[@]}"; do
  buildConfigs "${WORKER_POOL_8CORE}" "${BIGQUERY_TABLE_8CORE}" "${experiment}" -l c++
  buildConfigs "${WORKER_POOL_32CORE}" "${BIGQUERY_TABLE_32CORE}" "${experiment}" -l c++
done

deleteImages() {
  echo "deleting images on exit"
  ../test-infra/bin/delete_prebuilt_workers \
    -p "${PREBUILT_IMAGE_PREFIX}" \
    -t "${UNIQUE_IDENTIFIER}"
}
trap deleteImages EXIT

time ../test-infra/bin/prepare_prebuilt_workers \
  -l "cxx:${GRPC_CORE_REPO}:${GRPC_CORE_COMMIT}" \
  -p "${PREBUILT_IMAGE_PREFIX}" \
  -t "${UNIQUE_IDENTIFIER}" \
  -r "${ROOT_DIRECTORY_OF_DOCKERFILES}"

../test-infra/bin/runner \
  "${loadtest_files[@]}" \
  -log-url-prefix "${LOG_URL_PREFIX}" \
  -polling-interval 5s \
  -delete-successful-tests \
  -c "${WORKER_POOL_8CORE}:2" -c "${WORKER_POOL_32CORE}:2" \
  -o "runner/sponge_log.xml"
