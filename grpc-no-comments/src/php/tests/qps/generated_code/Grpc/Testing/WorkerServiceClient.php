<?php

// Copyright 2015 gRPC authors.

namespace Grpc\Testing;

class WorkerServiceClient extends \Grpc\BaseStub {

    public function __construct($hostname, $opts, $channel = null) {
        parent::__construct($hostname, $opts, $channel);
    }

    public function RunServer($metadata = [], $options = []) {
        return $this->_bidiRequest('/grpc.testing.WorkerService/RunServer',
        ['\Grpc\Testing\ServerStatus','decode'],
        $metadata, $options);
    }

    public function RunClient($metadata = [], $options = []) {
        return $this->_bidiRequest('/grpc.testing.WorkerService/RunClient',
        ['\Grpc\Testing\ClientStatus','decode'],
        $metadata, $options);
    }

    public function CoreCount(\Grpc\Testing\CoreRequest $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.WorkerService/CoreCount',
        $argument,
        ['\Grpc\Testing\CoreResponse', 'decode'],
        $metadata, $options);
    }

    public function QuitWorker(\Grpc\Testing\PBVoid $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.WorkerService/QuitWorker',
        $argument,
        ['\Grpc\Testing\PBVoid', 'decode'],
        $metadata, $options);
    }

}
