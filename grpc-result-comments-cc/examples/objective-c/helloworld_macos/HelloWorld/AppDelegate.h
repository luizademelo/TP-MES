Here's the commented version of the code snippet:

```c++
/*
 *
 * Copyright 2018 gRPC authors.
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

// Import Cocoa framework which provides core functionality for macOS applications
#import <Cocoa/Cocoa.h>

// AppDelegate interface declaration
// This class serves as the application delegate, receiving application-level events
// NSObject is the root class of most Objective-C class hierarchies
// NSApplicationDelegate protocol defines methods for handling app lifecycle events
@interface AppDelegate : NSObject <NSApplicationDelegate>

// Note: Implementation would typically include methods like:
// - applicationDidFinishLaunching: (called after app finishes launching)
// - applicationWillTerminate: (called before app terminates)
// - applicationShouldTerminate: (called to determine if app should terminate)
// These would be defined in the corresponding .m implementation file

@end
```

The comments explain:
1. The purpose of the Cocoa framework import
2. The role of the AppDelegate class
3. The inheritance from NSObject
4. The conformance to NSApplicationDelegate protocol
5. Notes about typical methods that would be implemented (though not shown in this header file)

The original copyright notice and license information has been preserved as-is since it's legally required and shouldn't be modified.