
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
#import <GRPCClient/internal_testing/GRPCCall+InternalTests.h>

#import "StressTests.h"

static NSString *const kHostAddress = @"10.0.0.1";

static int32_t kLocalInteropServerOverhead = 10;

@interface StressTestsCleartext : StressTests
@end

@implementation StressTestsCleartext

+ (NSString *)host {
  return [NSString stringWithFormat:@"%@:5050", kHostAddress];
}

+ (NSString *)hostAddress {
  return kHostAddress;
}

+ (NSString *)PEMRootCertificates {
  return nil;
}

+ (NSString *)hostNameOverride {
  return nil;
}

- (int32_t)encodingOverhead {
  return kLocalInteropServerOverhead;
}

- (void)setUp {
  [super setUp];

  [GRPCCall useInsecureConnectionsForHost:[[self class] host]];
}

+ (GRPCTransportType)transportType {
  return GRPCTransportTypeInsecure;
}

@end
