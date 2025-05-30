<?php

// Copyright 2015 gRPC authors.

namespace Routeguide;

class RouteGuideClient extends \Grpc\BaseStub {

    public function __construct($hostname, $opts, $channel = null) {
        parent::__construct($hostname, $opts, $channel);
    }

    public function GetFeature(\Routeguide\Point $argument,
      $metadata = [], $options = []) {
        return $this->_simpleRequest('/routeguide.RouteGuide/GetFeature',
        $argument,
        ['\Routeguide\Feature', 'decode'],
        $metadata, $options);
    }

    public function ListFeatures(\Routeguide\Rectangle $argument,
      $metadata = [], $options = []) {
        return $this->_serverStreamRequest('/routeguide.RouteGuide/ListFeatures',
        $argument,
        ['\Routeguide\Feature', 'decode'],
        $metadata, $options);
    }

    public function RecordRoute($metadata = [], $options = []) {
        return $this->_clientStreamRequest('/routeguide.RouteGuide/RecordRoute',
        ['\Routeguide\RouteSummary','decode'],
        $metadata, $options);
    }

    public function RouteChat($metadata = [], $options = []) {
        return $this->_bidiRequest('/routeguide.RouteGuide/RouteChat',
        ['\Routeguide\RouteNote','decode'],
        $metadata, $options);
    }

}
