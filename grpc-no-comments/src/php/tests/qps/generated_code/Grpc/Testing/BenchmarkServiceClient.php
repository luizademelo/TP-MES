<?php

// Copyright 2015 gRPC authors.

namespace Grpc\Testing;

class BenchmarkServiceClient extends \Grpc\BaseStub {

    public function __construct($hostname, $opts, $channel = null) {
        parent::__construct($hostname, $opts, $channel);
    }

    public function UnaryCall(\Grpc\Testing\SimpleRequest $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.BenchmarkService/UnaryCall',
        $argument,
        ['\Grpc\Testing\SimpleResponse', 'decode'],
        $metadata, $options);
    }

    public function StreamingCall($metadata = [], $options = []) {
        return $this->_bidiRequest('/grpc.testing.BenchmarkService/StreamingCall',
        ['\Grpc\Testing\SimpleResponse','decode'],
        $metadata, $options);
    }

    public function StreamingFromClient($metadata = [], $options = []) {
        return $this->_clientStreamRequest('/grpc.testing.BenchmarkService/StreamingFromClient',
        ['\Grpc\Testing\SimpleResponse','decode'],
        $metadata, $options);
    }

    public function StreamingFromServer(\Grpc\Testing\SimpleRequest $argument,
      $metadata = [], $options = []) {
        return $this->_serverStreamRequest('/grpc.testing.BenchmarkService/StreamingFromServer',
        $argument,
        ['\Grpc\Testing\SimpleResponse', 'decode'],
        $metadata, $options);
    }

    public function StreamingBothWays($metadata = [], $options = []) {
        return $this->_bidiRequest('/grpc.testing.BenchmarkService/StreamingBothWays',
        ['\Grpc\Testing\SimpleResponse','decode'],
        $metadata, $options);
    }

}
