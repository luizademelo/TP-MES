<?php

// Copyright 2015-2016 gRPC authors.

namespace Grpc\Testing;

class ReconnectServiceStub {

    public function Start(
        \Grpc\Testing\ReconnectParams $request,
        \Grpc\ServerContext $context
    ): ?\Grpc\Testing\EmptyMessage {
        $context->setStatus(\Grpc\Status::unimplemented());
        return null;
    }

    public function Stop(
        \Grpc\Testing\EmptyMessage $request,
        \Grpc\ServerContext $context
    ): ?\Grpc\Testing\ReconnectInfo {
        $context->setStatus(\Grpc\Status::unimplemented());
        return null;
    }

    public final function getMethodDescriptors(): array
    {
        return [
            '/grpc.testing.ReconnectService/Start' => new \Grpc\MethodDescriptor(
                $this,
                'Start',
                '\Grpc\Testing\ReconnectParams',
                \Grpc\MethodDescriptor::UNARY_CALL
            ),
            '/grpc.testing.ReconnectService/Stop' => new \Grpc\MethodDescriptor(
                $this,
                'Stop',
                '\Grpc\Testing\EmptyMessage',
                \Grpc\MethodDescriptor::UNARY_CALL
            ),
        ];
    }

}
