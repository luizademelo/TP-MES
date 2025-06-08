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

import logging
import threading

import grpc
from grpc_testing import _common

# Set up basic logging configuration
logging.basicConfig()
# Create logger for this module
_LOGGER = logging.getLogger(__name__)

class Rpc(object):
    """Class representing an RPC (Remote Procedure Call) with state management and callback handling."""

    def __init__(self, handler, invocation_metadata):
        """Initialize RPC with handler and invocation metadata.
        
        Args:
            handler: The RPC handler for sending responses/metadata
            invocation_metadata: Metadata received from the client invocation
        """
        self._condition = threading.Condition()  # Thread synchronization primitive
        self._handler = handler  # Handler for RPC operations
        self._invocation_metadata = invocation_metadata  # Client call metadata
        self._initial_metadata_sent = False  # Track if initial metadata was sent
        self._pending_trailing_metadata = None  # Pending trailing metadata to send
        self._pending_code = None  # Pending status code to send
        self._pending_details = None  # Pending status details to send
        self._callbacks = []  # List of callbacks to invoke on completion
        self._active = True  # Whether RPC is still active
        self._rpc_errors = []  # List of RPC errors encountered

    def _ensure_initial_metadata_sent(self):
        """Ensure initial metadata is sent if not already sent."""
        if not self._initial_metadata_sent:
            self._handler.send_initial_metadata(_common.FUSSED_EMPTY_METADATA)
            self._initial_metadata_sent = True

    def _call_back(self):
        """Execute all registered callbacks in a separate thread."""
        callbacks = tuple(self._callbacks)
        self._callbacks = None  # Clear callbacks to prevent duplicate execution

        def call_back():
            """Inner function to execute callbacks and handle exceptions."""
            for callback in callbacks:
                try:
                    callback()
                except Exception:
                    _LOGGER.exception("Exception calling server-side callback!")

        # Execute callbacks in a separate thread
        callback_calling_thread = threading.Thread(target=call_back)
        callback_calling_thread.start()

    def _terminate(self, trailing_metadata, code, details):
        """Terminate the RPC with given metadata, status code, and details.
        
        Args:
            trailing_metadata: Metadata to send with termination
            code: Status code for termination
            details: Status details for termination
        """
        if self._active:
            self._active = False
            self._handler.send_termination(trailing_metadata, code, details)
            self._call_back()  # Execute any pending callbacks
            self._condition.notify_all()  # Notify all waiting threads

    def _complete(self):
        """Complete the RPC using pending termination values or defaults."""
        trailing_metadata = (
            _common.FUSSED_EMPTY_METADATA
            if self._pending_trailing_metadata is None
            else self._pending_trailing_metadata
        )
        code = grpc.StatusCode.OK if self._pending_code is None else self._pending_code
        details = "" if self._pending_details is None else self._pending_details
        self._terminate(trailing_metadata, code, details)

    def _abort(self, code, details):
        """Abort the RPC with given status code and details.
        
        Args:
            code: Status code for abort
            details: Status details for abort
        """
        self._terminate(_common.FUSSED_EMPTY_METADATA, code, details)

    def add_rpc_error(self, rpc_error):
        """Add an RPC error to the error list.
        
        Args:
            rpc_error: Error to add to the list
        """
        with self._condition:
            self._rpc_errors.append(rpc_error)

    def application_cancel(self):
        """Cancel the RPC from the application side."""
        with self._condition:
            self._abort(
                grpc.StatusCode.CANCELLED,
                "Cancelled by server-side application!",
            )

    def application_exception_abort(self, exception):
        """Abort RPC due to application exception if not already recorded.
        
        Args:
            exception: Exception that caused the abort
        """
        with self._condition:
            if exception not in self._rpc_errors:
                _LOGGER.exception("Exception calling application!")
                self._abort(
                    grpc.StatusCode.UNKNOWN,
                    "Exception calling application: {}".format(exception),
                )

    def extrinsic_abort(self):
        """Abort RPC from external source (not application)."""
        with self._condition:
            if self._active:
                self._active = False
                self._call_back()  # Execute any pending callbacks
                self._condition.notify_all()  # Notify all waiting threads

    def unary_response_complete(self, response):
        """Complete a unary RPC with the given response.
        
        Args:
            response: The response to send
        """
        with self._condition:
            self._ensure_initial_metadata_sent()
            self._handler.add_response(response)
            self._complete()

    def stream_response(self, response):
        """Send a stream response.
        
        Args:
            response: The response to stream
        """
        with self._condition:
            self._ensure_initial_metadata_sent()
            self._handler.add_response(response)

    def stream_response_complete(self):
        """Complete a streaming RPC."""
        with self._condition:
            self._ensure_initial_metadata_sent()
            self._complete()

    def send_initial_metadata(self, initial_metadata):
        """Send initial metadata if not already sent.
        
        Args:
            initial_metadata: Metadata to send
        Returns:
            bool: True if metadata was sent, False if already sent
        """
        with self._condition:
            if self._initial_metadata_sent:
                return False
            else:
                self._handler.send_initial_metadata(initial_metadata)
                self._initial_metadata_sent = True
                return True

    def is_active(self):
        """Check if RPC is still active.
        
        Returns:
            bool: True if RPC is active, False otherwise
        """
        with self._condition:
            return self._active

    def add_callback(self, callback):
        """Add a callback to be executed on RPC completion.
        
        Args:
            callback: Callback function to add
        Returns:
            bool: True if callback was added, False if RPC already completed
        """
        with self._condition:
            if self._callbacks is None:
                return False
            else:
                self._callbacks.append(callback)
                return True

    def invocation_metadata(self):
        """Get the invocation metadata from the client.
        
        Returns:
            The invocation metadata
        """
        with self._condition:
            return self._invocation_metadata

    def set_trailing_metadata(self, trailing_metadata):
        """Set trailing metadata to be sent on completion.
        
        Args:
            trailing_metadata: Metadata to send
        """
        with self._condition:
            self._pending_trailing_metadata = trailing_metadata

    def set_code(self, code):
        """Set status code to be sent on completion.
        
        Args:
            code: Status code to send
        """
        with self._condition:
            self._pending_code = code

    def set_details(self, details):
        """Set status details to be sent on completion.
        
        Args:
            details: Status details to send
        """
        with self._condition:
            self._pending_details = details
```