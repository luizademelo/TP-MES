<?php

// Copyright 2015-2016 gRPC authors.

namespace Grpc\Testing;

class ReconnectServiceClient extends \Grpc\BaseStub {

    public function __construct($hostname, $opts, $channel = null) {
        parent::__construct($hostname, $opts, $channel);
    }

    public function Start(\Grpc\Testing\ReconnectParams $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.ReconnectService/Start',
        $argument,
        ['\Grpc\Testing\EmptyMessage', 'decode'],
        $metadata, $options);
    }

    public function Stop(\Grpc\Testing\EmptyMessage $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.ReconnectService/Stop',
        $argument,
        ['\Grpc\Testing\ReconnectInfo', 'decode'],
        $metadata, $options);
    }

}
