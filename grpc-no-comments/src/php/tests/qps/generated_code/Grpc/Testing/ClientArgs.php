<?php
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: src/proto/grpc/testing/control.proto

namespace Grpc\Testing;

use Google\Protobuf\Internal\GPBType;
use Google\Protobuf\Internal\RepeatedField;
use Google\Protobuf\Internal\GPBUtil;

class ClientArgs extends \Google\Protobuf\Internal\Message
{
    protected $argtype;

    public function __construct($data = NULL) {
        \GPBMetadata\Src\Proto\Grpc\Testing\Control::initOnce();
        parent::__construct($data);
    }

    public function getSetup()
    {
        return $this->readOneof(1);
    }

    public function setSetup($var)
    {
        GPBUtil::checkMessage($var, \Grpc\Testing\ClientConfig::class);
        $this->writeOneof(1, $var);

        return $this;
    }

    public function getMark()
    {
        return $this->readOneof(2);
    }

    public function setMark($var)
    {
        GPBUtil::checkMessage($var, \Grpc\Testing\Mark::class);
        $this->writeOneof(2, $var);

        return $this;
    }

    public function getArgtype()
    {
        return $this->whichOneof("argtype");
    }

}
