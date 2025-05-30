#!/bin/bash
# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# IMPORTANT: Instructions for updating

set -ex

cd "$(dirname "$0")"

CLOUD_PROJECT=grpc-testing
ZONE=us-central1-b

INSTANCE_NAME="${1:-grpc-kokoro-performance-server1}"
MACHINE_TYPE=e2-standard-32

gcloud compute instances create "$INSTANCE_NAME" \
    --project="$CLOUD_PROJECT" \
    --zone "$ZONE" \
    --machine-type $MACHINE_TYPE \
    --image-project ubuntu-os-cloud \
    --image-family ubuntu-2004-lts \
    --boot-disk-size 300 \
    --scopes https://www.googleapis.com/auth/bigquery \
    --tags=allow-ssh

echo 'Created GCE instance, waiting 60 seconds for it to come online.'
sleep 60

gcloud compute copy-files \
    --project="$CLOUD_PROJECT" \
    --zone "$ZONE" \
    kokoro_performance.pub linux_kokoro_performance_worker_init.sh "kbuilder@${INSTANCE_NAME}":~

gcloud compute ssh \
    --project="$CLOUD_PROJECT" \
    --zone "$ZONE" \
    "kbuilder@${INSTANCE_NAME}" --command "./linux_kokoro_performance_worker_init.sh"
