Here's the commented version of the code:

```python
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.service.auth.v2 import external_auth_pb2 as envoy_dot_service_dot_auth_dot_v2_dot_external__auth__pb2

class AuthorizationStub(object):
    """[#protodoc-title: Authorization Service ]

    The authorization service request messages used by external authorization :ref:`network filter
    <config_network_filters_ext_authz>` and :ref:`HTTP filter <config_http_filters_ext_authz>`.

    A generic interface for performing authorization check on incoming
    requests to a networked service.
    """

    def __init__(self, channel):
        """Constructor.

        Initializes the AuthorizationStub with a gRPC channel and sets up the Check RPC method.

        Args:
            channel: A grpc.Channel. The gRPC channel used for communication with the server.
        """
        # Set up a unary-unary RPC method for the Check service
        self.Check = channel.unary_unary(
                '/envoy.service.auth.v2alpha.Authorization/Check',
                request_serializer=envoy_dot_service_dot_auth_dot_v2_dot_external__auth__pb2.CheckRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_auth_dot_v2_dot_external__auth__pb2.CheckResponse.FromString,
                )

class AuthorizationServicer(object):
    """[#protodoc-title: Authorization Service ]

    The authorization service request messages used by external authorization :ref:`network filter
    <config_network_filters_ext_authz>` and :ref:`HTTP filter <config_http_filters_ext_authz>`.

    A generic interface for performing authorization check on incoming
    requests to a networked service.
    """

    def Check(self, request, context):
        """Performs authorization check based on the attributes associated with the
        incoming request, and returns status `OK` or not `OK`.

        Args:
            request: The incoming authorization request.
            context: gRPC context for the RPC call.

        Raises:
            NotImplementedError: Indicates this method needs to be implemented by subclasses.
        """
        # Default implementation returns UNIMPLEMENTED status
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_AuthorizationServicer_to_server(servicer, server):
    """Adds Authorization service to a gRPC server.

    Args:
        servicer: An implementation of AuthorizationServicer that handles the RPC methods.
        server: The gRPC server to which the service will be added.
    """
    # Define RPC method handlers for the Authorization service
    rpc_method_handlers = {
            'Check': grpc.unary_unary_rpc_method_handler(
                    servicer.Check,
                    request_deserializer=envoy_dot_service_dot_auth_dot_v2_dot_external__auth__pb2.CheckRequest.FromString,
                    response_serializer=envoy_dot_service_dot_auth_dot_v2_dot_external__auth__pb2.CheckResponse.SerializeToString,
            ),
    }
    # Create a generic handler for the Authorization service
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.auth.v2alpha.Authorization', rpc_method_handlers)
    # Add the generic handler to the server
    server.add_generic_rpc_handlers((generic_handler,))

class Authorization(object):
    """[#protodoc-title: Authorization Service ]

    The authorization service request messages used by external authorization :ref:`network filter
    <config_network_filters_ext_authz>` and :ref:`HTTP filter <config_http_filters_ext_authz>`.

    A generic interface for performing authorization check on incoming
    requests to a networked service.
    """

    @staticmethod
    def Check(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Makes a Check RPC call to the Authorization service.

        Args:
            request: The CheckRequest to send to the server.
            target: The server address.
            options: (Optional) A list of key-value pairs for channel configuration.
            channel_credentials: (Optional) The channel credentials.
            call_credentials: (Optional) The call credentials.
            insecure: (Optional) Boolean indicating if the connection should be insecure.
            compression: (Optional) The compression method.
            wait_for_ready: (Optional) Boolean indicating if the call should wait for the server to be ready.
            timeout: (Optional) The timeout for the call in seconds.
            metadata: (Optional) Additional metadata to provide with the call.

        Returns:
            The CheckResponse from the server.
        """
        return grpc.experimental.unary_unary(request, target, '/envoy.service.auth.v2alpha.Authorization/Check',
            envoy_dot_service_dot_auth_dot_v2_dot_external__auth__pb2.CheckRequest.SerializeToString,
            envoy_dot_service_dot_auth_dot_v2_dot_external__auth__pb2.CheckResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)
```