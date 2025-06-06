
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.service.rate_limit_quota.v3 import rlqs_pb2 as envoy_dot_service_dot_rate__limit__quota_dot_v3_dot_rlqs__pb2

class RateLimitQuotaServiceStub(object):
    """[#protodoc-title: Rate Limit Quota Service (RLQS)]

    The Rate Limit Quota Service (RLQS) is a Envoy global rate limiting service that allows to
    delegate rate limit decisions to a remote service. The service will aggregate the usage reports
    from multiple data plane instances, and distribute Rate Limit Assignments to each instance
    based on its business logic. The logic is outside of the scope of the protocol API.

    The protocol is designed as a streaming-first API. It utilizes watch-like subscription model.
    The data plane groups requests into Quota Buckets as directed by the filter config,
    and periodically reports them to the RLQS server along with the Bucket identifier, :ref:`BucketId
    <envoy_v3_api_msg_service.rate_limit_quota.v3.BucketId>`. Once RLQS server has collected enough
    reports to make a decision, it'll send back the assignment with the rate limiting instructions.

    The first report sent by the data plane is interpreted by the RLQS server as a "watch" request,
    indicating that the data plane instance is interested in receiving further updates for the
    ``BucketId``. From then on, RLQS server may push assignments to this instance at will, even if
    the instance is not sending usage reports. It's the responsibility of the RLQS server
    to determine when the data plane instance didn't send ``BucketId`` reports for too long,
    and to respond with the :ref:`AbandonAction
    <envoy_v3_api_msg_service.rate_limit_quota.v3.RateLimitQuotaResponse.BucketAction.AbandonAction>`,
    indicating that the server has now stopped sending quota assignments for the ``BucketId`` bucket,
    and the data plane instance should :ref:`abandon
    <envoy_v3_api_field_service.rate_limit_quota.v3.RateLimitQuotaResponse.BucketAction.abandon_action>`
    it.

    If for any reason the RLQS client doesn't receive the initial assignment for the reported bucket,
    in order to prevent memory exhaustion, the data plane will limit the time such bucket
    is retained. The exact time to wait for the initial assignment is chosen by the filter,
    and may vary based on the implementation.
    Once the duration ends, the data plane will stop reporting bucket usage, reject any enqueued
    requests, and purge the bucket from the memory. Subsequent requests matched into the bucket
    will re-initialize the bucket in the "no assignment" state, restarting the reports.

    Refer to Rate Limit Quota :ref:`configuration overview <config_http_filters_rate_limit_quota>`
    for further details.

    Defines the Rate Limit Quota Service (RLQS).
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.StreamRateLimitQuotas = channel.stream_stream(
                '/envoy.service.rate_limit_quota.v3.RateLimitQuotaService/StreamRateLimitQuotas',
                request_serializer=envoy_dot_service_dot_rate__limit__quota_dot_v3_dot_rlqs__pb2.RateLimitQuotaUsageReports.SerializeToString,
                response_deserializer=envoy_dot_service_dot_rate__limit__quota_dot_v3_dot_rlqs__pb2.RateLimitQuotaResponse.FromString,
                )

class RateLimitQuotaServiceServicer(object):
    """[#protodoc-title: Rate Limit Quota Service (RLQS)]

    The Rate Limit Quota Service (RLQS) is a Envoy global rate limiting service that allows to
    delegate rate limit decisions to a remote service. The service will aggregate the usage reports
    from multiple data plane instances, and distribute Rate Limit Assignments to each instance
    based on its business logic. The logic is outside of the scope of the protocol API.

    The protocol is designed as a streaming-first API. It utilizes watch-like subscription model.
    The data plane groups requests into Quota Buckets as directed by the filter config,
    and periodically reports them to the RLQS server along with the Bucket identifier, :ref:`BucketId
    <envoy_v3_api_msg_service.rate_limit_quota.v3.BucketId>`. Once RLQS server has collected enough
    reports to make a decision, it'll send back the assignment with the rate limiting instructions.

    The first report sent by the data plane is interpreted by the RLQS server as a "watch" request,
    indicating that the data plane instance is interested in receiving further updates for the
    ``BucketId``. From then on, RLQS server may push assignments to this instance at will, even if
    the instance is not sending usage reports. It's the responsibility of the RLQS server
    to determine when the data plane instance didn't send ``BucketId`` reports for too long,
    and to respond with the :ref:`AbandonAction
    <envoy_v3_api_msg_service.rate_limit_quota.v3.RateLimitQuotaResponse.BucketAction.AbandonAction>`,
    indicating that the server has now stopped sending quota assignments for the ``BucketId`` bucket,
    and the data plane instance should :ref:`abandon
    <envoy_v3_api_field_service.rate_limit_quota.v3.RateLimitQuotaResponse.BucketAction.abandon_action>`
    it.

    If for any reason the RLQS client doesn't receive the initial assignment for the reported bucket,
    in order to prevent memory exhaustion, the data plane will limit the time such bucket
    is retained. The exact time to wait for the initial assignment is chosen by the filter,
    and may vary based on the implementation.
    Once the duration ends, the data plane will stop reporting bucket usage, reject any enqueued
    requests, and purge the bucket from the memory. Subsequent requests matched into the bucket
    will re-initialize the bucket in the "no assignment" state, restarting the reports.

    Refer to Rate Limit Quota :ref:`configuration overview <config_http_filters_rate_limit_quota>`
    for further details.

    Defines the Rate Limit Quota Service (RLQS).
    """

    def StreamRateLimitQuotas(self, request_iterator, context):
        """Main communication channel: the data plane sends usage reports to the RLQS server,
        and the server asynchronously responding with the assignments.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_RateLimitQuotaServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'StreamRateLimitQuotas': grpc.stream_stream_rpc_method_handler(
                    servicer.StreamRateLimitQuotas,
                    request_deserializer=envoy_dot_service_dot_rate__limit__quota_dot_v3_dot_rlqs__pb2.RateLimitQuotaUsageReports.FromString,
                    response_serializer=envoy_dot_service_dot_rate__limit__quota_dot_v3_dot_rlqs__pb2.RateLimitQuotaResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.rate_limit_quota.v3.RateLimitQuotaService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class RateLimitQuotaService(object):
    """[#protodoc-title: Rate Limit Quota Service (RLQS)]

    The Rate Limit Quota Service (RLQS) is a Envoy global rate limiting service that allows to
    delegate rate limit decisions to a remote service. The service will aggregate the usage reports
    from multiple data plane instances, and distribute Rate Limit Assignments to each instance
    based on its business logic. The logic is outside of the scope of the protocol API.

    The protocol is designed as a streaming-first API. It utilizes watch-like subscription model.
    The data plane groups requests into Quota Buckets as directed by the filter config,
    and periodically reports them to the RLQS server along with the Bucket identifier, :ref:`BucketId
    <envoy_v3_api_msg_service.rate_limit_quota.v3.BucketId>`. Once RLQS server has collected enough
    reports to make a decision, it'll send back the assignment with the rate limiting instructions.

    The first report sent by the data plane is interpreted by the RLQS server as a "watch" request,
    indicating that the data plane instance is interested in receiving further updates for the
    ``BucketId``. From then on, RLQS server may push assignments to this instance at will, even if
    the instance is not sending usage reports. It's the responsibility of the RLQS server
    to determine when the data plane instance didn't send ``BucketId`` reports for too long,
    and to respond with the :ref:`AbandonAction
    <envoy_v3_api_msg_service.rate_limit_quota.v3.RateLimitQuotaResponse.BucketAction.AbandonAction>`,
    indicating that the server has now stopped sending quota assignments for the ``BucketId`` bucket,
    and the data plane instance should :ref:`abandon
    <envoy_v3_api_field_service.rate_limit_quota.v3.RateLimitQuotaResponse.BucketAction.abandon_action>`
    it.

    If for any reason the RLQS client doesn't receive the initial assignment for the reported bucket,
    in order to prevent memory exhaustion, the data plane will limit the time such bucket
    is retained. The exact time to wait for the initial assignment is chosen by the filter,
    and may vary based on the implementation.
    Once the duration ends, the data plane will stop reporting bucket usage, reject any enqueued
    requests, and purge the bucket from the memory. Subsequent requests matched into the bucket
    will re-initialize the bucket in the "no assignment" state, restarting the reports.

    Refer to Rate Limit Quota :ref:`configuration overview <config_http_filters_rate_limit_quota>`
    for further details.

    Defines the Rate Limit Quota Service (RLQS).
    """

    @staticmethod
    def StreamRateLimitQuotas(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.rate_limit_quota.v3.RateLimitQuotaService/StreamRateLimitQuotas',
            envoy_dot_service_dot_rate__limit__quota_dot_v3_dot_rlqs__pb2.RateLimitQuotaUsageReports.SerializeToString,
            envoy_dot_service_dot_rate__limit__quota_dot_v3_dot_rlqs__pb2.RateLimitQuotaResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)
