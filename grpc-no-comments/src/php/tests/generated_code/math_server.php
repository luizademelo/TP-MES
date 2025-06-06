<?php

/*
 *
 * Copyright 2020 gRPC authors.
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

include 'vendor/autoload.php';

class MathService extends Math\MathStub
{
    public function Div(
        \Math\DivArgs $request,
        \Grpc\ServerContext $context
    ): ?\Math\DivReply {
        $dividend = $request->getDividend();
        $divisor = $request->getDivisor();
        if ($divisor == 0) {
            $context->setStatus(
                \Grpc\Status::status(
                    \Grpc\STATUS_INVALID_ARGUMENT,
                    'Cannot divide by zero'
                )
            );
            return null;
        }

        $metadata = $context->clientMetadata();
        if (array_key_exists('response-unavailable', $metadata)) {
            $trailingMetadata = array_key_exists('grpc-previous-rpc-attempts', $metadata)
            ? ['unavailable-retry-attempts' => $metadata['grpc-previous-rpc-attempts']]
            : null;
            $context->setStatus(
                \Grpc\Status::status(
                    \Grpc\STATUS_UNAVAILABLE,
                    "unavailable",
                    $trailingMetadata
                )
            );
            return null;
        }
        usleep(1000);
        $quotient = intdiv($dividend, $divisor);
        $remainder = $dividend % $divisor;
        $reply = new \Math\DivReply([
            'quotient' => $quotient,
            'remainder' => $remainder,
        ]);
        return $reply;
    }

    public function DivMany(
        \Grpc\ServerCallReader $reader,
        \Grpc\ServerCallWriter $writer,
        \Grpc\ServerContext $context
    ): void {
        while ($divArgs = $reader->read()) {
            $dividend = $divArgs->getDividend();
            $divisor = $divArgs->getDivisor();
            if ($divisor == 0) {
                $context->setStatus(\Grpc\Status::status(
                    \Grpc\STATUS_INVALID_ARGUMENT,
                    'Cannot divide by zero'
                ));
                $writer->finish();
                return;
            }
            $quotient = intdiv($dividend, $divisor);
            $remainder = $dividend % $divisor;
            $reply = new \Math\DivReply([
                'quotient' => $quotient,
                'remainder' => $remainder,
            ]);
            $writer->write($reply);
        }
        $writer->finish();
    }

    public function Fib(
        \Math\FibArgs $request,
        \Grpc\ServerCallWriter $writer,
        \Grpc\ServerContext $context
    ): void {
        $previous = 0;
        $current = 1;
        $limit = $request->getLimit();
        for ($i = 0; $i < $limit; $i++) {
            $num = new \Math\Num();
            $num->setNum($current);
            $writer->write($num);
            $next = $previous + $current;
            $previous = $current;
            $current = $next;
        }
        $writer->finish();
    }

    public function Sum(
        \Grpc\ServerCallReader $reader,
        \Grpc\ServerContext $context
    ): ?\Math\Num {
        $sum = 0;
        while ($num = $reader->read()) {
            $sum += $num->getNum();
        }
        $reply = new \Math\Num();
        $reply->setNum($sum);
        return $reply;
    }
}

$server = new \Grpc\RpcServer();
$server->addHttp2Port('0.0.0.0:50052');
$server_credentials = Grpc\ServerCredentials::createSsl(
    null,
    file_get_contents(dirname(__FILE__) . '/../data/server1.key'),
    file_get_contents(dirname(__FILE__) . '/../data/server1.pem')
);
$server->addSecureHttp2Port('0.0.0.0:50051', $server_credentials);
$server->handle(new MathService());
$server->run();
