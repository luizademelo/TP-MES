Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

// Header includes for message size filter implementation
#include "src/core/ext/filters/message_size/message_size_filter.h"

#include <grpc/impl/channel_arg_names.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <inttypes.h>

#include <functional>
#include <utility>

#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/latch.h"
#include "src/core/lib/promise/race.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/service_config/service_config_call_data.h"
#include "src/core/util/latent_see.h"

namespace grpc_core {

// Gets the message size configuration from the call context
const MessageSizeParsedConfig* MessageSizeParsedConfig::GetFromCallContext(
    Arena* arena, size_t service_config_parser_index) {
  auto* svc_cfg_call_data = arena->GetContext<ServiceConfigCallData>();
  if (svc_cfg_call_data == nullptr) return nullptr;
  return static_cast<const MessageSizeParsedConfig*>(
      svc_cfg_call_data->GetMethodParsedConfig(service_config_parser_index));
}

// Gets message size limits from channel arguments
MessageSizeParsedConfig MessageSizeParsedConfig::GetFromChannelArgs(
    const ChannelArgs& channel_args) {
  MessageSizeParsedConfig limits;
  limits.max_send_size_ = GetMaxSendSizeFromChannelArgs(channel_args);
  limits.max_recv_size_ = GetMaxRecvSizeFromChannelArgs(channel_args);
  return limits;
}

// Gets the maximum receive message size from channel arguments
std::optional<uint32_t> GetMaxRecvSizeFromChannelArgs(const ChannelArgs& args) {
  if (args.WantMinimalStack()) return std::nullopt;
  int size = args.GetInt(GRPC_ARG_MAX_RECEIVE_MESSAGE_LENGTH)
                 .value_or(GRPC_DEFAULT_MAX_RECV_MESSAGE_LENGTH);
  if (size < 0) return std::nullopt;
  return static_cast<uint32_t>(size);
}

// Gets the maximum send message size from channel arguments
std::optional<uint32_t> GetMaxSendSizeFromChannelArgs(const ChannelArgs& args) {
  if (args.WantMinimalStack()) return std::nullopt;
  int size = args.GetInt(GRPC_ARG_MAX_SEND_MESSAGE_LENGTH)
                 .value_or(GRPC_DEFAULT_MAX_SEND_MESSAGE_LENGTH);
  if (size < 0) return std::nullopt;
  return static_cast<uint32_t>(size);
}

// JSON loader configuration for message size parameters
const JsonLoaderInterface* MessageSizeParsedConfig::JsonLoader(
    const JsonArgs&) {
  static const auto* loader =
      JsonObjectLoader<MessageSizeParsedConfig>()
          .OptionalField("maxRequestMessageBytes",
                         &MessageSizeParsedConfig::max_send_size_)
          .OptionalField("maxResponseMessageBytes",
                         &MessageSizeParsedConfig::max_recv_size_)
          .Finish();
  return loader;
}

// Parses per-method parameters from JSON configuration
std::unique_ptr<ServiceConfigParser::ParsedConfig>
MessageSizeParser::ParsePerMethodParams(const ChannelArgs& ,
                                        const Json& json,
                                        ValidationErrors* errors) {
  return LoadFromJson<std::unique_ptr<MessageSizeParsedConfig>>(
      json, JsonArgs(), errors);
}

// Registers the message size parser with the core configuration
void MessageSizeParser::Register(CoreConfiguration::Builder* builder) {
  builder->service_config_parser()->RegisterParser(
      std::make_unique<MessageSizeParser>());
}

// Gets the parser index for message size configuration
size_t MessageSizeParser::ParserIndex() {
  return CoreConfiguration::Get().service_config_parser().GetParserIndex(
      parser_name());
}

// Client message size filter definition
const grpc_channel_filter ClientMessageSizeFilter::kFilter =
    MakePromiseBasedFilter<ClientMessageSizeFilter, FilterEndpoint::kClient,
                           kFilterExaminesOutboundMessages |
                               kFilterExaminesInboundMessages>();

// Server message size filter definition
const grpc_channel_filter ServerMessageSizeFilter::kFilter =
    MakePromiseBasedFilter<ServerMessageSizeFilter, FilterEndpoint::kServer,
                           kFilterExaminesOutboundMessages |
                               kFilterExaminesInboundMessages>();

// Creates a client message size filter instance
absl::StatusOr<std::unique_ptr<ClientMessageSizeFilter>>
ClientMessageSizeFilter::Create(const ChannelArgs& args, ChannelFilter::Args) {
  return std::make_unique<ClientMessageSizeFilter>(args);
}

// Creates a server message size filter instance
absl::StatusOr<std::unique_ptr<ServerMessageSizeFilter>>
ServerMessageSizeFilter::Create(const ChannelArgs& args, ChannelFilter::Args) {
  return std::make_unique<ServerMessageSizeFilter>(args);
}

namespace {
// Checks if a message payload exceeds size limits and returns appropriate metadata if it does
ServerMetadataHandle CheckPayload(const Message& msg,
                                  std::optional<uint32_t> max_length,
                                  bool is_client, bool is_send) {
  if (!max_length.has_value()) return nullptr;
  GRPC_TRACE_LOG(call, INFO)
      << GetContext<Activity>()->DebugTag() << "[message_size] "
      << (is_send ? "send" : "recv") << " len:" << msg.payload()->Length()
      << " max:" << *max_length;
  if (msg.payload()->Length() <= *max_length) return nullptr;
  return CancelledServerMetadataFromStatus(
      GRPC_STATUS_RESOURCE_EXHAUSTED,
      absl::StrFormat("%s: %s message larger than max (%u vs. %d)",
                      is_client ? "CLIENT" : "SERVER",
                      is_send ? "Sent" : "Received", msg.payload()->Length(),
                      *max_length));
}
}

// Handles client initial metadata and sets up message size limits
void ClientMessageSizeFilter::Call::OnClientInitialMetadata(
    ClientMetadata&, ClientMessageSizeFilter* filter) {
  limits_ = filter->parsed_config_;

  // Note: Per-method config is only available on the client, so we
  // can apply more specific limits from the service config if available
  const MessageSizeParsedConfig* config_from_call_context =
      MessageSizeParsedConfig::GetFromCallContext(
          GetContext<Arena>(), filter->service_config_parser_index_);
  if (config_from_call_context != nullptr) {
    std::optional<uint32_t> max_send_size = limits_.max_send_size();
    std::optional<uint32_t> max_recv_size = limits_.max_recv_size();
    if (config_from_call_context->max_send_size().has_value() &&
        (!max_send_size.has_value() ||
         *config_from_call_context->max_send_size() < *max_send_size)) {
      max_send_size = config_from_call_context->max_send_size();
    }
    if (config_from_call_context->max_recv_size().has_value() &&
        (!max_recv_size.has_value() ||
         *config_from_call_context->max_recv_size() < *max_recv_size)) {
      max_recv_size = config_from_call_context->max_recv_size();
    }
    limits_ = MessageSizeParsedConfig(max_send_size, max_recv_size);
  }
}

// Checks incoming client-to-server messages against size limits
ServerMetadataHandle ServerMessageSizeFilter::Call::OnClientToServerMessage(
    const Message& message, ServerMessageSizeFilter* filter) {
  GRPC_LATENT_SEE_INNER_SCOPE(
      "ServerMessageSizeFilter::Call::OnClientToServerMessage");
  return CheckPayload(message, filter->parsed_config_.max_recv_size(),
                      false, false);
}

// Checks outgoing server-to-client messages against size limits
ServerMetadataHandle ServerMessageSizeFilter::Call::OnServerToClientMessage(
    const Message& message, ServerMessageSizeFilter* filter) {
  GRPC_LATENT_SEE_INNER_SCOPE(
      "ServerMessageSizeFilter::Call::OnServerToClientMessage");
  return CheckPayload(message, filter->parsed_config_.max_send_size(),
                      false, true);
}

// Checks outgoing client-to-server messages against size limits
ServerMetadataHandle ClientMessageSizeFilter::Call::OnClientToServerMessage(
    const Message& message) {
  GRPC_LATENT_SEE_INNER_SCOPE(
      "ClientMessageSizeFilter::Call::OnClientToServerMessage");
  return CheckPayload(message, limits_.max_send_size(), true,
                      true);
}

// Checks incoming server-to-client messages against size limits
ServerMetadataHandle ClientMessageSizeFilter::Call::OnServerToClientMessage(
    const Message& message) {
  GRPC_LATENT_SEE_INNER_SCOPE(
      "ClientMessageSizeFilter::Call::OnServerToClientMessage");
  return CheckPayload(message, limits_.max_recv_size(), true,
                      false);
}

namespace {
// Checks if channel args specify any message size limits
bool HasMessageSizeLimits(const ChannelArgs& channel_args) {
  MessageSizeParsedConfig limits =
      MessageSizeParsedConfig::GetFromChannelArgs(channel_args);
  return limits.max_send_size().has_value() ||
         limits.max_recv_size().has_value() ||
         channel_args.GetString(GRPC_ARG_SERVICE_CONFIG).has_value();
}
}

// Registers message size filters with the core configuration
void RegisterMessageSizeFilter(CoreConfiguration::Builder* builder) {
  MessageSizeParser::Register(builder);
  builder->channel_init()
      ->RegisterFilter<ClientMessageSizeFilter>(GRPC_CLIENT_SUBCHANNEL)
      .ExcludeFromMinimalStack();
  builder->channel_init()
      ->RegisterFilter<ClientMessageSizeFilter>(GRPC_CLIENT_DIRECT_CHANNEL)
      .ExcludeFromMinimalStack()
      .If(HasMessageSizeLimits);
  builder->channel_init()
      ->RegisterFilter<ServerMessageSizeFilter>(GRPC_SERVER_CHANNEL)
      .ExcludeFromMinimalStack()
      .If(HasMessageSizeLimits);
}
}
```