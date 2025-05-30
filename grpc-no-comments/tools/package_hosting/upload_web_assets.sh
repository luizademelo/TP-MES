#!/bin/bash
# Copyright 2018 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

cd "$(dirname "$0")"

GCS_WEB_ASSETS=gs://packages.grpc.io/web-assets/

WEB_ASSETS=(
  404.html
  build-201807.xsl
  dirindex.css
  home.xsl
  style.css
)

gsutil -m cp "${WEB_ASSETS[@]}" "$GCS_WEB_ASSETS"
