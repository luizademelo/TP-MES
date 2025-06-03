Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

#include "src/core/lib/surface/validate_metadata.h"

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/util/bitset.h"

namespace grpc_core {

namespace {
// BitSet representing legal characters for HTTP/2 header keys
class LegalHeaderKeyBits : public BitSet<256> {
 public:
  // Constructor initializes the bitset with allowed characters:
  // - lowercase letters a-z
  // - digits 0-9
  // - special characters: '-', '_', '.'
  constexpr LegalHeaderKeyBits() {
    for (int i = 'a'; i <= 'z'; i++) set(i);
    for (int i = '0'; i <= '9'; i++) set(i);
    set('-');
    set('_');
    set('.');
  }
};
// Global constant containing legal header key characters
constexpr LegalHeaderKeyBits g_legal_header_key_bits;

// Checks if a string view conforms to the given bitset of legal characters
// Returns validation error if any character is invalid
ValidateMetadataResult ConformsTo(absl::string_view x,
                                  const BitSet<256>& legal_bits,
                                  ValidateMetadataResult error) {
  for (uint8_t c : x) {
    if (!legal_bits.is_set(c)) {
      return error;
    }
  }
  return ValidateMetadataResult::kOk;
}

// Converts a ValidateMetadataResult to an absl::Status
absl::Status UpgradeToStatus(ValidateMetadataResult result) {
  if (result == ValidateMetadataResult::kOk) return absl::OkStatus();
  return absl::InternalError(ValidateMetadataResultToString(result));
}

}  // namespace

// Validates a header key according to HTTP/2 specifications:
// - Cannot be empty
// - Length must be <= UINT32_MAX
// - Must only contain legal characters
ValidateMetadataResult ValidateHeaderKeyIsLegal(absl::string_view key) {
  if (key.empty()) {
    return ValidateMetadataResult::kCannotBeZeroLength;
  }
  if (key.size() > UINT32_MAX) {
    return ValidateMetadataResult::kTooLong;
  }
  return ConformsTo(key, g_legal_header_key_bits,
                    ValidateMetadataResult::kIllegalHeaderKey);
}

// Converts a ValidateMetadataResult enum to its string representation
const char* ValidateMetadataResultToString(ValidateMetadataResult result) {
  switch (result) {
    case ValidateMetadataResult::kOk:
      return "Ok";
    case ValidateMetadataResult::kCannotBeZeroLength:
      return "Metadata keys cannot be zero length";
    case ValidateMetadataResult::kTooLong:
      return "Metadata keys cannot be larger than UINT32_MAX";
    case ValidateMetadataResult::kIllegalHeaderKey:
      return "Illegal header key";
    case ValidateMetadataResult::kIllegalHeaderValue:
      return "Illegal header value";
  }
  GPR_UNREACHABLE_CODE(return "Unknown");
}

}  // namespace grpc_core

// Converts a grpc_error_handle to an integer (1 for OK, 0 for error)
static int error2int(grpc_error_handle error) {
  int r = (error.ok());
  return r;
}

// Validates a header key from a grpc_slice
grpc_error_handle grpc_validate_header_key_is_legal(const grpc_slice& slice) {
  return grpc_core::UpgradeToStatus(grpc_core::ValidateHeaderKeyIsLegal(
      grpc_core::StringViewFromSlice(slice)));
}

// Validates header key and returns result as integer (1 for valid, 0 for invalid)
int grpc_header_key_is_legal(grpc_slice slice) {
  return error2int(grpc_validate_header_key_is_legal(slice));
}

namespace {
// BitSet representing legal characters for non-binary header values
// Allows printable ASCII characters (32-126)
class LegalHeaderNonBinValueBits : public grpc_core::BitSet<256> {
 public:
  constexpr LegalHeaderNonBinValueBits() {
    for (int i = 32; i <= 126; i++) {
      set(i);
    }
  }
};
// Global constant containing legal non-binary header value characters
constexpr LegalHeaderNonBinValueBits g_legal_header_non_bin_value_bits;
}  // namespace

// Validates a non-binary header value from a grpc_slice
grpc_error_handle grpc_validate_header_nonbin_value_is_legal(
    const grpc_slice& slice) {
  return grpc_core::UpgradeToStatus(grpc_core::ConformsTo(
      grpc_core::StringViewFromSlice(slice), g_legal_header_non_bin_value_bits,
      grpc_core::ValidateMetadataResult::kIllegalHeaderValue));
}

// Validates non-binary header value and returns result as integer (1 for valid, 0 for invalid)
int grpc_header_nonbin_value_is_legal(grpc_slice slice) {
  return error2int(grpc_validate_header_nonbin_value_is_legal(slice));
}

// Internal function to check if a header is binary
int grpc_is_binary_header_internal(const grpc_slice& slice) {
  return grpc_key_is_binary_header(GRPC_SLICE_START_PTR(slice),
                                   GRPC_SLICE_LENGTH(slice));
}

// Public interface to check if a header is binary
int grpc_is_binary_header(grpc_slice slice) {
  return grpc_is_binary_header_internal(slice);
}
```