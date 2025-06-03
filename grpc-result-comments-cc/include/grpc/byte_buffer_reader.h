Here's the commented version of the code:

```c++
/*
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
 */

#ifndef GRPC_BYTE_BUFFER_READER_H
#define GRPC_BYTE_BUFFER_READER_H

#include <grpc/support/port_platform.h>  // Platform-specific configuration

#ifdef __cplusplus
extern "C" {  // Ensures C linkage when included in C++ code
#endif

// Forward declaration of grpc_byte_buffer structure
struct grpc_byte_buffer;

/**
 * Structure for reading data from a grpc_byte_buffer.
 * Provides a way to sequentially read data from byte buffers.
 */
struct grpc_byte_buffer_reader {
  // The input buffer being read
  struct grpc_byte_buffer* buffer_in;
  
  // The output buffer (if any) where processed data might be stored
  struct grpc_byte_buffer* buffer_out;

  // Union for storing reader's current position/state
  // Currently only contains an index for tracking position,
  // but designed to be extensible for different buffer types
  union grpc_byte_buffer_reader_current {
    // Current position/index in the buffer
    unsigned index;
  } current;
};

#ifdef __cplusplus
}  // End of extern "C" block
#endif

#endif  // GRPC_BYTE_BUFFER_READER_H
```

Key additions in the comments:
1. Explained the purpose of the header file and its structures
2. Documented each field in the grpc_byte_buffer_reader structure
3. Added explanation for the union and its current implementation
4. Noted the purpose of the extern "C" block
5. Added comments for platform-specific includes
6. Maintained all original license information

The comments provide context about the structure's purpose and usage while maintaining the original code's functionality.