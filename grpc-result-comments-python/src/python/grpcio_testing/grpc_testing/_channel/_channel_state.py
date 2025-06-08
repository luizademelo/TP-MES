Here's the commented version of the code:

```c++
# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import collections
import threading

from grpc_testing import _common
from grpc_testing._channel import _rpc_state

class State(_common.ChannelHandler):
    """A thread-safe state manager for RPC (Remote Procedure Call) operations.
    
    This class maintains the state of RPC invocations and allows for safe
    access and modification across multiple threads.
    """
    def __init__(self):
        """Initialize the State with a threading condition and RPC state storage."""
        self._condition = threading.Condition()  # Synchronization primitive for thread safety
        self._rpc_states = collections.defaultdict(list)  # Stores RPC states keyed by method name

    def invoke_rpc(
        self,
        method_full_rpc_name,
        invocation_metadata,
        requests,
        requests_closed,
        timeout,
    ):
        """Invoke a new RPC and store its state.
        
        Args:
            method_full_rpc_name: Full name of the RPC method in format /Service/Method
            invocation_metadata: Metadata for the RPC invocation
            requests: Iterable of request messages
            requests_closed: Boolean indicating if request stream is closed
            timeout: Optional timeout for the RPC
            
        Returns:
            The created RPC state object
        """
        # Create a new RPC state object with the provided parameters
        rpc_state = _rpc_state.State(
            invocation_metadata, requests, requests_closed
        )
        # Thread-safe addition of the new RPC state to the storage
        with self._condition:
            self._rpc_states[method_full_rpc_name].append(rpc_state)
            self._condition.notify_all()  # Notify any waiting threads
        return rpc_state

    def take_rpc_state(self, method_descriptor):
        """Retrieve and remove the next available RPC state for the given method.
        
        This method blocks until an RPC state becomes available for the specified method.
        
        Args:
            method_descriptor: Descriptor of the method to get RPC state for
            
        Returns:
            The oldest RPC state object for the specified method
        """
        # Construct the full RPC method name from the descriptor
        method_full_rpc_name = "/{}/{}".format(
            method_descriptor.containing_service.full_name,
            method_descriptor.name,
        )
        # Thread-safe retrieval of RPC state
        with self._condition:
            while True:
                method_rpc_states = self._rpc_states[method_full_rpc_name]
                if method_rpc_states:
                    return method_rpc_states.pop(0)  # Return and remove the oldest state
                else:
                    self._condition.wait()  # Wait until a state becomes available
```