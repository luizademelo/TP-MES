<?php
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: src/proto/grpc/testing/messages.proto

namespace Grpc\Testing\ClientConfigureRequest;

use Google\Protobuf\Internal\GPBType;
use Google\Protobuf\Internal\RepeatedField;
use Google\Protobuf\Internal\GPBUtil;

class Metadata extends \Google\Protobuf\Internal\Message
{

    protected $type = 0;

    protected $key = '';

    protected $value = '';

    public function __construct($data = NULL) {
        \GPBMetadata\Src\Proto\Grpc\Testing\Messages::initOnce();
        parent::__construct($data);
    }

    public function getType()
    {
        return $this->type;
    }

    public function setType($var)
    {
        GPBUtil::checkEnum($var, \Grpc\Testing\ClientConfigureRequest\RpcType::class);
        $this->type = $var;

        return $this;
    }

    public function getKey()
    {
        return $this->key;
    }

    public function setKey($var)
    {
        GPBUtil::checkString($var, True);
        $this->key = $var;

        return $this;
    }

    public function getValue()
    {
        return $this->value;
    }

    public function setValue($var)
    {
        GPBUtil::checkString($var, True);
        $this->value = $var;

        return $this;
    }

}

class_alias(Metadata::class, \Grpc\Testing\ClientConfigureRequest_Metadata::class);
