Here's the commented version of the code:

```python
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

import helloworld_pb2 as helloworld__pb2

class GreeterStub(object):
    """Client-side stub for the Greeter service.
    
    Provides methods to call the RPC methods defined in the Greeter service.
    """
    def __init__(self, channel):
        """Initializes the GreeterStub with a gRPC channel.
        
        Args:
            channel: A grpc.Channel used to make RPC calls.
        """
        # Sets up a unary-unary RPC call for the SayHello method
        self.SayHello = channel.unary_unary(
                '/helloworld.Greeter/SayHello',  # Service method path
                request_serializer=helloworld__pb2.HelloRequest.SerializeToString,  # Request serializer
                response_deserializer=helloworld__pb2.HelloReply.FromString,  # Response deserializer
                )

class GreeterServicer(object):
    """Server-side implementation of the Greeter service.
    
    Defines the interface that must be implemented by the actual service.
    """
    def SayHello(self, request, context):
        """Implementation of the SayHello RPC method.
        
        Args:
            request: The HelloRequest message from the client.
            context: gRPC context for the RPC call.
            
        Raises:
            NotImplementedError: Indicates the method is not implemented.
        """
        # Sets the RPC status to UNIMPLEMENTED by default
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_GreeterServicer_to_server(servicer, server):
    """Registers the Greeter service implementation with the gRPC server.
    
    Args:
        servicer: An instance of GreeterServicer implementing the service methods.
        server: The gRPC server to which the service will be added.
    """
    # Defines the RPC method handlers for the service
    rpc_method_handlers = {
            'SayHello': grpc.unary_unary_rpc_method_handler(
                    servicer.SayHello,  # Service implementation
                    request_deserializer=helloworld__pb2.HelloRequest.FromString,  # Request deserializer
                    response_serializer=helloworld__pb2.HelloReply.SerializeToString,  # Response serializer
            ),
    }
    # Creates a generic handler for the service
    generic_handler = grpc.method_handlers_generic_handler(
            'helloworld.Greeter', rpc_method_handlers)
    # Adds the service handler to the server
    server.add_generic_rpc_handlers((generic_handler,))

class Greeter(object):
    """Convenience class providing static methods for client-side Greeter service calls."""

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
        """Makes a unary RPC call to the SayHello method.
        
        Args:
            request: The HelloRequest message to send.
            target: The server address.
            options: Optional gRPC channel options.
            channel_credentials: Optional channel credentials.
            call_credentials: Optional call credentials.
            insecure: If True, uses insecure channel.
            compression: Optional compression method.
            wait_for_ready: If True, waits for server to be ready.
            timeout: Optional timeout in seconds.
            metadata: Optional metadata to send with the call.
            
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