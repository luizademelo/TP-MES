Here's the commented version of the code snippet:

```c++
// Copyright 2024 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_METADATA_PARSER_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_METADATA_PARSER_H

// Include necessary headers:
// - Protocol Buffers generated header for envoy metadata configuration
#include "envoy/config/core/v3/base.upb.h"
// - Header for validation error handling utilities
#include "src/core/util/validation_errors.h"
// - Header for XDS metadata type definitions
#include "src/core/xds/grpc/xds_metadata.h"
// - Header for XDS resource type definitions
#include "src/core/xds/xds_client/xds_resource_type.h"

namespace grpc_core {

// Function declaration for parsing XDS metadata from envoy configuration
// Parameters:
//   context - Contains context information needed for decoding XDS resources
//   metadata - Pointer to envoy metadata configuration to be parsed
//   errors - Pointer to ValidationErrors object to collect parsing errors
// Returns:
//   XdsMetadataMap - A map containing the parsed metadata key-value pairs
XdsMetadataMap ParseXdsMetadataMap(
    const XdsResourceType::DecodeContext& context,
    const envoy_config_core_v3_Metadata* metadata, ValidationErrors* errors);

}  // namespace grpc_core

// End of header guard
#endif  // GRPC_SRC_CORE_XDS_GRPC_XDS_METADATA_PARSER_H
```

The comments provide:
1. Explanation of the header guard
2. Documentation for each included header
3. Namespace documentation
4. Detailed function documentation including parameters and return value
5. Clear indication of the header guard closure

The comments follow a consistent style and provide meaningful information without being overly verbose. They explain the purpose of each component while maintaining readability.