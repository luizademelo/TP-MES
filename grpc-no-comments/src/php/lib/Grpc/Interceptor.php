<?php

/*
 *
 * Copyright 2018 gRPC authors.
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

namespace Grpc;

class Interceptor
{
    public function interceptUnaryUnary(
        $method,
        $argument,
        $deserialize,
        $continuation,
        array $metadata = [],
        array $options = []
    ) {
        return $continuation($method, $argument, $deserialize, $metadata, $options);
    }

    public function interceptStreamUnary(
        $method,
        $deserialize,
        $continuation,
        array $metadata = [],
        array $options = []
    ) {
        return $continuation($method, $deserialize, $metadata, $options);
    }

    public function interceptUnaryStream(
        $method,
        $argument,
        $deserialize,
        $continuation,
        array $metadata = [],
        array $options = []
    ) {
        return $continuation($method, $argument, $deserialize, $metadata, $options);
    }

    public function interceptStreamStream(
        $method,
        $deserialize,
        $continuation,
        array $metadata = [],
        array $options = []
    ) {
        return $continuation($method, $deserialize, $metadata, $options);
    }

    public static function intercept($channel, $interceptors)
    {
        if (is_array($interceptors)) {
            for ($i = count($interceptors) - 1; $i >= 0; $i--) {
                $channel = new Internal\InterceptorChannel($channel, $interceptors[$i]);
            }
        } else {
            $channel =  new Internal\InterceptorChannel($channel, $interceptors);
        }
        return $channel;
    }
}
