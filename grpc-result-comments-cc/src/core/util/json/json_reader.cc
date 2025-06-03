Here's the commented version of the code:

```c++
// Copyright 2015-2016 gRPC authors.

// Include necessary headers for JSON parsing functionality
#include <grpc/support/json.h>
#include <grpc/support/port_platform.h>
#include <inttypes.h>
#include <stdlib.h>

// Standard library includes
#include <algorithm>
#include <map>
#include <string>
#include <utility>
#include <variant>
#include <vector>

// ABSL (Abseil) library includes for utilities
#include "absl/base/attributes.h"
#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/string_view.h"
#include "src/core/util/json/json.h"
#include "src/core/util/match.h"

// Maximum depth for JSON nesting
#define GRPC_JSON_MAX_DEPTH 255
// Maximum number of errors to collect before truncating
#define GRPC_JSON_MAX_ERRORS 16

namespace grpc_core {

namespace {

// JsonReader class implements a JSON parser with state machine approach
class JsonReader {
 public:
  // Static method to parse JSON input string and return Json object or error
  static absl::StatusOr<Json> Parse(absl::string_view input);

 private:
  // Enumeration for parser status
  enum class Status {
    GRPC_JSON_DONE,          // Parsing completed successfully
    GRPC_JSON_PARSE_ERROR,    // Error encountered during parsing
    GRPC_JSON_INTERNAL_ERROR  // Internal parser error
  };

  // Enumeration for parser states (finite state machine)
  enum class State {
    GRPC_JSON_STATE_OBJECT_KEY_BEGIN,       // Start of object key
    GRPC_JSON_STATE_OBJECT_KEY_STRING,      // Parsing object key string
    GRPC_JSON_STATE_OBJECT_KEY_END,         // End of object key
    GRPC_JSON_STATE_VALUE_BEGIN,            // Start of value
    GRPC_JSON_STATE_VALUE_STRING,           // Parsing string value
    GRPC_JSON_STATE_STRING_ESCAPE,          // Handling string escape character
    GRPC_JSON_STATE_STRING_ESCAPE_U1,       // Unicode escape sequence part 1
    GRPC_JSON_STATE_STRING_ESCAPE_U2,       // Unicode escape sequence part 2
    GRPC_JSON_STATE_STRING_ESCAPE_U3,       // Unicode escape sequence part 3
    GRPC_JSON_STATE_STRING_ESCAPE_U4,       // Unicode escape sequence part 4
    GRPC_JSON_STATE_VALUE_NUMBER,           // Parsing number value
    GRPC_JSON_STATE_VALUE_NUMBER_WITH_DECIMAL,  // Number with decimal point
    GRPC_JSON_STATE_VALUE_NUMBER_ZERO,      // Number starting with zero
    GRPC_JSON_STATE_VALUE_NUMBER_DOT,       // Decimal point in number
    GRPC_JSON_STATE_VALUE_NUMBER_E,         // Exponent part in number
    GRPC_JSON_STATE_VALUE_NUMBER_EPM,       // Exponent sign in number
    GRPC_JSON_STATE_VALUE_TRUE_R,           // Parsing 'true' (r)
    GRPC_JSON_STATE_VALUE_TRUE_U,           // Parsing 'true' (u)
    GRPC_JSON_STATE_VALUE_TRUE_E,           // Parsing 'true' (e)
    GRPC_JSON_STATE_VALUE_FALSE_A,          // Parsing 'false' (a)
    GRPC_JSON_STATE_VALUE_FALSE_L,          // Parsing 'false' (l)
    GRPC_JSON_STATE_VALUE_FALSE_S,          // Parsing 'false' (s)
    GRPC_JSON_STATE_VALUE_FALSE_E,          // Parsing 'false' (e)
    GRPC_JSON_STATE_VALUE_NULL_U,           // Parsing 'null' (u)
    GRPC_JSON_STATE_VALUE_NULL_L1,          // Parsing 'null' (first l)
    GRPC_JSON_STATE_VALUE_NULL_L2,          // Parsing 'null' (second l)
    GRPC_JSON_STATE_VALUE_END,              // End of value
    GRPC_JSON_STATE_END                     // End of parsing
  };

  // Special value indicating end of input
  static constexpr uint32_t GRPC_JSON_READ_CHAR_EOF = 0x7ffffff0;

  // Nested scope structure for tracking JSON containers (objects/arrays)
  struct Scope {
    std::string parent_object_key;  // Key of parent object (if any)
    std::variant<Json::Object, Json::Array> data;  // Container data

    // Returns the type of this scope (object or array)
    Json::Type type() const {
      return Match(
          data, [](const Json::Object&) { return Json::Type::kObject; },
          [](const Json::Array&) { return Json::Type::kArray; });
    }

    // Converts the scope data to a Json object
    Json TakeAsJson() {
      return MatchMutable(
          &data,
          [&](Json::Object* object) {
            return Json::FromObject(std::move(*object));
          },
          [&](Json::Array* array) {
            return Json::FromArray(std::move(*array));
          });
    }
  };

  // Constructor initializes the reader with input data
  explicit JsonReader(absl::string_view input)
      : original_input_(reinterpret_cast<const uint8_t*>(input.data())),
        input_(original_input_),
        remaining_input_(input.size()) {}

  // Main parsing method
  Status Run();
  // Reads next character from input
  uint32_t ReadChar();
  // Checks if parsing is complete
  bool IsComplete();

  // Returns current position in input
  size_t CurrentIndex() const { return input_ - original_input_ - 1; }

  // Adds a character to the current string being built
  GRPC_MUST_USE_RESULT bool StringAddChar(uint32_t c);
  // Adds a UTF-32 character to the current string being built
  GRPC_MUST_USE_RESULT bool StringAddUtf32(uint32_t c);

  // Creates a new JSON value and links it to current container
  Json* CreateAndLinkValue();
  // Starts a new container (object or array)
  bool StartContainer(Json::Type type);
  // Ends current container
  void EndContainer();
  // Sets the current key for object properties
  void SetKey();
  // Sets a string value
  void SetString();
  // Sets a number value
  bool SetNumber();
  // Sets a true boolean value
  void SetTrue();
  // Sets a false boolean value
  void SetFalse();
  // Sets a null value
  void SetNull();

  // Input data pointers and counters
  const uint8_t* original_input_;
  const uint8_t* input_;
  size_t remaining_input_;

  // Parser state variables
  State state_ = State::GRPC_JSON_STATE_VALUE_BEGIN;
  bool escaped_string_was_key_ = false;
  bool container_just_begun_ = false;
  uint16_t unicode_char_ = 0;
  uint16_t unicode_high_surrogate_ = 0;
  std::vector<std::string> errors_;
  bool truncated_errors_ = false;
  uint8_t utf8_bytes_remaining_ = 0;
  uint8_t utf8_first_byte_ = 0;

  // Result storage
  Json root_value_;
  std::vector<Scope> stack_;

  // Temporary storage for keys and string values
  std::string key_;
  std::string string_;
};

// Adds a character to the current string being built, with UTF-8 validation
bool JsonReader::StringAddChar(uint32_t c) {
  if (utf8_bytes_remaining_ == 0) {
    // Determine UTF-8 sequence length based on first byte
    if ((c & 0x80) == 0) {
      utf8_bytes_remaining_ = 0;
    } else if ((c & 0xe0) == 0xc0 && c >= 0xc2) {
      // 2-byte sequence (skip overlong encoding 0xc0, 0xc1)
      utf8_bytes_remaining_ = 1;
    } else if ((c & 0xf0) == 0xe0) {
      // 3-byte sequence
      utf8_bytes_remaining_ = 2;
    } else if ((c & 0xf8) == 0xf0 && c <= 0xf4) {
      // 4-byte sequence (limit to U+1FFFFF)
      utf8_bytes_remaining_ = 3;
    } else {
      return false;  // Invalid UTF-8 sequence
    }
    utf8_first_byte_ = c;
  } else if (utf8_bytes_remaining_ == 1) {
    // Check continuation byte
    if ((c & 0xc0) != 0x80) {
      return false;
    }
    --utf8_bytes_remaining_;
  } else if (utf8_bytes_remaining_ == 2) {
    // Check continuation byte and validate range
    if (((c & 0xc0) != 0x80) || (utf8_first_byte_ == 0xe0 && c < 0xa0) ||
        (utf8_first_byte_ == 0xed && c > 0x9f)) {
      return false;
    }
    --utf8_bytes_remaining_;
  } else if (utf8_bytes_remaining_ == 3) {
    // Check continuation byte and validate range
    if (((c & 0xc0) != 0x80) || (utf8_first_byte_ == 0xf0 && c < 0x90) ||
        (utf8_first_byte_ == 0xf4 && c > 0x8f)) {
      return false;
    }
    --utf8_bytes_remaining_;
  } else {
    abort();  // Should never happen
  }

  string_.push_back(static_cast<uint8_t>(c));
  return true;
}

// Adds a UTF-32 character to the current string, converting to UTF-8
bool JsonReader::StringAddUtf32(uint32_t c) {
  if (c <= 0x7f) {
    // 1-byte UTF-8
    return StringAddChar(c);
  } else if (c <= 0x7ff) {
    // 2-byte UTF-8
    uint32_t b1 = 0xc0 | ((c >> 6) & 0x1f);
    uint32_t b2 = 0x80 | (c & 0x3f);
    return StringAddChar(b1) && StringAddChar(b2);
  } else if (c <= 0xffff) {
    // 3-byte UTF-8
    uint32_t b1 = 0xe0 | ((c >> 12) & 0x0f);
    uint32_t b2 = 0x80 | ((c >> 6) & 0x3f);
    uint32_t b3 = 0x80 | (c & 0x3f);
    return StringAddChar(b1) && StringAddChar(b2) && StringAddChar(b3);
  } else if (c <= 0x1fffff) {
    // 4-byte UTF-8
    uint32_t b1 = 0xf0 | ((c >> 18) & 0x07);
    uint32_t b2 = 0x80 | ((c >> 12) & 0x3f);
    uint32_t b3 = 0x80 | ((c >> 6) & 0x3f);
    uint32_t b4 = 0x80 | (c & 0x3f);
    return StringAddChar(b1) && StringAddChar(b2) && StringAddChar(b3) &&
           StringAddChar(b4);
  } else {
    return false;  // Code point too large
  }
}

// Reads next character from input, handling EOF
uint32_t JsonReader::ReadChar() {
  if (remaining_input_ == 0) return GRPC_JSON_READ_CHAR_EOF;
  const uint32_t r = *input_++;
  --remaining_input_;
  if (r == 0) {
    remaining_input_ = 0;
    return GRPC_JSON_READ_CHAR_EOF;
  }
  return r;
}

// Creates a new JSON value and links it to the current container
Json* JsonReader::CreateAndLinkValue() {
  if (stack_.empty()) return &root_value_;
  return MatchMutable(
      &stack_.back().data,
      [&](Json::Object* object) { return &(*object)[std::move(key_)]; },
      [&](Json::Array* array) {
        array->emplace_back();
        return &array->back();
      });
}

// Starts a new container (object or array)
bool JsonReader::StartContainer(Json::Type type) {
  if (stack_.size() == GRPC_JSON_MAX_DEPTH) {
    if (errors_.size() == GRPC_JSON_MAX_ERRORS) {
      truncated_errors_ = true;
    } else {
      errors_.push_back(
          absl::StrFormat("exceeded max stack depth (%d) at index %" PRIuPTR,
                          GRPC_JSON_MAX_DEPTH, CurrentIndex()));
    }
    return false;
  }
  stack_.emplace_back();
  Scope& scope = stack_.back();
  scope.parent_object_key = std::move(key_);
  if (type == Json::Type::kObject) {
    scope.data = Json::Object();
  } else {
    CHECK(type == Json::Type::kArray);
    scope.data = Json::Array();
  }
  return true;
}

// Ends current container and moves back to parent scope
void JsonReader::EndContainer() {
  CHECK(!stack_.empty());
  Scope scope = std::move(stack_.back());
  stack_.pop_back();
  key_ = std::move(scope.parent_object_key);
  Json* value = CreateAndLinkValue();
  *value = scope.TakeAsJson();
}

// Sets the current key for object properties
void JsonReader::SetKey() {
  key_ = std::move(string_);
  string_.clear();
  const Json::Object& object = std::get<Json::Object>(stack_.back().data);
  if (object.find(key_) != object.end()) {
    if (errors_.size() == GRPC_JSON_MAX_ERRORS) {
      truncated_errors_ = true;
    } else {
      errors_.push_back(
          absl::StrFormat("duplicate key \"%s\" at index %" PRIuPTR, key_,
                          CurrentIndex() - key_.size() - 2));
    }
  }
}

// Sets a string value in the current context
void JsonReader::SetString() {
  Json* value = CreateAndLinkValue();
  *value = Json::FromString(std::move(string_));
  string_.clear();
}

// Sets a number value in the current context
bool JsonReader::SetNumber() {
  Json* value = CreateAndLinkValue();
  *value = Json::FromNumber(std::move(string_));
  string_.clear();
  return true;
}

// Sets a true boolean value in the current context
void JsonReader::SetTrue() {
  Json* value = CreateAndLinkValue();
  *value = Json::FromBool(true);
  string_.clear();
}

// Sets a false boolean value in the current context
void JsonReader::SetFalse() {
  Json* value = CreateAndLinkValue();
  *value = Json::FromBool(false);
  string_.clear();
}

// Sets a null value in the current context
void JsonReader::SetNull() { CreateAndLinkValue(); }

// Checks if parsing is complete (reached end state with empty stack)
bool JsonReader::IsComplete() {
  return (stack_.empty() && (state_ == State::GRPC_JSON_STATE_END ||
                             state_ == State::GRPC_JSON_STATE_VALUE_END));
}

// Main parsing state machine implementation
JsonReader::Status JsonReader::Run() {
  uint32_t c;

  while (true) {
    c = ReadChar();
    switch (c) {
      // Handle end of input
      case GRPC_JSON_READ_CHAR_EOF:
        switch (state_) {
          case State::GRPC_JSON_STATE_VALUE_NUMBER:
          case State::GRPC_JSON_STATE_VALUE_NUMBER_WITH_DECIMAL:
          case State::GRPC_JSON_STATE_VALUE_NUMBER_ZERO:
          case State::GRPC_JSON_STATE_VALUE_NUMBER_EPM:
            if (!SetNumber()) return Status::GRPC_JSON_PARSE_ERROR;
            state_ = State::GRPC_JSON_STATE_VALUE_END;
            break;

          default:
            break;
        }
        if (IsComplete()) {
          return Status::GRPC_JSON_DONE;
        }
        return Status::GRPC_JSON_PARSE_ERROR;

      // Handle whitespace characters
      case ' ':
      case '\t':
      case '\n':
      case '\r':
        switch (state_) {
          case State::GRPC_JSON_STATE_OBJECT_KEY_BEGIN:
          case State::GRPC_JSON_STATE_OBJECT_KEY_END:
          case State::GRPC_JSON_STATE_VALUE_BEGIN:
          case State::GRPC_JSON_STATE_VALUE_END:
          case State::GRPC_JSON_STATE_END:
            break;  // Whitespace is allowed in these states

          case State::GRPC_JSON_STATE_OBJECT_KEY_STRING:
          case State::GRPC_JSON_STATE_VALUE_STRING:
            if (c != ' ') return Status::GRPC_JSON_PARSE_ERROR;
            if (unicode_high_surrogate_ != 0) {
              return Status::GRPC_JSON_PARSE_ERROR;
            }
            if (!StringAddChar(c)) return Status::GRPC_JSON_PARSE_ERROR;
            break;

          case State::GRPC_JSON_STATE_VALUE_NUMBER:
          case State::GRPC_JSON_STATE_VALUE_NUMBER_WITH_DECIMAL:
          case State::GRPC_JSON_STATE_VALUE_NUMBER_ZERO:
          case