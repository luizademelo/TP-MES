
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.service.ratelimit.v3 import rls_pb2 as envoy_dot_service_dot_ratelimit_dot_v3_dot_rls__pb2

class RateLimitServiceStub(object):
    """[#protodoc-title: Rate limit service (RLS)]

    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.ShouldRateLimit = channel.unary_unary(
                '/envoy.service.ratelimit.v3.RateLimitService/ShouldRateLimit',
                request_serializer=envoy_dot_service_dot_ratelimit_dot_v3_dot_rls__pb2.RateLimitRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_ratelimit_dot_v3_dot_rls__pb2.RateLimitResponse.FromString,
                )

class RateLimitServiceServicer(object):
    """[#protodoc-title: Rate limit service (RLS)]

    """

    def ShouldRateLimit(self, request, context):
        """Determine whether rate limiting should take place.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_RateLimitServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'ShouldRateLimit': grpc.unary_unary_rpc_method_handler(
                    servicer.ShouldRateLimit,
                    request_deserializer=envoy_dot_service_dot_ratelimit_dot_v3_dot_rls__pb2.RateLimitRequest.FromString,
                    response_serializer=envoy_dot_service_dot_ratelimit_dot_v3_dot_rls__pb2.RateLimitResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.ratelimit.v3.RateLimitService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class RateLimitService(object):
    """[#protodoc-title: Rate limit service (RLS)]

    """

    @staticmethod
    def ShouldRateLimit(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/envoy.service.ratelimit.v3.RateLimitService/ShouldRateLimit',
            envoy_dot_service_dot_ratelimit_dot_v3_dot_rls__pb2.RateLimitRequest.SerializeToString,
            envoy_dot_service_dot_ratelimit_dot_v3_dot_rls__pb2.RateLimitResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)
