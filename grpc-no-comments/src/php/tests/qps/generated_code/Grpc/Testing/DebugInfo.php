<?php
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: src/proto/grpc/testing/echo_messages.proto

namespace Grpc\Testing;

use Google\Protobuf\Internal\GPBType;
use Google\Protobuf\Internal\RepeatedField;
use Google\Protobuf\Internal\GPBUtil;

class DebugInfo extends \Google\Protobuf\Internal\Message
{

    private $stack_entries;

    protected $detail = '';

    public function __construct($data = NULL) {
        \GPBMetadata\Src\Proto\Grpc\Testing\EchoMessages::initOnce();
        parent::__construct($data);
    }

    public function getStackEntries()
    {
        return $this->stack_entries;
    }

    public function setStackEntries($var)
    {
        $arr = GPBUtil::checkRepeatedField($var, \Google\Protobuf\Internal\GPBType::STRING);
        $this->stack_entries = $arr;

        return $this;
    }

    public function getDetail()
    {
        return $this->detail;
    }

    public function setDetail($var)
    {
        GPBUtil::checkString($var, True);
        $this->detail = $var;

        return $this;
    }

}
