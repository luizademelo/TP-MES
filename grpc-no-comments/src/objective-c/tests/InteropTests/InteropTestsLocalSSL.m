
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

#import <GRPCClient/GRPCCall+Tests.h>
#import <GRPCClient/GRPCTransport.h>
#import <GRPCClient/internal_testing/GRPCCall+InternalTests.h>

#import "../Common/TestUtils.h"
#import "InteropTests.h"

#define NSStringize_helper(x) #x
#define NSStringize(x) @NSStringize_helper(x)

static int32_t kLocalInteropServerOverhead = 10;

@interface InteropTestsLocalSSL : InteropTests
@end

@implementation InteropTestsLocalSSL

+ (NSString *)host {
  return GRPCGetLocalInteropTestServerAddressSSL();
}

+ (NSString *)PEMRootCertificates {
  NSBundle *bundle = [NSBundle bundleForClass:[self class]];
  NSString *certsPath = [bundle pathForResource:@"TestCertificates.bundle/test-certificates"
                                         ofType:@"pem"];
  NSError *error;
  return [NSString stringWithContentsOfFile:certsPath encoding:NSUTF8StringEncoding error:&error];
}

+ (NSString *)hostNameOverride {
  return @"foo.test.google.fr";
}

- (int32_t)encodingOverhead {
  return kLocalInteropServerOverhead;
}

+ (GRPCTransportID)transport {
  return GRPCDefaultTransportImplList.core_secure;
}

- (void)setUp {
  [super setUp];

  NSBundle *bundle = [NSBundle bundleForClass:[self class]];
  NSString *certsPath = [bundle pathForResource:@"TestCertificates.bundle/test-certificates"
                                         ofType:@"pem"];
  [GRPCCall useTestCertsPath:certsPath
                    testName:@"foo.test.google.fr"
                     forHost:GRPCGetLocalInteropTestServerAddressSSL()];
}

- (void)testExceptions {

  @try {
    [GRPCCall useTestCertsPath:nil testName:nil forHost:nil];
    XCTFail(@"Did not receive an exception when parameters are nil");
  } @catch (NSException *theException) {
    NSLog(@"Received exception as expected: %@", theException.name);
  }
}

@end
