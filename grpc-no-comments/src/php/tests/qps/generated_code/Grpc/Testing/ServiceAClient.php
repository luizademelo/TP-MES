<?php

// Copyright 2016 gRPC authors.

namespace Grpc\Testing;

class ServiceAClient extends \Grpc\BaseStub {

    public function __construct($hostname, $opts, $channel = null) {
        parent::__construct($hostname, $opts, $channel);
    }

    public function MethodA1(\Grpc\Testing\Request $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.ServiceA/MethodA1',
        $argument,
        ['\Grpc\Testing\Response', 'decode'],
        $metadata, $options);
    }

    public function MethodA2($metadata = [], $options = []) {
        return $this->_clientStreamRequest('/grpc.testing.ServiceA/MethodA2',
        ['\Grpc\Testing\Response','decode'],
        $metadata, $options);
    }

    public function MethodA3(\Grpc\Testing\Request $argument,
      $metadata = [], $options = []) {
        return $this->_serverStreamRequest('/grpc.testing.ServiceA/MethodA3',
        $argument,
        ['\Grpc\Testing\Response', 'decode'],
        $metadata, $options);
    }

    public function MethodA4($metadata = [], $options = []) {
        return $this->_bidiRequest('/grpc.testing.ServiceA/MethodA4',
        ['\Grpc\Testing\Response','decode'],
        $metadata, $options);
    }

}
