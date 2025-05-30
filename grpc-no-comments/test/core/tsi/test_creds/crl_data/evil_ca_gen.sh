#!/bin/bash
# Copyright 2024 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

rm -rf evil_ca
mkdir evil_ca
cp evil_ca.cnf evil_ca/
pushd evil_ca  || exit
touch index.txt
echo 1 > ./serial
echo 1000 > ./crlnumber

openssl req -x509 -new -newkey rsa:2048 -nodes -keyout evil_ca.key -out evil_ca.pem \
  -config evil_ca.cnf -days 3650 -extensions v3_req

openssl ca -config=evil_ca.cnf -gencrl -out evil.crl -keyfile evil_ca.key -cert evil_ca.pem -crldays 3650
popd || exit
cp "./evil_ca/evil.crl" ./crls/
rm -rf evil_ca