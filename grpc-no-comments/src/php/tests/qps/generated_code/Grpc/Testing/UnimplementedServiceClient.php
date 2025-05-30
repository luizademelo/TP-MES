<?php

// Copyright 2015-2016 gRPC authors.

namespace Grpc\Testing;

class UnimplementedServiceClient extends \Grpc\BaseStub {

    public function __construct($hostname, $opts, $channel = null) {
        parent::__construct($hostname, $opts, $channel);
    }

    public function UnimplementedCall(\Grpc\Testing\EmptyMessage $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.UnimplementedService/UnimplementedCall',
        $argument,
        ['\Grpc\Testing\EmptyMessage', 'decode'],
        $metadata, $options);
    }

}
