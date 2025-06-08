Here's the commented version of the code:

```python
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

# Import generated protobuf messages for the helloworld service
import helloworld_pb2 as helloworld__pb2

class GreeterStub(object):
    """Client-side stub for the Greeter service.
    
    Provides methods to call the RPC methods exposed by the Greeter server.
    """

    def __init__(self, channel):
        """Constructor.

        Initializes the RPC method stubs for the Greeter service.

        Args:
            channel: A grpc.Channel used for communication with the gRPC server.
        """
        # Create a unary-unary RPC method stub for SayHello
        self.SayHello = channel.unary_unary(
                '/helloworld.Greeter/SayHello',  # Service method path
                request_serializer=helloworld__pb2.HelloRequest.SerializeToString,  # Request serializer
                response_deserializer=helloworld__pb2.HelloReply.FromString,  # Response deserializer
                )

class GreeterServicer(object):
    """Server-side implementation of the Greeter service.
    
    This provides the interface that actual server implementations should inherit from.
    """

    def SayHello(self, request, context):
        """Implementation of the SayHello RPC method.
        
        Args:
            request: The HelloRequest message from the client.
            context: gRPC context for RPC invocation.
            
        Raises:
            NotImplementedError: This is a base class that must be implemented by subclasses.
        """
        # Indicate that this method is not implemented in this base class
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_GreeterServicer_to_server(servicer, server):
    """Registers a GreeterServicer implementation with a gRPC server.
    
    Args:
        servicer: An implementation of GreeterServicer.
        server: The gRPC server to which the servicer will be added.
    """
    # Define the RPC method handlers for the service
    rpc_method_handlers = {
            'SayHello': grpc.unary_unary_rpc_method_handler(
                    servicer.SayHello,  # Method implementation
                    request_deserializer=helloworld__pb2.HelloRequest.FromString,  # Request deserializer
                    response_serializer=helloworld__pb2.HelloReply.SerializeToString,  # Response serializer
            ),
    }
    # Create a generic handler for the Greeter service
    generic_handler = grpc.method_handlers_generic_handler(
            'helloworld.Greeter', rpc_method_handlers)
    # Register the handler with the server
    server.add_generic_rpc_handlers((generic_handler,))

class Greeter(object):
    """Convenience class providing static methods for client-side Greeter service access.
    
    This provides a higher-level interface for calling Greeter service methods.
    """

    @staticmethod
    def SayHello(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Static method to call the SayHello RPC.
        
        Args:
            request: The HelloRequest message to send.
            target: The server address.
            options: Optional gRPC channel options.
            channel_credentials: Credentials for the channel.
            call_credentials: Credentials for the call.
            insecure: If True, use an insecure channel.
            compression: Compression algorithm to use.
            wait_for_ready: If True, waits for server to be ready.
            timeout: Optional timeout for the RPC.
            metadata: Optional metadata to send with the RPC.
            
        Returns:
            The HelloReply message from the server.
        """
        return grpc.experimental.unary_unary(
            request, 
            target, 
            '/helloworld.Greeter/SayHello',  # Service method path
            helloworld__pb2.HelloRequest.SerializeToString,  # Request serializer
            helloworld__pb2.HelloReply.FromString,  # Response deserializer
            options, 
            channel_credentials,
            insecure, 
            call_credentials, 
            compression, 
            wait_for_ready, 
            timeout, 
            metadata)
```