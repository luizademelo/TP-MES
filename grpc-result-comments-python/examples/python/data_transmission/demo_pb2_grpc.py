Here's the commented version of the code:

```python
"""Client and server classes corresponding to protobuf-defined services."""
import grpc
import demo_pb2 as demo__pb2

class GRPCDemoStub(object):
    """Client-side stub for GRPCDemo service.
    
    Provides methods to call the gRPC service. Each method corresponds to one of the
    RPC methods defined in the .proto file. The stub is generated automatically by
    the gRPC framework.
    """

    def __init__(self, channel):
        """Initializes the GRPCDemoStub with the given channel.
        
        Args:
            channel: A grpc.Channel used to make RPC calls.
        """
        # Unary-Unary RPC: Single request, single response
        self.SimpleMethod = channel.unary_unary(
                '/demo.GRPCDemo/SimpleMethod',
                request_serializer=demo__pb2.Request.SerializeToString,
                response_deserializer=demo__pb2.Response.FromString,
                )
        # Client Streaming RPC: Stream of requests, single response
        self.ClientStreamingMethod = channel.stream_unary(
                '/demo.GRPCDemo/ClientStreamingMethod',
                request_serializer=demo__pb2.Request.SerializeToString,
                response_deserializer=demo__pb2.Response.FromString,
                )
        # Server Streaming RPC: Single request, stream of responses
        self.ServerStreamingMethod = channel.unary_stream(
                '/demo.GRPCDemo/ServerStreamingMethod',
                request_serializer=demo__pb2.Request.SerializeToString,
                response_deserializer=demo__pb2.Response.FromString,
                )
        # Bidirectional Streaming RPC: Stream of requests, stream of responses
        self.BidirectionalStreamingMethod = channel.stream_stream(
                '/demo.GRPCDemo/BidirectionalStreamingMethod',
                request_serializer=demo__pb2.Request.SerializeToString,
                response_deserializer=demo__pb2.Response.FromString,
                )

class GRPCDemoServicer(object):
    """Server-side implementation of GRPCDemo service.
    
    Contains the actual implementation of the RPC methods. This class should be
    subclassed and methods overridden to provide the actual functionality.
    """

    def SimpleMethod(self, request, context):
        """Unary-Unary RPC implementation.
        
        Args:
            request: The request message.
            context: The gRPC context for the RPC.
        
        Returns:
            The response message.
        
        Note:
            This is a placeholder implementation that should be overridden.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def ClientStreamingMethod(self, request_iterator, context):
        """Client Streaming RPC implementation.
        
        Args:
            request_iterator: An iterator of request messages.
            context: The gRPC context for the RPC.
        
        Returns:
            The response message.
        
        Note:
            This is a placeholder implementation that should be overridden.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def ServerStreamingMethod(self, request, context):
        """Server Streaming RPC implementation.
        
        Args:
            request: The request message.
            context: The gRPC context for the RPC.
        
        Returns:
            An iterator of response messages.
        
        Note:
            This is a placeholder implementation that should be overridden.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def BidirectionalStreamingMethod(self, request_iterator, context):
        """Bidirectional Streaming RPC implementation.
        
        Args:
            request_iterator: An iterator of request messages.
            context: The gRPC context for the RPC.
        
        Returns:
            An iterator of response messages.
        
        Note:
            This is a placeholder implementation that should be overridden.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_GRPCDemoServicer_to_server(servicer, server):
    """Registers GRPCDemoServicer with the gRPC server.
    
    Args:
        servicer: An instance of GRPCDemoServicer implementing the RPC methods.
        server: The gRPC server to which the servicer will be added.
    """
    # Dictionary mapping method names to their respective handlers
    rpc_method_handlers = {
            'SimpleMethod': grpc.unary_unary_rpc_method_handler(
                    servicer.SimpleMethod,
                    request_deserializer=demo__pb2.Request.FromString,
                    response_serializer=demo__pb2.Response.SerializeToString,
            ),
            'ClientStreamingMethod': grpc.stream_unary_rpc_method_handler(
                    servicer.ClientStreamingMethod,
                    request_deserializer=demo__pb2.Request.FromString,
                    response_serializer=demo__pb2.Response.SerializeToString,
            ),
            'ServerStreamingMethod': grpc.unary_stream_rpc_method_handler(
                    servicer.ServerStreamingMethod,
                    request_deserializer=demo__pb2.Request.FromString,
                    response_serializer=demo__pb2.Response.SerializeToString,
            ),
            'BidirectionalStreamingMethod': grpc.stream_stream_rpc_method_handler(
                    servicer.BidirectionalStreamingMethod,
                    request_deserializer=demo__pb2.Request.FromString,
                    response_serializer=demo__pb2.Response.SerializeToString,
            ),
    }
    # Create a generic handler for the service
    generic_handler = grpc.method_handlers_generic_handler(
            'demo.GRPCDemo', rpc_method_handlers)
    # Register the handler with the server
    server.add_generic_rpc_handlers((generic_handler,))

class GRPCDemo(object):
    """Static methods for making RPC calls to GRPCDemo service.
    
    Provides convenience methods for making RPC calls without needing to create
    a stub instance manually.
    """

    @staticmethod
    def SimpleMethod(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Makes a Unary-Unary RPC call to SimpleMethod."""
        return grpc.experimental.unary_unary(request, target, '/demo.GRPCDemo/SimpleMethod',
            demo__pb2.Request.SerializeToString,
            demo__pb2.Response.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def ClientStreamingMethod(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Makes a Client Streaming RPC call to ClientStreamingMethod."""
        return grpc.experimental.stream_unary(request_iterator, target, '/demo.GRPCDemo/ClientStreamingMethod',
            demo__pb2.Request.SerializeToString,
            demo__pb2.Response.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def ServerStreamingMethod(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Makes a Server Streaming RPC call to ServerStreamingMethod."""
        return grpc.experimental.unary_stream(request, target, '/demo.GRPCDemo/ServerStreamingMethod',
            demo__pb2.Request.SerializeToString,
            demo__pb2.Response.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def BidirectionalStreamingMethod(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Makes a Bidirectional Streaming RPC call to BidirectionalStreamingMethod."""
        return grpc.experimental.stream_stream(request_iterator, target, '/demo.GRPCDemo/BidirectionalStreamingMethod',
            demo__pb2.Request.SerializeToString,
            demo__pb2.Response.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)
```