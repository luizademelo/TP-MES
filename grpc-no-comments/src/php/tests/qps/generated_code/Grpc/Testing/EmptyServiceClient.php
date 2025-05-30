<?php

// Copyright 2018 gRPC authors.

namespace Grpc\Testing;

class EmptyServiceClient extends \Grpc\BaseStub {

    public function __construct($hostname, $opts, $channel = null) {
        parent::__construct($hostname, $opts, $channel);
    }

}
