<?php

// Copyright 2015-2016 gRPC authors.

namespace Grpc\Testing;

class XdsUpdateClientConfigureServiceStub {

    public function Configure(
        \Grpc\Testing\ClientConfigureRequest $request,
        \Grpc\ServerContext $context
    ): ?\Grpc\Testing\ClientConfigureResponse {
        $context->setStatus(\Grpc\Status::unimplemented());
        return null;
    }

    public final function getMethodDescriptors(): array
    {
        return [
            '/grpc.testing.XdsUpdateClientConfigureService/Configure' => new \Grpc\MethodDescriptor(
                $this,
                'Configure',
                '\Grpc\Testing\ClientConfigureRequest',
                \Grpc\MethodDescriptor::UNARY_CALL
            ),
        ];
    }

}
