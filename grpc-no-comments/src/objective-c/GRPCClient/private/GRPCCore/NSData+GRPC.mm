
/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#import "NSData+GRPC.h"

#include <grpc/byte_buffer.h>
#include <grpc/byte_buffer_reader.h>
#include <string.h>

static void MallocAndCopyByteBufferToCharArray(grpc_byte_buffer *buffer, size_t *length,
                                               char **array) {
  grpc_byte_buffer_reader reader;
  if (!grpc_byte_buffer_reader_init(&reader, buffer)) {

    *array = NULL;
    *length = 0;
    return;
  }

  grpc_slice slice = grpc_byte_buffer_reader_readall(&reader);
  size_t uncompressed_length = GRPC_SLICE_LENGTH(slice);
  char *result = (char *)malloc(uncompressed_length);
  if (result) {
    memcpy(result, GRPC_SLICE_START_PTR(slice), uncompressed_length);
  }
  grpc_slice_unref(slice);
  *array = result;
  *length = uncompressed_length;

  grpc_byte_buffer_reader_destroy(&reader);
}

static grpc_byte_buffer *CopyCharArrayToNewByteBuffer(const char *array, size_t length) {
  grpc_slice slice = grpc_slice_from_copied_buffer(array, length);
  grpc_byte_buffer *buffer = grpc_raw_byte_buffer_create(&slice, 1);
  grpc_slice_unref(slice);
  return buffer;
}

@implementation NSData (GRPC)
+ (instancetype)grpc_dataWithByteBuffer:(grpc_byte_buffer *)buffer {
  if (buffer == NULL) {
    return nil;
  }
  char *array;
  size_t length;
  MallocAndCopyByteBufferToCharArray(buffer, &length, &array);
  if (!array) {

    return nil;
  }

  NSUInteger length_max = MIN(length, UINT_MAX);
  return [self dataWithBytesNoCopy:array length:length_max freeWhenDone:YES];
}

- (grpc_byte_buffer *)grpc_byteBuffer {

  return CopyCharArrayToNewByteBuffer((const char *)self.bytes, (size_t)self.length);
}
@end
