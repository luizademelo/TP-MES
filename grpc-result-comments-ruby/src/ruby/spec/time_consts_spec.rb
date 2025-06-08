Here's the commented version of the code:

```c++
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'spec_helper'

# Module containing time-related constants for GRPC
TimeConsts = GRPC::Core::TimeConsts

# Test suite for TimeConsts module
describe TimeConsts do
  before(:each) do
    # Define expected constants that should be present in TimeConsts
    @known_consts = [:ZERO, :INFINITE_FUTURE, :INFINITE_PAST].sort
  end

  # Test that TimeConsts contains all expected constants
  it 'should have all the known types' do
    expect(TimeConsts.constants.collect.sort).to eq(@known_consts)
  end

  # Test suite for the to_time conversion method
  describe '#to_time' do
    # Test that each constant can be converted to a Time object
    it 'converts each constant to a Time' do
      m = TimeConsts
      m.constants.each do |c|
        expect(m.const_get(c).to_time).to be_a(Time)
      end
    end
  end
end

# Test suite for from_relative_time method
describe '#from_relative_time' do
  # Test that the method rejects invalid input types
  it 'cannot handle arbitrary objects' do
    expect { TimeConsts.from_relative_time(Object.new) }.to raise_error
  end

  # Test that TimeConsts constants are preserved when passed to the method
  it 'preserves TimeConsts' do
    m = TimeConsts
    m.constants.each do |c|
      const = m.const_get(c)
      expect(TimeConsts.from_relative_time(const)).to be(const)
    end
  end

  # Test that 0 is converted to TimeConsts::ZERO
  it 'converts 0 to TimeConsts::ZERO' do
    expect(TimeConsts.from_relative_time(0)).to eq(TimeConsts::ZERO)
  end

  # Test that nil is converted to TimeConsts::ZERO
  it 'converts nil to TimeConsts::ZERO' do
    expect(TimeConsts.from_relative_time(nil)).to eq(TimeConsts::ZERO)
  end

  # Test that negative values are converted to INFINITE_FUTURE
  it 'converts negative values to TimeConsts::INFINITE_FUTURE' do
    [-1, -3.2, -1e6].each do |t|
      y = TimeConsts.from_relative_time(t)
      expect(y).to eq(TimeConsts::INFINITE_FUTURE)
    end
  end

  # Test that positive values are converted to absolute time values
  it 'converts a positive value to an absolute time' do
    epsilon = 1  # Allowed margin of error in seconds
    [1, 3.2, 1e6].each do |t|
      want = Time.now + t
      abs = TimeConsts.from_relative_time(t)
      expect(abs.to_f).to be_within(epsilon).of(want.to_f)
    end
  end
end
```

The comments I've added:
1. Explained the purpose of the TimeConsts module
2. Documented the test structure and purpose of each test block
3. Clarified the intent behind each test case
4. Added notes about expected behavior and edge cases
5. Explained the epsilon value used for time comparison
6. Made it clear what each test is verifying about the code's functionality

The comments are designed to help future maintainers understand:
- What the code is supposed to do
- What each test is verifying
- The expected behavior for different input cases
- The relationships between different parts of the test suite