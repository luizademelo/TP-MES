Here's the commented version of the code:

```python
# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Test times."""

import collections
import logging
import threading
import time as _time

import grpc
import grpc_testing

# Set up basic logging configuration
logging.basicConfig()
_LOGGER = logging.getLogger(__name__)

def _call(behaviors):
    """Execute all behaviors in sequence, logging any exceptions."""
    for behavior in behaviors:
        try:
            behavior()
        except Exception:
            _LOGGER.exception('Exception calling behavior "%r"!', behavior)

def _call_in_thread(behaviors):
    """Execute behaviors in a separate thread."""
    calling = threading.Thread(target=_call, args=(behaviors,))
    calling.start()
    calling.join()

class _State(object):
    """Thread-safe state container for time-based behavior scheduling."""
    def __init__(self):
        self.condition = threading.Condition()  # Synchronization primitive
        # Dictionary mapping times to lists of behaviors scheduled for that time
        self.times_to_behaviors = collections.defaultdict(list)

class _Delta(
    collections.namedtuple(
        "_Delta",
        (
            "mature_behaviors",         # Behaviors ready to execute
            "earliest_mature_time",     # Time of earliest ready behavior
            "earliest_immature_time",  # Time of next behavior not yet ready
        ),
    )
):
    """Container for results of processing scheduled behaviors."""
    pass

def _process(state, now):
    """
    Process scheduled behaviors, separating those ready to run from those not yet ready.
    
    Args:
        state: The _State instance containing scheduled behaviors
        now: Current time to compare against scheduled times
    
    Returns:
        _Delta: Container with mature behaviors and timing information
    """
    mature_behaviors = []
    earliest_mature_time = None
    while state.times_to_behaviors:
        earliest_time = min(state.times_to_behaviors)
        if earliest_time <= now:
            if earliest_mature_time is None:
                earliest_mature_time = earliest_time
            earliest_mature_behaviors = state.times_to_behaviors.pop(
                earliest_time
            )
            mature_behaviors.extend(earliest_mature_behaviors)
        else:
            earliest_immature_time = earliest_time
            break
    else:
        earliest_immature_time = None
    return _Delta(
        mature_behaviors, earliest_mature_time, earliest_immature_time
    )

class _Future(grpc.Future):
    """Future implementation for scheduled behaviors."""
    def __init__(self, state, behavior, time):
        self._state = state
        self._behavior = behavior
        self._time = time
        self._cancelled = False

    def cancel(self):
        """Attempt to cancel the scheduled behavior."""
        with self._state.condition:
            if self._cancelled:
                return True
            else:
                behaviors_at_time = self._state.times_to_behaviors.get(
                    self._time
                )
                if behaviors_at_time is None:
                    return False
                else:
                    behaviors_at_time.remove(self._behavior)
                    if not behaviors_at_time:
                        self._state.times_to_behaviors.pop(self._time)
                        self._state.condition.notify_all()
                    self._cancelled = True
                    return True

    def cancelled(self):
        """Check if the behavior was cancelled."""
        with self._state.condition:
            return self._cancelled

    # The following methods are part of the Future interface but not implemented
    def running(self):
        raise NotImplementedError()

    def done(self):
        raise NotImplementedError()

    def result(self, timeout=None):
        raise NotImplementedError()

    def exception(self, timeout=None):
        raise NotImplementedError()

    def traceback(self, timeout=None):
        raise NotImplementedError()

    def add_done_callback(self, fn):
        raise NotImplementedError()

class StrictRealTime(grpc_testing.Time):
    """Time implementation using real system time."""
    def __init__(self):
        self._state = _State()
        self._active = False  # Whether the activity thread is running
        self._calling = None  # Time of currently executing behaviors

    def _activity(self):
        """Main activity thread that processes scheduled behaviors."""
        while True:
            with self._state.condition:
                while True:
                    now = _time.time()
                    delta = _process(self._state, now)
                    self._state.condition.notify_all()
                    if delta.mature_behaviors:
                        self._calling = delta.earliest_mature_time
                        break
                    self._calling = None
                    if delta.earliest_immature_time is None:
                        self._active = False
                        return
                    else:
                        timeout = max(0, delta.earliest_immature_time - now)
                        self._state.condition.wait(timeout=timeout)
            _call(delta.mature_behaviors)

    def _ensure_called_through(self, time):
        """Wait until all behaviors scheduled before 'time' have executed."""
        with self._state.condition:
            while (
                self._state.times_to_behaviors
                and min(self._state.times_to_behaviors) < time
            ) or (self._calling is not None and self._calling < time):
                self._state.condition.wait()

    def _call_at(self, behavior, time):
        """Schedule a behavior to run at a specific time."""
        with self._state.condition:
            self._state.times_to_behaviors[time].append(behavior)
            if self._active:
                self._state.condition.notify_all()
            else:
                activity = threading.Thread(target=self._activity)
                activity.start()
                self._active = True
            return _Future(self._state, behavior, time)

    def time(self):
        """Get current time."""
        return _time.time()

    def call_in(self, behavior, delay):
        """Schedule a behavior to run after a delay."""
        return self._call_at(behavior, _time.time() + delay)

    def call_at(self, behavior, time):
        """Schedule a behavior to run at a specific time."""
        return self._call_at(behavior, time)

    def sleep_for(self, duration):
        """Sleep for specified duration and ensure behaviors execute."""
        time = _time.time() + duration
        _time.sleep(duration)
        self._ensure_called_through(time)

    def sleep_until(self, time):
        """Sleep until specified time and ensure behaviors execute."""
        _time.sleep(max(0, time - _time.time()))
        self._ensure_called_through(time)

class StrictFakeTime(grpc_testing.Time):
    """Time implementation using simulated time for testing."""
    def __init__(self, time):
        self._state = _State()
        self._time = time  # Current simulated time

    def time(self):
        """Get current simulated time."""
        return self._time

    def call_in(self, behavior, delay):
        """Schedule a behavior to run after a delay in simulated time."""
        if delay <= 0:
            _call_in_thread((behavior,))
        else:
            with self._state.condition:
                time = self._time + delay
                self._state.times_to_behaviors[time].append(behavior)
        return _Future(self._state, behavior, time)

    def call_at(self, behavior, time):
        """Schedule a behavior to run at a specific simulated time."""
        with self._state.condition:
            if time <= self._time:
                _call_in_thread((behavior,))
            else:
                self._state.times_to_behaviors[time].append(behavior)
        return _Future(self._state, behavior, time)

    def sleep_for(self, duration):
        """Advance simulated time and execute any mature behaviors."""
        if 0 < duration:
            with self._state.condition:
                self._time += duration
                delta = _process(self._state, self._time)
                _call_in_thread(delta.mature_behaviors)

    def sleep_until(self, time):
        """Advance simulated time to specified value and execute mature behaviors."""
        with self._state.condition:
            if self._time < time:
                self._time = time
                delta = _process(self._state, self._time)
                _call_in_thread(delta.mature_behaviors)
```