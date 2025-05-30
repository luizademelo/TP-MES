<?php

// Copyright 2015-2016 gRPC authors.

namespace Grpc\Testing;

class HookServiceClient extends \Grpc\BaseStub {

    public function __construct($hostname, $opts, $channel = null) {
        parent::__construct($hostname, $opts, $channel);
    }

    public function Hook(\Grpc\Testing\EmptyMessage $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.HookService/Hook',
        $argument,
        ['\Grpc\Testing\EmptyMessage', 'decode'],
        $metadata, $options);
    }

    public function SetReturnStatus(\Grpc\Testing\SetReturnStatusRequest $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.HookService/SetReturnStatus',
        $argument,
        ['\Grpc\Testing\EmptyMessage', 'decode'],
        $metadata, $options);
    }

    public function ClearReturnStatus(\Grpc\Testing\EmptyMessage $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.HookService/ClearReturnStatus',
        $argument,
        ['\Grpc\Testing\EmptyMessage', 'decode'],
        $metadata, $options);
    }

}
