Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#include "src/core/tsi/alts/handshaker/alts_tsi_utils.h"

#include <grpc/byte_buffer_reader.h>
#include <grpc/support/port_platform.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_internal.h"

/**
 * Converts a gRPC status code to a TSI (Transport Security Interface) result.
 * 
 * @param code The gRPC status code to convert
 * @return The corresponding TSI result code:
 *         - TSI_OK for GRPC_STATUS_OK
 *         - TSI_UNKNOWN_ERROR for GRPC_STATUS_UNKNOWN
 *         - TSI_INVALID_ARGUMENT for GRPC_STATUS_INVALID_ARGUMENT
 *         - TSI_NOT_FOUND for GRPC_STATUS_NOT_FOUND
 *         - TSI_INTERNAL_ERROR for GRPC_STATUS_INTERNAL
 *         - TSI_UNKNOWN_ERROR for all other status codes
 */
tsi_result alts_tsi_utils_convert_to_tsi_result(grpc_status_code code) {
  switch (code) {
    case GRPC_STATUS_OK:
      return TSI_OK;
    case GRPC_STATUS_UNKNOWN:
      return TSI_UNKNOWN_ERROR;
    case GRPC_STATUS_INVALID_ARGUMENT:
      return TSI_INVALID_ARGUMENT;
    case GRPC_STATUS_NOT_FOUND:
      return TSI_NOT_FOUND;
    case GRPC_STATUS_INTERNAL:
      return TSI_INTERNAL_ERROR;
    default:
      return TSI_UNKNOWN_ERROR;
  }
}

/**
 * Deserializes a gRPC byte buffer containing a handshaker response into a 
 * grpc_gcp_HandshakerResp protobuf message.
 *
 * @param resp_buffer The input byte buffer containing serialized response data
 * @param arena The upb arena to use for memory allocation
 * @return Pointer to the deserialized HandshakerResp message, or nullptr if 
 *         deserialization fails
 *
 * The function performs the following steps:
 * 1. Validates input parameters are non-null
 * 2. Initializes a byte buffer reader
 * 3. Reads all data from the buffer into a slice
 * 4. Allocates memory from the arena and copies the slice data
 * 5. Parses the copied data into a HandshakerResp message
 * 6. Cleans up resources (slice and reader)
 * 7. Returns the parsed message or nullptr if parsing failed
 */
grpc_gcp_HandshakerResp* alts_tsi_utils_deserialize_response(
    grpc_byte_buffer* resp_buffer, upb_Arena* arena) {
  // Validate input parameters
  CHECK_NE(resp_buffer, nullptr);
  CHECK_NE(arena, nullptr);
  
  // Initialize byte buffer reader
  grpc_byte_buffer_reader bbr;
  grpc_byte_buffer_reader_init(&bbr, resp_buffer);
  
  // Read all data from buffer into a slice
  grpc_slice slice = grpc_byte_buffer_reader_readall(&bbr);
  size_t buf_size = GRPC_SLICE_LENGTH(slice);
  
  // Allocate memory from arena and copy slice data
  void* buf = upb_Arena_Malloc(arena, buf_size);
  memcpy(buf, reinterpret_cast<const char*>(GRPC_SLICE_START_PTR(slice)),
         buf_size);
  
  // Parse the copied data into HandshakerResp message
  grpc_gcp_HandshakerResp* resp = grpc_gcp_HandshakerResp_parse(
      reinterpret_cast<char*>(buf), buf_size, arena);
  
  // Clean up resources
  grpc_core::CSliceUnref(slice);
  grpc_byte_buffer_reader_destroy(&bbr);
  
  // Validate parsing was successful
  if (resp == nullptr) {
    LOG(ERROR) << "grpc_gcp_handshaker_resp_decode() failed";
    return nullptr;
  }
  return resp;
}
```