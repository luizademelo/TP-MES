#!/bin/bash
# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

cd "$(dirname "$0")/../../.."

base=$(pwd)

mkdir -p artifacts/

# NOTE: Besides the platform-specific native gems, all the artifact build

cp -r "${EXTERNAL_GIT_ROOT}"/input_artifacts/ruby_native_gem_*/* artifacts/ || true

well_known_protos=( any api compiler/plugin descriptor duration empty field_mask source_context struct timestamp type wrappers )

for arch in {x86,x64}; do
  case $arch in
    x64)
      ruby_arch=x86_64
      ;;
    *)
      ruby_arch=$arch
      ;;
  esac
  for plat in {windows,linux,macos}; do

    if [[ "${plat}_${arch}" == "macos_x86" ]]
    then
      continue
    fi
    input_dir="${EXTERNAL_GIT_ROOT}/input_artifacts/protoc_${plat}_${arch}"
    output_dir="$base/src/ruby/tools/bin/${ruby_arch}-${plat}"
    mkdir -p "$output_dir"/google/protobuf
    mkdir -p "$output_dir"/google/protobuf/compiler
    cp "$input_dir"/protoc* "$input_dir"/grpc_ruby_plugin* "$output_dir/"
    if [[ "$plat" != "windows" ]]
    then
      chmod +x "$output_dir/protoc" "$output_dir/grpc_ruby_plugin"
    fi
    for proto in "${well_known_protos[@]}"; do
      cp "$base/third_party/protobuf/src/google/protobuf/$proto.proto" "$output_dir/google/protobuf/$proto.proto"
    done
  done
done

cd "$base/src/ruby/tools"
gem build grpc-tools.gemspec
cp ./grpc-tools*.gem "$base/artifacts/"
