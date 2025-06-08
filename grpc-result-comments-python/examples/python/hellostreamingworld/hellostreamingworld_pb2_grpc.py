Here's the commented version of the code:

```python
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

import hellostreamingworld_pb2 as hellostreamingworld__pb2

class MultiGreeterStub(object):
    """Client-side stub for the MultiGreeter service.
    
    Provides methods to call the RPC methods exposed by the server.
    """

    def __init__(self, channel):
        """Constructor.

        Initializes the client stub with the provided gRPC channel and sets up
        the RPC method handlers.

        Args:
            channel: A grpc.Channel object used for communication with the server.
        """
        self.sayHello = channel.unary_stream(
                '/hellostreamingworld.MultiGreeter/sayHello',
                request_serializer=hellostreamingworld__pb2.HelloRequest.SerializeToString,
                response_deserializer=hellostreamingworld__pb2.HelloReply.FromString,
                )

class MultiGreeterServicer(object):
    """Server-side implementation of the MultiGreeter service.

    This class defines the actual server implementation that clients can call.
    """

    def sayHello(self, request, context):
        """Implementation of the sayHello RPC method.

        This method should be overridden to provide actual functionality.
        Currently raises NotImplementedError to indicate it needs implementation.

        Args:
            request: The HelloRequest message from the client.
            context: gRPC context object providing RPC-specific information.

        Raises:
            NotImplementedError: Indicates the method is not implemented.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_MultiGreeterServicer_to_server(servicer, server):
    """Registers the MultiGreeter service implementation with the gRPC server.

    Args:
        servicer: An instance of MultiGreeterServicer implementing the service methods.
        server: The gRPC server to which the service will be added.
    """
    rpc_method_handlers = {
            'sayHello': grpc.unary_stream_rpc_method_handler(
                    servicer.sayHello,
                    request_deserializer=hellostreamingworld__pb2.HelloRequest.FromString,
                    response_serializer=hellostreamingworld__pb2.HelloReply.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'hellostreamingworld.MultiGreeter', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class MultiGreeter(object):
    """Static methods for client-side convenience when calling the MultiGreeter service.

    Provides a simplified interface for making RPC calls without needing to create a stub.
    """

    @staticmethod
    def sayHello(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Makes a unary-stream RPC call to the sayHello method.

        Args:
            request: The HelloRequest message to send to the server.
            target: The server address.
            options: Optional gRPC channel options.
            channel_credentials: Credentials for the channel.
            call_credentials: Credentials for the call.
            insecure: If True, uses insecure channel credentials.
            compression: Compression algorithm to use.
            wait_for_ready: If True, waits for server to be ready.
            timeout: Optional timeout for the call.
            metadata: Optional metadata to send with the call.

        Returns:
            A stream of HelloReply messages from the server.
        """
        return grpc.experimental.unary_stream(request, target, '/hellostreamingworld.MultiGreeter/sayHello',
            hellostreamingworld__pb2.HelloRequest.SerializeToString,
            hellostreamingworld__pb2.HelloReply.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)
```