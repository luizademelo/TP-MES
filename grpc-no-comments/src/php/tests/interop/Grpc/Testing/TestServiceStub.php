<?php

// Copyright 2015-2016 gRPC authors.

namespace Grpc\Testing;

class TestServiceStub {

    public function EmptyCall(
        \Grpc\Testing\EmptyMessage $request,
        \Grpc\ServerContext $context
    ): ?\Grpc\Testing\EmptyMessage {
        $context->setStatus(\Grpc\Status::unimplemented());
        return null;
    }

    public function UnaryCall(
        \Grpc\Testing\SimpleRequest $request,
        \Grpc\ServerContext $context
    ): ?\Grpc\Testing\SimpleResponse {
        $context->setStatus(\Grpc\Status::unimplemented());
        return null;
    }

    public function CacheableUnaryCall(
        \Grpc\Testing\SimpleRequest $request,
        \Grpc\ServerContext $context
    ): ?\Grpc\Testing\SimpleResponse {
        $context->setStatus(\Grpc\Status::unimplemented());
        return null;
    }

    public function StreamingOutputCall(
        \Grpc\Testing\StreamingOutputCallRequest $request,
        \Grpc\ServerCallWriter $writer,
        \Grpc\ServerContext $context
    ): void {
        $context->setStatus(\Grpc\Status::unimplemented());
        $writer->finish();
    }

    public function StreamingInputCall(
        \Grpc\ServerCallReader $reader,
        \Grpc\ServerContext $context
    ): ?\Grpc\Testing\StreamingInputCallResponse {
        $context->setStatus(\Grpc\Status::unimplemented());
        return null;
    }

    public function FullDuplexCall(
        \Grpc\ServerCallReader $reader,
        \Grpc\ServerCallWriter $writer,
        \Grpc\ServerContext $context
    ): void {
        $context->setStatus(\Grpc\Status::unimplemented());
        $writer->finish();
    }

    public function HalfDuplexCall(
        \Grpc\ServerCallReader $reader,
        \Grpc\ServerCallWriter $writer,
        \Grpc\ServerContext $context
    ): void {
        $context->setStatus(\Grpc\Status::unimplemented());
        $writer->finish();
    }

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
            '/grpc.testing.TestService/EmptyCall' => new \Grpc\MethodDescriptor(
                $this,
                'EmptyCall',
                '\Grpc\Testing\EmptyMessage',
                \Grpc\MethodDescriptor::UNARY_CALL
            ),
            '/grpc.testing.TestService/UnaryCall' => new \Grpc\MethodDescriptor(
                $this,
                'UnaryCall',
                '\Grpc\Testing\SimpleRequest',
                \Grpc\MethodDescriptor::UNARY_CALL
            ),
            '/grpc.testing.TestService/CacheableUnaryCall' => new \Grpc\MethodDescriptor(
                $this,
                'CacheableUnaryCall',
                '\Grpc\Testing\SimpleRequest',
                \Grpc\MethodDescriptor::UNARY_CALL
            ),
            '/grpc.testing.TestService/StreamingOutputCall' => new \Grpc\MethodDescriptor(
                $this,
                'StreamingOutputCall',
                '\Grpc\Testing\StreamingOutputCallRequest',
                \Grpc\MethodDescriptor::SERVER_STREAMING_CALL
            ),
            '/grpc.testing.TestService/StreamingInputCall' => new \Grpc\MethodDescriptor(
                $this,
                'StreamingInputCall',
                '\Grpc\Testing\StreamingInputCallRequest',
                \Grpc\MethodDescriptor::CLIENT_STREAMING_CALL
            ),
            '/grpc.testing.TestService/FullDuplexCall' => new \Grpc\MethodDescriptor(
                $this,
                'FullDuplexCall',
                '\Grpc\Testing\StreamingOutputCallRequest',
                \Grpc\MethodDescriptor::BIDI_STREAMING_CALL
            ),
            '/grpc.testing.TestService/HalfDuplexCall' => new \Grpc\MethodDescriptor(
                $this,
                'HalfDuplexCall',
                '\Grpc\Testing\StreamingOutputCallRequest',
                \Grpc\MethodDescriptor::BIDI_STREAMING_CALL
            ),
            '/grpc.testing.TestService/UnimplementedCall' => new \Grpc\MethodDescriptor(
                $this,
                'UnimplementedCall',
                '\Grpc\Testing\EmptyMessage',
                \Grpc\MethodDescriptor::UNARY_CALL
            ),
        ];
    }

}
