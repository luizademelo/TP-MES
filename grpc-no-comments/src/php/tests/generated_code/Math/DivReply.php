<?php
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: math.proto

namespace Math;

use Google\Protobuf\Internal\GPBType;
use Google\Protobuf\Internal\RepeatedField;
use Google\Protobuf\Internal\GPBUtil;

class DivReply extends \Google\Protobuf\Internal\Message
{

    protected $quotient = 0;

    protected $remainder = 0;

    public function __construct($data = NULL) {
        \GPBMetadata\Math::initOnce();
        parent::__construct($data);
    }

    public function getQuotient()
    {
        return $this->quotient;
    }

    public function setQuotient($var)
    {
        GPBUtil::checkInt64($var);
        $this->quotient = $var;

        return $this;
    }

    public function getRemainder()
    {
        return $this->remainder;
    }

    public function setRemainder($var)
    {
        GPBUtil::checkInt64($var);
        $this->remainder = $var;

        return $this;
    }

}
