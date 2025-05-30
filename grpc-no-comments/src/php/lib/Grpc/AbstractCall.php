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

namespace Grpc;

abstract class AbstractCall
{

    protected $call;
    protected $deserialize;
    protected $metadata;
    protected $trailing_metadata;

    public function __construct(Channel $channel,
                                $method,
                                $deserialize,
                                array $options = [])
    {
        if (array_key_exists('timeout', $options) &&
            is_numeric($timeout = $options['timeout'])
        ) {
            $now = Timeval::now();
            $delta = new Timeval($timeout);
            $deadline = $now->add($delta);
        } else {
            $deadline = Timeval::infFuture();
        }
        $this->call = new Call($channel, $method, $deadline);
        $this->deserialize = $deserialize;
        $this->metadata = null;
        $this->trailing_metadata = null;
        if (array_key_exists('call_credentials_callback', $options) &&
            is_callable($call_credentials_callback =
                $options['call_credentials_callback'])
        ) {
            $call_credentials = CallCredentials::createFromPlugin(
                $call_credentials_callback
            );
            $this->call->setCredentials($call_credentials);
        }
    }

    public function getMetadata()
    {
        return $this->metadata;
    }

    public function getTrailingMetadata()
    {
        return $this->trailing_metadata;
    }

    public function getPeer()
    {
        return $this->call->getPeer();
    }

    public function cancel()
    {
        $this->call->cancel();
    }

    protected function _serializeMessage($data)
    {

        return $data->serializeToString();
    }

    protected function _deserializeResponse($value)
    {
        if ($value === null) {
            return;
        }
        list($className, $deserializeFunc) = $this->deserialize;
        $obj = new $className();
        $obj->mergeFromString($value);
        return $obj;
    }

    public function setCallCredentials($call_credentials)
    {
        $this->call->setCredentials($call_credentials);
    }
}
