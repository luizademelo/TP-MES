<?php
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: src/proto/grpc/testing/control.proto

namespace Grpc\Testing;

use Google\Protobuf\Internal\GPBType;
use Google\Protobuf\Internal\RepeatedField;
use Google\Protobuf\Internal\GPBUtil;

class LoadParams extends \Google\Protobuf\Internal\Message
{
    protected $load;

    public function __construct($data = NULL) {
        \GPBMetadata\Src\Proto\Grpc\Testing\Control::initOnce();
        parent::__construct($data);
    }

    public function getClosedLoop()
    {
        return $this->readOneof(1);
    }

    public function setClosedLoop($var)
    {
        GPBUtil::checkMessage($var, \Grpc\Testing\ClosedLoopParams::class);
        $this->writeOneof(1, $var);

        return $this;
    }

    public function getPoisson()
    {
        return $this->readOneof(2);
    }

    public function setPoisson($var)
    {
        GPBUtil::checkMessage($var, \Grpc\Testing\PoissonParams::class);
        $this->writeOneof(2, $var);

        return $this;
    }

    public function getLoad()
    {
        return $this->whichOneof("load");
    }

}
