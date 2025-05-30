#!/bin/bash
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

source ~/.rvm/scripts/rvm
set -ex

cd "$(dirname "$0")/../../.."
bazel=$(pwd)/tools/bazel

CONFIG=${CONFIG:-opt}

if [ "$OSTYPE" != "msys" ]
then

  mkdir -p cmake/build
  cd cmake/build
  cmake -DgRPC_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Release ../..
  make qps_worker qps_json_driver -j8
  cd ../..

  (cd third_party/zlib; git checkout zconf.h)
fi

PHP_ALREADY_BUILT=""
for language in "$@"
do
  case "$language" in
  "c++")
    ;;
  "java")
    (cd ../grpc-java/ &&
      ./gradlew -PskipCodegen=true -PskipAndroid=true :grpc-benchmarks:installDist)
    ;;
  "go")
    tools/run_tests/performance/build_performance_go.sh
    ;;
  "php7"|"php7_protobuf_c")
    if [ -n "$PHP_ALREADY_BUILT" ]; then
      echo "Skipping PHP build as already built by $PHP_ALREADY_BUILT"
    else
      PHP_ALREADY_BUILT=$language
      tools/run_tests/performance/build_performance_php7.sh
    fi
    ;;
  "csharp")
    python tools/run_tests/run_tests.py -l "$language" -c "$CONFIG" --build_only -j 8

    (cd third_party/zlib; git checkout zconf.h)
    ;;
  "node")
    tools/run_tests/performance/build_performance_node.sh
    ;;
  "python")
    $bazel build -c opt //src/python/grpcio_tests/tests/qps:qps_worker
    ;;
  "python_asyncio")
    $bazel build -c opt //src/python/grpcio_tests/tests_aio/benchmark:worker
    ;;
  *)
    python tools/run_tests/run_tests.py -l "$language" -c "$CONFIG" --build_only -j 8
    ;;
  esac
done
