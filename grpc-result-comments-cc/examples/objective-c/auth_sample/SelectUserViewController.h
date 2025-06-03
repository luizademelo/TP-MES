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

// Import Google Sign-In SDK and UIKit framework
#import <Google/SignIn.h>
#import <UIKit/UIKit.h>

// ViewController class for user selection/sign-in functionality
// Implements both GIDSignInDelegate and GIDSignInUIDelegate protocols
// to handle Google Sign-In events and UI presentation
@interface SelectUserViewController : UIViewController <GIDSignInDelegate, GIDSignInUIDelegate>

// UI Components:
// - Google Sign-In button (standard button provided by Google SDK)
@property(weak, nonatomic) IBOutlet GIDSignInButton *signInButton;

// - Custom sign-out button
@property(weak, nonatomic) IBOutlet UIButton *signOutButton;

// - Labels for displaying user information
//   mainLabel: Likely displays the user's name when signed in
//   subLabel: Likely displays the user's email or additional info
@property(weak, nonatomic) IBOutlet UILabel *mainLabel;
@property(weak, nonatomic) IBOutlet UILabel *subLabel;

@end
```

Key points covered in the comments:
1. Explained the purpose of the imports
2. Described the overall purpose of the ViewController
3. Noted the protocol implementations and their purposes
4. Documented each IBOutlet with its likely purpose
5. Added context about the Google Sign-In button being a standard component
6. Made clear which elements are custom vs. provided by SDK

The comments are designed to help future developers quickly understand:
- What this view controller does
- What UI elements it contains
- How it integrates with Google Sign-In
- The purpose of each component