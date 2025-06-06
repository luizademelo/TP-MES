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

DIRS="examples/cpp src/core src/cpp test/core test/cpp include src/compiler src/ruby src/objective-c tools/distrib/python src/python/grpcio_observability"

GLOB="*.h *.c *.cc *.m *.mm"

CLANG_FORMAT=${CLANG_FORMAT:-clang-format}

CPU_COUNT=`nproc`

files=
for dir in $DIRS
do
  for glob in $GLOB
  do
    files="$files `find ${CLANG_FORMAT_ROOT}/$dir -name $glob \
    -and -not -name '*.generated.*' \
    -and -not -name '*.upb.h' \
    -and -not -name '*.upbdefs.h' \
    -and -not -name '*.upbdefs.c' \
    -and -not -name '*.upb_minitable.h' \
    -and -not -name '*.upb_minitable.c' \
    -and -not -name '*.pb.h' \
    -and -not -name '*.pb.c' \
    -and -not -name '*.pb.cc' \
    -and -not -name '*.pbobjc.h' \
    -and -not -name '*.pbobjc.m' \
    -and -not -name '*.pbrpc.h' \
    -and -not -name '*.pbrpc.m' \
    -and -not -name end2end_tests.cc \
    -and -not -name grpc_shadow_boringssl.h \
    -and -not -name grpc_tls_credentials_options.h \
    -and -not -name grpc_tls_credentials_options_comparator_test.cc \
    -and -not -path '*/cmake/build/*' \
    -and -not -path '*/third_party/*' \
    -and -not -path '*/src/python/grpcio_observability/grpc_root/*' \
    `"
  done
done

if [ -n "$CHANGED_FILES" ]; then
  files=$(comm -12 <(echo $files | tr ' ' '\n' | sort -u) <(echo $CHANGED_FILES | tr ' ' '\n' | sort -u))
fi

files=`echo $files | sort -R`

FILES_PER_PROCESS="$(expr $(echo "$files" | grep -o '\n' | wc -l) / $CPU_COUNT + 1)"

if [ "$TEST" == "" ]
then
  echo $files | xargs -P $CPU_COUNT -n $FILES_PER_PROCESS $CLANG_FORMAT -i
else
  ok=yes
  for file in $files
  do
    tmp=`mktemp`
    $CLANG_FORMAT $file > $tmp
    diff -u $file $tmp || ok=no
    rm $tmp
  done
  if [ $ok == no ]
  then
    false
  fi
fi
