
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.service.load_stats.v3 import lrs_pb2 as envoy_dot_service_dot_load__stats_dot_v3_dot_lrs__pb2

class LoadReportingServiceStub(object):
    """[#protodoc-title: Load reporting service (LRS)]

    Load Reporting Service is an Envoy API to emit load reports. Envoy will initiate a bi-directional
    stream with a management server. Upon connecting, the management server can send a
    :ref:`LoadStatsResponse <envoy_v3_api_msg_service.load_stats.v3.LoadStatsResponse>` to a node it is
    interested in getting the load reports for. Envoy in this node will start sending
    :ref:`LoadStatsRequest <envoy_v3_api_msg_service.load_stats.v3.LoadStatsRequest>`. This is done periodically
    based on the :ref:`load reporting interval <envoy_v3_api_field_service.load_stats.v3.LoadStatsResponse.load_reporting_interval>`
    For details, take a look at the :ref:`Load Reporting Service sandbox example <install_sandboxes_load_reporting_service>`.

    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.StreamLoadStats = channel.stream_stream(
                '/envoy.service.load_stats.v3.LoadReportingService/StreamLoadStats',
                request_serializer=envoy_dot_service_dot_load__stats_dot_v3_dot_lrs__pb2.LoadStatsRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_load__stats_dot_v3_dot_lrs__pb2.LoadStatsResponse.FromString,
                )

class LoadReportingServiceServicer(object):
    """[#protodoc-title: Load reporting service (LRS)]

    Load Reporting Service is an Envoy API to emit load reports. Envoy will initiate a bi-directional
    stream with a management server. Upon connecting, the management server can send a
    :ref:`LoadStatsResponse <envoy_v3_api_msg_service.load_stats.v3.LoadStatsResponse>` to a node it is
    interested in getting the load reports for. Envoy in this node will start sending
    :ref:`LoadStatsRequest <envoy_v3_api_msg_service.load_stats.v3.LoadStatsRequest>`. This is done periodically
    based on the :ref:`load reporting interval <envoy_v3_api_field_service.load_stats.v3.LoadStatsResponse.load_reporting_interval>`
    For details, take a look at the :ref:`Load Reporting Service sandbox example <install_sandboxes_load_reporting_service>`.

    """

    def StreamLoadStats(self, request_iterator, context):
        """Advanced API to allow for multi-dimensional load balancing by remote
        server. For receiving LB assignments, the steps are:
        1, The management server is configured with per cluster/zone/load metric
        capacity configuration. The capacity configuration definition is
        outside of the scope of this document.
        2. Envoy issues a standard {Stream,Fetch}Endpoints request for the clusters
        to balance.

        Independently, Envoy will initiate a StreamLoadStats bidi stream with a
        management server:
        1. Once a connection establishes, the management server publishes a
        LoadStatsResponse for all clusters it is interested in learning load
        stats about.
        2. For each cluster, Envoy load balances incoming traffic to upstream hosts
        based on per-zone weights and/or per-instance weights (if specified)
        based on intra-zone LbPolicy. This information comes from the above
        {Stream,Fetch}Endpoints.
        3. When upstream hosts reply, they optionally add header <define header
        name> with ASCII representation of EndpointLoadMetricStats.
        4. Envoy aggregates load reports over the period of time given to it in
        LoadStatsResponse.load_reporting_interval. This includes aggregation
        stats Envoy maintains by itself (total_requests, rpc_errors etc.) as
        well as load metrics from upstream hosts.
        5. When the timer of load_reporting_interval expires, Envoy sends new
        LoadStatsRequest filled with load reports for each cluster.
        6. The management server uses the load reports from all reported Envoys
        from around the world, computes global assignment and prepares traffic
        assignment destined for each zone Envoys are located in. Goto 2.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_LoadReportingServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'StreamLoadStats': grpc.stream_stream_rpc_method_handler(
                    servicer.StreamLoadStats,
                    request_deserializer=envoy_dot_service_dot_load__stats_dot_v3_dot_lrs__pb2.LoadStatsRequest.FromString,
                    response_serializer=envoy_dot_service_dot_load__stats_dot_v3_dot_lrs__pb2.LoadStatsResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.load_stats.v3.LoadReportingService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class LoadReportingService(object):
    """[#protodoc-title: Load reporting service (LRS)]

    Load Reporting Service is an Envoy API to emit load reports. Envoy will initiate a bi-directional
    stream with a management server. Upon connecting, the management server can send a
    :ref:`LoadStatsResponse <envoy_v3_api_msg_service.load_stats.v3.LoadStatsResponse>` to a node it is
    interested in getting the load reports for. Envoy in this node will start sending
    :ref:`LoadStatsRequest <envoy_v3_api_msg_service.load_stats.v3.LoadStatsRequest>`. This is done periodically
    based on the :ref:`load reporting interval <envoy_v3_api_field_service.load_stats.v3.LoadStatsResponse.load_reporting_interval>`
    For details, take a look at the :ref:`Load Reporting Service sandbox example <install_sandboxes_load_reporting_service>`.

    """

    @staticmethod
    def StreamLoadStats(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.load_stats.v3.LoadReportingService/StreamLoadStats',
            envoy_dot_service_dot_load__stats_dot_v3_dot_lrs__pb2.LoadStatsRequest.SerializeToString,
            envoy_dot_service_dot_load__stats_dot_v3_dot_lrs__pb2.LoadStatsResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)
