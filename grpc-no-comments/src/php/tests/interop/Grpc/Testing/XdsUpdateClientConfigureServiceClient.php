<?php

// Copyright 2015-2016 gRPC authors.

namespace Grpc\Testing;

class XdsUpdateClientConfigureServiceClient extends \Grpc\BaseStub {

    public function __construct($hostname, $opts, $channel = null) {
        parent::__construct($hostname, $opts, $channel);
    }

    public function Configure(\Grpc\Testing\ClientConfigureRequest $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.XdsUpdateClientConfigureService/Configure',
        $argument,
        ['\Grpc\Testing\ClientConfigureResponse', 'decode'],
        $metadata, $options);
    }

}
