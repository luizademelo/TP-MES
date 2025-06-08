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
            channel: A grpc.Channel used for communication with the gRPC server.
        """
        self.Check = channel.unary_unary(
                '/envoy.service.auth.v2.Authorization/Check',
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

        This is a placeholder implementation that should be overridden by actual authorization logic.
        By default, it returns UNIMPLEMENTED status.

        Args:
            request: The authorization check request.
            context: gRPC context for the RPC call.

        Raises:
            NotImplementedError: Indicates the method is not implemented.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_AuthorizationServicer_to_server(servicer, server):
    """Registers the AuthorizationServicer with a gRPC server.

    Args:
        servicer: An instance of AuthorizationServicer implementing the service methods.
        server: The gRPC server to which the servicer will be added.
    """
    rpc_method_handlers = {
            'Check': grpc.unary_unary_rpc_method_handler(
                    servicer.Check,
                    request_deserializer=envoy_dot_service_dot_auth_dot_v2_dot_external__auth__pb2.CheckRequest.FromString,
                    response_serializer=envoy_dot_service_dot_auth_dot_v2_dot_external__auth__pb2.CheckResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.auth.v2.Authorization', rpc_method_handlers)
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
        """Makes a Check RPC call to the authorization service.

        Args:
            request: The CheckRequest to send to the server.
            target: The server address.
            options: (Optional) A list of key-value pairs for channel configuration.
            channel_credentials: (Optional) The channel credentials.
            call_credentials: (Optional) The call credentials.
            insecure: (Optional) Boolean indicating if the connection should be insecure.
            compression: (Optional) The compression algorithm to use.
            wait_for_ready: (Optional) Boolean indicating if the call should wait for the server to be ready.
            timeout: (Optional) The timeout for the RPC call.
            metadata: (Optional) Additional metadata to send with the call.

        Returns:
            The CheckResponse from the server.
        """
        return grpc.experimental.unary_unary(request, target, '/envoy.service.auth.v2.Authorization/Check',
            envoy_dot_service_dot_auth_dot_v2_dot_external__auth__pb2.CheckRequest.SerializeToString,
            envoy_dot_service_dot_auth_dot_v2_dot_external__auth__pb2.CheckResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)
```