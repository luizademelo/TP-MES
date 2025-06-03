Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// This file implements fake transport security functionality for testing purposes.
// It provides implementations for fake handshakers, frame protectors, and zero-copy protectors.

#include "src/core/tsi/fake_transport_security.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <stdlib.h>
#include <string.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/tsi/transport_security_grpc.h"
#include "src/core/tsi/transport_security_interface.h"
#include "src/core/util/crash.h"
#include "src/core/util/memory.h"

// Constants for frame sizes and buffers
#define TSI_FAKE_FRAME_HEADER_SIZE 4  // Size of frame header in bytes
#define TSI_FAKE_FRAME_INITIAL_ALLOCATED_SIZE 64  // Initial allocated size for frames
#define TSI_FAKE_DEFAULT_FRAME_SIZE 16384  // Default maximum frame size
#define TSI_FAKE_HANDSHAKER_OUTGOING_BUFFER_INITIAL_SIZE 256  // Initial buffer size for handshaker

// Structure representing a fake frame
struct tsi_fake_frame {
  unsigned char* data;        // Frame data
  size_t size;                // Total frame size (including header)
  size_t allocated_size;      // Allocated memory size
  size_t offset;              // Current read/write offset
  int needs_draining;         // Flag indicating if frame needs to be drained
};

// Enum for fake handshake messages
typedef enum {
  TSI_FAKE_CLIENT_INIT = 0,    // Client initial message
  TSI_FAKE_SERVER_INIT = 1,    // Server initial message
  TSI_FAKE_CLIENT_FINISHED = 2, // Client finished message
  TSI_FAKE_SERVER_FINISHED = 3, // Server finished message
  TSI_FAKE_HANDSHAKE_MESSAGE_MAX = 4 // Maximum number of messages
} tsi_fake_handshake_message;

// Structure representing a fake handshaker
struct tsi_fake_handshaker {
  tsi_handshaker base;                     // Base handshaker structure
  int is_client;                           // Flag indicating if this is a client
  tsi_fake_handshake_message next_message_to_send; // Next message to send
  int needs_incoming_message;              // Flag indicating if expecting incoming message
  tsi_fake_frame incoming_frame;           // Incoming frame buffer
  tsi_fake_frame outgoing_frame;           // Outgoing frame buffer
  unsigned char* outgoing_bytes_buffer;     // Buffer for outgoing bytes
  size_t outgoing_bytes_buffer_size;       // Size of outgoing buffer
  tsi_result result;                       // Current handshake result
};

// Structure representing a fake frame protector
struct tsi_fake_frame_protector {
  tsi_frame_protector base;    // Base frame protector structure
  tsi_fake_frame protect_frame;   // Frame for protecting data
  tsi_fake_frame unprotect_frame; // Frame for unprotecting data
  size_t max_frame_size;       // Maximum frame size
};

// Structure representing a fake zero-copy protector
struct tsi_fake_zero_copy_grpc_protector {
  tsi_zero_copy_grpc_protector base; // Base zero-copy protector structure
  grpc_slice_buffer header_sb;       // Slice buffer for frame headers
  grpc_slice_buffer protected_sb;    // Slice buffer for protected data
  size_t max_frame_size;             // Maximum frame size
  size_t parsed_frame_size;          // Size of currently parsed frame
};

// Array of handshake message strings
static const char* tsi_fake_handshake_message_strings[] = {
    "CLIENT_INIT", "SERVER_INIT", "CLIENT_FINISHED", "SERVER_FINISHED"};

// Converts handshake message enum to string
static const char* tsi_fake_handshake_message_to_string(int msg) {
  if (msg < 0 || msg >= TSI_FAKE_HANDSHAKE_MESSAGE_MAX) {
    LOG(ERROR) << "Invalid message " << msg;
    return "UNKNOWN";
  }
  return tsi_fake_handshake_message_strings[msg];
}

// Converts handshake message string to enum
static tsi_result tsi_fake_handshake_message_from_string(
    const char* msg_string, tsi_fake_handshake_message* msg,
    std::string* error) {
  for (int i = 0; i < TSI_FAKE_HANDSHAKE_MESSAGE_MAX; i++) {
    if (strncmp(msg_string, tsi_fake_handshake_message_strings[i],
                strlen(tsi_fake_handshake_message_strings[i])) == 0) {
      *msg = static_cast<tsi_fake_handshake_message>(i);
      return TSI_OK;
    }
  }
  LOG(ERROR) << "Invalid handshake message.";
  if (error != nullptr) *error = "invalid handshake message";
  return TSI_DATA_CORRUPTED;
}

// Loads a 32-bit value in little-endian format
static uint32_t load32_little_endian(const unsigned char* buf) {
  return (static_cast<uint32_t>(buf[0]) | static_cast<uint32_t>(buf[1] << 8) |
          static_cast<uint32_t>(buf[2] << 16) |
          static_cast<uint32_t>(buf[3] << 24));
}

// Stores a 32-bit value in little-endian format
static void store32_little_endian(uint32_t value, unsigned char* buf) {
  buf[3] = static_cast<unsigned char>((value >> 24) & 0xFF);
  buf[2] = static_cast<unsigned char>((value >> 16) & 0xFF);
  buf[1] = static_cast<unsigned char>((value >> 8) & 0xFF);
  buf[0] = static_cast<unsigned char>((value) & 0xFF);
}

// Reads frame size from slice buffer
static uint32_t read_frame_size(const grpc_slice_buffer* sb) {
  CHECK(sb != nullptr);
  CHECK(sb->length >= TSI_FAKE_FRAME_HEADER_SIZE);
  uint8_t frame_size_buffer[TSI_FAKE_FRAME_HEADER_SIZE];
  uint8_t* buf = frame_size_buffer;

  // Copy frame header bytes from slice buffer
  size_t remaining = TSI_FAKE_FRAME_HEADER_SIZE;
  for (size_t i = 0; i < sb->count; i++) {
    size_t slice_length = GRPC_SLICE_LENGTH(sb->slices[i]);
    if (remaining <= slice_length) {
      memcpy(buf, GRPC_SLICE_START_PTR(sb->slices[i]), remaining);
      remaining = 0;
      break;
    } else {
      memcpy(buf, GRPC_SLICE_START_PTR(sb->slices[i]), slice_length);
      buf += slice_length;
      remaining -= slice_length;
    }
  }
  CHECK_EQ(remaining, 0u);
  return load32_little_endian(frame_size_buffer);
}

// Returns the size of the next frame in protected slices
uint32_t tsi_fake_zero_copy_grpc_protector_next_frame_size(
    const grpc_slice_buffer* protected_slices) {
  return read_frame_size(protected_slices);
}

// Resets a frame structure
static void tsi_fake_frame_reset(tsi_fake_frame* frame, int needs_draining) {
  frame->offset = 0;
  frame->needs_draining = needs_draining;
  if (!needs_draining) frame->size = 0;
}

// Ensures frame has enough allocated memory
static void tsi_fake_frame_ensure_size(tsi_fake_frame* frame) {
  if (frame->data == nullptr) {
    frame->allocated_size = frame->size;
    frame->data =
        static_cast<unsigned char*>(gpr_malloc(frame->allocated_size));
  } else if (frame->size > frame->allocated_size) {
    unsigned char* new_data =
        static_cast<unsigned char*>(gpr_realloc(frame->data, frame->size));
    frame->data = new_data;
    frame->allocated_size = frame->size;
  }
}

// Decodes data into a frame
static tsi_result tsi_fake_frame_decode(const unsigned char* incoming_bytes,
                                        size_t* incoming_bytes_size,
                                        tsi_fake_frame* frame,
                                        std::string* error) {
  size_t available_size = *incoming_bytes_size;
  size_t to_read_size = 0;
  const unsigned char* bytes_cursor = incoming_bytes;

  if (frame->needs_draining) {
    if (error != nullptr) *error = "fake handshaker frame needs draining";
    return TSI_INTERNAL_ERROR;
  }
  if (frame->data == nullptr) {
    // Initialize frame data buffer
    frame->allocated_size = TSI_FAKE_FRAME_INITIAL_ALLOCATED_SIZE;
    frame->data =
        static_cast<unsigned char*>(gpr_malloc(frame->allocated_size));
    memset(frame->data, 0xab, frame->allocated_size);
  }

  // Read frame header if not complete yet
  if (frame->offset < TSI_FAKE_FRAME_HEADER_SIZE) {
    to_read_size = TSI_FAKE_FRAME_HEADER_SIZE - frame->offset;
    if (to_read_size > available_size) {
      // Not enough data for header
      memcpy(frame->data + frame->offset, bytes_cursor, available_size);
      bytes_cursor += available_size;
      frame->offset += available_size;
      *incoming_bytes_size = static_cast<size_t>(bytes_cursor - incoming_bytes);
      return TSI_INCOMPLETE_DATA;
    }
    // Read complete header
    memcpy(frame->data + frame->offset, bytes_cursor, to_read_size);
    bytes_cursor += to_read_size;
    frame->offset += to_read_size;
    available_size -= to_read_size;
    frame->size = load32_little_endian(frame->data);
    // Validate frame size
    if (frame->size < 4) return TSI_DATA_CORRUPTED;
    if (frame->size > 16 * 1024 * 1024) return TSI_DATA_CORRUPTED;
    tsi_fake_frame_ensure_size(frame);
  }

  // Read frame payload
  to_read_size = frame->size - frame->offset;
  if (to_read_size > available_size) {
    // Not enough data for complete payload
    memcpy(frame->data + frame->offset, bytes_cursor, available_size);
    frame->offset += available_size;
    bytes_cursor += available_size;
    *incoming_bytes_size = static_cast<size_t>(bytes_cursor - incoming_bytes);
    return TSI_INCOMPLETE_DATA;
  }
  // Read complete payload
  memcpy(frame->data + frame->offset, bytes_cursor, to_read_size);
  bytes_cursor += to_read_size;
  *incoming_bytes_size = static_cast<size_t>(bytes_cursor - incoming_bytes);
  tsi_fake_frame_reset(frame, 1 /* needs_draining */);
  return TSI_OK;
}

// Encodes frame data into bytes
static tsi_result tsi_fake_frame_encode(unsigned char* outgoing_bytes,
                                        size_t* outgoing_bytes_size,
                                        tsi_fake_frame* frame,
                                        std::string* error) {
  size_t to_write_size = frame->size - frame->offset;
  if (!frame->needs_draining) {
    if (error != nullptr) *error = "fake frame needs draining";
    return TSI_INTERNAL_ERROR;
  }
  if (*outgoing_bytes_size < to_write_size) {
    // Not enough space to write complete frame
    memcpy(outgoing_bytes, frame->data + frame->offset, *outgoing_bytes_size);
    frame->offset += *outgoing_bytes_size;
    return TSI_INCOMPLETE_DATA;
  }
  // Write complete frame
  memcpy(outgoing_bytes, frame->data + frame->offset, to_write_size);
  *outgoing_bytes_size = to_write_size;
  tsi_fake_frame_reset(frame, 0 /* needs_draining */);
  return TSI_OK;
}

// Sets frame data
static void tsi_fake_frame_set_data(unsigned char* data, size_t data_size,
                                    tsi_fake_frame* frame) {
  frame->offset = 0;
  frame->size = data_size + TSI_FAKE_FRAME_HEADER_SIZE;
  tsi_fake_frame_ensure_size(frame);
  store32_little_endian(static_cast<uint32_t>(frame->size), frame->data);
  memcpy(frame->data + TSI_FAKE_FRAME_HEADER_SIZE, data, data_size);
  tsi_fake_frame_reset(frame, 1 /* needs_draining */);
}

// Destroys frame resources
static void tsi_fake_frame_destruct(tsi_fake_frame* frame) {
  if (frame->data != nullptr) gpr_free(frame->data);
}

// Protects data by framing it
static tsi_result fake_protector_protect(tsi_frame_protector* self,
                                         const unsigned char* unprotected_bytes,
                                         size_t* unprotected_bytes_size,
                                         unsigned char* protected_output_frames,
                                         size_t* protected_output_frames_size) {
  tsi_result result = TSI_OK;
  tsi_fake_frame_protector* impl =
      reinterpret_cast<tsi_fake_frame_protector*>(self);
  unsigned char frame_header[TSI_FAKE_FRAME_HEADER_SIZE];
  tsi_fake_frame* frame = &impl->protect_frame;
  size_t saved_output_size = *protected_output_frames_size;
  size_t drained_size = 0;
  size_t* num_bytes_written = protected_output_frames_size;
  *num_bytes_written = 0;

  // Drain any pending data first
  if (frame->needs_draining) {
    drained_size = saved_output_size - *num_bytes_written;
    result = tsi_fake_frame_encode(protected_output_frames, &drained_size,
                                   frame, nullptr);
    *num_bytes_written += drained_size;
    protected_output_frames += drained_size;
    if (result != TSI_OK) {
      if (result == TSI_INCOMPLETE_DATA) {
        *unprotected_bytes_size = 0;
        result = TSI_OK;
      }
      return result;
    }
  }

  if (frame->needs_draining) return TSI_INTERNAL_ERROR;
  
  // Initialize frame if empty
  if (frame->size == 0) {
    size_t written_in_frame_size = 0;
    store32_little_endian(static_cast<uint32_t>(impl->max_frame_size),
                          frame_header);
    written_in_frame_size = TSI_FAKE_FRAME_HEADER_SIZE;
    result = tsi_fake_frame_decode(frame_header, &written_in_frame_size, frame,
                                   nullptr);
    if (result != TSI_INCOMPLETE_DATA) {
      LOG(ERROR) << "tsi_fake_frame_decode returned "
                 << tsi_result_to_string(result);
      return result;
    }
  }
  
  // Process unprotected bytes
  result =
      tsi_fake_frame_decode(unprotected_bytes, unprotected_bytes_size, frame,
                            nullptr);
  if (result != TSI_OK) {
    if (result == TSI_INCOMPLETE_DATA) result = TSI_OK;
    return result;
  }

  if (!frame->needs_draining) return TSI_INTERNAL_ERROR;
  if (frame->offset != 0) return TSI_INTERNAL_ERROR;
  
  // Drain the processed frame
  drained_size = saved_output_size - *num_bytes_written;
  result = tsi_fake_frame_encode(protected_output_frames, &drained_size, frame,
                                 nullptr);
  *num_bytes_written += drained_size;
  if (result == TSI_INCOMPLETE_DATA) result = TSI_OK;
  return result;
}

// Flushes any remaining protected data
static tsi_result fake_protector_protect_flush(
    tsi_frame_protector* self, unsigned char* protected_output_frames,
    size_t* protected_output_frames_size, size_t* still_pending_size) {
  tsi_result result = TSI_OK;
  tsi_fake_frame_protector* impl =
      reinterpret_cast<tsi_fake_frame_protector*>(self);
  tsi_fake_frame* frame = &impl->protect_frame;
  
  // Prepare any pending data for draining
  if (!frame->needs_draining) {
    frame->size = frame->offset;
    frame->offset = 0;
    frame->needs_draining = 1;
    store32_little_endian(static_cast<uint32_t>(frame->size),
                          frame->data);
  }
  
  // Drain the frame
  result = tsi_fake_frame_encode(protected_output_frames,
                                 protected_output_frames_size, frame,
                                 nullptr);
  if (result == TSI_INCOMPLETE_DATA) result = TSI_OK;
  *still_pending_size = frame->size - frame->offset;
  return result;
}

// Unprotects framed data
static tsi_result fake_protector_unprotect(
    tsi_frame_protector* self, const unsigned char* protected_frames_bytes,
    size_t* protected_frames_bytes_size, unsigned char* unprotected_bytes,
    size_t* unprotected_bytes_size) {
  tsi_result result = TSI_OK;
  tsi_fake_frame_protector* impl =
      reinterpret_cast<tsi_fake_frame_protector*>(self);
  tsi_fake_frame* frame = &impl->unprotect_frame;
  size_t saved_output_size = *unprotected_bytes_size;
  size_t drained_size = 0;
  size_t* num_bytes_written = unprotected_bytes_size;
  *num_bytes_written = 0;

  // Drain any pending data first
  if (frame->needs_draining) {