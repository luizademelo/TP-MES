
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

#import <GRPCClient/GRPCCall+Tests.h>
#import <GRPCClient/GRPCTransport.h>
#import <GRPCClient/internal_testing/GRPCCall+InternalTests.h>

#import "PerfTests.h"

#define NSStringize_helper(x) #x
#define NSStringize(x) @NSStringize_helper(x)
static NSString *const kLocalSSLHost = NSStringize(HOST_PORT_LOCALSSL);

extern const char *kCFStreamVarName;

static int32_t kLocalInteropServerOverhead = 10;

@interface PerfTestsNoCFStreamSSL : PerfTests
@end

@implementation PerfTestsNoCFStreamSSL

+ (NSString *)host {
  return kLocalSSLHost;
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

+ (void)setUp {
  setenv(kCFStreamVarName, "0", 1);
}

- (void)setUp {
  [super setUp];

  NSBundle *bundle = [NSBundle bundleForClass:[self class]];
  NSString *certsPath = [bundle pathForResource:@"TestCertificates.bundle/test-certificates"
                                         ofType:@"pem"];
  [GRPCCall useTestCertsPath:certsPath testName:@"foo.test.google.fr" forHost:kLocalSSLHost];
}

@end
