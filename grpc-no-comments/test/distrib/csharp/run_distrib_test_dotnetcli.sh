#!/bin/bash
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

cd "$(dirname "$0")"

unzip -o "$EXTERNAL_GIT_ROOT/input_artifacts/csharp_nugets_windows_dotnetcli.zip" -d TestNugetFeed

./update_version.sh auto

cd DistribTest

CLR_OPENSSL_VERSION_OVERRIDE=1.1 dotnet restore DistribTestDotNet.csproj

dotnet build DistribTestDotNet.csproj

ls -R bin

if [ "${SKIP_NET45_DISTRIBTEST}" != "1" ]
then
  dotnet publish -f net45 DistribTestDotNet.csproj

  mono bin/Debug/net45/publish/DistribTestDotNet.exe

  mono bin/Debug/net45/publish/DistribTestDotNet.exe
fi

if [ "${SKIP_NETCOREAPP21_DISTRIBTEST}" != "1" ]
then
  dotnet publish -f netcoreapp2.1 DistribTestDotNet.csproj

  dotnet exec bin/Debug/netcoreapp2.1/DistribTestDotNet.dll

  dotnet exec bin/Debug/netcoreapp2.1/publish/DistribTestDotNet.dll
fi

if [ "${SKIP_NETCOREAPP31_DISTRIBTEST}" != "1" ]
then
  dotnet publish -f netcoreapp3.1 DistribTestDotNet.csproj

  dotnet exec bin/Debug/netcoreapp3.1/DistribTestDotNet.dll

  dotnet exec bin/Debug/netcoreapp3.1/publish/DistribTestDotNet.dll
fi

if [ "${SKIP_NET50_DISTRIBTEST}" != "1" ]
then
  dotnet publish -f net5.0 DistribTestDotNet.csproj

  dotnet publish -r linux-x64 -f net5.0 DistribTestDotNet.csproj -p:PublishSingleFile=true --self-contained true --output net5_singlefile_publish

  dotnet exec bin/Debug/net5.0/DistribTestDotNet.dll

  dotnet exec bin/Debug/net5.0/publish/DistribTestDotNet.dll

  ./net5_singlefile_publish/DistribTestDotNet
fi
