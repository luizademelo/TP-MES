
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

#import <XCTest/XCTest.h>
#import <grpc/grpc.h>
#import <grpc/support/port_platform.h>

#import <GRPCClient/GRPCCall+ChannelArg.h>
#import <GRPCClient/GRPCCall+OAuth2.h>
#import <GRPCClient/GRPCCall+Tests.h>
#import <GRPCClient/GRPCCall.h>
#import <GRPCClient/internal_testing/GRPCCall+InternalTests.h>
#import <ProtoRPC/ProtoMethod.h>
#import <RxLibrary/GRXBufferedPipe.h>
#import <RxLibrary/GRXWriteable.h>
#import <RxLibrary/GRXWriter+Immediate.h>
#import "src/objective-c/tests/RemoteTestClient/Messages.pbobjc.h"

#include <netinet/in.h>

#import "../Common/TestUtils.h"
#import "../version.h"

#define TEST_TIMEOUT 16

#define NSStringize_helper(x) #x
#define NSStringize(x) @NSStringize_helper(x)
static NSString *const kPackage = @"grpc.testing";
static NSString *const kService = @"TestService";

static GRPCProtoMethod *kInexistentMethod;
static GRPCProtoMethod *kEmptyCallMethod;
static GRPCProtoMethod *kUnaryCallMethod;
static GRPCProtoMethod *kFullDuplexCallMethod;

@interface PassthroughObserver : NSObject
- (instancetype)initWithCallback:(void (^)(NSString *, id, NSDictionary *))callback
    NS_DESIGNATED_INITIALIZER;

- (void)observeValueForKeyPath:(NSString *)keyPath
                      ofObject:(id)object
                        change:(NSDictionary *)change
                       context:(void *)context;
@end

@implementation PassthroughObserver {
  void (^_callback)(NSString *, id, NSDictionary *);
}

- (instancetype)init {
  return [self initWithCallback:nil];
}

- (instancetype)initWithCallback:(void (^)(NSString *, id, NSDictionary *))callback {
  if (!callback) {
    return nil;
  }
  if ((self = [super init])) {
    _callback = callback;
  }
  return self;
}

- (void)observeValueForKeyPath:(NSString *)keyPath
                      ofObject:(id)object
                        change:(NSDictionary *)change
                       context:(void *)context {
  _callback(keyPath, object, change);
  [object removeObserver:self forKeyPath:keyPath];
}

@end

#pragma mark Tests

@interface GRPCClientTests : XCTestCase
@end

@implementation GRPCClientTests

+ (void)setUp {
  NSLog(@"GRPCClientTests Started");
}

- (void)setUp {

  [GRPCCall setUserAgentPrefix:@"Foo" forHost:GRPCGetLocalInteropTestServerAddressPlainText()];
  [GRPCCall setUserAgentSuffix:@"Suffix" forHost:GRPCGetLocalInteropTestServerAddressPlainText()];

  [GRPCCall useInsecureConnectionsForHost:GRPCGetLocalInteropTestServerAddressPlainText()];

  kInexistentMethod = [[GRPCProtoMethod alloc] initWithPackage:kPackage
                                                       service:kService
                                                        method:@"Inexistent"];
  kEmptyCallMethod = [[GRPCProtoMethod alloc] initWithPackage:kPackage
                                                      service:kService
                                                       method:@"EmptyCall"];
  kUnaryCallMethod = [[GRPCProtoMethod alloc] initWithPackage:kPackage
                                                      service:kService
                                                       method:@"UnaryCall"];
  kFullDuplexCallMethod = [[GRPCProtoMethod alloc] initWithPackage:kPackage
                                                           service:kService
                                                            method:@"FullDuplexCall"];
}

- (void)testConnectionToRemoteServer {
  __weak XCTestExpectation *expectation = [self expectationWithDescription:@"Server reachable."];

  GRPCCall *call = [[GRPCCall alloc] initWithHost:GRPCGetLocalInteropTestServerAddressPlainText()
                                             path:kInexistentMethod.HTTPPath
                                   requestsWriter:[GRXWriter writerWithValue:[NSData data]]];

  id<GRXWriteable> responsesWriteable = [[GRXWriteable alloc]
      initWithValueHandler:^(NSData *value) {
        XCTFail(@"Received unexpected response: %@", value);
      }
      completionHandler:^(NSError *errorOrNil) {
        XCTAssertNotNil(errorOrNil, @"Finished without error!");
        XCTAssertEqual(errorOrNil.code, 12, @"Finished with unexpected error: %@", errorOrNil);
        [expectation fulfill];
      }];

  [call startWithWriteable:responsesWriteable];

  [self waitForExpectationsWithTimeout:TEST_TIMEOUT handler:nil];
}

- (void)testEmptyRPC {
  __weak XCTestExpectation *response =
      [self expectationWithDescription:@"Empty response received."];
  __weak XCTestExpectation *completion = [self expectationWithDescription:@"Empty RPC completed."];

  GRPCCall *call = [[GRPCCall alloc] initWithHost:GRPCGetLocalInteropTestServerAddressPlainText()
                                             path:kEmptyCallMethod.HTTPPath
                                   requestsWriter:[GRXWriter writerWithValue:[NSData data]]];

  id<GRXWriteable> responsesWriteable = [[GRXWriteable alloc]
      initWithValueHandler:^(NSData *value) {
        XCTAssertNotNil(value, @"nil value received as response.");
        XCTAssertEqual([value length], 0, @"Non-empty response received: %@", value);
        [response fulfill];
      }
      completionHandler:^(NSError *errorOrNil) {
        XCTAssertNil(errorOrNil, @"Finished with unexpected error: %@", errorOrNil);
        [completion fulfill];
      }];

  [call startWithWriteable:responsesWriteable];

  [self waitForExpectationsWithTimeout:TEST_TIMEOUT handler:nil];
}

- (void)testSimpleProtoRPC {
  __weak XCTestExpectation *response = [self expectationWithDescription:@"Expected response."];
  __weak XCTestExpectation *completion = [self expectationWithDescription:@"RPC completed."];

  RMTSimpleRequest *request = [RMTSimpleRequest message];
  request.responseSize = 100;
  request.fillUsername = YES;
  request.fillOauthScope = YES;
  GRXWriter *requestsWriter = [GRXWriter writerWithValue:[request data]];

  GRPCCall *call = [[GRPCCall alloc] initWithHost:GRPCGetLocalInteropTestServerAddressPlainText()
                                             path:kUnaryCallMethod.HTTPPath
                                   requestsWriter:requestsWriter];

  id<GRXWriteable> responsesWriteable = [[GRXWriteable alloc]
      initWithValueHandler:^(NSData *value) {
        XCTAssertNotNil(value, @"nil value received as response.");
        XCTAssertGreaterThan(value.length, 0, @"Empty response received.");
        RMTSimpleResponse *responseProto = [RMTSimpleResponse parseFromData:value error:NULL];

        XCTAssertNotNil(responseProto.username, @"Response's username is nil.");
        XCTAssertNotNil(responseProto.oauthScope, @"Response's OAuth scope is nil.");
        [response fulfill];
      }
      completionHandler:^(NSError *errorOrNil) {
        XCTAssertNil(errorOrNil, @"Finished with unexpected error: %@", errorOrNil);
        [completion fulfill];
      }];

  [call startWithWriteable:responsesWriteable];

  [self waitForExpectationsWithTimeout:TEST_TIMEOUT handler:nil];
}

- (void)testResponseMetadataKVO {
  __weak XCTestExpectation *response =
      [self expectationWithDescription:@"Empty response received."];
  __weak XCTestExpectation *completion = [self expectationWithDescription:@"Empty RPC completed."];
  __weak XCTestExpectation *metadata = [self expectationWithDescription:@"Metadata changed."];

  GRPCCall *call = [[GRPCCall alloc] initWithHost:GRPCGetLocalInteropTestServerAddressPlainText()
                                             path:kEmptyCallMethod.HTTPPath
                                   requestsWriter:[GRXWriter writerWithValue:[NSData data]]];

  PassthroughObserver *observer = [[PassthroughObserver alloc]
      initWithCallback:^(NSString *keypath, id object, NSDictionary *change) {
        if ([keypath isEqual:@"responseHeaders"]) {
          [metadata fulfill];
        }
      }];

  [call addObserver:observer forKeyPath:@"responseHeaders" options:0 context:NULL];

  id<GRXWriteable> responsesWriteable = [[GRXWriteable alloc]
      initWithValueHandler:^(NSData *value) {
        XCTAssertNotNil(value, @"nil value received as response.");
        XCTAssertEqual([value length], 0, @"Non-empty response received: %@", value);
        [response fulfill];
      }
      completionHandler:^(NSError *errorOrNil) {
        XCTAssertNil(errorOrNil, @"Finished with unexpected error: %@", errorOrNil);
        [completion fulfill];
      }];

  [call startWithWriteable:responsesWriteable];

  [self waitForExpectationsWithTimeout:TEST_TIMEOUT handler:nil];
}

- (void)testUserAgentPrefixAndSuffix {
  __weak XCTestExpectation *response =
      [self expectationWithDescription:@"Empty response received."];
  __weak XCTestExpectation *completion = [self expectationWithDescription:@"Empty RPC completed."];

  GRPCCall *call = [[GRPCCall alloc] initWithHost:GRPCGetLocalInteropTestServerAddressPlainText()
                                             path:kEmptyCallMethod.HTTPPath
                                   requestsWriter:[GRXWriter writerWithValue:[NSData data]]];

  call.requestHeaders[@"x-grpc-test-echo-useragent"] = @"";

  id<GRXWriteable> responsesWriteable = [[GRXWriteable alloc]
      initWithValueHandler:^(NSData *value) {
        XCTAssertNotNil(value, @"nil value received as response.");
        XCTAssertEqual([value length], 0, @"Non-empty response received: %@", value);

        NSString *userAgent = call.responseHeaders[@"x-grpc-test-echo-useragent"];
        NSError *error = nil;

        NSString *expectedUserAgent = @"Foo grpc-objc-cfstream/";
        expectedUserAgent = [expectedUserAgent stringByAppendingString:GRPC_OBJC_VERSION_STRING];
        expectedUserAgent = [expectedUserAgent stringByAppendingString:@" Suffix"];
        expectedUserAgent = [expectedUserAgent stringByAppendingString:@" grpc-c/"];
        expectedUserAgent = [expectedUserAgent stringByAppendingString:GRPC_C_VERSION_STRING];
        expectedUserAgent = [expectedUserAgent stringByAppendingString:@" ("];
        expectedUserAgent = [expectedUserAgent stringByAppendingString:@GPR_PLATFORM_STRING];
        expectedUserAgent = [expectedUserAgent stringByAppendingString:@"; chttp2)"];
        XCTAssertEqualObjects(userAgent, expectedUserAgent);

        NSRegularExpression *regex = [NSRegularExpression
            regularExpressionWithPattern:@" grpc-[a-zA-Z0-9]+(-[a-zA-Z0-9]+)?/[^ ,]+( \\([^)]*\\))?"
                                 options:0
                                   error:&error];
        NSString *customUserAgent =
            [regex stringByReplacingMatchesInString:userAgent
                                            options:0
                                              range:NSMakeRange(0, [userAgent length])
                                       withTemplate:@""];

        NSArray *userAgentArray = [customUserAgent componentsSeparatedByString:@" "];
        XCTAssertEqual([userAgentArray count], 2);
        XCTAssertEqualObjects([userAgentArray objectAtIndex:0], @"Foo");
        XCTAssertEqualObjects([userAgentArray objectAtIndex:1], @"Suffix");
        [response fulfill];
      }
      completionHandler:^(NSError *errorOrNil) {
        XCTAssertNil(errorOrNil, @"Finished with unexpected error: %@", errorOrNil);
        [completion fulfill];
      }];

  [call startWithWriteable:responsesWriteable];

  [self waitForExpectationsWithTimeout:TEST_TIMEOUT handler:nil];
}

- (void)testTrailers {
  __weak XCTestExpectation *response =
      [self expectationWithDescription:@"Empty response received."];
  __weak XCTestExpectation *completion = [self expectationWithDescription:@"Empty RPC completed."];

  GRPCCall *call = [[GRPCCall alloc] initWithHost:GRPCGetLocalInteropTestServerAddressPlainText()
                                             path:kEmptyCallMethod.HTTPPath
                                   requestsWriter:[GRXWriter writerWithValue:[NSData data]]];

  const unsigned char raw_bytes[] = {1, 2, 3, 4};
  NSData *trailer_data = [NSData dataWithBytes:raw_bytes length:sizeof(raw_bytes)];
  call.requestHeaders[@"x-grpc-test-echo-trailing-bin"] = trailer_data;

  id<GRXWriteable> responsesWriteable = [[GRXWriteable alloc]
      initWithValueHandler:^(NSData *value) {
        XCTAssertNotNil(value, @"nil value received as response.");
        XCTAssertEqual([value length], 0, @"Non-empty response received: %@", value);
        [response fulfill];
      }
      completionHandler:^(NSError *errorOrNil) {
        XCTAssertNil(errorOrNil, @"Finished with unexpected error: %@", errorOrNil);
        XCTAssertEqualObjects((NSData *)call.responseTrailers[@"x-grpc-test-echo-trailing-bin"],
                              trailer_data, @"Did not receive expected trailer");
        [completion fulfill];
      }];

  [call startWithWriteable:responsesWriteable];
  [self waitForExpectationsWithTimeout:TEST_TIMEOUT handler:nil];
}

- (void)testExceptions {
  GRXWriter *writer = [GRXWriter writerWithValue:[NSData data]];

  @try {
    (void)[[GRPCCall alloc] initWithHost:nil path:nil requestsWriter:writer];
    XCTFail(@"Did not receive an exception when parameters are nil");
  } @catch (NSException *theException) {
    NSLog(@"Received exception as expected: %@", theException.name);
  }

  GRXWriter *requestsWriter = [GRXWriter emptyWriter];
  [requestsWriter finishWithError:nil];
  @try {
    (void)[[GRPCCall alloc] initWithHost:GRPCGetLocalInteropTestServerAddressPlainText()
                                    path:kUnaryCallMethod.HTTPPath
                          requestsWriter:requestsWriter];
    XCTFail(@"Did not receive an exception when GRXWriter has incorrect state.");
  } @catch (NSException *theException) {
    NSLog(@"Received exception as expected: %@", theException.name);
  }
}

- (void)testAlternateDispatchQueue {
  const int32_t kPayloadSize = 100;
  RMTSimpleRequest *request = [RMTSimpleRequest message];
  request.responseSize = kPayloadSize;

  __weak XCTestExpectation *expectation1 =
      [self expectationWithDescription:@"AlternateDispatchQueue1"];

  NSString *main_queue_label =
      [NSString stringWithUTF8String:dispatch_queue_get_label(dispatch_get_main_queue())];

  GRXWriter *requestsWriter1 = [GRXWriter writerWithValue:[request data]];

  GRPCCall *call1 = [[GRPCCall alloc] initWithHost:GRPCGetLocalInteropTestServerAddressPlainText()
                                              path:kUnaryCallMethod.HTTPPath
                                    requestsWriter:requestsWriter1];

  id<GRXWriteable> responsesWriteable1 = [[GRXWriteable alloc]
      initWithValueHandler:^(NSData *value) {
        NSString *label =
            [NSString stringWithUTF8String:dispatch_queue_get_label(DISPATCH_CURRENT_QUEUE_LABEL)];
        XCTAssert([label isEqualToString:main_queue_label]);

        [expectation1 fulfill];
      }
         completionHandler:^(NSError *errorOrNil){
         }];

  [call1 startWithWriteable:responsesWriteable1];

  [self waitForExpectationsWithTimeout:TEST_TIMEOUT handler:nil];

  __weak XCTestExpectation *expectation2 =
      [self expectationWithDescription:@"AlternateDispatchQueue2"];

  NSString *queue_label = @"test.queue1";
  dispatch_queue_t queue = dispatch_queue_create([queue_label UTF8String], DISPATCH_QUEUE_SERIAL);

  GRXWriter *requestsWriter2 = [GRXWriter writerWithValue:[request data]];

  GRPCCall *call2 = [[GRPCCall alloc] initWithHost:GRPCGetLocalInteropTestServerAddressPlainText()
                                              path:kUnaryCallMethod.HTTPPath
                                    requestsWriter:requestsWriter2];

  [call2 setResponseDispatchQueue:queue];

  id<GRXWriteable> responsesWriteable2 = [[GRXWriteable alloc]
      initWithValueHandler:^(NSData *value) {
        NSString *label =
            [NSString stringWithUTF8String:dispatch_queue_get_label(DISPATCH_CURRENT_QUEUE_LABEL)];
        XCTAssert([label isEqualToString:queue_label]);

        [expectation2 fulfill];
      }
         completionHandler:^(NSError *errorOrNil){
         }];

  [call2 startWithWriteable:responsesWriteable2];

  [self waitForExpectationsWithTimeout:TEST_TIMEOUT handler:nil];
}

- (void)testTimeout {
  __weak XCTestExpectation *completion = [self expectationWithDescription:@"RPC completed."];

  GRXBufferedPipe *pipe = [GRXBufferedPipe pipe];
  GRPCCall *call = [[GRPCCall alloc] initWithHost:GRPCGetLocalInteropTestServerAddressPlainText()
                                             path:kFullDuplexCallMethod.HTTPPath
                                   requestsWriter:pipe];

  id<GRXWriteable> responsesWriteable = [[GRXWriteable alloc]
      initWithValueHandler:^(NSData *value) {
        XCTAssert(0, @"Failure: response received; Expect: no response received.");
      }
      completionHandler:^(NSError *errorOrNil) {
        XCTAssertNotNil(errorOrNil,
                        @"Failure: no error received; Expect: receive deadline exceeded.");
        XCTAssertEqual(errorOrNil.code, GRPCErrorCodeDeadlineExceeded);
        [completion fulfill];
      }];

  call.timeout = 0.001;
  [call startWithWriteable:responsesWriteable];

  [self waitForExpectationsWithTimeout:TEST_TIMEOUT handler:nil];
}

- (int)findFreePort {
  struct sockaddr_in addr;
  unsigned int addr_len = sizeof(addr);
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  XCTAssertEqual(bind(fd, (struct sockaddr *)&addr, sizeof(addr)), 0);
  XCTAssertEqual(getsockname(fd, (struct sockaddr *)&addr, &addr_len), 0);
  XCTAssertEqual(addr_len, sizeof(addr));
  close(fd);
  return addr.sin_port;
}

- (void)testErrorCode {
  int port = [self findFreePort];
  NSString *const kPhonyAddress = [NSString stringWithFormat:@"localhost:%d", port];
  __weak XCTestExpectation *completion =
      [self expectationWithDescription:@"Received correct error code."];

  GRPCCall *call = [[GRPCCall alloc] initWithHost:kPhonyAddress
                                             path:kEmptyCallMethod.HTTPPath
                                   requestsWriter:[GRXWriter writerWithValue:[NSData data]]];

  id<GRXWriteable> responsesWriteable = [[GRXWriteable alloc]
      initWithValueHandler:^(NSData *value) {

        XCTAssert(NO);
      }
      completionHandler:^(NSError *errorOrNil) {
        XCTAssertNotNil(errorOrNil, @"Finished with no error");
        XCTAssertEqual(errorOrNil.code, GRPC_STATUS_UNAVAILABLE);
        [completion fulfill];
      }];

  [call startWithWriteable:responsesWriteable];

  [self waitForExpectationsWithTimeout:TEST_TIMEOUT handler:nil];
}

- (void)testTimeoutBackoffWithTimeout:(double)timeout Backoff:(double)backoff {
  const double maxConnectTime = timeout > backoff ? timeout : backoff;
  const double kMargin = 0.2;

  __weak XCTestExpectation *completion = [self expectationWithDescription:@"Timeout in a second."];
  NSString *const kPhonyAddress = [NSString stringWithFormat:@"8.8.8.8:1"];
  [GRPCCall useInsecureConnectionsForHost:kPhonyAddress];
  [GRPCCall setMinConnectTimeout:timeout * 1000
                  initialBackoff:backoff * 1000
                      maxBackoff:0
                         forHost:kPhonyAddress];
  GRPCCall *call = [[GRPCCall alloc] initWithHost:kPhonyAddress
                                             path:@"/phonyPath"
                                   requestsWriter:[GRXWriter writerWithValue:[NSData data]]];
  NSDate *startTime = [NSDate date];
  id<GRXWriteable> responsesWriteable = [[GRXWriteable alloc]
      initWithValueHandler:^(id value) {
        XCTAssert(NO, @"Received message. Should not reach here");
      }
      completionHandler:^(NSError *errorOrNil) {
        XCTAssertNotNil(errorOrNil, @"Finished with no error");

        XCTAssertLessThan([[NSDate date] timeIntervalSinceDate:startTime],
                          maxConnectTime + kMargin);
        [completion fulfill];
      }];

  [call startWithWriteable:responsesWriteable];

  [self waitForExpectationsWithTimeout:TEST_TIMEOUT handler:nil];
}

- (void)testTimeoutBackoff1 {
  [self testTimeoutBackoffWithTimeout:0.7 Backoff:0.3];
}

- (void)testTimeoutBackoff2 {
  [self testTimeoutBackoffWithTimeout:0.3 Backoff:0.7];
}

@end
