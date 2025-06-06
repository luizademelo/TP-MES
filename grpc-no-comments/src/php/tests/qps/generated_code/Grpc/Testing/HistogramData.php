<?php
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: src/proto/grpc/testing/stats.proto

namespace Grpc\Testing;

use Google\Protobuf\Internal\GPBType;
use Google\Protobuf\Internal\RepeatedField;
use Google\Protobuf\Internal\GPBUtil;

class HistogramData extends \Google\Protobuf\Internal\Message
{

    private $bucket;

    protected $min_seen = 0.0;

    protected $max_seen = 0.0;

    protected $sum = 0.0;

    protected $sum_of_squares = 0.0;

    protected $count = 0.0;

    public function __construct($data = NULL) {
        \GPBMetadata\Src\Proto\Grpc\Testing\Stats::initOnce();
        parent::__construct($data);
    }

    public function getBucket()
    {
        return $this->bucket;
    }

    public function setBucket($var)
    {
        $arr = GPBUtil::checkRepeatedField($var, \Google\Protobuf\Internal\GPBType::UINT32);
        $this->bucket = $arr;

        return $this;
    }

    public function getMinSeen()
    {
        return $this->min_seen;
    }

    public function setMinSeen($var)
    {
        GPBUtil::checkDouble($var);
        $this->min_seen = $var;

        return $this;
    }

    public function getMaxSeen()
    {
        return $this->max_seen;
    }

    public function setMaxSeen($var)
    {
        GPBUtil::checkDouble($var);
        $this->max_seen = $var;

        return $this;
    }

    public function getSum()
    {
        return $this->sum;
    }

    public function setSum($var)
    {
        GPBUtil::checkDouble($var);
        $this->sum = $var;

        return $this;
    }

    public function getSumOfSquares()
    {
        return $this->sum_of_squares;
    }

    public function setSumOfSquares($var)
    {
        GPBUtil::checkDouble($var);
        $this->sum_of_squares = $var;

        return $this;
    }

    public function getCount()
    {
        return $this->count;
    }

    public function setCount($var)
    {
        GPBUtil::checkDouble($var);
        $this->count = $var;

        return $this;
    }

}
