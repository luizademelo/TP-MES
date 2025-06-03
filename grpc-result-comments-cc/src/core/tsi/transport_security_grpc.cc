Here's the commented version of the code:

```c++
// Copyright 2017 gRPC authors.

#include "src/core/tsi/transport_security_grpc.h"
#include <grpc/support/port_platform.h>

/// Creates a zero-copy grpc protector object from a handshaker result.
/// @param self Pointer to the handshaker result instance
/// @param max_output_protected_frame_size Pointer to store maximum frame size
/// @param protector Output parameter for the created protector
/// @return TSI_OK on success, TSI_INVALID_ARGUMENT for null arguments,
///         or TSI_UNIMPLEMENTED if operation not supported by handshaker
tsi_result tsi_handshaker_result_create_zero_copy_grpc_protector(
    const tsi_handshaker_result* self, size_t* max_output_protected_frame_size,
    tsi_zero_copy_grpc_protector** protector) {
  // Validate input parameters
  if (self == nullptr || self->vtable == nullptr || protector == nullptr) {
    return TSI_INVALID_ARGUMENT;
  }
  // Check if the operation is supported by the handshaker implementation
  if (self->vtable->create_zero_copy_grpc_protector == nullptr) {
    return TSI_UNIMPLEMENTED;
  }
  // Delegate to the handshaker implementation's create method
  return self->vtable->create_zero_copy_grpc_protector(
      self, max_output_protected_frame_size, protector);
}

/// Protects data using the zero-copy protector.
/// @param self Pointer to the protector instance
/// @param unprotected_slices Buffer containing unprotected data
/// @param protected_slices Output buffer for protected data
/// @return TSI_OK on success, TSI_INVALID_ARGUMENT for null arguments,
///         or TSI_UNIMPLEMENTED if operation not supported
tsi_result tsi_zero_copy_grpc_protector_protect(
    tsi_zero_copy_grpc_protector* self, grpc_slice_buffer* unprotected_slices,
    grpc_slice_buffer* protected_slices) {
  // Validate input parameters
  if (self == nullptr || self->vtable == nullptr ||
      unprotected_slices == nullptr || protected_slices == nullptr) {
    return TSI_INVALID_ARGUMENT;
  }
  // Check if protect operation is supported
  if (self->vtable->protect == nullptr) return TSI_UNIMPLEMENTED;
  // Delegate to the implementation's protect method
  return self->vtable->protect(self, unprotected_slices, protected_slices);
}

/// Unprotects data using the zero-copy protector.
/// @param self Pointer to the protector instance
/// @param protected_slices Buffer containing protected data
/// @param unprotected_slices Output buffer for unprotected data
/// @param min_progress_size Optional output for minimum progress size
/// @return TSI_OK on success, TSI_INVALID_ARGUMENT for null arguments,
///         or TSI_UNIMPLEMENTED if operation not supported
tsi_result tsi_zero_copy_grpc_protector_unprotect(
    tsi_zero_copy_grpc_protector* self, grpc_slice_buffer* protected_slices,
    grpc_slice_buffer* unprotected_slices, int* min_progress_size) {
  // Validate input parameters
  if (self == nullptr || self->vtable == nullptr ||
      protected_slices == nullptr || unprotected_slices == nullptr) {
    return TSI_INVALID_ARGUMENT;
  }
  // Check if unprotect operation is supported
  if (self->vtable->unprotect == nullptr) return TSI_UNIMPLEMENTED;
  // Delegate to the implementation's unprotect method
  return self->vtable->unprotect(self, protected_slices, unprotected_slices,
                                 min_progress_size);
}

/// Destroys a zero-copy protector instance.
/// @param self Pointer to the protector instance to destroy
void tsi_zero_copy_grpc_protector_destroy(tsi_zero_copy_grpc_protector* self) {
  if (self == nullptr) return;
  // Delegate to the implementation's destroy method
  self->vtable->destroy(self);
}

/// Gets the maximum frame size supported by the protector.
/// @param self Pointer to the protector instance
/// @param max_frame_size Output parameter for maximum frame size
/// @return TSI_OK on success, TSI_INVALID_ARGUMENT for null arguments,
///         or TSI_UNIMPLEMENTED if operation not supported
tsi_result tsi_zero_copy_grpc_protector_max_frame_size(
    tsi_zero_copy_grpc_protector* self, size_t* max_frame_size) {
  // Validate input parameters
  if (self == nullptr || max_frame_size == nullptr) return TSI_INVALID_ARGUMENT;
  // Check if max frame size operation is supported
  if (self->vtable->max_frame_size == nullptr) return TSI_UNIMPLEMENTED;
  // Delegate to the implementation's max_frame_size method
  return self->vtable->max_frame_size(self, max_frame_size);
}
```

The comments provide:
1. A description of each function's purpose
2. Documentation of parameters
3. Return value explanations
4. Clear indication of null checks and validation
5. Explanation of vtable delegation pattern used throughout
6. Notes about unimplemented functionality cases

The comments follow a consistent style and provide enough information for future maintainers to understand both the interface contract and implementation details without being overly verbose.