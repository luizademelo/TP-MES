
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_UPB_TEST_PARSE_TEXT_PROTO_H_
#define UPB_UPB_TEST_PARSE_TEXT_PROTO_H_

#include <string>

#include <gtest/gtest.h>
#include "google/protobuf/message.h"
#include "google/protobuf/text_format.h"

namespace upb_test {

class ParseTextProtoOrDie {
 public:
  explicit ParseTextProtoOrDie(absl::string_view text_proto)
      : text_proto_(text_proto) {}

  template <class T>
  operator T() {

    T message;
    if (!google::protobuf::TextFormat::ParseFromString(text_proto_, &message)) {
      ADD_FAILURE() << "Failed to parse textproto: " << text_proto_;
      abort();
    }
    return message;
  }

 private:
  std::string text_proto_;
};

}

#endif
