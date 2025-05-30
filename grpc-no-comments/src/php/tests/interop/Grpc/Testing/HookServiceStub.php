<?php

// Copyright 2015-2016 gRPC authors.

namespace Grpc\Testing;

class HookServiceStub {

    public function Hook(
        \Grpc\Testing\EmptyMessage $request,
        \Grpc\ServerContext $context
    ): ?\Grpc\Testing\EmptyMessage {
        $context->setStatus(\Grpc\Status::unimplemented());
        return null;
    }

    public function SetReturnStatus(
        \Grpc\Testing\SetReturnStatusRequest $request,
        \Grpc\ServerContext $context
    ): ?\Grpc\Testing\EmptyMessage {
        $context->setStatus(\Grpc\Status::unimplemented());
        return null;
    }

    public function ClearReturnStatus(
        \Grpc\Testing\EmptyMessage $request,
        \Grpc\ServerContext $context
    ): ?\Grpc\Testing\EmptyMessage {
        $context->setStatus(\Grpc\Status::unimplemented());
        return null;
    }

    public final function getMethodDescriptors(): array
    {
        return [
            '/grpc.testing.HookService/Hook' => new \Grpc\MethodDescriptor(
                $this,
                'Hook',
                '\Grpc\Testing\EmptyMessage',
                \Grpc\MethodDescriptor::UNARY_CALL
            ),
            '/grpc.testing.HookService/SetReturnStatus' => new \Grpc\MethodDescriptor(
                $this,
                'SetReturnStatus',
                '\Grpc\Testing\SetReturnStatusRequest',
                \Grpc\MethodDescriptor::UNARY_CALL
            ),
            '/grpc.testing.HookService/ClearReturnStatus' => new \Grpc\MethodDescriptor(
                $this,
                'ClearReturnStatus',
                '\Grpc\Testing\EmptyMessage',
                \Grpc\MethodDescriptor::UNARY_CALL
            ),
        ];
    }

}
