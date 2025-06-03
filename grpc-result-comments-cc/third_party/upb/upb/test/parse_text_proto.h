Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

// Header guard to prevent multiple inclusions
#ifndef UPB_UPB_TEST_PARSE_TEXT_PROTO_H_
#define UPB_UPB_TEST_PARSE_TEXT_PROTO_H_

#include <string>

#include <gtest/gtest.h>  // Google Test framework
#include "google/protobuf/message.h"  // Protobuf message base class
#include "google/protobuf/text_format.h"  // Text format parsing

namespace upb_test {

// A utility class for parsing text format protocol buffers in tests.
// The name "OrDie" indicates that parsing failures will terminate the program.
class ParseTextProtoOrDie {
 public:
  // Constructor that takes a text format protocol buffer string.
  // @param text_proto The protocol buffer in text format to be parsed.
  explicit ParseTextProtoOrDie(absl::string_view text_proto)
      : text_proto_(text_proto) {}

  // Conversion operator template that allows implicit conversion to any
  // protocol buffer message type.
  // @tparam T The protocol buffer message type to parse into.
  // @return The parsed protocol buffer message.
  // @note If parsing fails, the test will fail and the program will abort.
  template <class T>
  operator T() {
    T message;
    // Attempt to parse the text format string into the message
    if (!google::protobuf::TextFormat::ParseFromString(text_proto_, &message)) {
      // Log failure and abort if parsing fails
      ADD_FAILURE() << "Failed to parse textproto: " << text_proto_;
      abort();
    }
    return message;
  }

 private:
  std::string text_proto_;  // Stores the text format protocol buffer string
};

}  // namespace upb_test

#endif  // UPB_UPB_TEST_PARSE_TEXT_PROTO_H_
```

Key points about the comments:
1. Added explanation of the header guard purpose
2. Documented each include with its purpose
3. Added class-level documentation explaining the utility's purpose
4. Documented the constructor parameter
5. Added detailed documentation for the conversion operator template
6. Explained the parsing failure behavior
7. Added comments for the private member variable
8. Added namespace closing comment for clarity
9. Documented the end of header guard

The comments now provide clear explanations of:
- What each component does
- The expected behavior
- The failure mode
- The template usage
- The overall purpose of the utility class