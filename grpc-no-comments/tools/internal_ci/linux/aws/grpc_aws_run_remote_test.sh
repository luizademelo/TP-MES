#!/usr/bin/env bash
# Copyright 2021 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -e

if [ -z "$KOKORO_KEYSTORE_DIR" ]; then
    echo "KOKORO_KEYSTORE_DIR is unset. This must be run from kokoro"
    exit 1
fi

AWS_CREDENTIALS=${KOKORO_KEYSTORE_DIR}/73836_grpc_aws_ec2_credentials

curl "https://awscli.amazonaws.com/awscli-exe-linux-x86_64.zip" -o "awscliv2.zip"
unzip -q awscliv2.zip
sudo ./aws/install
aws --version

mkdir ~/.aws/
echo "[default]" >> ~/.aws/config
ln -s $AWS_CREDENTIALS ~/.aws/credentials

sudo apt update && sudo apt install -y jq

AWS_MACHINE_IMAGE=ami-026141f3d5c6d2d0c

AWS_INSTANCE_TYPE=${AWS_INSTANCE_TYPE:-t4g.xlarge}
AWS_SECURITY_GROUP=sg-021240e886feba750

AWS_INSTANCE_MAX_LIFESPAN_MINS=120

AWS_STORAGE_SIZE_GB=75
AWS_DEVICE_MAPPING="DeviceName='/dev/sda1',Ebs={VolumeSize=${AWS_STORAGE_SIZE_GB}}"
AWS_INSTANCE_TAGS="ResourceType='instance',Tags=[{Key='kokoro_job_name',Value='${KOKORO_JOB_NAME}'},{Key='kokoro_build_number',Value='${KOKORO_BUILD_NUMBER}'},{Key='kokoro_aws_integration',Value='true'}]"

ssh-keygen -N '' -t rsa -b 4096 -f ~/.ssh/temp_client_key
ssh-keygen -N '' -t ecdsa -b 256 -f ~/.ssh/temp_server_key
SERVER_PRIVATE_KEY=$(cat ~/.ssh/temp_server_key | sed 's/\(.*\)/    \1/')
SERVER_PUBLIC_KEY=$(cat ~/.ssh/temp_server_key.pub | awk '{print $1 " " $2 " root@localhost"}')
SERVER_HOST_KEY_ENTRY=$(cat ~/.ssh/temp_server_key.pub | awk '{print $1 " " $2}')
CLIENT_PUBLIC_KEY=$(cat ~/.ssh/temp_client_key.pub)

echo '#cloud-config' > userdata
echo 'ssh_authorized_keys:' >> userdata
echo " - $CLIENT_PUBLIC_KEY" >> userdata
echo 'ssh_keys:' >> userdata
echo '  ecdsa_private: |' >> userdata
echo "$SERVER_PRIVATE_KEY" >> userdata
echo "  ecdsa_public: $SERVER_PUBLIC_KEY" >> userdata
echo '' >> userdata
echo 'runcmd:' >> userdata
echo " - sleep ${AWS_INSTANCE_MAX_LIFESPAN_MINS}m" >> userdata
echo ' - shutdown' >> userdata

ID=$(aws ec2 run-instances --image-id $AWS_MACHINE_IMAGE --instance-initiated-shutdown-behavior=terminate \
    --instance-type $AWS_INSTANCE_TYPE \
    --security-group-ids $AWS_SECURITY_GROUP \
    --user-data file://userdata \
    --block-device-mapping "$AWS_DEVICE_MAPPING" \
    --tag-specifications "$AWS_INSTANCE_TAGS" \
    --region us-east-2 | jq .Instances[0].InstanceId | sed 's/"//g')
echo "instance-id=$ID"
echo "Waiting 1m for instance ip..."
sleep 1m
IP=$(aws ec2 describe-instances \
    --instance-id=$ID \
    --region us-east-2 | jq .Reservations[0].Instances[0].NetworkInterfaces[0].Association.PublicIp | sed 's/"//g')
SERVER_HOST_KEY_ENTRY="$IP $SERVER_HOST_KEY_ENTRY"
echo $SERVER_HOST_KEY_ENTRY >> ~/.ssh/known_hosts
echo "Waiting 2m for instance to initialize..."
sleep 2m

echo "Copying workspace to remote instance..."

time rsync -e "ssh -i ~/.ssh/temp_client_key" -a github/grpc ubuntu@$IP:~/workspace
echo "Beginning CI workload..."

REMOTE_WORKLOAD_SCRIPT=${REMOTE_WORKLOAD_SCRIPT:-tools/internal_ci/linux/aws/grpc_aws_experiment_remote.sh}

REMOTE_WORKLOAD_COMMAND="nohup bash -c '(bash grpc/${REMOTE_WORKLOAD_SCRIPT}; echo \$? >/tmp/aws_build.exitcode) >>/tmp/aws_build.log 2>&1' >/dev/null 2>&1 & echo \$! >/tmp/aws_build.pid"

SSH_COMMAND='uname -a; rm -f /tmp/aws_build.log /tmp/aws_build.exitcode /tmp/aws_build.pid; touch /tmp/aws_build.log; cd ~/workspace; '"${REMOTE_WORKLOAD_COMMAND};"' tail -f /tmp/aws_build.log --pid $(cat /tmp/aws_build.pid); exit $(cat /tmp/aws_build.exitcode)'

REMOTE_SCRIPT_EXITCODE=0
time ssh -i ~/.ssh/temp_client_key ubuntu@$IP "${SSH_COMMAND}" || REMOTE_SCRIPT_EXITCODE=$?

echo "Copying artifacts from the remote instance..."
ARTIFACT_RSYNC_PATTERN="**/*sponge_log.*"
# NOTE: the include "*/" rule and --prune-empty-dirs are important for not

COPY_ARTIFACTS_EXITCODE=0
time rsync -av -e "ssh -i ~/.ssh/temp_client_key" --include="${ARTIFACT_RSYNC_PATTERN}" --include="*/" --exclude="*" --prune-empty-dirs ubuntu@$IP:~/workspace/grpc github || COPY_ARTIFACTS_EXITCODE=$?

echo "Shutting down instance $ID."
ssh -i ~/.ssh/temp_client_key ubuntu@$IP "sudo shutdown +1" || echo "WARNING: Failed to initiate AWS instance shutdown."

if [ "$REMOTE_SCRIPT_EXITCODE" == "0" ] && [ "$COPY_ARTIFACTS_EXITCODE" != "0" ]
then
  echo "Exiting with exitcode $COPY_ARTIFACTS_EXITCODE since remote script has passed, but copying artifacts has failed."
  exit $COPY_ARTIFACTS_EXITCODE
fi

echo "Exiting with exitcode $REMOTE_SCRIPT_EXITCODE based on remote script output."
exit $REMOTE_SCRIPT_EXITCODE
