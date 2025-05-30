#!/usr/bin/env ruby

# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'thread'

class Histogram

  def bucket_for(value)
    (Math.log(value)/Math.log(@multiplier)).to_i
  end

  def initialize(resolution, max_possible)
    @lock = Mutex.new
    @resolution=resolution
    @max_possible=max_possible
    @sum=0
    @sum_of_squares=0
    @multiplier=1+resolution
    @count=0
    @min_seen=max_possible
    @max_seen=0
    @buckets=Array.new(bucket_for(max_possible)+1, 0)
  end

  def add(value)
    @sum += value
    @sum_of_squares += value * value
    @count += 1
    if value < @min_seen
      @min_seen = value
    end
    if value > @max_seen
      @max_seen = value
    end
    @buckets[bucket_for(value)] += 1
  end
  def minimum
    @min_seen
  end
  def maximum
    @max_seen
  end
  def sum
    @sum
  end
  def sum_of_squares
    @sum_of_squares
  end
  def count
    @count
  end
  def contents
    @buckets
  end

  def merge(hist)
    @lock.synchronize do
      @min_seen = hist.min_seen
      @max_seen = hist.max_seen
      @sum += hist.sum
      @sum_of_squares += hist.sum_of_squares
      @count += hist.count
      received_bucket = hist.bucket.to_a
      @buckets = @buckets.map.with_index{ |m,i| m + received_bucket[i].to_i }
    end
  end
end
