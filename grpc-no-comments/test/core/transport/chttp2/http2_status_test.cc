
// Copyright 2025 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/http2_status.h"

#include <string>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "gtest/gtest.h"
#include "src/core/ext/transport/chttp2/transport/frame.h"
#include "test/core/transport/chttp2/http2_common_test_inputs.h"

namespace grpc_core {
namespace http2 {
namespace testing {

TEST(Http2StatusTest, MoveTest) {
  Http2Status old_status = Http2Status::Http2ConnectionError(
      Http2ErrorCode::kProtocolError, "Message1");
  EXPECT_GT(old_status.DebugString().size(), 1);
  auto test_lambda = [new_status = std::move(old_status)]() {
    LOG(INFO) << new_status.DebugString();
    EXPECT_GT(new_status.DebugString().size(), 1);
  };
  test_lambda();
}

TEST(Http2StatusTest, ReturnTest) {
  auto test_lambda = []() -> Http2Status {
    constexpr absl::string_view kMessage = "Message2";
    Http2Status status1 = Http2Status::Http2ConnectionError(
        Http2ErrorCode::kProtocolError, std::string(kMessage));
    EXPECT_GT(status1.DebugString().size(), 1);
    return status1;
  };
  Http2Status status2 = test_lambda();
  EXPECT_GT(status2.DebugString().size(), 1);
}

TEST(Http2StatusTest, OkTest) {
  Http2Status status = Http2Status::Ok();

  Http2Status::Http2ErrorType type = status.GetType();
  EXPECT_EQ(type, Http2Status::Http2ErrorType::kOk);

  ASSERT_DEATH(
      { GRPC_UNUSED Http2ErrorCode code1 = status.GetConnectionErrorCode(); },
      "");
  ASSERT_DEATH(
      { GRPC_UNUSED Http2ErrorCode code2 = status.GetStreamErrorCode(); }, "");

  EXPECT_GT(status.DebugString().size(), 1);

  EXPECT_TRUE(status.IsOk());

}

TEST(Http2StatusTest, Http2ConnectionErrorTest) {
  std::vector<Http2ErrorCode> codes = GetErrorCodes();
  for (const Http2ErrorCode& code : codes) {
    Http2Status status = Http2Status::Http2ConnectionError(code, "Message1");

    EXPECT_EQ(status.GetType(), Http2Status::Http2ErrorType::kConnectionError);

    EXPECT_EQ(status.GetConnectionErrorCode(), code);
    ASSERT_DEATH(
        { GRPC_UNUSED Http2ErrorCode code1 = status.GetStreamErrorCode(); },
        "");

    EXPECT_FALSE(status.IsOk());

    absl::Status absl_status = status.GetAbslConnectionError();
    EXPECT_FALSE(absl_status.ok());
    EXPECT_STREQ(std::string(absl_status.message()).c_str(), "Message1");
  }
}

TEST(Http2StatusTest, Http2StreamErrorTest) {
  std::vector<Http2ErrorCode> codes = GetErrorCodes();
  for (const Http2ErrorCode& code : codes) {
    Http2Status status = Http2Status::Http2StreamError(code, "Message1");

    EXPECT_EQ(status.GetType(), Http2Status::Http2ErrorType::kStreamError);

    EXPECT_EQ(status.GetStreamErrorCode(), code);
    ASSERT_DEATH(
        { GRPC_UNUSED Http2ErrorCode code1 = status.GetConnectionErrorCode(); },
        "");

    EXPECT_FALSE(status.IsOk());

    absl::Status absl_status = status.GetAbslStreamError();
    EXPECT_FALSE(absl_status.ok());
    EXPECT_STREQ(std::string(absl_status.message()).c_str(), "Message1");
  }
}

TEST(Http2StatusTest, AbslConnectionErrorTest) {
  std::vector<absl::StatusCode> codes = FewAbslErrorCodes();
  for (const absl::StatusCode& code : codes) {
    Http2Status status = Http2Status::AbslConnectionError(code, "Message1");

    EXPECT_EQ(status.GetType(), Http2Status::Http2ErrorType::kConnectionError);

    EXPECT_EQ(status.GetConnectionErrorCode(), Http2ErrorCode::kInternalError);
    ASSERT_DEATH(
        { GRPC_UNUSED Http2ErrorCode code1 = status.GetStreamErrorCode(); },
        "");

    EXPECT_FALSE(status.IsOk());

    absl::Status absl_status = status.GetAbslConnectionError();
    EXPECT_FALSE(absl_status.ok());
    EXPECT_EQ(absl_status.code(), code);
    EXPECT_STREQ(std::string(absl_status.message()).c_str(), "Message1");
  }
}

TEST(Http2StatusTest, AbslStreamErrorTest) {
  std::vector<absl::StatusCode> codes = FewAbslErrorCodes();
  for (const absl::StatusCode& code : codes) {
    Http2Status status = Http2Status::AbslStreamError(code, "Message1");

    EXPECT_EQ(status.GetType(), Http2Status::Http2ErrorType::kStreamError);

    EXPECT_EQ(status.GetStreamErrorCode(), Http2ErrorCode::kInternalError);
    ASSERT_DEATH(
        { GRPC_UNUSED Http2ErrorCode code1 = status.GetConnectionErrorCode(); },
        "");

    EXPECT_FALSE(status.IsOk());

    absl::Status absl_status = status.GetAbslStreamError();
    EXPECT_FALSE(absl_status.ok());
    EXPECT_EQ(absl_status.code(), code);
    EXPECT_STREQ(std::string(absl_status.message()).c_str(), "Message1");
  }
}

TEST(ValueOrHttp2StatusTest, ValuePrimitiveDataType) {
  auto test_lambda = []() -> ValueOrHttp2Status<int> {
    return ValueOrHttp2Status<int>(100);
  };
  ValueOrHttp2Status<int> result = test_lambda();

  EXPECT_TRUE(result.IsOk());

  int result1 = result.value();
  EXPECT_EQ(result1, 100);
}

TEST(ValueOrHttp2StatusTest, ValueSliceBuffer) {
  auto test_lambda = []() -> ValueOrHttp2Status<SliceBuffer> {
    SliceBuffer payload;
    payload.Append(Slice::FromCopiedString(kStr1024));
    return ValueOrHttp2Status<SliceBuffer>(std::move(payload));
  };
  ValueOrHttp2Status<SliceBuffer> result = test_lambda();

  EXPECT_TRUE(result.IsOk());

  SliceBuffer result3 = TakeValue(std::move(result));
  EXPECT_EQ(result3.Length(), 1024);
  EXPECT_STREQ(result3.JoinIntoString().c_str(), std::string(kStr1024).c_str());
}

TEST(ValueOrHttp2StatusTest, ValueHttp2WindowUpdateFrame) {
  auto test_lambda = []() -> ValueOrHttp2Status<Http2WindowUpdateFrame> {
    return ValueOrHttp2Status<Http2WindowUpdateFrame>(
        Http2WindowUpdateFrame{0, 100});
  };
  ValueOrHttp2Status<Http2WindowUpdateFrame> result = test_lambda();

  EXPECT_TRUE(result.IsOk());

  Http2WindowUpdateFrame result3 = result.value();
  EXPECT_EQ(result3.stream_id, 0);
  EXPECT_EQ(result3.increment, 100);
}

TEST(ValueOrHttp2StatusTest, ValueHttp2DataFrame) {
  auto test_lambda = []() -> ValueOrHttp2Status<Http2DataFrame> {
    SliceBuffer temp;
    temp.Append(Slice::FromCopiedString(kStr1024));
    Http2DataFrame frame = Http2DataFrame{1, false, std::move(temp)};
    return ValueOrHttp2Status<Http2DataFrame>(std::move(frame));
  };
  ValueOrHttp2Status<Http2DataFrame> result = test_lambda();

  EXPECT_TRUE(result.IsOk());

  Http2DataFrame result3 = TakeValue(std::move(result));
  EXPECT_EQ(result3.stream_id, 1);
  EXPECT_EQ(result3.end_stream, false);
  EXPECT_STREQ(result3.payload.JoinIntoString().c_str(),
               std::string(kStr1024).c_str());
}

TEST(ValueOrHttp2StatusTest, Http2ConnectionError) {
  auto test_lambda = []() -> ValueOrHttp2Status<int> {
    return ValueOrHttp2Status<int>(Http2Status::Http2ConnectionError(
        Http2ErrorCode::kProtocolError, "Message1"));
  };
  ValueOrHttp2Status<int> result = test_lambda();

  EXPECT_FALSE(result.IsOk());

  EXPECT_EQ(result.GetErrorType(),
            Http2Status::Http2ErrorType::kConnectionError);

  EXPECT_EQ(result.GetConnectionErrorCode(), Http2ErrorCode::kProtocolError);
  ASSERT_DEATH(
      { GRPC_UNUSED Http2ErrorCode code1 = result.GetStreamErrorCode(); }, "");

  absl::Status absl_status = result.GetAbslConnectionError();
  EXPECT_FALSE(absl_status.ok());
  ASSERT_DEATH(
      { GRPC_UNUSED absl::Status result1 = result.GetAbslStreamError(); }, "");
  EXPECT_STREQ(std::string(absl_status.message()).c_str(), "Message1");

  std::string message = result.DebugString();
  EXPECT_STREQ(
      message.c_str(),
      "Connection Error: {Error Code:PROTOCOL_ERROR, Message:Message1}");
}

TEST(ValueOrHttp2StatusTest, Http2StreamError) {
  auto test_lambda = []() -> ValueOrHttp2Status<std::string> {
    return ValueOrHttp2Status<std::string>(Http2Status::Http2StreamError(
        Http2ErrorCode::kProtocolError, "Message1"));
  };
  ValueOrHttp2Status<std::string> result = test_lambda();

  EXPECT_FALSE(result.IsOk());

  EXPECT_EQ(result.GetErrorType(), Http2Status::Http2ErrorType::kStreamError);

  EXPECT_EQ(result.GetStreamErrorCode(), Http2ErrorCode::kProtocolError);
  ASSERT_DEATH(
      { GRPC_UNUSED Http2ErrorCode code1 = result.GetConnectionErrorCode(); },
      "");

  absl::Status absl_status = result.GetAbslStreamError();
  EXPECT_FALSE(absl_status.ok());
  ASSERT_DEATH(
      { GRPC_UNUSED absl::Status result1 = result.GetAbslConnectionError(); },
      "");
  EXPECT_STREQ(std::string(absl_status.message()).c_str(), "Message1");

  std::string message = result.DebugString();
  EXPECT_STREQ(message.c_str(),
               "Stream Error: {Error Code:PROTOCOL_ERROR, Message:Message1}");
}

TEST(ValueOrHttp2StatusTest, AbslConnectionError) {
  auto test_lambda = []() -> ValueOrHttp2Status<std::string> {
    return ValueOrHttp2Status<std::string>(Http2Status::AbslConnectionError(
        absl::StatusCode::kCancelled, "Message1"));
  };
  ValueOrHttp2Status<std::string> result = test_lambda();

  EXPECT_FALSE(result.IsOk());

  EXPECT_EQ(result.GetErrorType(),
            Http2Status::Http2ErrorType::kConnectionError);

  EXPECT_EQ(result.GetConnectionErrorCode(), Http2ErrorCode::kInternalError);
  ASSERT_DEATH(
      { GRPC_UNUSED Http2ErrorCode code2 = result.GetStreamErrorCode(); }, "");

  absl::Status absl_status = result.GetAbslConnectionError();
  EXPECT_FALSE(absl_status.ok());
  ASSERT_DEATH(
      { GRPC_UNUSED absl::Status result1 = result.GetAbslStreamError(); }, "");
  EXPECT_STREQ(std::string(absl_status.message()).c_str(), "Message1");

  std::string message = result.DebugString();
  EXPECT_STREQ(
      message.c_str(),
      "Connection Error: {Error Code:INTERNAL_ERROR, Message:Message1}");
}

TEST(ValueOrHttp2StatusTest, AbslStreamError) {
  auto test_lambda = []() -> ValueOrHttp2Status<std::string> {
    return ValueOrHttp2Status<std::string>(
        Http2Status::AbslStreamError(absl::StatusCode::kCancelled, "Message1"));
  };
  ValueOrHttp2Status<std::string> result = test_lambda();

  EXPECT_FALSE(result.IsOk());

  EXPECT_EQ(result.GetErrorType(), Http2Status::Http2ErrorType::kStreamError);

  EXPECT_EQ(result.GetStreamErrorCode(), Http2ErrorCode::kInternalError);
  ASSERT_DEATH(
      { GRPC_UNUSED Http2ErrorCode code2 = result.GetConnectionErrorCode(); },
      "");

  absl::Status absl_status = result.GetAbslStreamError();
  EXPECT_FALSE(absl_status.ok());
  ASSERT_DEATH(
      { GRPC_UNUSED absl::Status result1 = result.GetAbslConnectionError(); },
      "");
  EXPECT_STREQ(std::string(absl_status.message()).c_str(), "Message1");

  std::string message = result.DebugString();
  EXPECT_STREQ(message.c_str(),
               "Stream Error: {Error Code:INTERNAL_ERROR, Message:Message1}");
}

TEST(ValueOrHttp2StatusTest, TakeStatusStreamTest) {
  auto test_lambda = []() -> ValueOrHttp2Status<std::string> {
    return ValueOrHttp2Status<std::string>(
        Http2Status::AbslStreamError(absl::StatusCode::kCancelled, "Message1"));
  };
  ValueOrHttp2Status<std::string> result = test_lambda();
  Http2Status status =
      ValueOrHttp2Status<std::string>::TakeStatus(std::move(result));

  EXPECT_FALSE(status.IsOk());

  EXPECT_EQ(status.GetType(), Http2Status::Http2ErrorType::kStreamError);

  EXPECT_EQ(status.GetStreamErrorCode(), Http2ErrorCode::kInternalError);
  ASSERT_DEATH(
      { GRPC_UNUSED Http2ErrorCode code2 = status.GetConnectionErrorCode(); },
      "");

  absl::Status absl_status = status.GetAbslStreamError();
  EXPECT_FALSE(absl_status.ok());
  EXPECT_STREQ(std::string(absl_status.message()).c_str(), "Message1");
}

TEST(ValueOrHttp2StatusTest, TakeStatusConnectionTest) {
  auto test_lambda = []() -> ValueOrHttp2Status<std::string> {
    return ValueOrHttp2Status<std::string>(Http2Status::AbslConnectionError(
        absl::StatusCode::kCancelled, "Message1"));
  };
  ValueOrHttp2Status<std::string> result = test_lambda();
  Http2Status status =
      ValueOrHttp2Status<std::string>::TakeStatus(std::move(result));

  EXPECT_FALSE(status.IsOk());

  EXPECT_EQ(status.GetType(), Http2Status::Http2ErrorType::kConnectionError);

  EXPECT_EQ(status.GetConnectionErrorCode(), Http2ErrorCode::kInternalError);
  ASSERT_DEATH(
      { GRPC_UNUSED Http2ErrorCode code2 = status.GetStreamErrorCode(); }, "");

  absl::Status absl_status = status.GetAbslConnectionError();
  EXPECT_FALSE(absl_status.ok());
  EXPECT_STREQ(std::string(absl_status.message()).c_str(), "Message1");
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
