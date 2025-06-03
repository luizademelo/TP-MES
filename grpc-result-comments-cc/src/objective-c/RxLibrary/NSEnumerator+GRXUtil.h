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

#import <Foundation/Foundation.h>

/**
 * Category extension for NSEnumerator providing gRPC utility methods.
 * These methods create enumerators for different types of data sources.
 */
@interface NSEnumerator (GRXUtil)

/**
 * Creates and returns an enumerator that enumerates over the elements of the specified container.
 *
 * @param container An object conforming to NSFastEnumeration protocol (like NSArray, NSSet, etc.)
 * @return An enumerator object for the container's elements.
 */
+ (NSEnumerator *)grx_enumeratorWithContainer:(id<NSFastEnumeration>)container;

/**
 * Creates and returns an enumerator that enumerates a single value.
 * Useful for creating enumerators from single objects.
 *
 * @param value The single value to be enumerated.
 * @return An enumerator object that will enumerate the single value.
 */
+ (NSEnumerator *)grx_enumeratorWithSingleValue:(id)value;

/**
 * Creates and returns an enumerator that gets its values from the supplied block.
 * The block will be called each time the next object is requested from the enumerator.
 * When the block returns nil, enumeration ends.
 *
 * @param block A block that supplies values one at a time.
 * @return An enumerator object that uses the block to generate values.
 */
+ (NSEnumerator *)grx_enumeratorWithValueSupplier:(id (^)(void))block;

@end
```

The comments I've added:
1. Added a category description explaining its purpose
2. For each method:
   - Added a description of what the method does
   - Documented parameters with @param tags
   - Documented return values with @return tags
   - Explained special behaviors (like the nil-termination for the block-based enumerator)
   - Clarified expected input types where relevant

The comments follow standard Objective-C documentation conventions and provide clear explanations of each method's purpose and usage.