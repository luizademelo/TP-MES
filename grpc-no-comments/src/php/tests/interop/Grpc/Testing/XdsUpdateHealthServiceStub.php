<?php

// Copyright 2015-2016 gRPC authors.

namespace Grpc\Testing;

class XdsUpdateHealthServiceStub {

    public function SetServing(
        \Grpc\Testing\EmptyMessage $request,
        \Grpc\ServerContext $context
    ): ?\Grpc\Testing\EmptyMessage {
        $context->setStatus(\Grpc\Status::unimplemented());
        return null;
    }

    public function SetNotServing(
        \Grpc\Testing\EmptyMessage $request,
        \Grpc\ServerContext $context
    ): ?\Grpc\Testing\EmptyMessage {
        $context->setStatus(\Grpc\Status::unimplemented());
        return null;
    }

    public function SendHookRequest(
        \Grpc\Testing\HookRequest $request,
        \Grpc\ServerContext $context
    ): ?\Grpc\Testing\HookResponse {
        $context->setStatus(\Grpc\Status::unimplemented());
        return null;
    }

    public final function getMethodDescriptors(): array
    {
        return [
            '/grpc.testing.XdsUpdateHealthService/SetServing' => new \Grpc\MethodDescriptor(
                $this,
                'SetServing',
                '\Grpc\Testing\EmptyMessage',
                \Grpc\MethodDescriptor::UNARY_CALL
            ),
            '/grpc.testing.XdsUpdateHealthService/SetNotServing' => new \Grpc\MethodDescriptor(
                $this,
                'SetNotServing',
                '\Grpc\Testing\EmptyMessage',
                \Grpc\MethodDescriptor::UNARY_CALL
            ),
            '/grpc.testing.XdsUpdateHealthService/SendHookRequest' => new \Grpc\MethodDescriptor(
                $this,
                'SendHookRequest',
                '\Grpc\Testing\HookRequest',
                \Grpc\MethodDescriptor::UNARY_CALL
            ),
        ];
    }

}
