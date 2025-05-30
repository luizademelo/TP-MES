<?php

// Copyright 2016 gRPC authors.

namespace Grpc\Testing;

class ServiceBClient extends \Grpc\BaseStub {

    public function __construct($hostname, $opts, $channel = null) {
        parent::__construct($hostname, $opts, $channel);
    }

    public function MethodB1(\Grpc\Testing\Request $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.ServiceB/MethodB1',
        $argument,
        ['\Grpc\Testing\Response', 'decode'],
        $metadata, $options);
    }

}
