<?php

// Copyright 2017 gRPC authors.

namespace Grpc\Testing;

class ProxyClientServiceClient extends \Grpc\BaseStub {

    public function __construct($hostname, $opts, $channel = null) {
        parent::__construct($hostname, $opts, $channel);
    }

    public function GetConfig(\Grpc\Testing\PBVoid $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/grpc.testing.ProxyClientService/GetConfig',
        $argument,
        ['\Grpc\Testing\ClientConfig', 'decode'],
        $metadata, $options);
    }

    public function ReportTime($metadata = [], $options = []) {
        return $this->_clientStreamRequest('/grpc.testing.ProxyClientService/ReportTime',
        ['\Grpc\Testing\PBVoid','decode'],
        $metadata, $options);
    }

    public function ReportHist($metadata = [], $options = []) {
        return $this->_clientStreamRequest('/grpc.testing.ProxyClientService/ReportHist',
        ['\Grpc\Testing\PBVoid','decode'],
        $metadata, $options);
    }

}
