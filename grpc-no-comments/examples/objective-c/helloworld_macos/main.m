
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

#import <Cocoa/Cocoa.h>

#import <GRPCClient/GRPCCall+ChannelArg.h>
#import <GRPCClient/GRPCCall+Tests.h>
#import <GRPCClient/GRPCTransport.h>
#if COCOAPODS
#import <HelloWorld/Helloworld.pbrpc.h>
#else
#import "examples/protos/Helloworld.pbrpc.h"
#endif

static NSString * const kHostAddress = @"localhost:50051";

@interface HLWResponseHandler : NSObject<GRPCProtoResponseHandler>

@end

@implementation HLWResponseHandler

- (dispatch_queue_t)dispatchQueue {
  return dispatch_get_main_queue();
}

- (void)didReceiveProtoMessage:(GPBMessage *)message {
  NSLog(@"%@", message);
}

@end

int main(int argc, const char * argv[]) {
  @autoreleasepool {
    HLWGreeter *client = [[HLWGreeter alloc] initWithHost:kHostAddress];

    HLWHelloRequest *request = [HLWHelloRequest message];
    request.name = @"Objective-C";

    GRPCMutableCallOptions *options = [[GRPCMutableCallOptions alloc] init];

    options.transport = GRPCDefaultTransportImplList.core_insecure;
    options.userAgentPrefix = @"HelloWorld/1.0";

    GRPCUnaryProtoCall *call = [client sayHelloWithMessage:request
                                           responseHandler:[[HLWResponseHandler alloc] init]
                                               callOptions:options];

    [call start];
  }

  return NSApplicationMain(argc, argv);
}
