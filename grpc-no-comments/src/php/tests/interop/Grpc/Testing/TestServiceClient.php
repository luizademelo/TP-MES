<?php

// Copyright 2015-2016 gRPC authors.

namespace Grpc\Testing;

class TestServiceClient extends \Grpc\BaseStub {

    public function __construct($hostname, $opts, $channel = null) {
        parent::__construct($hostname, $opts, $channel);
    }

    public function EmptyCall(\Grpc\Testing\EmptyMessage $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.TestService/EmptyCall',
        $argument,
        ['\Grpc\Testing\EmptyMessage', 'decode'],
        $metadata, $options);
    }

    public function UnaryCall(\Grpc\Testing\SimpleRequest $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.TestService/UnaryCall',
        $argument,
        ['\Grpc\Testing\SimpleResponse', 'decode'],
        $metadata, $options);
    }

    public function CacheableUnaryCall(\Grpc\Testing\SimpleRequest $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.TestService/CacheableUnaryCall',
        $argument,
        ['\Grpc\Testing\SimpleResponse', 'decode'],
        $metadata, $options);
    }

    public function StreamingOutputCall(\Grpc\Testing\StreamingOutputCallRequest $argument,
      $metadata = [], $options = []) {
        return $this->_serverStreamRequest('/grpc.testing.TestService/StreamingOutputCall',
        $argument,
        ['\Grpc\Testing\StreamingOutputCallResponse', 'decode'],
        $metadata, $options);
    }

    public function StreamingInputCall($metadata = [], $options = []) {
        return $this->_clientStreamRequest('/grpc.testing.TestService/StreamingInputCall',
        ['\Grpc\Testing\StreamingInputCallResponse','decode'],
        $metadata, $options);
    }

    public function FullDuplexCall($metadata = [], $options = []) {
        return $this->_bidiRequest('/grpc.testing.TestService/FullDuplexCall',
        ['\Grpc\Testing\StreamingOutputCallResponse','decode'],
        $metadata, $options);
    }

    public function HalfDuplexCall($metadata = [], $options = []) {
        return $this->_bidiRequest('/grpc.testing.TestService/HalfDuplexCall',
        ['\Grpc\Testing\StreamingOutputCallResponse','decode'],
        $metadata, $options);
    }

    public function UnimplementedCall(\Grpc\Testing\EmptyMessage $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.TestService/UnimplementedCall',
        $argument,
        ['\Grpc\Testing\EmptyMessage', 'decode'],
        $metadata, $options);
    }

}
