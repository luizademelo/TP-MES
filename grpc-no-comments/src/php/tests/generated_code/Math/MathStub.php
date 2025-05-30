<?php

// Copyright 2015 gRPC authors.

namespace Math;

class MathStub {

    public function Div(
        \Math\DivArgs $request,
        \Grpc\ServerContext $context
    ): ?\Math\DivReply {
        $context->setStatus(\Grpc\Status::unimplemented());
        return null;
    }

    public function DivMany(
        \Grpc\ServerCallReader $reader,
        \Grpc\ServerCallWriter $writer,
        \Grpc\ServerContext $context
    ): void {
        $context->setStatus(\Grpc\Status::unimplemented());
        $writer->finish();
    }

    public function Fib(
        \Math\FibArgs $request,
        \Grpc\ServerCallWriter $writer,
        \Grpc\ServerContext $context
    ): void {
        $context->setStatus(\Grpc\Status::unimplemented());
        $writer->finish();
    }

    public function Sum(
        \Grpc\ServerCallReader $reader,
        \Grpc\ServerContext $context
    ): ?\Math\Num {
        $context->setStatus(\Grpc\Status::unimplemented());
        return null;
    }

    public final function getMethodDescriptors(): array
    {
        return [
            '/math.Math/Div' => new \Grpc\MethodDescriptor(
                $this,
                'Div',
                '\Math\DivArgs',
                \Grpc\MethodDescriptor::UNARY_CALL
            ),
            '/math.Math/DivMany' => new \Grpc\MethodDescriptor(
                $this,
                'DivMany',
                '\Math\DivArgs',
                \Grpc\MethodDescriptor::BIDI_STREAMING_CALL
            ),
            '/math.Math/Fib' => new \Grpc\MethodDescriptor(
                $this,
                'Fib',
                '\Math\FibArgs',
                \Grpc\MethodDescriptor::SERVER_STREAMING_CALL
            ),
            '/math.Math/Sum' => new \Grpc\MethodDescriptor(
                $this,
                'Sum',
                '\Math\Num',
                \Grpc\MethodDescriptor::CLIENT_STREAMING_CALL
            ),
        ];
    }

}
