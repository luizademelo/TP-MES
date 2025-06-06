<?php

/*
 *
 * Copyright 2015 gRPC authors.
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
require_once dirname(__FILE__).'/AbstractGeneratedCodeTest.php';

class GeneratedCodeWithCallbackTest extends AbstractGeneratedCodeTest
{
    public function setUp(): void
    {
        self::$client = new Math\MathClient(
        getenv('GRPC_TEST_HOST'),
        ['credentials' => Grpc\ChannelCredentials::createSsl(
            file_get_contents(dirname(__FILE__).'/../data/ca.pem')),
         'grpc.ssl_target_name_override' => 'foo.test.google.fr',
         'update_metadata' => function ($a_hash,
                                        $client = []) {
                                $a_copy = $a_hash;
                                $a_copy['foo'] = ['bar'];

                                return $a_copy;
                              },
            ] + self::$clientOptions
        );
    }

    public function tearDown(): void
    {
        self::$client->close();
    }
}
