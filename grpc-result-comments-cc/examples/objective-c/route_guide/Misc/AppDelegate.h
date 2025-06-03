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

// Import UIKit framework which provides required classes for iOS app development
#import <UIKit/UIKit.h>

// AppDelegate interface declaration
// The AppDelegate is the root object of the application and handles important app lifecycle events
// It inherits from UIResponder and conforms to the UIApplicationDelegate protocol
@interface AppDelegate : UIResponder <UIApplicationDelegate>

// Main window property for the application
// This window acts as a container for all the app's visible content
// The 'strong' attribute indicates the property maintains a strong reference to the UIWindow object
// The 'nonatomic' attribute specifies that the property is not thread-safe (but faster for single-threaded use)
@property (strong, nonatomic) UIWindow *window;

@end
```

The comments added explain:
1. The purpose of the UIKit import
2. The role of the AppDelegate class in iOS applications
3. The inheritance and protocol conformance
4. The purpose and attributes of the window property
5. The meaning of the property attributes (strong, nonatomic)