Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Header guard to prevent multiple inclusions
#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_COMMON_TYPES_PARSER_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_COMMON_TYPES_PARSER_H

#include <optional>

// Include necessary protocol buffer definitions
#include "envoy/config/core/v3/base.upb.h"
#include "envoy/extensions/transport_sockets/tls/v3/tls.upb.h"
#include "google/protobuf/any.upb.h"
#include "google/protobuf/duration.upb.h"
#include "google/protobuf/struct.upb.h"
#include "google/protobuf/wrappers.upb.h"

// Include core gRPC dependencies
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/util/time.h"
#include "src/core/util/validation_errors.h"
#include "src/core/xds/grpc/xds_common_types.h"
#include "src/core/xds/xds_client/xds_resource_type.h"

namespace grpc_core {

// Parses a protocol buffer Duration message into a Duration object
// @param proto_duration The protocol buffer Duration message to parse
// @param errors ValidationErrors object to collect any parsing errors
// @return Parsed Duration object
Duration ParseDuration(const google_protobuf_Duration* proto_duration,
                       ValidationErrors* errors);

// Parses a protocol buffer BoolValue message into a boolean
// @param bool_value_proto The protocol buffer BoolValue message to parse
// @param default_value Default value to return if bool_value_proto is null
// @return The boolean value or default_value if input is null
inline bool ParseBoolValue(const google_protobuf_BoolValue* bool_value_proto,
                           bool default_value = false) {
  if (bool_value_proto == nullptr) return default_value;
  return google_protobuf_BoolValue_value(bool_value_proto);
}

// Parses a protocol buffer UInt64Value message into an optional uint64_t
// @param proto The protocol buffer UInt64Value message to parse
// @return The parsed uint64_t value or std::nullopt if input is null
inline std::optional<uint64_t> ParseUInt64Value(
    const google_protobuf_UInt64Value* proto) {
  if (proto == nullptr) return std::nullopt;
  return google_protobuf_UInt64Value_value(proto);
}

// Parses a protocol buffer UInt32Value message into an optional uint32_t
// @param proto The protocol buffer UInt32Value message to parse
// @return The parsed uint32_t value or std::nullopt if input is null
inline std::optional<uint32_t> ParseUInt32Value(
    const google_protobuf_UInt32Value* proto) {
  if (proto == nullptr) return std::nullopt;
  return google_protobuf_UInt32Value_value(proto);
}

// Parses an XDS address from a protocol buffer Address message
// @param address The protocol buffer Address message to parse
// @param errors ValidationErrors object to collect any parsing errors
// @return Optional containing parsed resolved address or std::nullopt on failure
std::optional<grpc_resolved_address> ParseXdsAddress(
    const envoy_config_core_v3_Address* address, ValidationErrors* errors);

// Parses a CommonTlsContext from its protocol buffer representation
// @param context XDS decoding context
// @param common_tls_context_proto Protocol buffer message to parse
// @param errors ValidationErrors object to collect any parsing errors
// @return Parsed CommonTlsContext object
CommonTlsContext CommonTlsContextParse(
    const XdsResourceType::DecodeContext& context,
    const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext*
        common_tls_context_proto,
    ValidationErrors* errors);

// Converts a protocol buffer Struct message to a JSON representation
// @param context XDS decoding context
// @param resource Protocol buffer Struct message to convert
// @return StatusOr containing the JSON representation or error status
absl::StatusOr<Json> ParseProtobufStructToJson(
    const XdsResourceType::DecodeContext& context,
    const google_protobuf_Struct* resource);

// Extracts an XDS extension from a protocol buffer Any message
// @param context XDS decoding context
// @param any Protocol buffer Any message containing the extension
// @param errors ValidationErrors object to collect any parsing errors
// @return Optional containing the parsed XdsExtension or std::nullopt on failure
std::optional<XdsExtension> ExtractXdsExtension(
    const XdsResourceType::DecodeContext& context,
    const google_protobuf_Any* any, ValidationErrors* errors);

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_XDS_GRPC_XDS_COMMON_TYPES_PARSER_H
```

The comments now:
1. Explain the purpose of each function
2. Document parameters and their meanings
3. Specify return values and their possible states
4. Include important notes about null handling and default values
5. Maintain consistent formatting
6. Provide context about the expected inputs and outputs
7. Include namespace closure comment for clarity
8. Keep the header guard comment for completeness