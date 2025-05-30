<?php

// Copyright 2015-2016 gRPC authors.

namespace Grpc\Testing;

class LoadBalancerStatsServiceClient extends \Grpc\BaseStub {

    public function __construct($hostname, $opts, $channel = null) {
        parent::__construct($hostname, $opts, $channel);
    }

    public function GetClientStats(\Grpc\Testing\LoadBalancerStatsRequest $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.LoadBalancerStatsService/GetClientStats',
        $argument,
        ['\Grpc\Testing\LoadBalancerStatsResponse', 'decode'],
        $metadata, $options);
    }

    public function GetClientAccumulatedStats(\Grpc\Testing\LoadBalancerAccumulatedStatsRequest $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.LoadBalancerStatsService/GetClientAccumulatedStats',
        $argument,
        ['\Grpc\Testing\LoadBalancerAccumulatedStatsResponse', 'decode'],
        $metadata, $options);
    }

}
