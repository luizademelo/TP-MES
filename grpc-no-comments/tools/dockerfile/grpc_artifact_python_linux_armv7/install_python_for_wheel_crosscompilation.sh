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

PYTHON_VERSION="$1"
PYTHON_RELEASE="$2"
PYTHON_PREFIX="$3"

curl -O "https://www.python.org/ftp/python/${PYTHON_VERSION}/Python-${PYTHON_RELEASE}.tar.xz"
tar -xf "Python-${PYTHON_RELEASE}.tar.xz"
pushd "Python-${PYTHON_RELEASE}"

(unset AS AR CC CPP CXX LD && ./configure --prefix="${PYTHON_PREFIX}" && make -j 4 && make install)

./configure && cp pyconfig.h "${PYTHON_PREFIX}"/include/python*

popd

rm -rf "Python-${PYTHON_VERSION}"

"${PYTHON_PREFIX}/bin/python3" -m pip install --upgrade 'cython==3.1.1' wheel
