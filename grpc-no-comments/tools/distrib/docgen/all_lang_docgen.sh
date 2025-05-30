#! /bin/bash
# Copyright 2020 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -e

GRPC_VERSION="$(grep -m1 -Eo ' version: .*' build_handwritten.yaml | grep -Eo '[0-9][^ ]*')"
echo "Generating documents for version ${GRPC_VERSION}..."

if [ $
    read -r -p "- Are you sure to generate documents without pushing to GitHub? [y/N] " response
    if [[ "${response[0]}" =~ ^([yY][eE][sS]|[yY])$ ]]; then
        GITHUB_USER=''
    else
        echo "Generation stopped"
        exit 1
    fi
else
    if [ $
        GITHUB_USER=$1
    else
        echo "Too many arguments!"
        exit 1
    fi
fi

git diff --exit-code
git submodule update --init --recursive

dir=$(dirname "${0}")
cd "${dir}/../../.."

PAGES_PATH="/tmp/gh-pages"
rm -rf "${PAGES_PATH}"
git clone -o upstream --single-branch https://github.com/grpc/grpc -b gh-pages "${PAGES_PATH}"

rm -rf "${PAGES_PATH}/core" "${PAGES_PATH}/cpp" "${PAGES_PATH}/objc" "${PAGES_PATH}/php"
echo "Generating Core / C++ / ObjC / PHP documents in Docker..."
docker run --rm -it \
    -v "$(pwd)":/work/grpc \
    --user "$(id -u):$(id -g)" \
    hrektts/doxygen /work/grpc/tools/doxygen/run_doxygen.sh
mv doc/ref/c++/html "${PAGES_PATH}/cpp"
mv doc/ref/core/html "${PAGES_PATH}/core"
mv doc/ref/objc/html "${PAGES_PATH}/objc"
mv doc/ref/php/html "${PAGES_PATH}/php"

rm -rf "${PAGES_PATH}/python"
echo "Generating Python documents in Docker..."
docker run --rm -it \
    -v "$(pwd)":/work \
    -w /work \
    --user "$(id -u):$(id -g)" \
    python:3.9 tools/distrib/docgen/_generate_python_doc.sh
mv doc/build "${PAGES_PATH}/python"

echo "================================================================="
echo "  Successfully generated documents for version ${GRPC_VERSION}."
echo "================================================================="

echo "Generated docs are in ${PAGES_PATH}, use the internal release script to create a PR."
