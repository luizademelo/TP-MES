Here's the commented version of the code:

```c++
/*
 * Copyright 2019 gRPC authors.
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

// Import UIKit framework which provides required classes for iOS app development
#import <UIKit/UIKit.h>

// AppDelegate interface declaration
// The AppDelegate is the entry point of the application and handles application-level events
// It inherits from UIResponder and conforms to the UIApplicationDelegate protocol
@interface AppDelegate : UIResponder <UIApplicationDelegate>

// Main window property for the application
// This is a strong reference to the UIWindow instance that will contain the app's visual content
// The window property is typically set up in the application:didFinishLaunchingWithOptions: method
@property(strong, nonatomic) UIWindow* window;

@end
```

The comments added explain:
1. The purpose of the UIKit import
2. The role of the AppDelegate class in an iOS application
3. The inheritance and protocol connotation
4. The purpose and typical usage of the window property

The original license header has been preserved without modification.