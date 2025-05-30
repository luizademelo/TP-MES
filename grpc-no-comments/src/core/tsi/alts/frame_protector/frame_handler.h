
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_ALTS_FRAME_PROTECTOR_FRAME_HANDLER_H
#define GRPC_SRC_CORE_TSI_ALTS_FRAME_PROTECTOR_FRAME_HANDLER_H

#include <grpc/support/port_platform.h>
#include <stdbool.h>
#include <stdlib.h>

const size_t kFrameMessageType = 0x06;
const size_t kFrameLengthFieldSize = 4;
const size_t kFrameMessageTypeFieldSize = 4;
const size_t kFrameMaxSize = 1024 * 1024;
const size_t kFrameHeaderSize =
    kFrameLengthFieldSize + kFrameMessageTypeFieldSize;

typedef struct alts_frame_writer {
  const unsigned char* input_buffer;
  unsigned char header_buffer[kFrameHeaderSize];
  size_t input_bytes_written;
  size_t header_bytes_written;
  size_t input_size;
} alts_frame_writer;

typedef struct alts_frame_reader {
  unsigned char* output_buffer;
  unsigned char header_buffer[kFrameHeaderSize];
  size_t header_bytes_read;
  size_t output_bytes_read;
  size_t bytes_remaining;
} alts_frame_reader;

alts_frame_writer* alts_create_frame_writer();

bool alts_reset_frame_writer(alts_frame_writer* writer,
                             const unsigned char* buffer, size_t length);

bool alts_write_frame_bytes(alts_frame_writer* writer, unsigned char* output,
                            size_t* bytes_size);

bool alts_is_frame_writer_done(alts_frame_writer* writer);

size_t alts_get_num_writer_bytes_remaining(alts_frame_writer* writer);

void alts_destroy_frame_writer(alts_frame_writer* writer);

alts_frame_reader* alts_create_frame_reader();

bool alts_reset_frame_reader(alts_frame_reader* reader, unsigned char* buffer);

bool alts_read_frame_bytes(alts_frame_reader* reader,
                           const unsigned char* bytes, size_t* bytes_size);

bool alts_has_read_frame_length(alts_frame_reader* reader);

size_t alts_get_reader_bytes_remaining(alts_frame_reader* reader);

void alts_reset_reader_output_buffer(alts_frame_reader* reader,
                                     unsigned char* buffer);

bool alts_is_frame_reader_done(alts_frame_reader* reader);

size_t alts_get_output_bytes_read(alts_frame_reader* reader);

unsigned char* alts_get_output_buffer(alts_frame_reader* reader);

void alts_destroy_frame_reader(alts_frame_reader* reader);

#endif
