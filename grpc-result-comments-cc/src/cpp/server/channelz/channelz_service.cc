Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#include "src/cpp/server/channelz/channelz_service.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpcpp/impl/codegen/config_protobuf.h>

#include <memory>

#include "absl/log/log.h"

namespace grpc {

namespace {

// Parses a JSON string into a Protocol Buffers message.
// Args:
//   json_str: The JSON string to parse
//   message: The Protocol Buffers message to populate with parsed data
// Returns:
//   Status indicating success or failure of the parsing operation
// Notes:
//   - Uses case-insensitive parsing for enum values
//   - Logs errors if parsing fails
grpc::protobuf::util::Status ParseJson(const char* json_str,
                                       grpc::protobuf::Message* message) {
  grpc::protobuf::json::JsonParseOptions options;
  options.case_insensitive_enum_parsing = true;
  auto r =
      grpc::protobuf::json::JsonStringToMessage(json_str, message, options);
  if (!r.ok()) {
    LOG(ERROR) << "channelz json parse failed: error=" << r.ToString()
               << " json:\n"
               << json_str;
  }
  return r;
}

}  // namespace

// Gets top-level channels information from channelz.
// Args:
//   request: Contains the starting channel ID for the query
//   response: Will be populated with the channel information
// Returns:
//   Status OK if successful, INTERNAL error if JSON parsing fails or null is returned
Status ChannelzService::GetTopChannels(
    ServerContext* ,
    const channelz::v1::GetTopChannelsRequest* request,
    channelz::v1::GetTopChannelsResponse* response) {
  char* json_str = grpc_channelz_get_top_channels(request->start_channel_id());
  if (json_str == nullptr) {
    return Status(StatusCode::INTERNAL,
                  "grpc_channelz_get_top_channels returned null");
  }
  grpc::protobuf::util::Status s = ParseJson(json_str, response);
  gpr_free(json_str);
  if (!s.ok()) {
    return Status(StatusCode::INTERNAL, s.ToString());
  }
  return Status::OK;
}

// Gets server information from channelz.
// Args:
//   request: Contains the starting server ID for the query
//   response: Will be populated with the server information
// Returns:
//   Status OK if successful, INTERNAL error if JSON parsing fails or null is returned
Status ChannelzService::GetServers(
    ServerContext* , const channelz::v1::GetServersRequest* request,
    channelz::v1::GetServersResponse* response) {
  char* json_str = grpc_channelz_get_servers(request->start_server_id());
  if (json_str == nullptr) {
    return Status(StatusCode::INTERNAL,
                  "grpc_channelz_get_servers returned null");
  }
  grpc::protobuf::util::Status s = ParseJson(json_str, response);
  gpr_free(json_str);
  if (!s.ok()) {
    return Status(StatusCode::INTERNAL, s.ToString());
  }
  return Status::OK;
}

// Gets specific server information from channelz.
// Args:
//   request: Contains the server ID to query
//   response: Will be populated with the server information
// Returns:
//   Status OK if successful, INTERNAL error if JSON parsing fails or null is returned
Status ChannelzService::GetServer(ServerContext* ,
                                  const channelz::v1::GetServerRequest* request,
                                  channelz::v1::GetServerResponse* response) {
  char* json_str = grpc_channelz_get_server(request->server_id());
  if (json_str == nullptr) {
    return Status(StatusCode::INTERNAL,
                  "grpc_channelz_get_server returned null");
  }
  grpc::protobuf::util::Status s = ParseJson(json_str, response);
  gpr_free(json_str);
  if (!s.ok()) {
    return Status(StatusCode::INTERNAL, s.ToString());
  }
  return Status::OK;
}

// Gets server sockets information from channelz.
// Args:
//   request: Contains server ID, starting socket ID, and max results count
//   response: Will be populated with the sockets information
// Returns:
//   Status OK if successful, INTERNAL error if JSON parsing fails or null is returned
Status ChannelzService::GetServerSockets(
    ServerContext* ,
    const channelz::v1::GetServerSocketsRequest* request,
    channelz::v1::GetServerSocketsResponse* response) {
  char* json_str = grpc_channelz_get_server_sockets(
      request->server_id(), request->start_socket_id(), request->max_results());
  if (json_str == nullptr) {
    return Status(StatusCode::INTERNAL,
                  "grpc_channelz_get_server_sockets returned null");
  }
  grpc::protobuf::util::Status s = ParseJson(json_str, response);
  gpr_free(json_str);
  if (!s.ok()) {
    return Status(StatusCode::INTERNAL, s.ToString());
  }
  return Status::OK;
}

// Gets specific channel information from channelz.
// Args:
//   request: Contains the channel ID to query
//   response: Will be populated with the channel information
// Returns:
//   Status OK if successful, NOT_FOUND if channel doesn't exist, INTERNAL error if JSON parsing fails
Status ChannelzService::GetChannel(
    ServerContext* , const channelz::v1::GetChannelRequest* request,
    channelz::v1::GetChannelResponse* response) {
  char* json_str = grpc_channelz_get_channel(request->channel_id());
  if (json_str == nullptr) {
    return Status(StatusCode::NOT_FOUND, "No object found for that ChannelId");
  }
  grpc::protobuf::util::Status s = ParseJson(json_str, response);
  gpr_free(json_str);
  if (!s.ok()) {
    return Status(StatusCode::INTERNAL, s.ToString());
  }
  return Status::OK;
}

// Gets specific subchannel information from channelz.
// Args:
//   request: Contains the subchannel ID to query
//   response: Will be populated with the subchannel information
// Returns:
//   Status OK if successful, NOT_FOUND if subchannel doesn't exist, INTERNAL error if JSON parsing fails
Status ChannelzService::GetSubchannel(
    ServerContext* ,
    const channelz::v1::GetSubchannelRequest* request,
    channelz::v1::GetSubchannelResponse* response) {
  char* json_str = grpc_channelz_get_subchannel(request->subchannel_id());
  if (json_str == nullptr) {
    return Status(StatusCode::NOT_FOUND,
                  "No object found for that SubchannelId");
  }
  grpc::protobuf::util::Status s = ParseJson(json_str, response);
  gpr_free(json_str);
  if (!s.ok()) {
    return Status(StatusCode::INTERNAL, s.ToString());
  }
  return Status::OK;
}

// Gets specific socket information from channelz.
// Args:
//   request: Contains the socket ID to query
//   response: Will be populated with the socket information
// Returns:
//   Status OK if successful, NOT_FOUND if socket doesn't exist, INTERNAL error if JSON parsing fails
Status ChannelzService::GetSocket(ServerContext* ,
                                  const channelz::v1::GetSocketRequest* request,
                                  channelz::v1::GetSocketResponse* response) {
  char* json_str = grpc_channelz_get_socket(request->socket_id());
  if (json_str == nullptr) {
    return Status(StatusCode::NOT_FOUND, "No object found for that SocketId");
  }
  grpc::protobuf::util::Status s = ParseJson(json_str, response);
  gpr_free(json_str);
  if (!s.ok()) {
    return Status(StatusCode::INTERNAL, s.ToString());
  }
  return Status::OK;
}

}  // namespace grpc
```

The comments I've added:
1. Documented the ParseJson helper function with its purpose, parameters, return value, and notes
2. Added detailed documentation for each service method including:
   - Purpose of the method
   - Parameters and their purposes
   - Return values and possible error conditions
3. Maintained consistent formatting and style throughout
4. Added namespace closing comments for better readability
5. Included notes about error conditions and handling

The comments follow a clear pattern for each method while providing specific details about each one's unique behavior and purpose.