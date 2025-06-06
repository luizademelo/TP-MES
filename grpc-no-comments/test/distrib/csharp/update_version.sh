#!/bin/bash
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -e

cd "$(dirname "$0")"

CSHARP_VERSION="$1"
if [ "$CSHARP_VERSION" == "auto" ]
then

  # TODO: find a better shellcheck-compliant way to write the following line

  CSHARP_VERSION=$(ls TestNugetFeed | grep -m 1 '^Grpc\.Tools\.[0-9].*\.nupkg$' | sed s/^Grpc\.Tools\.// | sed s/\.nupkg$// | sed s/\.symbols$//)
  echo "Autodetected nuget ${CSHARP_VERSION}"
fi

sed -ibak "s/__GRPC_NUGET_VERSION__/${CSHARP_VERSION}/g" DistribTest/DistribTestDotNet.csproj
