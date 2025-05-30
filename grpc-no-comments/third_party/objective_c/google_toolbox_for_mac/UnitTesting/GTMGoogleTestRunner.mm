
//  Copyright 2013 Google Inc.

#if !defined(__has_feature) || !__has_feature(objc_arc)
#error "This file requires ARC support."
#endif

// NOTE:

#import <XCTest/XCTest.h>
#import <objc/runtime.h>

#include <gtest/gtest.h>

using ::testing::EmptyTestEventListener;
using ::testing::TestCase;
using ::testing::TestEventListener;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::TestResult;
using ::testing::UnitTest;

namespace {

class GoogleTestPrinter : public EmptyTestEventListener {
 public:
  GoogleTestPrinter(XCTestCase *test_case) : test_case_(test_case) {}

  virtual ~GoogleTestPrinter() {}

  virtual void OnTestPartResult(const TestPartResult &test_part_result) {
    if (!test_part_result.passed()) {
      const char *file_name = test_part_result.file_name();
      NSString *file = @(file_name ? file_name : "<file name unavailable>");
      int line = test_part_result.line_number();
      NSString *summary = @(test_part_result.summary());

      NSString *oneLineSummary =
          [summary stringByReplacingOccurrencesOfString:@"\n" withString:@" "];
      BOOL expected = test_part_result.nonfatally_failed();
      [test_case_ recordFailureWithDescription:oneLineSummary
                                        inFile:file
                                        atLine:line
                                      expected:expected];
    }
  }

 private:
  XCTestCase *test_case_;
};

NSString *SelectorNameFromGTestName(NSString *testName) {
  NSRange dot = [testName rangeOfString:@"."];
  return [NSString stringWithFormat:@"%@::%@",
          [testName substringToIndex:dot.location],
          [testName substringFromIndex:dot.location + 1]];
}

}

@interface GTMGoogleTestRunner : XCTestCase {
  NSString *testName_;
}

- (id)initWithName:(NSString *)testName;
@end

@implementation GTMGoogleTestRunner

+ (void)initGoogleTest {
  static dispatch_once_t onceToken;
  dispatch_once(&onceToken, ^{
    NSArray *arguments = [NSProcessInfo processInfo].arguments;
    int argc = (int)arguments.count;
    char **argv = static_cast<char **>(alloca((sizeof(char *) * (argc + 1))));
    for (int index = 0; index < argc; index++) {
      argv[index] = const_cast<char *> ([arguments[index] UTF8String]);
    }
    argv[argc] = NULL;

    testing::InitGoogleTest(&argc, argv);
  });
}

+ (id)defaultTestSuite {
  [GTMGoogleTestRunner initGoogleTest];
  XCTestSuite *result = [[XCTestSuite alloc] initWithName:NSStringFromClass(self)];
  UnitTest *test = UnitTest::GetInstance();

  int total_test_case_count = test->total_test_case_count();
  for (int i = 0; i < total_test_case_count; ++i) {
    const TestCase *test_case = test->GetTestCase(i);
    int total_test_count = test_case->total_test_count();
    XCTestSuite *subSuite = [[XCTestSuite alloc] initWithName:@(test_case->name())];
    [result addTest:subSuite];
    for (int j = 0; j < total_test_count; ++j) {
      const TestInfo *test_info = test_case->GetTestInfo(j);
      NSString *testName = [NSString stringWithFormat:@"%s.%s",
                            test_case->name(), test_info->name()];
      XCTestCase *xcTest = [[self alloc] initWithName:testName];
      [subSuite addTest:xcTest];
    }
  }
  return result;
}

- (id)initWithName:(NSString *)testName {

  Class cls = [self class];
  NSString *selectorTestName = SelectorNameFromGTestName(testName);
  SEL selector = sel_registerName([selectorTestName UTF8String]);
  Method method = class_getInstanceMethod(cls, @selector(runGoogleTest));
  IMP implementation = method_getImplementation(method);
  const char *encoding = method_getTypeEncoding(method);
  if (!class_addMethod(cls, selector, implementation, encoding)) {

    [NSException raise:NSInternalInconsistencyException
                format:@"Unable to add %@ to %@.", testName, cls];
  }
  if ((self = [super initWithSelector:selector])) {
    testName_ = testName;
  }
  return self;
}

- (NSString *)name {

  NSRange dot = [testName_ rangeOfString:@"."];
  return [NSString stringWithFormat:@"-[%@ %@]",
          [testName_ substringToIndex:dot.location],
          [testName_ substringFromIndex:dot.location + 1]];
}

- (void)runGoogleTest {
  [GTMGoogleTestRunner initGoogleTest];

  TestEventListeners& listeners = UnitTest::GetInstance()->listeners();

  GoogleTestPrinter printer = GoogleTestPrinter(self);
  listeners.Append(&printer);

  TestEventListener *defaultListener = listeners.default_result_printer();
  if (defaultListener) {
    delete listeners.Release(defaultListener);
  }

  ::testing::GTEST_FLAG(filter) = [testName_ UTF8String];

  (void)RUN_ALL_TESTS();

  listeners.Release(&printer);
}

@end
