<?php
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: src/proto/grpc/testing/messages.proto

namespace Grpc\Testing;

use Google\Protobuf\Internal\GPBType;
use Google\Protobuf\Internal\RepeatedField;
use Google\Protobuf\Internal\GPBUtil;

class ResponseParameters extends \Google\Protobuf\Internal\Message
{

    protected $size = 0;

    protected $interval_us = 0;

    protected $compressed = null;

    public function __construct($data = NULL) {
        \GPBMetadata\Src\Proto\Grpc\Testing\Messages::initOnce();
        parent::__construct($data);
    }

    public function getSize()
    {
        return $this->size;
    }

    public function setSize($var)
    {
        GPBUtil::checkInt32($var);
        $this->size = $var;

        return $this;
    }

    public function getIntervalUs()
    {
        return $this->interval_us;
    }

    public function setIntervalUs($var)
    {
        GPBUtil::checkInt32($var);
        $this->interval_us = $var;

        return $this;
    }

    public function getCompressed()
    {
        return $this->compressed;
    }

    public function setCompressed($var)
    {
        GPBUtil::checkMessage($var, \Grpc\Testing\BoolValue::class);
        $this->compressed = $var;

        return $this;
    }

}
