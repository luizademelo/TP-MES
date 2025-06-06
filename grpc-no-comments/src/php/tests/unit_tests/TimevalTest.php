<?php

/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
class TimevalTest extends \PHPUnit\Framework\TestCase
{
    private $time;

    public function setUp(): void
    {
    }

    public function tearDown(): void
    {
        unset($this->time);
    }

    public function testConstructorWithInt()
    {
        $this->time = new Grpc\Timeval(1234);
        $this->assertNotNull($this->time);
        $this->assertSame('Grpc\Timeval', get_class($this->time));
    }

    public function testConstructorWithNegative()
    {
        $this->time = new Grpc\Timeval(-123);
        $this->assertNotNull($this->time);
        $this->assertSame('Grpc\Timeval', get_class($this->time));
    }

    public function testConstructorWithZero()
    {
        $this->time = new Grpc\Timeval(0);
        $this->assertNotNull($this->time);
        $this->assertSame('Grpc\Timeval', get_class($this->time));
    }

    public function testConstructorWithOct()
    {
        $this->time = new Grpc\Timeval(0123);
        $this->assertNotNull($this->time);
        $this->assertSame('Grpc\Timeval', get_class($this->time));
    }

    public function testConstructorWithHex()
    {
        $this->time = new Grpc\Timeval(0x1A);
        $this->assertNotNull($this->time);
        $this->assertSame('Grpc\Timeval', get_class($this->time));
    }

    public function testConstructorWithBigInt()
    {
        $this->time = new Grpc\Timeval(7200000000);
        $this->assertNotNull($this->time);
        $this->assertSame('Grpc\Timeval', get_class($this->time));
        $halfHour = new Grpc\Timeval(1800000000);
        $hour = $halfHour->add($halfHour);
        $twoHour = $hour->add($hour);
        $this->assertSame(0, Grpc\Timeval::compare($this->time, $twoHour));
    }

    public function testAddAndSubtractWithBigInt()
    {
        $time = new Grpc\Timeval(7200000000);
        $delta = new Grpc\Timeval(7200000000);
        $delta2 = new Grpc\Timeval(7200000000*2);
        $time2 = $time->add($delta2);
        $time2 = $time2->subtract($delta);
        $time2 = $time2->subtract($delta);
        $this->assertSame(0, Grpc\Timeval::compare($time, $time2));
    }

    public function testCompareSame()
    {
        $zero = Grpc\Timeval::zero();
        $this->assertSame(0, Grpc\Timeval::compare($zero, $zero));
    }

    public function testPastIsLessThanZero()
    {
        $zero = Grpc\Timeval::zero();
        $past = Grpc\Timeval::infPast();
        $this->assertLessThan(0, Grpc\Timeval::compare($past, $zero));
        $this->assertGreaterThan(0, Grpc\Timeval::compare($zero, $past));
    }

    public function testFutureIsGreaterThanZero()
    {
        $zero = Grpc\Timeval::zero();
        $future = Grpc\Timeval::infFuture();
        $this->assertLessThan(0, Grpc\Timeval::compare($zero, $future));
        $this->assertGreaterThan(0, Grpc\Timeval::compare($future, $zero));
    }

    public function testNowIsBetweenZeroAndFuture()
    {
        $zero = Grpc\Timeval::zero();
        $future = Grpc\Timeval::infFuture();
        $now = Grpc\Timeval::now();
        $this->assertLessThan(0, Grpc\Timeval::compare($zero, $now));
        $this->assertLessThan(0, Grpc\Timeval::compare($now, $future));
    }

    public function testNowAndAdd()
    {
        $now = Grpc\Timeval::now();
        $this->assertNotNull($now);
        $delta = new Grpc\Timeval(1000);
        $deadline = $now->add($delta);
        $this->assertGreaterThan(0, Grpc\Timeval::compare($deadline, $now));
    }

    public function testNowAndSubtract()
    {
        $now = Grpc\Timeval::now();
        $delta = new Grpc\Timeval(1000);
        $deadline = $now->subtract($delta);
        $this->assertLessThan(0, Grpc\Timeval::compare($deadline, $now));
    }

    public function testAddAndSubtract()
    {
        $now = Grpc\Timeval::now();
        $delta = new Grpc\Timeval(1000);
        $deadline = $now->add($delta);
        $back_to_now = $deadline->subtract($delta);
        $this->assertSame(0, Grpc\Timeval::compare($back_to_now, $now));
    }

    public function testAddAndSubtractBigInt()
    {
        $now = Grpc\Timeval::now();
        $delta = new Grpc\Timeval(7200000000);
        $deadline = $now->add($delta);
        $back_to_now = $deadline->subtract($delta);
        $this->assertSame(0, Grpc\Timeval::compare($back_to_now, $now));
    }

    public function testSimilar()
    {
        $a = Grpc\Timeval::now();
        $delta = new Grpc\Timeval(1000);
        $b = $a->add($delta);
        $thresh = new Grpc\Timeval(1100);
        $this->assertTrue(Grpc\Timeval::similar($a, $b, $thresh));
        $thresh = new Grpc\Timeval(900);
        $this->assertFalse(Grpc\Timeval::similar($a, $b, $thresh));
    }

    public function testSleepUntil()
    {
        $curr_microtime = microtime(true);
        $now = Grpc\Timeval::now();
        $delta = new Grpc\Timeval(1000);
        $deadline = $now->add($delta);
        $deadline->sleepUntil();
        $done_microtime = microtime(true);
        $this->assertTrue(($done_microtime - $curr_microtime) > 0.0009);
    }

    public function testConstructorInvalidParam()
    {
        $this->expectException(\InvalidArgumentException::class);
        $delta = new Grpc\Timeval('abc');
    }

    public function testAddInvalidParam()
    {
        $this->expectException(\InvalidArgumentException::class);
        $a = Grpc\Timeval::now();
        $a->add(1000);
    }

    public function testSubtractInvalidParam()
    {
        $this->expectException(\InvalidArgumentException::class);
        $a = Grpc\Timeval::now();
        $a->subtract(1000);
    }

    public function testCompareInvalidParam()
    {
        $this->expectException(\InvalidArgumentException::class);
        $a = Grpc\Timeval::compare(1000, 1100);
    }

    public function testSimilarInvalidParam()
    {
        $this->expectException(\InvalidArgumentException::class);
        $a = Grpc\Timeval::similar(1000, 1100, 1200);
        $this->assertNull($delta);
    }
}
