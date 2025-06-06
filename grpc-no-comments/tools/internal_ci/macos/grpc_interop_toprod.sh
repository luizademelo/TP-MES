#!/bin/bash
# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

source $(dirname $0)/../../../tools/internal_ci/helper_scripts/move_src_tree_and_respawn_itself_rc

cd $(dirname $0)/../../..

source tools/internal_ci/helper_scripts/prepare_build_macos_rc
source tools/internal_ci/helper_scripts/prepare_build_macos_interop_rc

mkdir -p cmake/build
pushd cmake/build
cmake -DgRPC_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=17 -DCMAKE_POLICY_VERSION_MINIMUM=3.5 ../..
make interop_client interop_server -j4
popd

export GRPC_DEFAULT_SSL_ROOTS_FILE_PATH="$(pwd)/etc/roots.pem"

# NOTE: only tests a subset of languages for time & dependency constraints

tools/run_tests/run_interop_tests.py -l c++ \
    --cloud_to_prod --cloud_to_prod_auth \
    --google_default_creds_use_key_file \
    --prod_servers default gateway_v4 \
    --service_account_key_file="${KOKORO_KEYSTORE_DIR}/73836_interop_to_prod_tests_service_account_key" \
    --default_service_account="interop-to-prod-tests@grpc-testing.iam.gserviceaccount.com" \
    --skip_compute_engine_creds -t -j 4 || FAILED="true"

if [ "$FAILED" != "" ]
then
  exit 1
fi
