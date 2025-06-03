Here's the commented version of the code snippet:

```c++
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

// Import the base GRXWriter interface
#import "GRXWriter.h"

// Category extending GRXWriter with transformation capabilities
@interface GRXWriter (Transformations)

/**
 * Returns a new GRXWriter that applies the given transformation block to each value.
 * @param map A block that takes an input value and returns a transformed output value.
 * @return A new GRXWriter instance that will emit transformed values.
 *
 * Usage example:
 *   GRXWriter *originalWriter = ...;
 *   GRXWriter *mappedWriter = [originalWriter map:^id(id value) {
 *       return [value stringByAppendingString:@"_suffix"];
 *   }];
 *
 * The transformation is applied lazily when the returned writer is started.
 */
- (GRXWriter *)map:(id (^)(id value))map;

@end
```

The comments added explain:
1. The purpose of the file (transformation capabilities for GRXWriter)
2. The map method's functionality and parameters
3. Includes an example usage
4. Notes about lazy evaluation behavior
5. Documents the return value

The comments follow Objective-C conventions and provide both high-level context and specific details about the method's behavior.