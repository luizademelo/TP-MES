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

// Import UIKit framework which provides essential infrastructure for iOS apps
#import <UIKit/UIKit.h>

// Declaration of a constant string to be used as a test scope
// This is likely used for authentication or API scope purposes
extern NSString * const kTestScope;

// Interface declaration for MakeRPCViewController which inherits from UIViewController
// This view controller appears to be related to making RPC (Remote Procedure Call) operations
@interface MakeRPCViewController : UIViewController

// IBOutlet property for the main label in the view
// The 'weak' qualifier is used to avoid retain cycles as the parent view maintains a strong reference
// This is connected to a UILabel in the Interface Builder (hence IBOutlet)
@property(weak, nonatomic) IBOutlet UILabel *mainLabel;

@end
```

The comments explain:
1. The purpose of the UIKit import
2. The likely use of the kTestScope constant
3. The overall purpose of the MakeRPCViewController class
4. The connection between the IBOutlet property and Interface Builder
5. The reason for using 'weak' reference for the UILabel property

The comments are placed to provide context and understanding without being overly verbose, making it easier for future developers to understand and maintain the code.