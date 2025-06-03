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

// Import Foundation framework for basic Objective-C classes and functionality
#import <Foundation/Foundation.h>

/**
 * GRXNSBlockEnumerator is a custom NSEnumerator subclass that generates values using a block.
 * This allows for lazy evaluation of values in a sequence, where each value is produced
 * on-demand by the supplied block.
 *
 * This is particularly useful for implementing lazy sequences or streams where values
 * should only be computed when needed.
 */
@interface GRXNSBlockEnumerator : NSEnumerator

/**
 * Initializes the enumerator with a block that supplies values.
 *
 * @param block A block that returns the next value in the sequence each time it's called.
 *              When there are no more values to return, the block should return nil.
 * @return An initialized GRXNSBlockEnumerator instance.
 */
- (instancetype)initWithValueSupplier:(id (^)(void))block;

@end
```

Key points about the comments:
1. Added a class description explaining the purpose of GRXNSBlockEnumerator
2. Documented the initialization method with parameter and return value descriptions
3. Explained the behavior expected from the value supplier block
4. Maintained the original copyright and license header
5. Kept the code structure identical while adding documentation

The comments now provide clear guidance for developers who might need to use or maintain this class in the future.