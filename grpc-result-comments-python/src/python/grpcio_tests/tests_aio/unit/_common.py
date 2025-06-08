Here's the commented version of the code:

```c++
# Copyright 2020 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import asyncio
from typing import AsyncIterable

import grpc
from grpc.aio._metadata import Metadata
from grpc.aio._typing import MetadataKey
from grpc.aio._typing import MetadataValue
from grpc.aio._typing import MetadatumType
from grpc.experimental import aio

from tests.unit.framework.common import test_constants

# Constant defining the ad-hoc method path for testing
ADHOC_METHOD = "/test/AdHoc"

def seen_metadata(expected: Metadata, actual: Metadata):
    """Check if all expected metadata is present in the actual metadata.
    
    Args:
        expected: The expected metadata items
        actual: The actual metadata to check against
        
    Returns:
        bool: True if all expected metadata is present, False otherwise
    """
    return not bool(set(tuple(expected)) - set(tuple(actual)))

def seen_metadatum(
    expected_key: MetadataKey, expected_value: MetadataValue, actual: Metadata
) -> bool:
    """Check if a specific metadata key-value pair exists in the actual metadata.
    
    Args:
        expected_key: The metadata key to look for
        expected_value: The expected value for the key
        actual: The metadata to check
        
    Returns:
        bool: True if the key exists and matches the expected value
    """
    obtained = actual[expected_key]
    return obtained == expected_value

async def block_until_certain_state(
    channel: aio.Channel, expected_state: grpc.ChannelConnectivity
):
    """Block until the channel reaches the expected connectivity state.
    
    Args:
        channel: The gRPC channel to monitor
        expected_state: The desired connectivity state to wait for
    """
    state = channel.get_state()
    while state != expected_state:
        await channel.wait_for_state_change(state)
        state = channel.get_state()

def inject_callbacks(call: aio.Call):
    """Inject and validate two done callbacks on a gRPC call.
    
    Args:
        call: The gRPC call to attach callbacks to
        
    Returns:
        A coroutine that validates both callbacks were executed
    """
    first_callback_ran = asyncio.Event()

    def first_callback(call):
        """First callback that verifies call completion."""
        assert call.done()
        first_callback_ran.set()

    second_callback_ran = asyncio.Event()

    def second_callback(call):
        """Second callback that verifies call completion."""
        assert call.done()
        second_callback_ran.set()

    call.add_done_callback(first_callback)
    call.add_done_callback(second_callback)

    async def validation():
        """Wait for both callbacks to complete within timeout."""
        await asyncio.wait_for(
            asyncio.gather(
                first_callback_ran.wait(), second_callback_ran.wait()
            ),
            test_constants.SHORT_TIMEOUT,
        )

    return validation()

class CountingRequestIterator:
    """Iterator wrapper that counts the number of requests processed."""
    
    def __init__(self, request_iterator):
        """Initialize with request iterator and zero count."""
        self.request_cnt = 0
        self._request_iterator = request_iterator

    async def _forward_requests(self):
        """Forward requests while counting them."""
        async for request in self._request_iterator:
            self.request_cnt += 1
            yield request

    def __aiter__(self):
        """Return the async iterator."""
        return self._forward_requests()

class CountingResponseIterator:
    """Iterator wrapper that counts the number of responses processed."""
    
    def __init__(self, response_iterator):
        """Initialize with response iterator and zero count."""
        self.response_cnt = 0
        self._response_iterator = response_iterator

    async def _forward_responses(self):
        """Forward responses while counting them."""
        async for response in self._response_iterator:
            self.response_cnt += 1
            yield response

    def __aiter__(self):
        """Return the async iterator."""
        return self._forward_responses()

class AdhocGenericHandler(grpc.GenericRpcHandler):
    """A generic handler to plugin testing server methods on the fly."""

    _handler: grpc.RpcMethodHandler

    def __init__(self):
        """Initialize with no handler set."""
        self._handler = None

    def set_adhoc_handler(self, handler: grpc.RpcMethodHandler):
        """Set the handler for the ad-hoc method.
        
        Args:
            handler: The RPC method handler to use for ad-hoc calls
        """
        self._handler = handler

    def service(self, handler_call_details):
        """Return the handler if the method matches ADHOC_METHOD.
        
        Args:
            handler_call_details: Details about the incoming call
            
        Returns:
            The registered handler if method matches, None otherwise
        """
        if handler_call_details.method == ADHOC_METHOD:
            return self._handler
        else:
            return None
```