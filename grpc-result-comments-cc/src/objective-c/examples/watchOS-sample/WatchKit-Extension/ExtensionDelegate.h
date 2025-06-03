Here's the commented version of the code snippet:

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

// Import WatchKit framework which provides the essential classes for WatchOS apps
#import <WatchKit/WatchKit.h>

// Interface declaration for the ExtensionDelegate class
// This class serves as the main delegate for the WatchOS extension
// It conforms to the WKExtensionDelegate protocol which provides
// lifecycle event handlers for the WatchOS app extension
@interface ExtensionDelegate : NSObject <WKExtensionDelegate>

@end
```

The comments added explain:
1. The purpose of the WatchKit import
2. The role of the ExtensionDelegate class
3. The significance of conforming to WKExtensionDelegate protocol
4. The general context of this being for a WatchOS app extension

The original license header has been preserved as it's important legal information that shouldn't be modified.