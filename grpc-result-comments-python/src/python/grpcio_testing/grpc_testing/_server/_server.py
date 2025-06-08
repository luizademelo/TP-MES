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

import threading

import grpc_testing
from grpc_testing import _common
from grpc_testing._server import _handler
from grpc_testing._server import _rpc
from grpc_testing._server import _server_rpc
from grpc_testing._server import _service
from grpc_testing._server import _servicer_context

def _implementation(descriptors_to_servicers, method_descriptor):
    """Get the implementation of a gRPC method from the servicer.
    
    Args:
        descriptors_to_servicers: Mapping from service descriptors to servicer instances.
        method_descriptor: Descriptor of the method to be implemented.
    
    Returns:
        The method implementation from the servicer.
    """
    servicer = descriptors_to_servicers[method_descriptor.containing_service]
    return getattr(servicer, method_descriptor.name)

def _unary_unary_service(request):
    """Create a service function for unary-unary RPCs.
    
    Args:
        request: The request message for the RPC.
    
    Returns:
        A service function that handles unary-unary RPCs.
    """
    def service(implementation, rpc, servicer_context):
        _service.unary_unary(implementation, rpc, request, servicer_context)

    return service

def _unary_stream_service(request):
    """Create a service function for unary-stream RPCs.
    
    Args:
        request: The request message for the RPC.
    
    Returns:
        A service function that handles unary-stream RPCs.
    """
    def service(implementation, rpc, servicer_context):
        _service.unary_stream(implementation, rpc, request, servicer_context)

    return service

def _stream_unary_service(handler):
    """Create a service function for stream-unary RPCs.
    
    Args:
        handler: The handler for the RPC stream.
    
    Returns:
        A service function that handles stream-unary RPCs.
    """
    def service(implementation, rpc, servicer_context):
        _service.stream_unary(implementation, rpc, handler, servicer_context)

    return service

def _stream_stream_service(handler):
    """Create a service function for stream-stream RPCs.
    
    Args:
        handler: The handler for the RPC stream.
    
    Returns:
        A service function that handles stream-stream RPCs.
    """
    def service(implementation, rpc, servicer_context):
        _service.stream_stream(implementation, rpc, handler, servicer_context)

    return service

class _Serverish(_common.Serverish):
    """Internal implementation of Serverish interface for testing gRPC servers."""
    
    def __init__(self, descriptors_to_servicers, time):
        """Initialize the Serverish implementation.
        
        Args:
            descriptors_to_servicers: Mapping from service descriptors to servicer instances.
            time: Time interface for controlling time in tests.
        """
        self._descriptors_to_servicers = descriptors_to_servicers
        self._time = time

    def _invoke(
        self,
        service_behavior,
        method_descriptor,
        handler,
        invocation_metadata,
        deadline,
    ):
        """Internal method to invoke an RPC with the given behavior.
        
        Args:
            service_behavior: The service function to handle the RPC.
            method_descriptor: Descriptor of the method being invoked.
            handler: The RPC handler.
            invocation_metadata: Metadata for the RPC invocation.
            deadline: Deadline for the RPC completion.
        """
        implementation = _implementation(
            self._descriptors_to_servicers, method_descriptor
        )
        rpc = _rpc.Rpc(handler, invocation_metadata)
        if handler.add_termination_callback(rpc.extrinsic_abort):
            servicer_context = _servicer_context.ServicerContext(
                rpc, self._time, deadline
            )
            service_thread = threading.Thread(
                target=service_behavior,
                args=(
                    implementation,
                    rpc,
                    servicer_context,
                ),
            )
            service_thread.start()

    def invoke_unary_unary(
        self, method_descriptor, handler, invocation_metadata, request, deadline
    ):
        """Invoke a unary-unary RPC.
        
        Args:
            method_descriptor: Descriptor of the method being invoked.
            handler: The RPC handler.
            invocation_metadata: Metadata for the RPC invocation.
            request: The request message.
            deadline: Deadline for the RPC completion.
        """
        self._invoke(
            _unary_unary_service(request),
            method_descriptor,
            handler,
            invocation_metadata,
            deadline,
        )

    def invoke_unary_stream(
        self, method_descriptor, handler, invocation_metadata, request, deadline
    ):
        """Invoke a unary-stream RPC.
        
        Args:
            method_descriptor: Descriptor of the method being invoked.
            handler: The RPC handler.
            invocation_metadata: Metadata for the RPC invocation.
            request: The request message.
            deadline: Deadline for the RPC completion.
        """
        self._invoke(
            _unary_stream_service(request),
            method_descriptor,
            handler,
            invocation_metadata,
            deadline,
        )

    def invoke_stream_unary(
        self, method_descriptor, handler, invocation_metadata, deadline
    ):
        """Invoke a stream-unary RPC.
        
        Args:
            method_descriptor: Descriptor of the method being invoked.
            handler: The RPC handler.
            invocation_metadata: Metadata for the RPC invocation.
            deadline: Deadline for the RPC completion.
        """
        self._invoke(
            _stream_unary_service(handler),
            method_descriptor,
            handler,
            invocation_metadata,
            deadline,
        )

    def invoke_stream_stream(
        self, method_descriptor, handler, invocation_metadata, deadline
    ):
        """Invoke a stream-stream RPC.
        
        Args:
            method_descriptor: Descriptor of the method being invoked.
            handler: The RPC handler.
            invocation_metadata: Metadata for the RPC invocation.
            deadline: Deadline for the RPC completion.
        """
        self._invoke(
            _stream_stream_service(handler),
            method_descriptor,
            handler,
            invocation_metadata,
            deadline,
        )

def _deadline_and_handler(requests_closed, time, timeout):
    """Create a deadline and handler based on timeout.
    
    Args:
        requests_closed: Whether the requests are closed.
        time: Time interface for controlling time in tests.
        timeout: Timeout for the RPC.
    
    Returns:
        A tuple of (deadline, handler) for the RPC.
    """
    if timeout is None:
        return None, _handler.handler_without_deadline(requests_closed)
    else:
        deadline = time.time() + timeout
        handler = _handler.handler_with_deadline(
            requests_closed, time, deadline
        )
        return deadline, handler

class _Server(grpc_testing.Server):
    """Implementation of the gRPC testing Server interface."""
    
    def __init__(self, serverish, time):
        """Initialize the testing server.
        
        Args:
            serverish: The Serverish implementation to use.
            time: Time interface for controlling time in tests.
        """
        self._serverish = serverish
        self._time = time

    def invoke_unary_unary(
        self, method_descriptor, invocation_metadata, request, timeout
    ):
        """Invoke a unary-unary RPC.
        
        Args:
            method_descriptor: Descriptor of the method being invoked.
            invocation_metadata: Metadata for the RPC invocation.
            request: The request message.
            timeout: Timeout for the RPC.
        
        Returns:
            A UnaryUnaryServerRpc instance for the RPC.
        """
        deadline, handler = _deadline_and_handler(True, self._time, timeout)
        self._serverish.invoke_unary_unary(
            method_descriptor, handler, invocation_metadata, request, deadline
        )
        return _server_rpc.UnaryUnaryServerRpc(handler)

    def invoke_unary_stream(
        self, method_descriptor, invocation_metadata, request, timeout
    ):
        """Invoke a unary-stream RPC.
        
        Args:
            method_descriptor: Descriptor of the method being invoked.
            invocation_metadata: Metadata for the RPC invocation.
            request: The request message.
            timeout: Timeout for the RPC.
        
        Returns:
            A UnaryStreamServerRpc instance for the RPC.
        """
        deadline, handler = _deadline_and_handler(True, self._time, timeout)
        self._serverish.invoke_unary_stream(
            method_descriptor, handler, invocation_metadata, request, deadline
        )
        return _server_rpc.UnaryStreamServerRpc(handler)

    def invoke_stream_unary(
        self, method_descriptor, invocation_metadata, timeout
    ):
        """Invoke a stream-unary RPC.
        
        Args:
            method_descriptor: Descriptor of the method being invoked.
            invocation_metadata: Metadata for the RPC invocation.
            timeout: Timeout for the RPC.
        
        Returns:
            A StreamUnaryServerRpc instance for the RPC.
        """
        deadline, handler = _deadline_and_handler(False, self._time, timeout)
        self._serverish.invoke_stream_unary(
            method_descriptor, handler, invocation_metadata, deadline
        )
        return _server_rpc.StreamUnaryServerRpc(handler)

    def invoke_stream_stream(
        self, method_descriptor, invocation_metadata, timeout
    ):
        """Invoke a stream-stream RPC.
        
        Args:
            method_descriptor: Descriptor of the method being invoked.
            invocation_metadata: Metadata for the RPC invocation.
            timeout: Timeout for the RPC.
        
        Returns:
            A StreamStreamServerRpc instance for the RPC.
        """
        deadline, handler = _deadline_and_handler(False, self._time, timeout)
        self._serverish.invoke_stream_stream(
            method_descriptor, handler, invocation_metadata, deadline
        )
        return _server_rpc.StreamStreamServerRpc(handler)

def server_from_descriptor_to_servicers(descriptors_to_servicers, time):
    """Create a testing server from service descriptors to servicers mapping.
    
    Args:
        descriptors_to_servicers: Mapping from service descriptors to servicer instances.
        time: Time interface for controlling time in tests.
    
    Returns:
        A configured testing server instance.
    """
    return _Server(_Serverish(descriptors_to_servicers, time), time)
```