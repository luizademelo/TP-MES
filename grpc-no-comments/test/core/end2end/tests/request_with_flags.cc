
// Copyright 2015 gRPC authors.

#include <grpc/byte_buffer.h>
#include <grpc/grpc.h>
#include <grpc/slice.h>
#include <grpc/status.h>
#include <stdint.h>
#include <string.h>

#include <map>
#include <optional>
#include <utility>

#include "gtest/gtest.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/util/time.h"
#include "test/core/end2end/cq_verifier.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {
namespace {

void InvokeRequestWithFlags(CoreEnd2endTest& test,
                            std::map<grpc_op_type, uint32_t> flags_for_op,
                            grpc_call_error call_start_batch_expected_result) {
  grpc_slice request_payload_slice =
      grpc_slice_from_copied_string("hello world");
  grpc_byte_buffer* request_payload =
      grpc_raw_byte_buffer_create(&request_payload_slice, 1);
  grpc_op ops[6];
  grpc_op* op;
  grpc_metadata_array initial_metadata_recv;
  grpc_metadata_array trailing_metadata_recv;
  grpc_metadata_array request_metadata_recv;
  grpc_call_details call_details;
  grpc_status_code status;
  grpc_call_error error;
  grpc_slice details;

  auto get_flags = [flags_for_op](grpc_op_type op_type) -> uint32_t {
    auto it = flags_for_op.find(op_type);
    if (it == flags_for_op.end()) return 0;
    return it->second;
  };

  grpc_metadata_array_init(&initial_metadata_recv);
  grpc_metadata_array_init(&trailing_metadata_recv);
  grpc_metadata_array_init(&request_metadata_recv);
  grpc_call_details_init(&call_details);

  std::optional<CoreEnd2endTest::Call> c =
      test.NewClientCall("/foo").Timeout(Duration::Seconds(1)).Create();

  memset(ops, 0, sizeof(ops));
  op = ops;
  op->op = GRPC_OP_SEND_INITIAL_METADATA;
  op->data.send_initial_metadata.count = 0;
  op->flags = get_flags(op->op);
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_SEND_MESSAGE;
  op->data.send_message.send_message = request_payload;
  op->flags = get_flags(op->op);
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_SEND_CLOSE_FROM_CLIENT;
  op->flags = get_flags(op->op);
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_RECV_INITIAL_METADATA;
  op->data.recv_initial_metadata.recv_initial_metadata = &initial_metadata_recv;
  op->flags = get_flags(op->op);
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_RECV_STATUS_ON_CLIENT;
  op->data.recv_status_on_client.trailing_metadata = &trailing_metadata_recv;
  op->data.recv_status_on_client.status = &status;
  op->data.recv_status_on_client.status_details = &details;
  op->flags = get_flags(op->op);
  op->reserved = nullptr;
  op++;
  error = grpc_call_start_batch(c->c_call(), ops, static_cast<size_t>(op - ops),
                                CqVerifier::tag(1), nullptr);
  EXPECT_EQ(error, call_start_batch_expected_result);
  if (error == GRPC_CALL_OK) {
    if (test.test_config()->feature_mask & FEATURE_MASK_IS_MINSTACK) {
      c->Cancel();
    }
    test.Expect(1, true);
    test.Step();
    grpc_slice_unref(details);
  }

  c.reset();

  grpc_metadata_array_destroy(&initial_metadata_recv);
  grpc_metadata_array_destroy(&trailing_metadata_recv);
  grpc_metadata_array_destroy(&request_metadata_recv);
  grpc_call_details_destroy(&call_details);
  grpc_byte_buffer_destroy(request_payload);
}

CORE_END2END_TEST(CoreEnd2endTests, BadFlagsOnSendInitialMetadata) {
  InvokeRequestWithFlags(*this, {{GRPC_OP_SEND_INITIAL_METADATA, 0xdeadbeef}},
                         GRPC_CALL_ERROR_INVALID_FLAGS);
}

CORE_END2END_TEST(CoreEnd2endTests, BadFlagsOnSendMessage) {
  InvokeRequestWithFlags(*this, {{GRPC_OP_SEND_MESSAGE, 0xdeadbeef}},
                         GRPC_CALL_ERROR_INVALID_FLAGS);
}

CORE_END2END_TEST(CoreEnd2endTests, BadFlagsOnSendCloseFromClient) {
  InvokeRequestWithFlags(*this, {{GRPC_OP_SEND_CLOSE_FROM_CLIENT, 0xdeadbeef}},
                         GRPC_CALL_ERROR_INVALID_FLAGS);
}

CORE_END2END_TEST(CoreEnd2endTests, BadFlagsOnRecvInitialMetadata) {
  InvokeRequestWithFlags(*this, {{GRPC_OP_RECV_INITIAL_METADATA, 0xdeadbeef}},
                         GRPC_CALL_ERROR_INVALID_FLAGS);
}

CORE_END2END_TEST(CoreEnd2endTests, BadFlagsOnRecvStatusOnClient) {
  InvokeRequestWithFlags(*this, {{GRPC_OP_RECV_STATUS_ON_CLIENT, 0xdeadbeef}},
                         GRPC_CALL_ERROR_INVALID_FLAGS);
}

CORE_END2END_TEST(CoreEnd2endTests, WriteBufferIntAcceptedOnSendMessage) {
  InvokeRequestWithFlags(
      *this, {{GRPC_OP_SEND_MESSAGE, GRPC_WRITE_BUFFER_HINT}}, GRPC_CALL_OK);
}

CORE_END2END_TEST(CoreEnd2endTests, WriteNoCompressAcceptedOnSendMessage) {
  InvokeRequestWithFlags(
      *this, {{GRPC_OP_SEND_MESSAGE, GRPC_WRITE_NO_COMPRESS}}, GRPC_CALL_OK);
}

CORE_END2END_TEST(CoreEnd2endTests,
                  WriteBufferHintAndNoCompressAcceptedOnSendMessage) {
  InvokeRequestWithFlags(
      *this,
      {{GRPC_OP_SEND_MESSAGE, GRPC_WRITE_BUFFER_HINT | GRPC_WRITE_NO_COMPRESS}},
      GRPC_CALL_OK);
}

CORE_END2END_TEST(CoreEnd2endTests,
                  WriteInternalCompressAcceptedOnSendMessage) {
  InvokeRequestWithFlags(*this,
                         {{GRPC_OP_SEND_MESSAGE, GRPC_WRITE_INTERNAL_COMPRESS}},
                         GRPC_CALL_OK);
}

}
}
