Here's the commented version of the code:

```python
# Copyright 2017 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import random
import threading
import time
import unittest

import grpc_testing

# Constants defining time quantum for tests and number of iterations for stress tests
_QUANTUM = 0.3  # Time quantum (in seconds) used throughout tests
_MANY = 10000    # Number of iterations for stress testing

# Error message for when thread scheduling behaves unexpectedly
_PATHOLOGICAL_SCHEDULING = "pathological thread scheduling!"

class _TimeNoter(object):
    """Helper class to record timestamps of callback invocations."""
    def __init__(self, time):
        """Initialize with a time module and setup synchronization primitives."""
        self._condition = threading.Condition()  # For thread-safe access to call times
        self._time = time                       # Reference to time module (real or fake)
        self._call_times = []                   # Stores timestamps of callback invocations

    def __call__(self):
        """Callback method that records the current time when invoked."""
        with self._condition:
            self._call_times.append(self._time.time())

    def call_times(self):
        """Returns a thread-safe copy of recorded call times."""
        with self._condition:
            return tuple(self._call_times)

class TimeTest(object):
    """Base class containing time-related test cases."""
    def test_sleep_for(self):
        """Tests that sleep_for() sleeps for at least the specified duration."""
        start_time = self._time.time()
        self._time.sleep_for(_QUANTUM)
        end_time = self._time.time()

        self.assertLessEqual(start_time + _QUANTUM, end_time)

    def test_sleep_until(self):
        """Tests that sleep_until() sleeps until the specified time."""
        start_time = self._time.time()
        self._time.sleep_until(start_time + _QUANTUM)
        end_time = self._time.time()

        self.assertLessEqual(start_time + _QUANTUM, end_time)

    def test_call_in(self):
        """Tests that call_in() schedules a callback after the specified delay."""
        time_noter = _TimeNoter(self._time)

        start_time = self._time.time()
        self._time.call_in(time_noter, _QUANTUM)  # Schedule callback
        self._time.sleep_for(_QUANTUM * 2)        # Wait for callback to execute
        call_times = time_noter.call_times()

        self.assertTrue(call_times, msg=_PATHOLOGICAL_SCHEDULING)
        self.assertLessEqual(start_time + _QUANTUM, call_times[0])

    def test_call_at(self):
        """Tests that call_at() schedules a callback at the specified time."""
        time_noter = _TimeNoter(self._time)

        start_time = self._time.time()
        self._time.call_at(time_noter, self._time.time() + _QUANTUM)
        self._time.sleep_for(_QUANTUM * 2)
        call_times = time_noter.call_times()

        self.assertTrue(call_times, msg=_PATHOLOGICAL_SCHEDULING)
        self.assertLessEqual(start_time + _QUANTUM, call_times[0])

    def test_cancel(self):
        """Tests that scheduled callbacks can be successfully canceled."""
        time_noter = _TimeNoter(self._time)

        future = self._time.call_in(time_noter, _QUANTUM * 2)  # Schedule callback
        self._time.sleep_for(_QUANTUM)                         # Wait before canceling
        cancelled = future.cancel()                            # Attempt to cancel
        self._time.sleep_for(_QUANTUM * 2)                    # Wait to ensure no execution
        call_times = time_noter.call_times()

        self.assertFalse(call_times, msg=_PATHOLOGICAL_SCHEDULING)
        self.assertTrue(cancelled)
        self.assertTrue(future.cancelled())

    def test_many(self):
        """Stress test with many scheduled callbacks, some of which are canceled."""
        test_events = tuple(threading.Event() for _ in range(_MANY))
        possibly_cancelled_futures = {}
        background_noise_futures = []

        # Schedule many test events with random delays
        for test_event in test_events:
            possibly_cancelled_futures[test_event] = self._time.call_in(
                test_event.set, _QUANTUM * (2 + random.random())
            )
        
        # Create additional background noise with more scheduled events
        for _ in range(_MANY):
            background_noise_futures.append(
                self._time.call_in(
                    threading.Event().set, _QUANTUM * 1000 * random.random()
                )
            )
        
        self._time.sleep_for(_QUANTUM)
        cancelled = set()
        # Randomly cancel half of the test events
        for test_event, test_future in possibly_cancelled_futures.items():
            if bool(random.randint(0, 1)) and test_future.cancel():
                cancelled.add(test_event)
        self._time.sleep_for(_QUANTUM * 3)

        # Verify canceled events didn't execute and non-canceled ones did
        for test_event in test_events:
            (self.assertFalse if test_event in cancelled else self.assertTrue)(
                test_event.is_set()
            )
        # Clean up background noise futures
        for background_noise_future in background_noise_futures:
            background_noise_future.cancel()

    def test_same_behavior_used_several_times(self):
        """Tests behavior when multiple callbacks are scheduled for same times."""
        time_noter = _TimeNoter(self._time)

        start_time = self._time.time()
        # Schedule multiple callbacks at two different times
        first_future_at_one = self._time.call_in(time_noter, _QUANTUM)
        second_future_at_one = self._time.call_in(time_noter, _QUANTUM)
        first_future_at_three = self._time.call_in(time_noter, _QUANTUM * 3)
        second_future_at_three = self._time.call_in(time_noter, _QUANTUM * 3)
        
        self._time.sleep_for(_QUANTUM * 2)
        # Attempt to cancel callbacks at various stages
        first_future_at_one_cancelled = first_future_at_one.cancel()
        second_future_at_one_cancelled = second_future_at_one.cancel()
        first_future_at_three_cancelled = first_future_at_three.cancel()
        
        self._time.sleep_for(_QUANTUM * 2)
        second_future_at_three_cancelled = second_future_at_three.cancel()
        first_future_at_three_cancelled_again = first_future_at_three.cancel()
        call_times = time_noter.call_times()

        # Verify expected number of callbacks executed
        self.assertEqual(3, len(call_times), msg=_PATHOLOGICAL_SCHEDULING)
        # Verify cancellation results
        self.assertFalse(first_future_at_one_cancelled)
        self.assertFalse(second_future_at_one_cancelled)
        self.assertTrue(first_future_at_three_cancelled)
        self.assertFalse(second_future_at_three_cancelled)
        self.assertTrue(first_future_at_three_cancelled_again)
        # Verify callback timing
        self.assertLessEqual(start_time + _QUANTUM, call_times[0])
        self.assertLessEqual(start_time + _QUANTUM, call_times[1])
        self.assertLessEqual(start_time + _QUANTUM * 3, call_times[2])

# Test implementations using different time sources
class StrictRealTimeTest(TimeTest, unittest.TestCase):
    """Test implementation using real system time."""
    def setUp(self):
        self._time = grpc_testing.strict_real_time()

class StrictFakeTimeTest(TimeTest, unittest.TestCase):
    """Test implementation using fake time with random initialization."""
    def setUp(self):
        self._time = grpc_testing.strict_fake_time(
            random.randint(0, int(time.time()))
        )

if __name__ == "__main__":
    unittest.main(verbosity=2)
```