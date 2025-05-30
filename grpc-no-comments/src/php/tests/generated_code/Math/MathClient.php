<?php

// Copyright 2015 gRPC authors.

namespace Math;

class MathClient extends \Grpc\BaseStub {

    public function __construct($hostname, $opts, $channel = null) {
        parent::__construct($hostname, $opts, $channel);
    }

    public function Div(\Math\DivArgs $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/math.Math/Div',
        $argument,
        ['\Math\DivReply', 'decode'],
        $metadata, $options);
    }

    public function DivMany($metadata = [], $options = []) {
        return $this->_bidiRequest('/math.Math/DivMany',
        ['\Math\DivReply','decode'],
        $metadata, $options);
    }

    public function Fib(\Math\FibArgs $argument,
      $metadata = [], $options = []) {
        return $this->_serverStreamRequest('/math.Math/Fib',
        $argument,
        ['\Math\Num', 'decode'],
        $metadata, $options);
    }

    public function Sum($metadata = [], $options = []) {
        return $this->_clientStreamRequest('/math.Math/Sum',
        ['\Math\Num','decode'],
        $metadata, $options);
    }

}
