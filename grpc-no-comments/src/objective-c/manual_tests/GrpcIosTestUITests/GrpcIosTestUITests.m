
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

#import <XCTest/XCTest.h>

NSTimeInterval const kWaitTime = 30;
int const kNumIterations = 1;

@interface GrpcIosTestUITests : XCTestCase
@end

@implementation GrpcIosTestUITests {
  XCUIApplication *testApp;
  XCUIApplication *settingsApp;
}

- (void)setUp {
  self.continueAfterFailure = NO;
  [[[XCUIApplication alloc] init] launch];
  testApp = [[XCUIApplication alloc] initWithBundleIdentifier:@"io.grpc.GrpcIosTest"];
  [testApp activate];

  [self pressButton:@"Reset counter"];

  settingsApp = [[XCUIApplication alloc] initWithBundleIdentifier:@"com.apple.Preferences"];
  [settingsApp activate];
  [NSThread sleepForTimeInterval:1];

  XCUIElement *backButton = settingsApp.navigationBars.buttons.firstMatch;
  while (backButton.exists && backButton.isHittable) {
    NSLog(@"Tapping back button");
    [backButton tap];
  }
  XCTAssert([settingsApp.navigationBars[@"Settings"] waitForExistenceWithTimeout:kWaitTime]);
  NSLog(@"Turning off airplane mode");

  [self setAirplaneMode:NO];

  NSLog(@"Turning on wifi");
  [self setWifi:YES];
}

- (void)tearDown {
}

- (void)doUnaryCall {
  [testApp activate];
  [self pressButton:@"Unary call"];
}

- (void)do10UnaryCalls {
  [testApp activate];
  [self pressButton:@"10 Unary calls"];
}

- (void)pressButton:(NSString *)name {

  while (![testApp.buttons[name] exists] || ![testApp.buttons[name] isHittable]) {
    [NSThread sleepForTimeInterval:1];
  }

  while (CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.1, true) == kCFRunLoopRunHandledSource);

  NSLog(@"Pressing button: %@", name);
  [testApp.buttons[name] tap];
}

- (void)expectCallSuccess {
  XCTAssert([testApp.staticTexts[@"Call done"] waitForExistenceWithTimeout:kWaitTime]);
}

- (void)expectCallFailed {
  XCTAssert([testApp.staticTexts[@"Call failed"] waitForExistenceWithTimeout:kWaitTime]);
}

- (void)expectCallSuccessOrFailed {
  NSDate *startTime = [NSDate date];
  while (![testApp.staticTexts[@"Call done"] exists] &&
         ![testApp.staticTexts[@"Call failed"] exists]) {
    XCTAssertLessThan([[NSDate date] timeIntervalSinceDate:startTime], kWaitTime);
    [NSThread sleepForTimeInterval:1];
  }
}

- (void)setAirplaneMode:(BOOL)to {
  [settingsApp activate];
  XCUIElement *mySwitch = settingsApp.tables.element.cells.switches[@"Airplane Mode"];
  BOOL from = [(NSString *)mySwitch.value boolValue];
  NSLog(@"Setting airplane from: %d to: %d", from, to);
  if (from != to) {
    [mySwitch tap];

    [NSThread sleepForTimeInterval:5];
  }
  XCTAssert([(NSString *)mySwitch.value boolValue] == to);
}
- (void)setWifi:(BOOL)to {
  [settingsApp activate];
  [settingsApp.tables.element.cells.staticTexts[@"Wi-Fi"] tap];
  XCUIElement *wifiSwitch = settingsApp.tables.cells.switches[@"Wi-Fi"];
  BOOL from = [(NSString *)wifiSwitch.value boolValue];
  NSLog(@"Setting wifi from: %d to: %d", from, to);
  if (from != to) {
    [wifiSwitch tap];

    [NSThread sleepForTimeInterval:10];
  }

  XCUIElement *backButton = settingsApp.navigationBars.buttons.firstMatch;
  [backButton tap];
}

- (int)getRandomNumberBetween:(int)min max:(int)max {
  return min + arc4random_uniform((max - min + 1));
}

- (void)testBackgroundBeforeCall {
  NSLog(@"%s", __func__);

  [testApp activate];

  [XCUIDevice.sharedDevice pressButton:XCUIDeviceButtonHome];

  int sleepTime = [self getRandomNumberBetween:5 max:10];
  NSLog(@"Sleeping for %d seconds", sleepTime);
  [NSThread sleepForTimeInterval:sleepTime];

  [self doUnaryCall];
  [self expectCallSuccess];
}

- (void)testBackgroundDuringStreamingCall {
  NSLog(@"%s", __func__);

  [testApp activate];
  [self pressButton:@"Start streaming call"];

  [XCUIDevice.sharedDevice pressButton:XCUIDeviceButtonHome];

  int sleepTime = [self getRandomNumberBetween:5 max:10];
  NSLog(@"Sleeping for %d seconds", sleepTime);
  [NSThread sleepForTimeInterval:sleepTime];

  [testApp activate];
  [self pressButton:@"Send Message"];
  [self pressButton:@"Stop streaming call"];
  [self expectCallSuccess];
}

- (void)testCallAfterNetworkFlap {
  NSLog(@"%s", __func__);

  [self doUnaryCall];
  [self expectCallSuccess];

  [self setAirplaneMode:YES];
  [self setAirplaneMode:NO];

  [self doUnaryCall];
  [self expectCallSuccess];
}

- (void)testCallWhileNetworkDown {
  NSLog(@"%s", __func__);

  [self doUnaryCall];
  [self expectCallSuccess];

  [self setAirplaneMode:YES];

  [self setWifi:NO];

  [self doUnaryCall];
  [self expectCallFailed];

  [self setAirplaneMode:NO];

  [self setWifi:YES];

  [self doUnaryCall];
  [self expectCallSuccess];
}

- (void)testSwitchApp {
  NSLog(@"%s", __func__);

  [self doUnaryCall];
  [self expectCallSuccess];

  [XCUIDevice.sharedDevice pressButton:XCUIDeviceButtonHome];

  XCUIApplication *stocksApp =
      [[XCUIApplication alloc] initWithBundleIdentifier:@"com.apple.stocks"];
  [stocksApp activate];

  XCTAssert([stocksApp waitForState:XCUIApplicationStateRunningForeground timeout:5]);

  int sleepTime = [self getRandomNumberBetween:5 max:10];
  NSLog(@"Sleeping for %d seconds", sleepTime);
  [NSThread sleepForTimeInterval:sleepTime];
  [stocksApp terminate];

  [self doUnaryCall];
  [self expectCallSuccess];
}

- (void)testNetworkFlapDuringStreamingCall {
  NSLog(@"%s", __func__);

  [self doUnaryCall];
  [self expectCallSuccess];

  [self pressButton:@"Start streaming call"];
  [self pressButton:@"Send Message"];

  [self setAirplaneMode:YES];
  [self setWifi:NO];
  [self setAirplaneMode:NO];
  [self setWifi:YES];

  [testApp activate];
  [self pressButton:@"Stop streaming call"];

  [self expectCallSuccessOrFailed];

  [self doUnaryCall];
  [self expectCallSuccess];
}

- (void)testConcurrentCalls {
  NSLog(@"%s", __func__);

  [self do10UnaryCalls];

  [self setAirplaneMode:YES];
  [self setAirplaneMode:NO];

  [testApp activate];
  XCTAssert([testApp.staticTexts[@"Calls completed: 10"] waitForExistenceWithTimeout:kWaitTime]);
}

- (void)invokeTest {
  for (int i = 0; i < kNumIterations; i++) {
    [super invokeTest];
  }
}

- (void)testUnaryCallTurnOffWifi {
  NSLog(@"%s", __func__);

  [self doUnaryCall];
  [self expectCallSuccess];

  [self setWifi:NO];

  [self doUnaryCall];
  [self expectCallSuccess];

  [self setWifi:YES];

  [self doUnaryCall];
  [self expectCallSuccess];
}

- (void)testStreamingCallTurnOffWifi {
  NSLog(@"%s", __func__);

  [self doUnaryCall];
  [self expectCallSuccess];

  [self pressButton:@"Start streaming call"];
  [self pressButton:@"Send Message"];

  [self setWifi:NO];

  [testApp activate];
  [self pressButton:@"Stop streaming call"];
  [self expectCallFailed];

  [self setWifi:YES];

  [self doUnaryCall];
  [self expectCallSuccess];
}

@end
