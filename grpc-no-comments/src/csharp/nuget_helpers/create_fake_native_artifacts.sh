#!/bin/bash
# Copyright 2021 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

cd "$(dirname "$0")/../../.."

cd src/csharp

mkdir -p protoc_plugins
pushd protoc_plugins

if [[ "$(uname)" != "Linux" ]]
then
  mkdir -p protoc_linux_x64
  touch protoc_linux_x64/protoc
  touch protoc_linux_x64/grpc_csharp_plugin

  mkdir -p protoc_linux_x86
  touch protoc_linux_x86/protoc
  touch protoc_linux_x86/grpc_csharp_plugin

  mkdir -p protoc_linux_aarch64
  touch protoc_linux_aarch64/protoc
  touch protoc_linux_aarch64/grpc_csharp_plugin
fi

if [[ "$(uname)" != "Darwin" ]]
then
    mkdir -p protoc_macos_x64
    touch protoc_macos_x64/protoc
    touch protoc_macos_x64/grpc_csharp_plugin
fi

if [[ "$(uname)" != "WindowsNT" ]]
then
    mkdir -p protoc_windows_x86
    touch protoc_windows_x86/protoc.exe
    touch protoc_windows_x86/grpc_csharp_plugin.exe

    mkdir -p protoc_windows_x64
    touch protoc_windows_x64/protoc.exe
    touch protoc_windows_x64/grpc_csharp_plugin.exe
fi

popd
