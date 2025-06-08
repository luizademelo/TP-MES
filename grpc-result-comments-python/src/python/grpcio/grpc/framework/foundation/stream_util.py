Here's the commented version of the code:

```python
# Copyright 2015 gRPC authors.
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
"""Helpful utilities related to the stream module."""

import logging
import threading

from grpc.framework.foundation import stream

# Sentinel object used to represent no value
_NO_VALUE = object()
# Module-level logger
_LOGGER = logging.getLogger(__name__)

class TransformingConsumer(stream.Consumer):
    """A stream.Consumer that passes a transformation of its input to another."""

    def __init__(self, transformation, downstream):
        """Initialize the consumer with a transformation function and downstream consumer.
        
        Args:
            transformation: A function to transform consumed values
            downstream: The consumer to pass transformed values to
        """
        self._transformation = transformation
        self._downstream = downstream

    def consume(self, value):
        """Transform the value and pass it to the downstream consumer."""
        self._downstream.consume(self._transformation(value))

    def terminate(self):
        """Terminate the downstream consumer."""
        self._downstream.terminate()

    def consume_and_terminate(self, value):
        """Transform the value, pass it downstream, then terminate."""
        self._downstream.consume_and_terminate(self._transformation(value))

class IterableConsumer(stream.Consumer):
    """A Consumer that when iterated over emits the values it has consumed."""

    def __init__(self):
        """Initialize the consumer with thread synchronization primitives."""
        self._condition = threading.Condition()  # Synchronization lock
        self._values = []  # Buffer for consumed values
        self._active = True  # Flag indicating if consumer is active

    def consume(self, value):
        """Add a value to the buffer if consumer is active and notify waiters."""
        with self._condition:
            if self._active:
                self._values.append(value)
                self._condition.notify()

    def terminate(self):
        """Mark consumer as inactive and notify waiters."""
        with self._condition:
            self._active = False
            self._condition.notify()

    def consume_and_terminate(self, value):
        """Add a value, mark as inactive, and notify waiters."""
        with self._condition:
            if self._active:
                self._values.append(value)
                self._active = False
                self._condition.notify()

    def __iter__(self):
        """Return self as the iterator."""
        return self

    def __next__(self):
        """Python 3 iterator protocol method."""
        return self.next()

    def next(self):
        """Python 2 iterator protocol method.
        
        Blocks until a value is available or consumer is terminated.
        Raises StopIteration when no more values will be produced.
        """
        with self._condition:
            # Wait while active but no values available
            while self._active and not self._values:
                self._condition.wait()
            
            # Return value if available
            if self._values:
                return self._values.pop(0)
            else:
                raise StopIteration()

class ThreadSwitchingConsumer(stream.Consumer):
    """A Consumer decorator that affords serialization and asynchrony."""

    def __init__(self, sink, pool):
        """Initialize with a sink consumer and thread pool.
        
        Args:
            sink: The target consumer to forward values to
            pool: Thread pool for executing the forwarding
        """
        self._lock = threading.Lock()  # Protects internal state
        self._sink = sink  # Target consumer
        self._pool = pool  # Thread pool for async operations

        self._spinning = False  # Flag indicating active forwarding
        self._values = []  # Buffer for values waiting to be forwarded
        self._active = True  # Flag indicating if consumer is active

    def _spin(self, sink, value, terminate):
        """Continuously forward values to the sink until complete.
        
        Args:
            sink: Target consumer
            value: Initial value to forward
            terminate: Whether this is a termination operation
        """
        while True:
            try:
                if value is _NO_VALUE:
                    sink.terminate()
                elif terminate:
                    sink.consume_and_terminate(value)
                else:
                    sink.consume(value)
            except Exception as e:
                _LOGGER.exception(e)

            with self._lock:
                if terminate:
                    # Clean up after termination
                    self._spinning = False
                    return
                elif self._values:
                    # Get next value from buffer
                    value = self._values.pop(0)
                    terminate = not self._values and not self._active
                elif not self._active:
                    # No more values and inactive - terminate
                    value = _NO_VALUE
                    terminate = True
                else:
                    # No more work to do
                    self._spinning = False
                    return

    def consume(self, value):
        """Forward a value to the sink via the thread pool."""
        with self._lock:
            if self._active:
                if self._spinning:
                    # If already processing, buffer the value
                    self._values.append(value)
                else:
                    # Start processing with thread pool
                    self._pool.submit(self._spin, self._sink, value, False)
                    self._spinning = True

    def terminate(self):
        """Terminate the forwarding operation."""
        with self._lock:
            if self._active:
                self._active = False
                if not self._spinning:
                    # Start termination if not already processing
                    self._pool.submit(self._spin, self._sink, _NO_VALUE, True)
                    self._spinning = True

    def consume_and_terminate(self, value):
        """Forward a value and then terminate."""
        with self._lock:
            if self._active:
                self._active = False
                if self._spinning:
                    # If processing, buffer the value (termination will happen later)
                    self._values.append(value)
                else:
                    # Start processing with termination
                    self._pool.submit(self._spin, self._sink, value, True)
                    self._spinning = True
```