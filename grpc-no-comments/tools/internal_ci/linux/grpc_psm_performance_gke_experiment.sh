#!/usr/bin/env bash
# Copyright 2022 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
set -ex

cd "$(dirname "$0")/../../.."

source tools/internal_ci/helper_scripts/prepare_build_linux_rc

LOAD_TEST_PREFIX="${KOKORO_BUILD_INITIATOR}"

if [[ "${KOKORO_BUILD_INITIATOR%%-*}" == kokoro ]]; then
  LOAD_TEST_PREFIX=kokoro-test
fi
BIGQUERY_TABLE_8CORE=e2e_benchmarks.psm_experimental_results_8core

CLOUD_LOGGING_URL="https://source.cloud.google.com/results/invocations/${KOKORO_BUILD_ID}"
PREBUILT_IMAGE_PREFIX="us-docker.pkg.dev/grpc-testing/e2etest-prebuilt"
UNIQUE_IDENTIFIER="$(date +%Y%m%d%H%M%S)"
ROOT_DIRECTORY_OF_DOCKERFILES="../test-infra/containers/pre_built_workers/"

GRPC_GITREF="$(git show --format="%H" --no-patch)"

if [[ "${KOKORO_GITHUB_COMMIT_URL%/*}" == "https://github.com/grpc/grpc/commit" ]]; then
  GRPC_CORE_GITREF="${KOKORO_GIT_COMMIT}"
else
  GRPC_CORE_GITREF="$(git ls-remote -h https://github.com/grpc/grpc.git master | cut -f1)"
fi
GRPC_JAVA_GITREF="$(git ls-remote -h https://github.com/grpc/grpc-java.git master | cut -f1)"

DRIVER_POOL=drivers-ci
WORKER_POOL_8CORE=workers-c2-8core-ci

LOG_URL_PREFIX="http://cnsviewer/placer/prod/home/kokoro-dedicated/build_artifacts/${KOKORO_BUILD_ARTIFACTS_SUBDIR}/github/grpc/"

gcloud auth configure-docker --quiet
gcloud auth configure-docker "${PREBUILT_IMAGE_PREFIX%%/*}" --quiet

gcloud config set project grpc-testing
gcloud container clusters get-credentials psm-benchmarks-performance \
  --zone us-central1-b --project grpc-testing

pushd ..
git clone https://github.com/grpc/test-infra.git
cd test-infra

git checkout --detach
make all-tools

git fetch --all --tags
TEST_INFRA_VERSION=$(git describe --tags "$(git rev-list --tags --max-count=1)")
popd

PSM_IMAGE_PREFIX=us-docker.pkg.dev/grpc-testing/e2etest
PSM_IMAGE_TAG=${TEST_INFRA_VERSION}

psmBuildConfigs() {
  local -r pool="$1"
  local -r table="$2"
  local -r proxy_type="$3"

  shift 3
  tools/run_tests/performance/loadtest_config.py "$@" \
    -t ./tools/run_tests/performance/templates/loadtest_template_psm_"${proxy_type}"_prebuilt_all_languages.yaml \
    -s driver_pool="${DRIVER_POOL}" -s driver_image= \
    -s client_pool="${pool}" -s server_pool="${pool}" \
    -s big_query_table="${table}" -s timeout_seconds=900 \
    -s prebuilt_image_prefix="${PREBUILT_IMAGE_PREFIX}" \
    -s prebuilt_image_tag="${UNIQUE_IDENTIFIER}" \
    -s psm_image_prefix="${PSM_IMAGE_PREFIX}" \
    -s psm_image_tag="${PSM_IMAGE_TAG}" \
    -a ci_buildNumber="${KOKORO_BUILD_NUMBER}" \
    -a ci_buildUrl="${CLOUD_LOGGING_URL}" \
    -a ci_jobName="${KOKORO_JOB_NAME}" \
    -a ci_gitCommit="${GRPC_GITREF}" \
    -a ci_gitCommit_java="${GRPC_JAVA_GITREF}" \
    -a ci_gitActualCommit="${KOKORO_GIT_COMMIT}" \
    -a enablePrometheus=true \
    --prefix="${LOAD_TEST_PREFIX}" -u "${UNIQUE_IDENTIFIER}" -u "${pool}" -u "${proxy_type}" \
    -a pool="${pool}" \
    --category=psm \
    --allow_client_language=c++ --allow_server_language=c++ \
    -o "psm_${proxy_type}_loadtest_with_prebuilt_workers_${pool}.yaml"
}

psmBuildConfigs "${WORKER_POOL_8CORE}" "${BIGQUERY_TABLE_8CORE}" proxied -a queue="${WORKER_POOL_8CORE}-proxied" -l c++ -l java --client_channels=8 --server_threads=16 --offered_loads 100 300 500 700 900 1000 1500 2000 2500 4000 6000 8000 10000 12000 14000 16000 18000 20000 22000 24000 26000 28000 30000

psmBuildConfigs "${WORKER_POOL_8CORE}" "${BIGQUERY_TABLE_8CORE}" proxyless -a queue="${WORKER_POOL_8CORE}-proxyless" -l c++ -l java --client_channels=8 --server_threads=16 --offered_loads 100 300 500 700 900 1000 1500 2000 2500 4000 6000 8000 10000 12000 14000 16000 18000 20000 22000 24000 26000 28000 30000

buildConfigs() {
  local -r pool="$1"
  local -r table="$2"
  shift 2
  tools/run_tests/performance/loadtest_config.py "$@" \
    -t ./tools/run_tests/performance/templates/loadtest_template_prebuilt_all_languages.yaml \
    -s driver_pool="${DRIVER_POOL}" -s driver_image= \
    -s client_pool="${pool}" -s server_pool="${pool}" \
    -s big_query_table="${table}" -s timeout_seconds=900 \
    -s prebuilt_image_prefix="${PREBUILT_IMAGE_PREFIX}" \
    -s prebuilt_image_tag="${UNIQUE_IDENTIFIER}" \
    -a ci_buildNumber="${KOKORO_BUILD_NUMBER}" \
    -a ci_buildUrl="${CLOUD_LOGGING_URL}" \
    -a ci_jobName="${KOKORO_JOB_NAME}" \
    -a ci_gitCommit="${GRPC_GITREF}" \
    -a ci_gitCommit_java="${GRPC_JAVA_GITREF}" \
    -a ci_gitActualCommit="${KOKORO_GIT_COMMIT}" \
    -a enablePrometheus=true \
    --prefix="${LOAD_TEST_PREFIX}" -u "${UNIQUE_IDENTIFIER}" -u "${pool}" \
    -a pool="${pool}" --category=psm \
    --allow_client_language=c++ --allow_server_language=c++ \
    -o "regular_loadtest_with_prebuilt_workers_${pool}.yaml"
}

buildConfigs "${WORKER_POOL_8CORE}" "${BIGQUERY_TABLE_8CORE}" -a queue="${WORKER_POOL_8CORE}-regular" -l c++ -l java --client_channels=8 --server_threads=16 --offered_loads 100 300 500 700 900 1000 1500 2000 2500 4000 6000 8000 10000 12000 14000 16000 18000 20000 22000 24000 26000 28000 30000

deleteImages() {
  echo "deleting images on exit"
  ../test-infra/bin/delete_prebuilt_workers \
    -p "${PREBUILT_IMAGE_PREFIX}" \
    -t "${UNIQUE_IDENTIFIER}"
}
trap deleteImages EXIT

time ../test-infra/bin/prepare_prebuilt_workers \
  -l "cxx:${GRPC_CORE_GITREF}" \
  -l "java:${GRPC_JAVA_GITREF}" \
  -p "${PREBUILT_IMAGE_PREFIX}" \
  -t "${UNIQUE_IDENTIFIER}" \
  -r "${ROOT_DIRECTORY_OF_DOCKERFILES}"

time ../test-infra/bin/runner \
  -i "psm_proxied_loadtest_with_prebuilt_workers_${WORKER_POOL_8CORE}.yaml" \
  -i "psm_proxyless_loadtest_with_prebuilt_workers_${WORKER_POOL_8CORE}.yaml" \
  -i "regular_loadtest_with_prebuilt_workers_${WORKER_POOL_8CORE}.yaml" \
  -log-url-prefix "${LOG_URL_PREFIX}" \
  -annotation-key queue \
  -polling-interval 5s \
  -delete-successful-tests \
  -c "${WORKER_POOL_8CORE}-proxied:1" \
  -c "${WORKER_POOL_8CORE}-proxyless:1" \
  -c "${WORKER_POOL_8CORE}-regular:1" \
  -o "runner/sponge_log.xml"
