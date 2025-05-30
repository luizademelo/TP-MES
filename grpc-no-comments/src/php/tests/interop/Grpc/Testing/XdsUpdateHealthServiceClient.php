<?php

// Copyright 2015-2016 gRPC authors.

namespace Grpc\Testing;

class XdsUpdateHealthServiceClient extends \Grpc\BaseStub {

    public function __construct($hostname, $opts, $channel = null) {
        parent::__construct($hostname, $opts, $channel);
    }

    public function SetServing(\Grpc\Testing\EmptyMessage $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.XdsUpdateHealthService/SetServing',
        $argument,
        ['\Grpc\Testing\EmptyMessage', 'decode'],
        $metadata, $options);
    }

    public function SetNotServing(\Grpc\Testing\EmptyMessage $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.XdsUpdateHealthService/SetNotServing',
        $argument,
        ['\Grpc\Testing\EmptyMessage', 'decode'],
        $metadata, $options);
    }

    public function SendHookRequest(\Grpc\Testing\HookRequest $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.XdsUpdateHealthService/SendHookRequest',
        $argument,
        ['\Grpc\Testing\HookResponse', 'decode'],
        $metadata, $options);
    }

}
