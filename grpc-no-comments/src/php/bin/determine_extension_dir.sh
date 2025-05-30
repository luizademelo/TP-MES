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
default_extension_dir=$(php-config --extension-dir)
if [ ! -e $default_extension_dir/grpc.so ]; then

  module_dir=$(pwd)/../ext/grpc/modules
  if [ ! -e $module_dir/grpc.so ]; then
    echo "Please run 'phpize && ./configure && make' from ext/grpc first"
    exit 1
  fi

  for f in $default_extension_dir/*.so; do
    ln -s $f $module_dir/$(basename $f) &> /dev/null || true
  done
  extension_dir="-d extension_dir=${module_dir} -d extension=grpc.so"
else
  extension_dir="-d extension=grpc.so"
fi
