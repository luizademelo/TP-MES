Here's the commented version of the code:

```python
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

import helloworld_pb2 as helloworld__pb2

class GreeterStub(object):
    """Client-side stub for the Greeter service.
    
    Provides methods to call the RPC methods exposed by the Greeter service.
    """
    
    def __init__(self, channel):
        """Constructor.

        Initializes the RPC method handlers for the Greeter service.

        Args:
            channel: A grpc.Channel used for communication with the server.
        """
        self.SayHello = channel.unary_unary(
                '/helloworld.Greeter/SayHello',  # RPC method path
                request_serializer=helloworld__pb2.HelloRequest.SerializeToString,  # Request serializer
                response_deserializer=helloworld__pb2.HelloReply.FromString,  # Response deserializer
                )

class GreeterServicer(object):
    """Server-side implementation of the Greeter service.
    
    Contains the actual implementation of the service methods.
    """

    def SayHello(self, request, context):
        """Implementation of the SayHello RPC method.
        
        Args:
            request: The HelloRequest message from the client.
            context: RPC context for handling metadata, status, etc.
            
        Raises:
            NotImplementedError: Indicates the method is not implemented.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_GreeterServicer_to_server(servicer, server):
    """Registers the Greeter service implementation with the gRPC server.
    
    Args:
        servicer: An instance of GreeterServicer containing the service implementation.
        server: The gRPC server to which the service will be added.
    """
    rpc_method_handlers = {
            'SayHello': grpc.unary_unary_rpc_method_handler(
                    servicer.SayHello,  # Service method implementation
                    request_deserializer=helloworld__pb2.HelloRequest.FromString,  # Request deserializer
                    response_serializer=helloworld__pb2.HelloReply.SerializeToString,  # Response serializer
            ),
    }
    # Create a generic handler for the service
    generic_handler = grpc.method_handlers_generic_handler(
            'helloworld.Greeter', rpc_method_handlers)
    # Register the handler with the server
    server.add_generic_rpc_handlers((generic_handler,))

class Greeter(object):
    """Helper class providing static methods for client-side Greeter service access.
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
        """Client-side static method to call the SayHello RPC.
        
        Args:
            request: The HelloRequest message to send.
            target: The server address.
            options: Optional gRPC options.
            channel_credentials: Credentials for secure channel.
            call_credentials: Call credentials.
            insecure: If True, uses insecure channel.
            compression: Compression algorithm.
            wait_for_ready: If True, waits for server to be ready.
            timeout: Optional timeout in seconds.
            metadata: Optional metadata to send with the request.
            
        Returns:
            The HelloReply message from the server.
        """
        return grpc.experimental.unary_unary(
            request, 
            target, 
            '/helloworld.Greeter/SayHello',
            helloworld__pb2.HelloRequest.SerializeToString,
            helloworld__pb2.HelloReply.FromString,
            options, 
            channel_credentials,
            insecure, 
            call_credentials, 
            compression, 
            wait_for_ready, 
            timeout, 
            metadata)
```