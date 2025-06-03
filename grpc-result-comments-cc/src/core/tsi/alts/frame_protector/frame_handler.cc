Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#include "src/core/tsi/alts/frame_protector/frame_handler.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>

#include <algorithm>

#include "absl/log/log.h"
#include "src/core/util/crash.h"
#include "src/core/util/memory.h"

/**
 * Loads a 32-bit unsigned integer from a little-endian byte buffer.
 * @param buffer The input byte buffer (must have at least 4 bytes)
 * @return The loaded 32-bit value in host byte order
 */
static uint32_t load_32_le(const unsigned char* buffer) {
  return (static_cast<uint32_t>(buffer[3]) << 24) |
         (static_cast<uint32_t>(buffer[2]) << 16) |
         (static_cast<uint32_t>(buffer[1]) << 8) |
         static_cast<uint32_t>(buffer[0]);
}

/**
 * Stores a 32-bit unsigned integer in little-endian format into a byte buffer.
 * @param value The 32-bit value to store
 * @param buffer The output byte buffer (must have at least 4 bytes space)
 */
static void store_32_le(uint32_t value, unsigned char* buffer) {
  buffer[3] = static_cast<unsigned char>(value >> 24) & 0xFF;
  buffer[2] = static_cast<unsigned char>(value >> 16) & 0xFF;
  buffer[1] = static_cast<unsigned char>(value >> 8) & 0xFF;
  buffer[0] = static_cast<unsigned char>(value) & 0xFF;
}

/**
 * Creates and initializes a new frame writer.
 * @return Pointer to the newly allocated frame writer
 */
alts_frame_writer* alts_create_frame_writer() {
  return grpc_core::Zalloc<alts_frame_writer>();
}

/**
 * Resets the frame writer with new input data.
 * @param writer The frame writer to reset
 * @param buffer The input data buffer
 * @param length The length of input data
 * @return true if reset was successful, false otherwise
 */
bool alts_reset_frame_writer(alts_frame_writer* writer,
                             const unsigned char* buffer, size_t length) {
  if (buffer == nullptr) return false;
  size_t max_input_size = SIZE_MAX - kFrameLengthFieldSize;
  if (length > max_input_size) {
    LOG(ERROR) << "length must be at most " << max_input_size;
    return false;
  }
  writer->input_buffer = buffer;
  writer->input_size = length;
  writer->input_bytes_written = 0;
  writer->header_bytes_written = 0;
  // Store frame length (data length + message type field size) in header
  store_32_le(
      static_cast<uint32_t>(writer->input_size + kFrameMessageTypeFieldSize),
      writer->header_buffer);
  // Store message type in header
  store_32_le(kFrameMessageType, writer->header_buffer + kFrameLengthFieldSize);
  return true;
}

/**
 * Writes frame bytes to the output buffer.
 * @param writer The frame writer
 * @param output The output buffer to write to
 * @param bytes_size [in/out] Input: size of output buffer, Output: bytes written
 * @return true if operation succeeded, false otherwise
 */
bool alts_write_frame_bytes(alts_frame_writer* writer, unsigned char* output,
                            size_t* bytes_size) {
  if (bytes_size == nullptr || output == nullptr) return false;
  if (alts_is_frame_writer_done(writer)) {
    *bytes_size = 0;
    return true;
  }
  size_t bytes_written = 0;

  // First write header bytes if not completed
  if (writer->header_bytes_written != sizeof(writer->header_buffer)) {
    size_t bytes_to_write =
        std::min(*bytes_size,
                 sizeof(writer->header_buffer) - writer->header_bytes_written);
    memcpy(output, writer->header_buffer + writer->header_bytes_written,
           bytes_to_write);
    bytes_written += bytes_to_write;
    *bytes_size -= bytes_to_write;
    writer->header_bytes_written += bytes_to_write;
    output += bytes_to_write;
    if (writer->header_bytes_written != sizeof(writer->header_buffer)) {
      *bytes_size = bytes_written;
      return true;
    }
  }

  // Then write payload bytes
  size_t bytes_to_write =
      std::min(writer->input_size - writer->input_bytes_written, *bytes_size);
  memcpy(output, writer->input_buffer, bytes_to_write);
  writer->input_buffer += bytes_to_write;
  bytes_written += bytes_to_write;
  writer->input_bytes_written += bytes_to_write;
  *bytes_size = bytes_written;
  return true;
}

/**
 * Checks if frame writer has completed writing all data.
 * @param writer The frame writer to check
 * @return true if writing is complete, false otherwise
 */
bool alts_is_frame_writer_done(alts_frame_writer* writer) {
  return writer->input_buffer == nullptr ||
         writer->input_size == writer->input_bytes_written;
}

/**
 * Gets the number of remaining bytes to be written by the frame writer.
 * @param writer The frame writer
 * @return Total remaining bytes (header + payload)
 */
size_t alts_get_num_writer_bytes_remaining(alts_frame_writer* writer) {
  return (sizeof(writer->header_buffer) - writer->header_bytes_written) +
         (writer->input_size - writer->input_bytes_written);
}

/**
 * Destroys and deallocates a frame writer.
 * @param writer The frame writer to destroy
 */
void alts_destroy_frame_writer(alts_frame_writer* writer) { gpr_free(writer); }

/**
 * Creates and initializes a new frame reader.
 * @return Pointer to the newly allocated frame reader
 */
alts_frame_reader* alts_create_frame_reader() {
  alts_frame_reader* reader = grpc_core::Zalloc<alts_frame_reader>();
  return reader;
}

/**
 * Checks if frame reader has completed reading all data.
 * @param reader The frame reader to check
 * @return true if reading is complete, false otherwise
 */
bool alts_is_frame_reader_done(alts_frame_reader* reader) {
  return reader->output_buffer == nullptr ||
         (reader->header_bytes_read == sizeof(reader->header_buffer) &&
          reader->bytes_remaining == 0);
}

/**
 * Checks if the frame reader has read the frame length.
 * @param reader The frame reader to check
 * @return true if frame length has been read, false otherwise
 */
bool alts_has_read_frame_length(alts_frame_reader* reader) {
  return sizeof(reader->header_buffer) == reader->header_bytes_read;
}

/**
 * Gets the number of remaining payload bytes to be read.
 * @param reader The frame reader
 * @return Remaining payload bytes (0 if frame length hasn't been read yet)
 */
size_t alts_get_reader_bytes_remaining(alts_frame_reader* reader) {
  return alts_has_read_frame_length(reader) ? reader->bytes_remaining : 0;
}

/**
 * Resets the output buffer of the frame reader.
 * @param reader The frame reader
 * @param buffer The new output buffer
 */
void alts_reset_reader_output_buffer(alts_frame_reader* reader,
                                     unsigned char* buffer) {
  reader->output_buffer = buffer;
}

/**
 * Resets the frame reader with a new output buffer.
 * @param reader The frame reader to reset
 * @param buffer The output buffer for storing read data
 * @return true if reset was successful, false otherwise
 */
bool alts_reset_frame_reader(alts_frame_reader* reader, unsigned char* buffer) {
  if (buffer == nullptr) return false;
  reader->output_buffer = buffer;
  reader->bytes_remaining = 0;
  reader->header_bytes_read = 0;
  reader->output_bytes_read = 0;
  return true;
}

/**
 * Reads frame bytes from input buffer and processes them.
 * @param reader The frame reader
 * @param bytes The input buffer containing frame data
 * @param bytes_size [in/out] Input: size of input buffer, Output: bytes processed
 * @return true if operation succeeded, false otherwise
 */
bool alts_read_frame_bytes(alts_frame_reader* reader,
                           const unsigned char* bytes, size_t* bytes_size) {
  if (bytes_size == nullptr) return false;
  if (bytes == nullptr) {
    *bytes_size = 0;
    return false;
  }
  if (alts_is_frame_reader_done(reader)) {
    *bytes_size = 0;
    return true;
  }
  size_t bytes_processed = 0;

  // First read header bytes if not completed
  if (reader->header_bytes_read != sizeof(reader->header_buffer)) {
    size_t bytes_to_write = std::min(
        *bytes_size, sizeof(reader->header_buffer) - reader->header_bytes_read);
    memcpy(reader->header_buffer + reader->header_bytes_read, bytes,
           bytes_to_write);
    reader->header_bytes_read += bytes_to_write;
    bytes_processed += bytes_to_write;
    bytes += bytes_to_write;
    *bytes_size -= bytes_to_write;
    if (reader->header_bytes_read != sizeof(reader->header_buffer)) {
      *bytes_size = bytes_processed;
      return true;
    }
    // Validate frame header once complete
    size_t frame_length = load_32_le(reader->header_buffer);
    if (frame_length < kFrameMessageTypeFieldSize ||
        frame_length > kFrameMaxSize) {
      LOG(ERROR) << "Bad frame length (should be at least "
                 << kFrameMessageTypeFieldSize << ", and at most "
                 << kFrameMaxSize << ")";
      *bytes_size = 0;
      return false;
    }
    size_t message_type =
        load_32_le(reader->header_buffer + kFrameLengthFieldSize);
    if (message_type != kFrameMessageType) {
      LOG(ERROR) << "Unsupported message type " << message_type
                 << " (should be " << kFrameMessageType << ")";
      *bytes_size = 0;
      return false;
    }
    reader->bytes_remaining = frame_length - kFrameMessageTypeFieldSize;
  }

  // Then read payload bytes
  size_t bytes_to_write = std::min(*bytes_size, reader->bytes_remaining);
  memcpy(reader->output_buffer, bytes, bytes_to_write);
  reader->output_buffer += bytes_to_write;
  bytes_processed += bytes_to_write;
  reader->bytes_remaining -= bytes_to_write;
  reader->output_bytes_read += bytes_to_write;
  *bytes_size = bytes_processed;
  return true;
}

/**
 * Gets the number of payload bytes read so far.
 * @param reader The frame reader
 * @return Number of payload bytes read
 */
size_t alts_get_output_bytes_read(alts_frame_reader* reader) {
  return reader->output_bytes_read;
}

/**
 * Gets the current output buffer position.
 * @param reader The frame reader
 * @return Pointer to current position in output buffer
 */
unsigned char* alts_get_output_buffer(alts_frame_reader* reader) {
  return reader->output_buffer;
}

/**
 * Destroys and deallocates a frame reader.
 * @param reader The frame reader to destroy
 */
void alts_destroy_frame_reader(alts_frame_reader* reader) { gpr_free(reader); }
```