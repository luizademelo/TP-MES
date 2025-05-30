<?php

// Copyright 2015 gRPC authors.

namespace Routeguide;

class RouteGuideStub {

    public function GetFeature(
        \Routeguide\Point $request,
        \Grpc\ServerContext $context
    ): ?\Routeguide\Feature {
        $context->setStatus(\Grpc\Status::unimplemented());
        return null;
    }

    public function ListFeatures(
        \Routeguide\Rectangle $request,
        \Grpc\ServerCallWriter $writer,
        \Grpc\ServerContext $context
    ): void {
        $context->setStatus(\Grpc\Status::unimplemented());
        $writer->finish();
    }

    public function RecordRoute(
        \Grpc\ServerCallReader $reader,
        \Grpc\ServerContext $context
    ): ?\Routeguide\RouteSummary {
        $context->setStatus(\Grpc\Status::unimplemented());
        return null;
    }

    public function RouteChat(
        \Grpc\ServerCallReader $reader,
        \Grpc\ServerCallWriter $writer,
        \Grpc\ServerContext $context
    ): void {
        $context->setStatus(\Grpc\Status::unimplemented());
        $writer->finish();
    }

    public final function getMethodDescriptors(): array
    {
        return [
            '/routeguide.RouteGuide/GetFeature' => new \Grpc\MethodDescriptor(
                $this,
                'GetFeature',
                '\Routeguide\Point',
                \Grpc\MethodDescriptor::UNARY_CALL
            ),
            '/routeguide.RouteGuide/ListFeatures' => new \Grpc\MethodDescriptor(
                $this,
                'ListFeatures',
                '\Routeguide\Rectangle',
                \Grpc\MethodDescriptor::SERVER_STREAMING_CALL
            ),
            '/routeguide.RouteGuide/RecordRoute' => new \Grpc\MethodDescriptor(
                $this,
                'RecordRoute',
                '\Routeguide\Point',
                \Grpc\MethodDescriptor::CLIENT_STREAMING_CALL
            ),
            '/routeguide.RouteGuide/RouteChat' => new \Grpc\MethodDescriptor(
                $this,
                'RouteChat',
                '\Routeguide\RouteNote',
                \Grpc\MethodDescriptor::BIDI_STREAMING_CALL
            ),
        ];
    }

}
