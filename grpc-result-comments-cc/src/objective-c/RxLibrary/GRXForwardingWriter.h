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

// Import the base GRXWriter class
#import "GRXWriter.h"

/**
 * GRXForwardingWriter is a concrete subclass of GRXWriter that forwards values,
 * errors, and completion events from another writer.
 *
 * This class implements the "Decorator" pattern, allowing additional behavior
 * to be added to a GRXWriter instance without modifying the original writer.
 */
@interface GRXForwardingWriter : GRXWriter

/**
 * Initializes a new forwarding writer that wraps the specified writer.
 *
 * @param writer The writer whose values, errors, and completion events will be
 *               forwarded by this instance.
 * @return An initialized forwarding writer.
 * @note This is the designated initializer for this class.
 */
- (instancetype)initWithWriter:(GRXWriter *)writer NS_DESIGNATED_INITIALIZER;

@end
```

The comments I've added:
1. Added a brief description of what GRXForwardingWriter is and its purpose
2. Explained the design pattern being used (Decorator pattern)
3. Documented the initWithWriter: method with parameter and return value descriptions
4. Noted that this is the designated initializer
5. Added a simple comment for the import statement

The comments follow standard Objective-C documentation style and provide clear explanations of both the class's purpose and its main method.