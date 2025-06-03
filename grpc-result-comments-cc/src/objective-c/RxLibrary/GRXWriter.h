Here's the commented version of the code:

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

// Import Foundation framework for basic Objective-C functionality
#import <Foundation/Foundation.h>

// Import the GRXWriteable protocol which defines the writeable interface
#import "GRXWriteable.h"

// Enumeration defining the possible states of a GRXWriter
typedef NS_ENUM(NSInteger, GRXWriterState) {
  // Writer has been created but not started yet
  GRXWriterStateNotStarted,
  
  // Writer has started and may be actively writing values
  GRXWriterStateStarted,
  
  // Writer has been paused temporarily
  GRXWriterStatePaused,
  
  // Writer has finished either successfully or with an error
  GRXWriterStateFinished
};

/**
 * GRXWriter is an abstract base class for objects that produce a sequence of values.
 * The values are consumed by an object conforming to the GRXWriteable protocol.
 */
@interface GRXWriter : NSObject

// The current state of the writer
@property GRXWriterState state;

/**
 * Starts the writer with the provided writeable object that will receive the values.
 * @param writeable An object conforming to GRXWriteable protocol that will consume the values.
 */
- (void)startWithWriteable:(id<GRXWriteable>)writeable;

/**
 * Signals the writer to finish its operation, optionally with an error.
 * @param errorOrNil If non-nil, indicates that the writer finished due to an error.
 *                   If nil, indicates successful completion.
 */
- (void)finishWithError:(NSError *)errorOrNil;

@end
```

The comments I've added:
1. Explained the purpose of each import statement
2. Documented each state in the GRXWriterState enumeration
3. Added a class-level comment explaining GRXWriter's role
4. Documented the state property
5. Added detailed method documentation including parameter descriptions
6. Used appropriate comment styles (single-line, multi-line, and documentation comments)

The comments provide clear explanations of the code's purpose and functionality while maintaining readability and following common Objective-C documentation conventions.