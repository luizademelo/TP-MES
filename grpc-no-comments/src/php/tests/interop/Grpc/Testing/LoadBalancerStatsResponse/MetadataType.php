<?php
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: src/proto/grpc/testing/messages.proto

namespace Grpc\Testing\LoadBalancerStatsResponse;

use UnexpectedValueException;

class MetadataType
{

    const UNKNOWN = 0;

    const INITIAL = 1;

    const TRAILING = 2;

    private static $valueToName = [
        self::UNKNOWN => 'UNKNOWN',
        self::INITIAL => 'INITIAL',
        self::TRAILING => 'TRAILING',
    ];

    public static function name($value)
    {
        if (!isset(self::$valueToName[$value])) {
            throw new UnexpectedValueException(sprintf(
                    'Enum %s has no name defined for value %s', __CLASS__, $value));
        }
        return self::$valueToName[$value];
    }

    public static function value($name)
    {
        $const = __CLASS__ . '::' . strtoupper($name);
        if (!defined($const)) {
            throw new UnexpectedValueException(sprintf(
                    'Enum %s has no value defined for name %s', __CLASS__, $name));
        }
        return constant($const);
    }
}

class_alias(MetadataType::class, \Grpc\Testing\LoadBalancerStatsResponse_MetadataType::class);
