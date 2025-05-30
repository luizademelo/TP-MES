<?php

// Copyright 2015-2016 gRPC authors.

namespace Grpc\Testing;

class UnimplementedServiceStub {

    public function UnimplementedCall(
        \Grpc\Testing\EmptyMessage $request,
        \Grpc\ServerContext $context
    ): ?\Grpc\Testing\EmptyMessage {
        $context->setStatus(\Grpc\Status::unimplemented());
        return null;
    }

    public final function getMethodDescriptors(): array
    {
        return [
            '/grpc.testing.UnimplementedService/UnimplementedCall' => new \Grpc\MethodDescriptor(
                $this,
                'UnimplementedCall',
                '\Grpc\Testing\EmptyMessage',
                \Grpc\MethodDescriptor::UNARY_CALL
            ),
        ];
    }

}
