Here's the commented version of the code:

```c++
/*
 *
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
 *
 */

// Import UIKit framework which provides fundamental iOS infrastructure
// and UI components
#import <UIKit/UIKit.h>

// AppDelegate interface declaration
// The AppDelegate is the root object of the application and handles
// important application lifecycle events
@interface AppDelegate : UIResponder <UIApplicationDelegate>

// Strong reference to the application's main window
// The window property holds the root window of the application's UI
// It must be retained (strong) as it's fundamental to the app's display
@property(strong, nonatomic) UIWindow* window;

@end
```

The comments explain:
1. The purpose of the UIKit import
2. The role of the AppDelegate class in iOS applications
3. The significance of the window property and why it needs to be strong
4. The relationship between the AppDelegate and UIApplicationDelegate protocol

The comments are kept concise while providing essential context for future maintainers of the code.