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

class ClientStreamingCall extends AbstractCall
{

    public function start(array $metadata = [])
    {
        $this->call->startBatch([
            OP_SEND_INITIAL_METADATA => $metadata,
        ]);
    }

    public function write($data, array $options = [])
    {
        $message_array = ['message' => $this->_serializeMessage($data)];
        if (array_key_exists('flags', $options)) {
            $message_array['flags'] = $options['flags'];
        }
        $this->call->startBatch([
            OP_SEND_MESSAGE => $message_array,
        ]);
    }

    public function wait()
    {
        $event = $this->call->startBatch([
            OP_SEND_CLOSE_FROM_CLIENT => true,
            OP_RECV_INITIAL_METADATA => true,
            OP_RECV_MESSAGE => true,
            OP_RECV_STATUS_ON_CLIENT => true,
        ]);
        $this->metadata = $event->metadata;

        $status = $event->status;
        $this->trailing_metadata = $status->metadata;

        return [$this->_deserializeResponse($event->message), $status];
    }
}
