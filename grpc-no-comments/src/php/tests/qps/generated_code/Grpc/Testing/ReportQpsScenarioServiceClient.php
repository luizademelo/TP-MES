<?php

// Copyright 2015 gRPC authors.

namespace Grpc\Testing;

class ReportQpsScenarioServiceClient extends \Grpc\BaseStub {

    public function __construct($hostname, $opts, $channel = null) {
        parent::__construct($hostname, $opts, $channel);
    }

    public function ReportScenario(\Grpc\Testing\ScenarioResult $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.ReportQpsScenarioService/ReportScenario',
        $argument,
        ['\Grpc\Testing\PBVoid', 'decode'],
        $metadata, $options);
    }

}
