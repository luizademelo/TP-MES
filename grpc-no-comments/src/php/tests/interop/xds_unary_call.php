<?php

/*
 *
 * Copyright 2021 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

$autoload_path = realpath(dirname(__FILE__).'/../../vendor/autoload.php');
require_once $autoload_path;

$args = getopt('', ['server:', 'num:',
                    'metadata:', 'timeout_sec:']);
$TIMEOUT_US = 30 * 1e6;

$server_address = $args['server'];
$num = $args['num'];

$stub = new Grpc\Testing\TestServiceClient($server_address, [
    'credentials' => Grpc\ChannelCredentials::createInsecure()
]);

$simple_request = new Grpc\Testing\SimpleRequest();

$timeout = $args['timeout_sec'] ? $args['timeout_sec'] * 1e6 : $TIMEOUT_US;
$metadata = [];
if ($args['metadata']) {
    $metadata = unserialize($args['metadata']);
}

$call = $stub->UnaryCall($simple_request,
                         $metadata,
                         ['timeout' => $timeout]);
list($response, $status) = $call->wait();
exit($status->code);
