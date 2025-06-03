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

// Import UIKit framework which provides required iOS UI classes and functionalities
#import <UIKit/UIKit.h>

/**
 * AppDelegate interface declaration.
 * Serves as the main entry point for the application and handles application-level events.
 * Conforms to UIApplicationDelegate protocol which defines methods for managing app behavior.
 */
@interface AppDelegate : UIResponder <UIApplicationDelegate>

// Strong reference to the application's main window
// The window property is required for iOS apps to display content
@property(strong, nonatomic) UIWindow* window;

@end
```

The comments added explain:
1. The purpose of the UIKit import
2. The role of the AppDelegate class and its relationship to UIApplicationDelegate
3. The significance of the window property in an iOS application

The original copyright notice and license information has been preserved as it's important legal information that shouldn't be modified.