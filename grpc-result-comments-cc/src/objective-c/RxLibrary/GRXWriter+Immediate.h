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

// Category extension for GRXWriter providing immediate writer creation methods
@interface GRXWriter (Immediate)

// Creates a writer that emits values from the provided enumerator
// @param enumerator NSEnumerator that will provide values
+ (instancetype)writerWithEnumerator:(NSEnumerator *)enumerator;

// Creates a writer that emits values from the provided block
// The block will be called repeatedly until it returns nil
// @param block Supplier block that provides values
+ (instancetype)writerWithValueSupplier:(id (^)(void))block;

// Creates a writer that emits all values from the container
// @param container Container implementing NSFastEnumeration protocol
+ (instancetype)writerWithContainer:(id<NSFastEnumeration>)container;

// Creates a writer that emits a single value
// @param value The single value to be emitted
+ (instancetype)writerWithValue:(id)value;

// Creates a writer that immediately fails with the given error
// @param error The error to be emitted
+ (instancetype)writerWithError:(NSError *)error;

// Creates a writer that immediately completes without emitting any values
+ (instancetype)emptyWriter;

@end
```

The comments added explain:
1. The purpose of the Immediate category extension
2. Each factory method's functionality
3. The parameters each method accepts
4. The behavior of each writer type being created

The comments follow Objective-C conventions and provide clear, concise explanations that would help future developers understand how to use these factory methods without needing to examine the implementation details.