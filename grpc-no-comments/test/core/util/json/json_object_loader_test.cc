// Copyright 2021 gRPC authors.

#include "src/core/util/json/json_object_loader.h"

#include <grpc/support/json.h>

#include <cstdint>

#include "absl/status/status.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/util/json/json_reader.h"
#include "src/core/util/json/json_writer.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {
namespace {

template <typename T>
absl::StatusOr<T> Parse(absl::string_view json,
                        const JsonArgs& args = JsonArgs()) {
  auto parsed = JsonParse(json);
  if (!parsed.ok()) return parsed.status();
  return LoadFromJson<T>(*parsed, args);
}

template <typename T>
class SignedIntegerTest : public ::testing::Test {};

TYPED_TEST_SUITE_P(SignedIntegerTest);

TYPED_TEST_P(SignedIntegerTest, IntegerFields) {
  struct TestStruct {
    TypeParam value = 0;
    TypeParam optional_value = 0;
    std::optional<TypeParam> std_optional_value;
    std::unique_ptr<TypeParam> unique_ptr_value;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader =
          JsonObjectLoader<TestStruct>()
              .Field("value", &TestStruct::value)
              .OptionalField("optional_value", &TestStruct::optional_value)
              .OptionalField("std_optional_value",
                             &TestStruct::std_optional_value)
              .OptionalField("unique_ptr_value", &TestStruct::unique_ptr_value)
              .Finish();
      return loader;
    }
  };

  auto test_struct = Parse<TestStruct>("{\"value\": 5}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->value, 5);
  EXPECT_EQ(test_struct->optional_value, 0);
  EXPECT_FALSE(test_struct->std_optional_value.has_value());

  test_struct = Parse<TestStruct>("{\"value\": -5}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->value, -5);
  EXPECT_EQ(test_struct->optional_value, 0);
  EXPECT_FALSE(test_struct->std_optional_value.has_value());

  test_struct = Parse<TestStruct>("{\"value\": \"5\"}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->value, 5);
  EXPECT_EQ(test_struct->optional_value, 0);
  EXPECT_FALSE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(test_struct->unique_ptr_value, nullptr);

  test_struct = Parse<TestStruct>("{\"value\": \"foo\"}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(
      test_struct.status().message(),
      "errors validating JSON: [field:value error:failed to parse number]")
      << test_struct.status();

  test_struct = Parse<TestStruct>("{}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: [field:value error:field not present]")
      << test_struct.status();

  test_struct = Parse<TestStruct>(
      "{\"value\": 5, \"optional_value\": 7, "
      "\"std_optional_value\": 9, \"unique_ptr_value\": 11}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->value, 5);
  EXPECT_EQ(test_struct->optional_value, 7);
  EXPECT_EQ(test_struct->std_optional_value, 9);
  ASSERT_NE(test_struct->unique_ptr_value, nullptr);
  EXPECT_EQ(*test_struct->unique_ptr_value, 11);

  test_struct = Parse<TestStruct>(
      "{\"value\": 5, \"optional_value\": null, "
      "\"std_optional_value\": null, \"unique_ptr_value\": null}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->value, 5);
  EXPECT_EQ(test_struct->optional_value, 0);
  EXPECT_FALSE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(test_struct->unique_ptr_value, nullptr);

  test_struct = Parse<TestStruct>(
      "{\"value\": [], \"optional_value\": {}, "
      "\"std_optional_value\": true, \"unique_ptr_value\": false}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: ["
            "field:optional_value error:is not a number; "
            "field:std_optional_value error:is not a number; "
            "field:unique_ptr_value error:is not a number; "
            "field:value error:is not a number]")
      << test_struct.status();
}

REGISTER_TYPED_TEST_SUITE_P(SignedIntegerTest, IntegerFields);

using IntegerTypes = ::testing::Types<int32_t, int64_t>;
INSTANTIATE_TYPED_TEST_SUITE_P(My, SignedIntegerTest, IntegerTypes);

template <typename T>
class UnsignedIntegerTest : public ::testing::Test {};

TYPED_TEST_SUITE_P(UnsignedIntegerTest);

TYPED_TEST_P(UnsignedIntegerTest, IntegerFields) {
  struct TestStruct {
    TypeParam value = 0;
    TypeParam optional_value = 0;
    std::optional<TypeParam> std_optional_value;
    std::unique_ptr<TypeParam> unique_ptr_value;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader =
          JsonObjectLoader<TestStruct>()
              .Field("value", &TestStruct::value)
              .OptionalField("optional_value", &TestStruct::optional_value)
              .OptionalField("std_optional_value",
                             &TestStruct::std_optional_value)
              .OptionalField("unique_ptr_value", &TestStruct::unique_ptr_value)
              .Finish();
      return loader;
    }
  };

  auto test_struct = Parse<TestStruct>("{\"value\": 5}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->value, 5);
  EXPECT_EQ(test_struct->optional_value, 0);
  EXPECT_FALSE(test_struct->std_optional_value.has_value());

  test_struct = Parse<TestStruct>("{\"value\": -5}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: ["
            "field:value error:failed to parse non-negative number]")
      << test_struct.status();

  test_struct = Parse<TestStruct>("{\"value\": \"5\"}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->value, 5);
  EXPECT_EQ(test_struct->optional_value, 0);
  EXPECT_FALSE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(test_struct->unique_ptr_value, nullptr);

  test_struct = Parse<TestStruct>("{\"value\": \"foo\"}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: ["
            "field:value error:failed to parse non-negative number]")
      << test_struct.status();

  test_struct = Parse<TestStruct>("{}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: [field:value error:field not present]")
      << test_struct.status();

  test_struct = Parse<TestStruct>(
      "{\"value\": 5, \"optional_value\": 7, "
      "\"std_optional_value\": 9, \"unique_ptr_value\": 11}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->value, 5);
  EXPECT_EQ(test_struct->optional_value, 7);
  ASSERT_TRUE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(*test_struct->std_optional_value, 9);
  ASSERT_NE(test_struct->unique_ptr_value, nullptr);
  EXPECT_EQ(*test_struct->unique_ptr_value, 11);

  test_struct = Parse<TestStruct>(
      "{\"value\": 5, \"optional_value\": null, "
      "\"std_optional_value\": null, \"unique_ptr_value\": null}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->value, 5);
  EXPECT_EQ(test_struct->optional_value, 0);
  EXPECT_FALSE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(test_struct->unique_ptr_value, nullptr);

  test_struct = Parse<TestStruct>(
      "{\"value\": [], \"optional_value\": {}, "
      "\"std_optional_value\": true, \"unique_ptr_value\": false}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: ["
            "field:optional_value error:is not a number; "
            "field:std_optional_value error:is not a number; "
            "field:unique_ptr_value error:is not a number; "
            "field:value error:is not a number]")
      << test_struct.status();
}

REGISTER_TYPED_TEST_SUITE_P(UnsignedIntegerTest, IntegerFields);

using UnsignedIntegerTypes = ::testing::Types<uint32_t, uint64_t>;
INSTANTIATE_TYPED_TEST_SUITE_P(My, UnsignedIntegerTest, UnsignedIntegerTypes);

template <typename T>
class FloatingPointTest : public ::testing::Test {};

TYPED_TEST_SUITE_P(FloatingPointTest);

TYPED_TEST_P(FloatingPointTest, FloatFields) {
  struct TestStruct {
    TypeParam value = 0;
    TypeParam optional_value = 0;
    std::optional<TypeParam> std_optional_value;
    std::unique_ptr<TypeParam> unique_ptr_value;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader =
          JsonObjectLoader<TestStruct>()
              .Field("value", &TestStruct::value)
              .OptionalField("optional_value", &TestStruct::optional_value)
              .OptionalField("std_optional_value",
                             &TestStruct::std_optional_value)
              .OptionalField("unique_ptr_value", &TestStruct::unique_ptr_value)
              .Finish();
      return loader;
    }
  };

  auto test_struct = Parse<TestStruct>("{\"value\": 5.2}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_NEAR(test_struct->value, 5.2, 0.0001);
  EXPECT_EQ(test_struct->optional_value, 0);
  EXPECT_FALSE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(test_struct->unique_ptr_value, nullptr);

  test_struct = Parse<TestStruct>("{\"value\": -5.2}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_NEAR(test_struct->value, -5.2, 0.0001);

  test_struct = Parse<TestStruct>("{\"value\": \"5.2\"}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_NEAR(test_struct->value, 5.2, 0.0001);
  EXPECT_EQ(test_struct->optional_value, 0);
  EXPECT_FALSE(test_struct->std_optional_value.has_value());

  test_struct = Parse<TestStruct>("{\"value\": \"foo\"}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: ["
            "field:value error:failed to parse floating-point number]")
      << test_struct.status();

  test_struct = Parse<TestStruct>("{}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: [field:value error:field not present]")
      << test_struct.status();

  test_struct = Parse<TestStruct>(
      "{\"value\": 5.2, \"optional_value\": 7.5, "
      "\"std_optional_value\": 9.8, \"unique_ptr_value\": 11.5}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_NEAR(test_struct->value, 5.2, 0.0001);
  EXPECT_NEAR(test_struct->optional_value, 7.5, 0.0001);
  ASSERT_TRUE(test_struct->std_optional_value.has_value());
  EXPECT_NEAR(*test_struct->std_optional_value, 9.8, 0.0001);
  ASSERT_NE(test_struct->unique_ptr_value, nullptr);
  EXPECT_NEAR(*test_struct->unique_ptr_value, 11.5, 0.0001);

  test_struct = Parse<TestStruct>(
      "{\"value\": 5.2, \"optional_value\": null, "
      "\"std_optional_value\": null, \"unique_ptr_value\": null}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_NEAR(test_struct->value, 5.2, 0.0001);
  EXPECT_EQ(test_struct->optional_value, 0);
  EXPECT_FALSE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(test_struct->unique_ptr_value, nullptr);

  test_struct = Parse<TestStruct>(
      "{\"value\": [], \"optional_value\": {}, "
      "\"std_optional_value\": true, \"unique_ptr_value\": false}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: ["
            "field:optional_value error:is not a number; "
            "field:std_optional_value error:is not a number; "
            "field:unique_ptr_value error:is not a number; "
            "field:value error:is not a number]")
      << test_struct.status();
}

REGISTER_TYPED_TEST_SUITE_P(FloatingPointTest, FloatFields);

using FloatingPointTypes = ::testing::Types<float, double>;
INSTANTIATE_TYPED_TEST_SUITE_P(My, FloatingPointTest, FloatingPointTypes);

TEST(JsonObjectLoader, BooleanFields) {
  struct TestStruct {
    bool value = false;
    bool optional_value = true;
    std::optional<bool> std_optional_value;
    std::unique_ptr<bool> unique_ptr_value;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader =
          JsonObjectLoader<TestStruct>()
              .Field("value", &TestStruct::value)
              .OptionalField("optional_value", &TestStruct::optional_value)
              .OptionalField("std_optional_value",
                             &TestStruct::std_optional_value)
              .OptionalField("unique_ptr_value", &TestStruct::unique_ptr_value)
              .Finish();
      return loader;
    }
  };

  auto test_struct = Parse<TestStruct>("{\"value\": true}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->value, true);
  EXPECT_EQ(test_struct->optional_value, true);
  EXPECT_FALSE(test_struct->std_optional_value.has_value());

  test_struct = Parse<TestStruct>("{\"value\": false}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->value, false);
  EXPECT_EQ(test_struct->optional_value, true);
  EXPECT_FALSE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(test_struct->unique_ptr_value, nullptr);

  test_struct = Parse<TestStruct>("{}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: [field:value error:field not present]")
      << test_struct.status();

  test_struct = Parse<TestStruct>(
      "{\"value\": true, \"optional_value\": false,"
      "\"std_optional_value\": true, \"unique_ptr_value\": false}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->value, true);
  EXPECT_EQ(test_struct->optional_value, false);
  EXPECT_EQ(test_struct->std_optional_value, true);
  ASSERT_NE(test_struct->unique_ptr_value, nullptr);
  EXPECT_EQ(*test_struct->unique_ptr_value, false);

  test_struct = Parse<TestStruct>(
      "{\"value\": true, \"optional_value\": null,"
      "\"std_optional_value\": null, \"unique_ptr_value\": null}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->value, true);
  EXPECT_EQ(test_struct->optional_value, true);
  EXPECT_FALSE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(test_struct->unique_ptr_value, nullptr);

  test_struct = Parse<TestStruct>(
      "{\"value\": [], \"optional_value\": {}, "
      "\"std_optional_value\": 1, \"unique_ptr_value\": \"foo\"}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: ["
            "field:optional_value error:is not a boolean; "
            "field:std_optional_value error:is not a boolean; "
            "field:unique_ptr_value error:is not a boolean; "
            "field:value error:is not a boolean]")
      << test_struct.status();
}

TEST(JsonObjectLoader, StringFields) {
  struct TestStruct {
    std::string value;
    std::string optional_value;
    std::optional<std::string> std_optional_value;
    std::unique_ptr<std::string> unique_ptr_value;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader =
          JsonObjectLoader<TestStruct>()
              .Field("value", &TestStruct::value)
              .OptionalField("optional_value", &TestStruct::optional_value)
              .OptionalField("std_optional_value",
                             &TestStruct::std_optional_value)
              .OptionalField("unique_ptr_value", &TestStruct::unique_ptr_value)
              .Finish();
      return loader;
    }
  };

  auto test_struct = Parse<TestStruct>("{\"value\": \"foo\"}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->value, "foo");
  EXPECT_EQ(test_struct->optional_value, "");
  EXPECT_FALSE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(test_struct->unique_ptr_value, nullptr);

  test_struct = Parse<TestStruct>("{}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: [field:value error:field not present]")
      << test_struct.status();

  test_struct = Parse<TestStruct>(
      "{\"value\": \"foo\", \"optional_value\": \"bar\","
      "\"std_optional_value\": \"baz\", \"unique_ptr_value\": \"quux\"}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->value, "foo");
  EXPECT_EQ(test_struct->optional_value, "bar");
  EXPECT_EQ(test_struct->std_optional_value, "baz");
  ASSERT_NE(test_struct->unique_ptr_value, nullptr);
  EXPECT_EQ(*test_struct->unique_ptr_value, "quux");

  test_struct = Parse<TestStruct>(
      "{\"value\": \"foo\", \"optional_value\": null,"
      "\"std_optional_value\": null, \"unique_ptr_value\": null}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->value, "foo");
  EXPECT_EQ(test_struct->optional_value, "");
  EXPECT_FALSE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(test_struct->unique_ptr_value, nullptr);

  test_struct = Parse<TestStruct>(
      "{\"value\": [], \"optional_value\": {}, "
      "\"std_optional_value\": 1, \"unique_ptr_value\": true}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: ["
            "field:optional_value error:is not a string; "
            "field:std_optional_value error:is not a string; "
            "field:unique_ptr_value error:is not a string; "
            "field:value error:is not a string]")
      << test_struct.status();
}

TEST(JsonObjectLoader, DurationFields) {
  struct TestStruct {
    Duration value = Duration::Zero();
    Duration optional_value = Duration::Zero();
    std::optional<Duration> std_optional_value;
    std::unique_ptr<Duration> unique_ptr_value;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader =
          JsonObjectLoader<TestStruct>()
              .Field("value", &TestStruct::value)
              .OptionalField("optional_value", &TestStruct::optional_value)
              .OptionalField("std_optional_value",
                             &TestStruct::std_optional_value)
              .OptionalField("unique_ptr_value", &TestStruct::unique_ptr_value)
              .Finish();
      return loader;
    }
  };

  auto test_struct = Parse<TestStruct>("{\"value\": \"3s\"}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->value, Duration::Seconds(3));
  EXPECT_EQ(test_struct->optional_value, Duration::Zero());
  EXPECT_FALSE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(test_struct->unique_ptr_value, nullptr);

  test_struct = Parse<TestStruct>(
      "{\"value\": \"3sec\", \"optional_value\": \"foos\","
      "\"std_optional_value\": \"1.0123456789s\"}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: ["
            "field:optional_value error:"
            "Not a duration (not a number of seconds); "
            "field:std_optional_value error:"
            "Not a duration (too many digits after decimal); "
            "field:value error:Not a duration (no s suffix)]")
      << test_struct.status();
  test_struct = Parse<TestStruct>("{\"value\": \"315576000001s\"}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: ["
            "field:value error:seconds must be in the range [0, 315576000000]]")
      << test_struct.status();
  test_struct = Parse<TestStruct>("{\"value\": \"3.xs\"}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: ["
            "field:value error:Not a duration (not a number of nanoseconds)]")
      << test_struct.status();

  test_struct = Parse<TestStruct>("{}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: [field:value error:field not present]")
      << test_struct.status();

  test_struct = Parse<TestStruct>(
      "{\"value\": \"3s\", \"optional_value\": \"3.2s\", "
      "\"std_optional_value\": \"10s\", \"unique_ptr_value\": \"11s\"}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->value, Duration::Seconds(3));
  EXPECT_EQ(test_struct->optional_value, Duration::Milliseconds(3200));
  EXPECT_EQ(test_struct->std_optional_value, Duration::Seconds(10));
  ASSERT_NE(test_struct->unique_ptr_value, nullptr);
  EXPECT_EQ(*test_struct->unique_ptr_value, Duration::Seconds(11));

  test_struct = Parse<TestStruct>(
      "{\"value\": \"3s\", \"optional_value\": null, "
      "\"std_optional_value\": null, \"unique_ptr_value\": null}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->value, Duration::Seconds(3));
  EXPECT_EQ(test_struct->optional_value, Duration::Zero());
  EXPECT_FALSE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(test_struct->unique_ptr_value, nullptr);

  test_struct = Parse<TestStruct>(
      "{\"value\": [], \"optional_value\": {}, "
      "\"std_optional_value\": 1, \"unique_ptr_value\": true}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: ["
            "field:optional_value error:is not a string; "
            "field:std_optional_value error:is not a string; "
            "field:unique_ptr_value error:is not a string; "
            "field:value error:is not a string]")
      << test_struct.status();
}

TEST(JsonObjectLoader, JsonObjectFields) {
  struct TestStruct {
    Json::Object value;
    Json::Object optional_value;
    std::optional<Json::Object> std_optional_value;
    std::unique_ptr<Json::Object> unique_ptr_value;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader =
          JsonObjectLoader<TestStruct>()
              .Field("value", &TestStruct::value)
              .OptionalField("optional_value", &TestStruct::optional_value)
              .OptionalField("std_optional_value",
                             &TestStruct::std_optional_value)
              .OptionalField("unique_ptr_value", &TestStruct::unique_ptr_value)
              .Finish();
      return loader;
    }
  };

  auto test_struct = Parse<TestStruct>("{\"value\": {\"a\":1}}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(JsonDump(Json::FromObject(test_struct->value)), "{\"a\":1}");
  EXPECT_EQ(JsonDump(Json::FromObject(test_struct->optional_value)), "{}");
  EXPECT_FALSE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(test_struct->unique_ptr_value, nullptr);

  test_struct = Parse<TestStruct>("{}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: [field:value error:field not present]")
      << test_struct.status();

  test_struct = Parse<TestStruct>(
      "{\"value\": {\"a\":1}, \"optional_value\": {\"b\":2}, "
      "\"std_optional_value\": {\"c\":3}, \"unique_ptr_value\": {\"d\":4}}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(JsonDump(Json::FromObject(test_struct->value)), "{\"a\":1}");
  EXPECT_EQ(JsonDump(Json::FromObject(test_struct->optional_value)),
            "{\"b\":2}");
  ASSERT_TRUE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(JsonDump(Json::FromObject(*test_struct->std_optional_value)),
            "{\"c\":3}");
  ASSERT_NE(test_struct->unique_ptr_value, nullptr);
  EXPECT_EQ(JsonDump(Json::FromObject(*test_struct->unique_ptr_value)),
            "{\"d\":4}");

  test_struct = Parse<TestStruct>(
      "{\"value\": {\"a\":1}, \"optional_value\": null, "
      "\"std_optional_value\": null, \"unique_ptr_value\": null}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(JsonDump(Json::FromObject(test_struct->value)), "{\"a\":1}");
  EXPECT_EQ(JsonDump(Json::FromObject(test_struct->optional_value)), "{}");
  EXPECT_FALSE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(test_struct->unique_ptr_value, nullptr);

  test_struct = Parse<TestStruct>(
      "{\"value\": [], \"optional_value\": true, "
      "\"std_optional_value\": 1, \"unique_ptr_value\": \"foo\"}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: ["
            "field:optional_value error:is not an object; "
            "field:std_optional_value error:is not an object; "
            "field:unique_ptr_value error:is not an object; "
            "field:value error:is not an object]")
      << test_struct.status();
}

TEST(JsonObjectLoader, JsonArrayFields) {
  struct TestStruct {
    Json::Array value;
    Json::Array optional_value;
    std::optional<Json::Array> std_optional_value;
    std::unique_ptr<Json::Array> unique_ptr_value;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader =
          JsonObjectLoader<TestStruct>()
              .Field("value", &TestStruct::value)
              .OptionalField("optional_value", &TestStruct::optional_value)
              .OptionalField("std_optional_value",
                             &TestStruct::std_optional_value)
              .OptionalField("unique_ptr_value", &TestStruct::unique_ptr_value)
              .Finish();
      return loader;
    }
  };

  auto test_struct = Parse<TestStruct>("{\"value\": [1, \"a\"]}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(JsonDump(Json::FromArray(test_struct->value)), "[1,\"a\"]");
  EXPECT_EQ(JsonDump(Json::FromArray(test_struct->optional_value)), "[]");
  EXPECT_FALSE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(test_struct->unique_ptr_value, nullptr);

  test_struct = Parse<TestStruct>("{}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: [field:value error:field not present]")
      << test_struct.status();

  test_struct = Parse<TestStruct>(
      "{\"value\": [1, \"a\"], \"optional_value\": [2, \"b\"], "
      "\"std_optional_value\": [3, \"c\"], \"unique_ptr_value\": [4, \"d\"]}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(JsonDump(Json::FromArray(test_struct->value)), "[1,\"a\"]");
  EXPECT_EQ(JsonDump(Json::FromArray(test_struct->optional_value)),
            "[2,\"b\"]");
  ASSERT_TRUE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(JsonDump(Json::FromArray(*test_struct->std_optional_value)),
            "[3,\"c\"]");
  ASSERT_NE(test_struct->unique_ptr_value, nullptr);
  EXPECT_EQ(JsonDump(Json::FromArray(*test_struct->unique_ptr_value)),
            "[4,\"d\"]");

  test_struct = Parse<TestStruct>(
      "{\"value\": [1, \"a\"], \"optional_value\": null, "
      "\"std_optional_value\": null, \"unique_ptr_value\": null}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(JsonDump(Json::FromArray(test_struct->value)), "[1,\"a\"]");
  EXPECT_EQ(JsonDump(Json::FromArray(test_struct->optional_value)), "[]");
  EXPECT_FALSE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(test_struct->unique_ptr_value, nullptr);

  test_struct = Parse<TestStruct>(
      "{\"value\": {}, \"optional_value\": true, "
      "\"std_optional_value\": 1, \"unique_ptr_value\": \"foo\"}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: ["
            "field:optional_value error:is not an array; "
            "field:std_optional_value error:is not an array; "
            "field:unique_ptr_value error:is not an array; "
            "field:value error:is not an array]")
      << test_struct.status();
}

TEST(JsonObjectLoader, MapFields) {
  struct TestStruct {
    std::map<std::string, int32_t> value;
    std::map<std::string, std::string> optional_value;
    std::optional<std::map<std::string, bool>> std_optional_value;
    std::unique_ptr<std::map<std::string, int32_t>> unique_ptr_value;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader =
          JsonObjectLoader<TestStruct>()
              .Field("value", &TestStruct::value)
              .OptionalField("optional_value", &TestStruct::optional_value)
              .OptionalField("std_optional_value",
                             &TestStruct::std_optional_value)
              .OptionalField("unique_ptr_value", &TestStruct::unique_ptr_value)
              .Finish();
      return loader;
    }
  };

  auto test_struct = Parse<TestStruct>("{\"value\": {\"a\":1}}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_THAT(test_struct->value,
              ::testing::ElementsAre(::testing::Pair("a", 1)));
  EXPECT_THAT(test_struct->optional_value, ::testing::ElementsAre());
  EXPECT_FALSE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(test_struct->unique_ptr_value, nullptr);

  test_struct = Parse<TestStruct>("{}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: [field:value error:field not present]")
      << test_struct.status();

  test_struct = Parse<TestStruct>(
      "{\"value\": {\"a\":1}, \"optional_value\": {\"b\":\"foo\"}, "
      "\"std_optional_value\": {\"c\":true}, "
      "\"unique_ptr_value\": {\"d\":4}}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_THAT(test_struct->value,
              ::testing::ElementsAre(::testing::Pair("a", 1)));
  EXPECT_THAT(test_struct->optional_value,
              ::testing::ElementsAre(::testing::Pair("b", "foo")));
  ASSERT_TRUE(test_struct->std_optional_value.has_value());
  EXPECT_THAT(*test_struct->std_optional_value,
              ::testing::ElementsAre(::testing::Pair("c", true)));
  ASSERT_NE(test_struct->unique_ptr_value, nullptr);
  EXPECT_THAT(*test_struct->unique_ptr_value,
              ::testing::ElementsAre(::testing::Pair("d", 4)));

  test_struct = Parse<TestStruct>(
      "{\"value\": {\"a\":1}, \"optional_value\": null, "
      "\"std_optional_value\": null, \"unique_ptr_value\": null}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_THAT(test_struct->value,
              ::testing::ElementsAre(::testing::Pair("a", 1)));
  EXPECT_THAT(test_struct->optional_value, ::testing::ElementsAre());
  EXPECT_FALSE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(test_struct->unique_ptr_value, nullptr);

  test_struct = Parse<TestStruct>(
      "{\"value\": [], \"optional_value\": true, "
      "\"std_optional_value\": 1, \"unique_ptr_value\": \"foo\"}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: ["
            "field:optional_value error:is not an object; "
            "field:std_optional_value error:is not an object; "
            "field:unique_ptr_value error:is not an object; "
            "field:value error:is not an object]")
      << test_struct.status();

  test_struct = Parse<TestStruct>(
      "{\"value\": {\"a\":\"foo\"}, \"optional_value\": {\"b\":true}, "
      "\"std_optional_value\": {\"c\":1}}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: ["
            "field:optional_value[\"b\"] error:is not a string; "
            "field:std_optional_value[\"c\"] error:is not a boolean; "
            "field:value[\"a\"] error:failed to parse number]")
      << test_struct.status();
}

TEST(JsonObjectLoader, MapWithComparatorFields) {
  struct StringCmp {
    using is_transparent = void;
    bool operator()(absl::string_view a, absl::string_view b) const {
      return a < b;
    }
  };

  struct TestStruct {
    std::map<std::string, int32_t, StringCmp> value;
    std::map<std::string, std::string, StringCmp> optional_value;
    std::optional<std::map<std::string, bool, StringCmp>> std_optional_value;
    std::unique_ptr<std::map<std::string, int32_t, StringCmp>> unique_ptr_value;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader =
          JsonObjectLoader<TestStruct>()
              .Field("value", &TestStruct::value)
              .OptionalField("optional_value", &TestStruct::optional_value)
              .OptionalField("std_optional_value",
                             &TestStruct::std_optional_value)
              .OptionalField("unique_ptr_value", &TestStruct::unique_ptr_value)
              .Finish();
      return loader;
    }
  };

  auto test_struct = Parse<TestStruct>("{\"value\": {\"a\":1}}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_THAT(test_struct->value,
              ::testing::ElementsAre(::testing::Pair("a", 1)));
  EXPECT_THAT(test_struct->optional_value, ::testing::ElementsAre());
  EXPECT_FALSE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(test_struct->unique_ptr_value, nullptr);

  test_struct = Parse<TestStruct>("{}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: [field:value error:field not present]")
      << test_struct.status();

  test_struct = Parse<TestStruct>(
      "{\"value\": {\"a\":1}, \"optional_value\": {\"b\":\"foo\"}, "
      "\"std_optional_value\": {\"c\":true}, "
      "\"unique_ptr_value\": {\"d\":4}}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_THAT(test_struct->value,
              ::testing::ElementsAre(::testing::Pair("a", 1)));
  EXPECT_THAT(test_struct->optional_value,
              ::testing::ElementsAre(::testing::Pair("b", "foo")));
  ASSERT_TRUE(test_struct->std_optional_value.has_value());
  EXPECT_THAT(*test_struct->std_optional_value,
              ::testing::ElementsAre(::testing::Pair("c", true)));
  ASSERT_NE(test_struct->unique_ptr_value, nullptr);
  EXPECT_THAT(*test_struct->unique_ptr_value,
              ::testing::ElementsAre(::testing::Pair("d", 4)));

  test_struct = Parse<TestStruct>(
      "{\"value\": {\"a\":1}, \"optional_value\": null, "
      "\"std_optional_value\": null, \"unique_ptr_value\": null}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_THAT(test_struct->value,
              ::testing::ElementsAre(::testing::Pair("a", 1)));
  EXPECT_THAT(test_struct->optional_value, ::testing::ElementsAre());
  EXPECT_FALSE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(test_struct->unique_ptr_value, nullptr);

  test_struct = Parse<TestStruct>(
      "{\"value\": [], \"optional_value\": true, "
      "\"std_optional_value\": 1, \"unique_ptr_value\": \"foo\"}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: ["
            "field:optional_value error:is not an object; "
            "field:std_optional_value error:is not an object; "
            "field:unique_ptr_value error:is not an object; "
            "field:value error:is not an object]")
      << test_struct.status();

  test_struct = Parse<TestStruct>(
      "{\"value\": {\"a\":\"foo\"}, \"optional_value\": {\"b\":true}, "
      "\"std_optional_value\": {\"c\":1}}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: ["
            "field:optional_value[\"b\"] error:is not a string; "
            "field:std_optional_value[\"c\"] error:is not a boolean; "
            "field:value[\"a\"] error:failed to parse number]")
      << test_struct.status();
}

TEST(JsonObjectLoader, VectorFields) {
  struct TestStruct {
    std::vector<int32_t> value;
    std::vector<std::string> optional_value;
    std::optional<std::vector<bool>> std_optional_value;
    std::unique_ptr<std::vector<int32_t>> unique_ptr_value;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader =
          JsonObjectLoader<TestStruct>()
              .Field("value", &TestStruct::value)
              .OptionalField("optional_value", &TestStruct::optional_value)
              .OptionalField("std_optional_value",
                             &TestStruct::std_optional_value)
              .OptionalField("unique_ptr_value", &TestStruct::unique_ptr_value)
              .Finish();
      return loader;
    }
  };

  auto test_struct = Parse<TestStruct>("{\"value\": [1, 2, 3]}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_THAT(test_struct->value, ::testing::ElementsAre(1, 2, 3));
  EXPECT_THAT(test_struct->optional_value, ::testing::ElementsAre());
  EXPECT_FALSE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(test_struct->unique_ptr_value, nullptr);

  test_struct = Parse<TestStruct>("{}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: [field:value error:field not present]")
      << test_struct.status();

  test_struct = Parse<TestStruct>(
      "{\"value\": [4, 5, 6], \"optional_value\": [\"foo\", \"bar\"], "
      "\"std_optional_value\": [true, false, true], "
      "\"unique_ptr_value\": [1, 2, 3]}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_THAT(test_struct->value, ::testing::ElementsAre(4, 5, 6));
  EXPECT_THAT(test_struct->optional_value,
              ::testing::ElementsAre("foo", "bar"));
  ASSERT_TRUE(test_struct->std_optional_value.has_value());
  EXPECT_THAT(*test_struct->std_optional_value,
              ::testing::ElementsAre(true, false, true));
  ASSERT_NE(test_struct->unique_ptr_value, nullptr);
  EXPECT_THAT(*test_struct->unique_ptr_value, ::testing::ElementsAre(1, 2, 3));

  test_struct = Parse<TestStruct>(
      "{\"value\": [4, 5, 6], \"optional_value\": null, "
      "\"std_optional_value\": null, \"unique_ptr_value\": null}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_THAT(test_struct->value, ::testing::ElementsAre(4, 5, 6));
  EXPECT_THAT(test_struct->optional_value, ::testing::ElementsAre());
  EXPECT_FALSE(test_struct->std_optional_value.has_value());
  EXPECT_EQ(test_struct->unique_ptr_value, nullptr);

  test_struct = Parse<TestStruct>(
      "{\"value\": {}, \"optional_value\": true, "
      "\"std_optional_value\": 1, \"unique_ptr_value\": \"foo\"}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: ["
            "field:optional_value error:is not an array; "
            "field:std_optional_value error:is not an array; "
            "field:unique_ptr_value error:is not an array; "
            "field:value error:is not an array]")
      << test_struct.status();

  test_struct = Parse<TestStruct>(
      "{\"value\": [\"foo\", \"bar\"], \"optional_value\": [true, false], "
      "\"std_optional_value\": [1, 2]}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: ["
            "field:optional_value[0] error:is not a string; "
            "field:optional_value[1] error:is not a string; "
            "field:std_optional_value[0] error:is not a boolean; "
            "field:std_optional_value[1] error:is not a boolean; "
            "field:value[0] error:failed to parse number; "
            "field:value[1] error:failed to parse number]")
      << test_struct.status();
}

TEST(JsonObjectLoader, NestedStructFields) {
  struct NestedStruct {
    int32_t inner = 0;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader = JsonObjectLoader<NestedStruct>()
                                      .Field("inner", &NestedStruct::inner)
                                      .Finish();
      return loader;
    }
  };
  struct TestStruct {
    NestedStruct outer;
    NestedStruct optional_outer;
    std::optional<NestedStruct> absl_optional_outer;
    std::unique_ptr<NestedStruct> unique_ptr_outer;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader =
          JsonObjectLoader<TestStruct>()
              .Field("outer", &TestStruct::outer)
              .OptionalField("optional_outer", &TestStruct::optional_outer)
              .OptionalField("absl_optional_outer",
                             &TestStruct::absl_optional_outer)
              .OptionalField("unique_ptr_outer", &TestStruct::unique_ptr_outer)
              .Finish();
      return loader;
    }
  };

  auto test_struct = Parse<TestStruct>("{\"outer\": {\"inner\": 1}}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->outer.inner, 1);
  EXPECT_EQ(test_struct->optional_outer.inner, 0);
  EXPECT_FALSE(test_struct->absl_optional_outer.has_value());
  EXPECT_EQ(test_struct->unique_ptr_outer, nullptr);

  test_struct = Parse<TestStruct>("{}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: [field:outer error:field not present]")
      << test_struct.status();

  test_struct = Parse<TestStruct>("{\"outer\": {}}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(
      test_struct.status().message(),
      "errors validating JSON: [field:outer.inner error:field not present]")
      << test_struct.status();

  test_struct = Parse<TestStruct>(
      "{\"outer\": {\"inner\":1}, \"optional_outer\": {\"inner\":2}, "
      "\"absl_optional_outer\": {\"inner\":3}, "
      "\"unique_ptr_outer\": {\"inner\":4}}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->outer.inner, 1);
  EXPECT_EQ(test_struct->optional_outer.inner, 2);
  ASSERT_TRUE(test_struct->absl_optional_outer.has_value());
  EXPECT_EQ(test_struct->absl_optional_outer->inner, 3);
  ASSERT_NE(test_struct->unique_ptr_outer, nullptr);
  EXPECT_EQ(test_struct->unique_ptr_outer->inner, 4);

  test_struct = Parse<TestStruct>(
      "{\"outer\": {\"inner\":1}, \"optional_outer\": null, "
      "\"absl_optional_outer\": null, \"unique_ptr_outer\": null}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->outer.inner, 1);
  EXPECT_EQ(test_struct->optional_outer.inner, 0);
  EXPECT_FALSE(test_struct->absl_optional_outer.has_value());
  EXPECT_EQ(test_struct->unique_ptr_outer, nullptr);

  test_struct = Parse<TestStruct>(
      "{\"outer\": \"foo\", \"optional_outer\": true, "
      "\"absl_optional_outer\": 1, \"unique_ptr_outer\": \"foo\"}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: ["
            "field:absl_optional_outer error:is not an object; "
            "field:optional_outer error:is not an object; "
            "field:outer error:is not an object; "
            "field:unique_ptr_outer error:is not an object]")
      << test_struct.status();

  test_struct = Parse<TestStruct>(
      "{\"outer\": {\"inner\":\"foo\"}, \"optional_outer\": {\"inner\":true}, "
      "\"absl_optional_outer\": {\"inner\":[]}}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: ["
            "field:absl_optional_outer.inner error:is not a number; "
            "field:optional_outer.inner error:is not a number; "
            "field:outer.inner error:failed to parse number]")
      << test_struct.status();
}

TEST(JsonObjectLoader, BareString) {
  auto parsed = Parse<std::string>("\"foo\"");
  ASSERT_TRUE(parsed.ok()) << parsed.status();
  EXPECT_EQ(*parsed, "foo");
  parsed = Parse<std::string>("null");
  EXPECT_EQ(parsed.status().message(),
            "errors validating JSON: [field: error:is not a string]")
      << parsed.status();
}

TEST(JsonObjectLoader, BareDuration) {
  auto parsed = Parse<Duration>("\"1.5s\"");
  ASSERT_TRUE(parsed.ok()) << parsed.status();
  EXPECT_EQ(*parsed, Duration::Milliseconds(1500));
  parsed = Parse<Duration>("null");
  EXPECT_EQ(parsed.status().message(),
            "errors validating JSON: [field: error:is not a string]")
      << parsed.status();
}

TEST(JsonObjectLoader, BareSignedInteger) {
  auto parsed = Parse<int32_t>("5");
  ASSERT_TRUE(parsed.ok()) << parsed.status();
  EXPECT_EQ(*parsed, 5);
  parsed = Parse<int32_t>("null");
  EXPECT_EQ(parsed.status().message(),
            "errors validating JSON: [field: error:is not a number]")
      << parsed.status();
}

TEST(JsonObjectLoader, BareUnsignedInteger) {
  auto parsed = Parse<uint32_t>("5");
  ASSERT_TRUE(parsed.ok()) << parsed.status();
  EXPECT_EQ(*parsed, 5);
  parsed = Parse<uint32_t>("null");
  EXPECT_EQ(parsed.status().message(),
            "errors validating JSON: [field: error:is not a number]")
      << parsed.status();
}

TEST(JsonObjectLoader, BareFloat) {
  auto parsed = Parse<float>("5.2");
  ASSERT_TRUE(parsed.ok()) << parsed.status();
  EXPECT_NEAR(*parsed, 5.2, 0.001);
  parsed = Parse<float>("null");
  EXPECT_EQ(parsed.status().message(),
            "errors validating JSON: [field: error:is not a number]")
      << parsed.status();
}

TEST(JsonObjectLoader, BareBool) {
  auto parsed = Parse<bool>("true");
  ASSERT_TRUE(parsed.ok()) << parsed.status();
  EXPECT_TRUE(*parsed);
  parsed = Parse<bool>("null");
  EXPECT_EQ(parsed.status().message(),
            "errors validating JSON: [field: error:is not a boolean]")
      << parsed.status();
}

TEST(JsonObjectLoader, BareOptional) {
  auto parsed = Parse<std::optional<uint32_t>>("3");
  ASSERT_TRUE(parsed.ok()) << parsed.status();
  ASSERT_TRUE(parsed->has_value());
  EXPECT_EQ(**parsed, 3);
  parsed = Parse<std::optional<uint32_t>>("null");
  EXPECT_EQ(parsed.status().message(),
            "errors validating JSON: [field: error:is not a number]")
      << parsed.status();
}

TEST(JsonObjectLoader, BareUniquePtr) {
  auto parsed = Parse<std::unique_ptr<uint32_t>>("3");
  ASSERT_TRUE(parsed.ok()) << parsed.status();
  ASSERT_NE(*parsed, nullptr);
  EXPECT_EQ(**parsed, 3);
  parsed = Parse<std::unique_ptr<uint32_t>>("null");
  EXPECT_EQ(parsed.status().message(),
            "errors validating JSON: [field: error:is not a number]")
      << parsed.status();
}

TEST(JsonObjectLoader, BareRefCountedPtr) {
  class RefCountedObject : public RefCounted<RefCountedObject> {
   public:
    RefCountedObject() = default;

    int value() const { return value_; }

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader = JsonObjectLoader<RefCountedObject>()
                                      .Field("value", &RefCountedObject::value_)
                                      .Finish();
      return loader;
    }

   private:
    int value_ = -1;
  };
  auto parsed = Parse<RefCountedPtr<RefCountedObject>>("{\"value\": 3}");
  ASSERT_TRUE(parsed.ok()) << parsed.status();
  ASSERT_NE(*parsed, nullptr);
  EXPECT_EQ((*parsed)->value(), 3);
  parsed = Parse<RefCountedPtr<RefCountedObject>>("null");
  EXPECT_EQ(parsed.status().message(),
            "errors validating JSON: [field: error:is not an object]")
      << parsed.status();
}

TEST(JsonObjectLoader, BareVector) {
  auto parsed = Parse<std::vector<int32_t>>("[1, 2, 3]");
  ASSERT_TRUE(parsed.ok()) << parsed.status();
  EXPECT_THAT(*parsed, ::testing::ElementsAre(1, 2, 3));
  parsed = Parse<std::vector<int32_t>>("null");
  EXPECT_EQ(parsed.status().message(),
            "errors validating JSON: [field: error:is not an array]")
      << parsed.status();
}

TEST(JsonObjectLoader, BareMap) {
  auto parsed =
      Parse<std::map<std::string, int32_t>>("{\"a\":1, \"b\":2, \"c\":3}");
  ASSERT_TRUE(parsed.ok()) << parsed.status();
  EXPECT_THAT(*parsed, ::testing::ElementsAre(::testing::Pair("a", 1),
                                              ::testing::Pair("b", 2),
                                              ::testing::Pair("c", 3)));
  parsed = Parse<std::map<std::string, int32_t>>("null");
  EXPECT_EQ(parsed.status().message(),
            "errors validating JSON: [field: error:is not an object]")
      << parsed.status();
}

TEST(JsonObjectLoader, IgnoresUnsupportedFields) {
  struct TestStruct {
    int32_t a = 0;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader =
          JsonObjectLoader<TestStruct>().Field("a", &TestStruct::a).Finish();
      return loader;
    }
  };
  auto test_struct = Parse<TestStruct>("{\"a\": 3, \"b\":false}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->a, 3);
}

TEST(JsonObjectLoader, IgnoresDisabledFields) {
  class FakeJsonArgs : public JsonArgs {
   public:
    FakeJsonArgs() = default;

    bool IsEnabled(absl::string_view key) const override {
      return key != "disabled";
    }
  };
  struct TestStruct {
    int32_t a = 0;
    int32_t b = 0;
    int32_t c = 0;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader =
          JsonObjectLoader<TestStruct>()
              .Field("a", &TestStruct::a, "disabled")
              .OptionalField("b", &TestStruct::b, "disabled")
              .OptionalField("c", &TestStruct::c, "enabled")
              .Finish();
      return loader;
    }
  };

  auto test_struct =
      Parse<TestStruct>("{\"a\":false, \"b\":false, \"c\":1}", FakeJsonArgs());
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->a, 0);
  EXPECT_EQ(test_struct->b, 0);
  EXPECT_EQ(test_struct->c, 1);
}

TEST(JsonObjectLoader, PostLoadHook) {
  struct TestStruct {
    int32_t a = 0;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader = JsonObjectLoader<TestStruct>()
                                      .OptionalField("a", &TestStruct::a)
                                      .Finish();
      return loader;
    }

    void JsonPostLoad(const Json& , const JsonArgs& ,
                      ValidationErrors* ) {
      ++a;
    }
  };
  auto test_struct = Parse<TestStruct>("{\"a\": 1}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->a, 2);
  test_struct = Parse<TestStruct>("{}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->a, 1);
}

TEST(JsonObjectLoader, CustomValidationInPostLoadHook) {
  struct TestStruct {
    int32_t a = 0;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader =
          JsonObjectLoader<TestStruct>().Field("a", &TestStruct::a).Finish();
      return loader;
    }

    void JsonPostLoad(const Json& , const JsonArgs& ,
                      ValidationErrors* errors) {
      ValidationErrors::ScopedField field(errors, ".a");
      if (!errors->FieldHasErrors() && a <= 0) {
        errors->AddError("must be greater than 0");
      }
    }
  };

  auto test_struct = Parse<TestStruct>("{\"a\": 1}");
  ASSERT_TRUE(test_struct.ok()) << test_struct.status();
  EXPECT_EQ(test_struct->a, 1);

  test_struct = Parse<TestStruct>("{\"a\": 0}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: [field:a error:must be greater than 0]")
      << test_struct.status();

  test_struct = Parse<TestStruct>("{\"a\": []}");
  EXPECT_EQ(test_struct.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(test_struct.status().message(),
            "errors validating JSON: [field:a error:is not a number]")
      << test_struct.status();
}

TEST(JsonObjectLoader, LoadFromJsonWithValidationErrors) {
  struct TestStruct {
    int32_t a = 0;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader =
          JsonObjectLoader<TestStruct>().Field("a", &TestStruct::a).Finish();
      return loader;
    }
  };

  {
    absl::string_view json_str = "{\"a\":1}";
    auto json = JsonParse(json_str);
    ASSERT_TRUE(json.ok()) << json.status();
    ValidationErrors errors;
    TestStruct test_struct =
        LoadFromJson<TestStruct>(*json, JsonArgs(), &errors);
    ASSERT_TRUE(errors.ok()) << errors.status(
        absl::StatusCode::kInvalidArgument, "unexpected errors");
    EXPECT_EQ(test_struct.a, 1);
  }

  {
    absl::string_view json_str = "{\"a\":\"foo\"}";
    auto json = JsonParse(json_str);
    ASSERT_TRUE(json.ok()) << json.status();
    ValidationErrors errors;
    LoadFromJson<TestStruct>(*json, JsonArgs(), &errors);
    absl::Status status = errors.status(absl::StatusCode::kInvalidArgument,
                                        "errors validating JSON");
    EXPECT_EQ(status.code(), absl::StatusCode::kInvalidArgument);
    EXPECT_EQ(status.message(),
              "errors validating JSON: [field:a error:failed to parse number]")
        << status;
  }
}

TEST(JsonObjectLoader, LoadJsonObjectField) {
  absl::string_view json_str = "{\"int\":1}";
  auto json = JsonParse(json_str);
  ASSERT_TRUE(json.ok()) << json.status();

  {
    ValidationErrors errors;
    auto value = LoadJsonObjectField<int32_t>(json->object(), JsonArgs(), "int",
                                              &errors);
    ASSERT_TRUE(value.has_value()) << errors.status(
        absl::StatusCode::kInvalidArgument, "unexpected errors");
    EXPECT_EQ(*value, 1);
    EXPECT_TRUE(errors.ok());
  }

  {
    ValidationErrors errors;
    auto value = LoadJsonObjectField<int32_t>(json->object(), JsonArgs(),
                                              "not_present", &errors,
                                              false);
    EXPECT_FALSE(value.has_value());
    EXPECT_TRUE(errors.ok());
  }

  {
    ValidationErrors errors;
    auto value = LoadJsonObjectField<int32_t>(json->object(), JsonArgs(),
                                              "not_present", &errors);
    EXPECT_FALSE(value.has_value());
    auto status = errors.status(absl::StatusCode::kInvalidArgument,
                                "errors validating JSON");
    EXPECT_THAT(status.code(), absl::StatusCode::kInvalidArgument);
    EXPECT_EQ(status.message(),
              "errors validating JSON: ["
              "field:not_present error:field not present]")
        << status;
  }

  {
    ValidationErrors errors;
    auto value = LoadJsonObjectField<std::string>(json->object(), JsonArgs(),
                                                  "int", &errors);
    EXPECT_FALSE(value.has_value());
    auto status = errors.status(absl::StatusCode::kInvalidArgument,
                                "errors validating JSON");
    EXPECT_THAT(status.code(), absl::StatusCode::kInvalidArgument);
    EXPECT_EQ(status.message(),
              "errors validating JSON: [field:int error:is not a string]")
        << status;
  }
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
