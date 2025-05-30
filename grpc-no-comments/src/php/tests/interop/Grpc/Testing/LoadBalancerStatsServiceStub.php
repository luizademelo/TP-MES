<?php

// Copyright 2015-2016 gRPC authors.

namespace Grpc\Testing;

class LoadBalancerStatsServiceStub {

    public function GetClientStats(
        \Grpc\Testing\LoadBalancerStatsRequest $request,
        \Grpc\ServerContext $context
    ): ?\Grpc\Testing\LoadBalancerStatsResponse {
        $context->setStatus(\Grpc\Status::unimplemented());
        return null;
    }

    public function GetClientAccumulatedStats(
        \Grpc\Testing\LoadBalancerAccumulatedStatsRequest $request,
        \Grpc\ServerContext $context
    ): ?\Grpc\Testing\LoadBalancerAccumulatedStatsResponse {
        $context->setStatus(\Grpc\Status::unimplemented());
        return null;
    }

    public final function getMethodDescriptors(): array
    {
        return [
            '/grpc.testing.LoadBalancerStatsService/GetClientStats' => new \Grpc\MethodDescriptor(
                $this,
                'GetClientStats',
                '\Grpc\Testing\LoadBalancerStatsRequest',
                \Grpc\MethodDescriptor::UNARY_CALL
            ),
            '/grpc.testing.LoadBalancerStatsService/GetClientAccumulatedStats' => new \Grpc\MethodDescriptor(
                $this,
                'GetClientAccumulatedStats',
                '\Grpc\Testing\LoadBalancerAccumulatedStatsRequest',
                \Grpc\MethodDescriptor::UNARY_CALL
            ),
        ];
    }

}
