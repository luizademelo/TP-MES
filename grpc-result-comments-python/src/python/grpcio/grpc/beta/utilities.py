Here's the commented version of the code:

```python
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Utilities for the gRPC Python Beta API."""

import threading
import time

from grpc.beta import implementations
from grpc.beta import interfaces
from grpc.framework.foundation import callable_util
from grpc.framework.foundation import future

# Error message for exceptions in done callbacks
_DONE_CALLBACK_EXCEPTION_LOG_MESSAGE = (
    'Exception calling connectivity future "done" callback!'
)

class _ChannelReadyFuture(future.Future):
    """A Future that tracks when a gRPC channel becomes ready.
    
    This future matures when the channel connectivity state changes to READY.
    It provides standard Future interface methods and manages callbacks.
    """
    
    def __init__(self, channel):
        """Initialize the future with a channel to monitor.
        
        Args:
            channel: The gRPC channel whose connectivity state will be monitored.
        """
        self._condition = threading.Condition()  # Synchronization primitive
        self._channel = channel  # The channel being monitored

        # State flags
        self._matured = False    # True when channel is READY
        self._cancelled = False  # True if future was cancelled
        self._done_callbacks = []  # Callbacks to execute when future completes

    def _block(self, timeout):
        """Block until the future completes or times out.
        
        Args:
            timeout: Maximum time to wait in seconds (None for infinite wait).
            
        Raises:
            CancelledError: If the future was cancelled.
            TimeoutError: If the timeout expires before completion.
        """
        until = None if timeout is None else time.time() + timeout
        with self._condition:
            while True:
                if self._cancelled:
                    raise future.CancelledError()
                elif self._matured:
                    return
                else:
                    if until is None:
                        self._condition.wait()
                    else:
                        remaining = until - time.time()
                        if remaining < 0:
                            raise future.TimeoutError()
                        else:
                            self._condition.wait(timeout=remaining)

    def _update(self, connectivity):
        """Callback for channel connectivity state changes.
        
        Args:
            connectivity: The new connectivity state of the channel.
        """
        with self._condition:
            if (
                not self._cancelled
                and connectivity is interfaces.ChannelConnectivity.READY
            ):
                # Channel is ready - mark future as complete
                self._matured = True
                self._channel.unsubscribe(self._update)
                self._condition.notify_all()
                done_callbacks = tuple(self._done_callbacks)
                self._done_callbacks = None
            else:
                return

        # Execute callbacks outside the lock to prevent deadlocks
        for done_callback in done_callbacks:
            callable_util.call_logging_exceptions(
                done_callback, _DONE_CALLBACK_EXCEPTION_LOG_MESSAGE, self
            )

    def cancel(self):
        """Attempt to cancel the future.
        
        Returns:
            bool: True if the future was cancelled, False if it was already complete.
        """
        with self._condition:
            if not self._matured:
                self._cancelled = True
                self._channel.unsubscribe(self._update)
                self._condition.notify_all()
                done_callbacks = tuple(self._done_callbacks)
                self._done_callbacks = None
            else:
                return False

        # Execute callbacks outside the lock
        for done_callback in done_callbacks:
            callable_util.call_logging_exceptions(
                done_callback, _DONE_CALLBACK_EXCEPTION_LOG_MESSAGE, self
            )

        return True

    def cancelled(self):
        """Check if the future was cancelled.
        
        Returns:
            bool: True if the future was cancelled.
        """
        with self._condition:
            return self._cancelled

    def running(self):
        """Check if the future is still running (not cancelled or completed).
        
        Returns:
            bool: True if the future is still running.
        """
        with self._condition:
            return not self._cancelled and not self._matured

    def done(self):
        """Check if the future is done (either completed or cancelled).
        
        Returns:
            bool: True if the future is done.
        """
        with self._condition:
            return self._cancelled or self._matured

    def result(self, timeout=None):
        """Get the result of the future (always None in this implementation).
        
        Args:
            timeout: Maximum time to wait for completion.
            
        Returns:
            None: This future doesn't return a meaningful result.
        """
        self._block(timeout)
        return None

    def exception(self, timeout=None):
        """Get the exception (always None in this implementation).
        
        Args:
            timeout: Maximum time to wait for completion.
            
        Returns:
            None: This future doesn't raise exceptions.
        """
        self._block(timeout)
        return None

    def traceback(self, timeout=None):
        """Get the traceback (always None in this implementation).
        
        Args:
            timeout: Maximum time to wait for completion.
            
        Returns:
            None: This future doesn't raise exceptions.
        """
        self._block(timeout)
        return None

    def add_done_callback(self, fn):
        """Add a callback to be executed when the future completes.
        
        Args:
            fn: The callback function to add.
        """
        with self._condition:
            if not self._cancelled and not self._matured:
                self._done_callbacks.append(fn)
                return

        # If already complete, execute immediately
        fn(self)

    def start(self):
        """Start monitoring the channel's connectivity state."""
        with self._condition:
            self._channel.subscribe(self._update, try_to_connect=True)

    def __del__(self):
        """Destructor that cleans up the channel subscription."""
        with self._condition:
            if not self._cancelled and not self._matured:
                self._channel.unsubscribe(self._update)

def channel_ready_future(channel):
    """Creates a future.Future tracking when an implementations.Channel is ready.

    Cancelling the returned future.Future does not tell the given
    implementations.Channel to abandon attempts it may have been making to
    connect; cancelling merely deactivates the return future.Future's
    subscription to the given implementations.Channel's connectivity.

    Args:
      channel: An implementations.Channel.

    Returns:
      A future.Future that matures when the given Channel has connectivity
        interfaces.ChannelConnectivity.READY.
    """
    ready_future = _ChannelReadyFuture(channel)
    ready_future.start()
    return ready_future
```