
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

#import "MakeRPCViewController.h"

#import <AuthTestService/AuthSample.pbrpc.h>
#import <Google/SignIn.h>
#import <ProtoRPC/ProtoRPC.h>

NSString * const kTestScope = @"https://www.googleapis.com/auth/xapi.zoo";

static NSString * const kTestHostAddress = @"grpc-test.sandbox.googleapis.com";

@interface NSError (AuthSample)
- (NSString *)UIDescription;
@end

@implementation NSError (AuthSample)
- (NSString *)UIDescription {
  if (self.code == GRPCErrorCodeUnauthenticated) {

    NSString *challengeHeader = self.userInfo[kGRPCHeadersKey][@"www-authenticate"] ?: @"";
    return [@"Invalid credentials. Server challenge:\n" stringByAppendingString:challengeHeader];
  } else {

    return [NSString stringWithFormat:@"Unexpected RPC error %li: %@",
            (long)self.code, self.localizedDescription];
  }
}
@end

@interface MakeRPCViewController ()<GRPCProtoResponseHandler>

@end

@implementation MakeRPCViewController

- (dispatch_queue_t)dispatchQueue {
  return dispatch_get_main_queue();
}

- (void)viewWillAppear:(BOOL)animated {

  AUTHTestService *client = [[AUTHTestService alloc] initWithHost:kTestHostAddress];

  AUTHRequest *request = [AUTHRequest message];
  request.fillUsername = YES;
  request.fillOauthScope = YES;

  GRPCMutableCallOptions *options = [[GRPCMutableCallOptions alloc] init];
  options.oauth2AccessToken = GIDSignIn.sharedInstance.currentUser.authentication.accessToken;
  GRPCUnaryProtoCall *call = [client unaryCallWithMessage:request
                                          responseHandler:self
                                              callOptions:options];
  [call start];

  self.mainLabel.text = @"Waiting for RPC to complete...";
}

- (void)didReceiveProtoMessage:(GPBMessage *)message {
  AUTHResponse *response = (AUTHResponse *)message;
  if (response) {

    self.mainLabel.text = [NSString stringWithFormat:@"Used scope: %@ on behalf of user %@",
                           response.oauthScope, response.username];
  }
}

- (void)didCloseWithTrailingMetadata:(NSDictionary *)trailingMetadata error:(NSError *)error {
  if (error) {
    self.mainLabel.text = error.UIDescription;
  }
}

@end
