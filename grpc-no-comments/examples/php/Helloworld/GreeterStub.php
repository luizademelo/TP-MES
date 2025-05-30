<?php

// Copyright 2015 gRPC authors.

namespace Helloworld;

class GreeterStub {

    public function SayHello(
        \Helloworld\HelloRequest $request,
        \Grpc\ServerContext $context
    ): ?\Helloworld\HelloReply {
        $context->setStatus(\Grpc\Status::unimplemented());
        return null;
    }

    public final function getMethodDescriptors(): array
    {
        return [
            '/helloworld.Greeter/SayHello' => new \Grpc\MethodDescriptor(
                $this,
                'SayHello',
                '\Helloworld\HelloRequest',
                \Grpc\MethodDescriptor::UNARY_CALL
            ),
        ];
    }

}
