Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>
#include <stdint.h>
#include <stdlib.h>

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "absl/strings/string_view.h"
#include "src/core/util/json/json.h"

namespace grpc_core {

namespace {

// JsonWriter is a utility class for converting Json objects to formatted string representations
class JsonWriter {
 public:
  // Static method to dump Json object to string with specified indentation
  static std::string Dump(const Json& value, int indent);

 private:
  // Private constructor - only used internally by static Dump method
  explicit JsonWriter(int indent) : indent_(indent) {}

  // Internal helper methods for building the JSON string output
  void OutputCheck(size_t needed);  // Checks if output buffer has enough space
  void OutputChar(char c);          // Appends single character to output
  void OutputString(const absl::string_view str);  // Appends string to output
  void OutputIndent();              // Outputs proper indentation based on depth
  void ValueEnd();                  // Handles comma/newline after values
  void EscapeUtf16(uint16_t utf16); // Escapes UTF-16 characters
  void EscapeString(const std::string& string); // Escapes entire string
  void ContainerBegins(Json::Type type); // Handles opening of objects/arrays
  void ContainerEnds(Json::Type type);   // Handles closing of objects/arrays
  void ObjectKey(const std::string& string); // Handles object keys
  void ValueRaw(const std::string& string);  // Outputs raw JSON values
  void ValueString(const std::string& string); // Outputs string values

  // Methods for dumping different JSON types
  void DumpObject(const Json::Object& object);
  void DumpArray(const Json::Array& array);
  void DumpValue(const Json& value);

  // Member variables
  int indent_;              // Number of spaces per indentation level
  int depth_ = 0;           // Current nesting depth
  bool container_empty_ = true; // Whether current container is empty
  bool got_key_ = false;    // Whether we've just output an object key
  std::string output_;      // Buffer for building the output string
};

// Ensures output buffer has enough space for needed bytes
void JsonWriter::OutputCheck(size_t needed) {
  size_t free_space = output_.capacity() - output_.size();
  if (free_space >= needed) return;
  needed -= free_space;

  // Round up to nearest 256 bytes
  needed = (needed + 0xff) & ~0xffU;
  output_.reserve(output_.capacity() + needed);
}

// Appends a single character to the output buffer
void JsonWriter::OutputChar(char c) {
  OutputCheck(1);
  output_.push_back(c);
}

// Appends a string to the output buffer
void JsonWriter::OutputString(const absl::string_view str) {
  OutputCheck(str.size());
  output_.append(str.data(), str.size());
}

// Outputs proper indentation based on current depth
void JsonWriter::OutputIndent() {
  // Predefined spaces string for efficient indentation
  static const char spacesstr[] =
      "                "
      "                "
      "                "
      "                ";
  unsigned spaces = static_cast<unsigned>(depth_ * indent_);
  if (indent_ == 0) return;  // No indentation needed
  if (got_key_) {
    // For object keys, just output single space after colon
    OutputChar(' ');
    return;
  }
  // Output full blocks of 16 spaces
  while (spaces >= (sizeof(spacesstr) - 1)) {
    OutputString(absl::string_view(spacesstr, sizeof(spacesstr) - 1));
    spaces -= static_cast<unsigned>(sizeof(spacesstr) - 1);
  }
  if (spaces == 0) return;
  // Output remaining spaces
  OutputString(
      absl::string_view(spacesstr + sizeof(spacesstr) - 1 - spaces, spaces));
}

// Handles comma/newline after values based on container state
void JsonWriter::ValueEnd() {
  if (container_empty_) {
    container_empty_ = false;
    if (indent_ == 0 || depth_ == 0) return;
    OutputChar('\n');
  } else {
    OutputChar(',');
    if (indent_ == 0) return;
    OutputChar('\n');
  }
}

// Escapes UTF-16 character to \uXXXX format
void JsonWriter::EscapeUtf16(uint16_t utf16) {
  static const char hex[] = "0123456789abcdef";
  OutputString(absl::string_view("\\u", 2));
  OutputChar(hex[(utf16 >> 12) & 0x0f]);
  OutputChar(hex[(utf16 >> 8) & 0x0f]);
  OutputChar(hex[(utf16 >> 4) & 0x0f]);
  OutputChar(hex[(utf16) & 0x0f]);
}

// Escapes a string according to JSON rules
void JsonWriter::EscapeString(const std::string& string) {
  OutputChar('"');
  for (size_t idx = 0; idx < string.size(); ++idx) {
    uint8_t c = static_cast<uint8_t>(string[idx]);
    if (c >= 32 && c <= 126) {
      // Printable ASCII characters (except " and \ which need escaping)
      if (c == '\\' || c == '"') OutputChar('\\');
      OutputChar(static_cast<char>(c));
    } else if (c < 32 || c == 127) {
      // Control characters with special escapes
      switch (c) {
        case '\b':
          OutputString(absl::string_view("\\b", 2));
          break;
        case '\f':
          OutputString(absl::string_view("\\f", 2));
          break;
        case '\n':
          OutputString(absl::string_view("\\n", 2));
          break;
        case '\r':
          OutputString(absl::string_view("\\r", 2));
          break;
        case '\t':
          OutputString(absl::string_view("\\t", 2));
          break;
        default:
          // Other control characters use Unicode escape
          EscapeUtf16(c);
          break;
      }
    } else {
      // Handle UTF-8 multi-byte sequences
      uint32_t utf32 = 0;
      int extra = 0;
      int i;
      int valid = 1;
      // Determine number of extra bytes in UTF-8 sequence
      if ((c & 0xe0) == 0xc0) {
        utf32 = c & 0x1f;
        extra = 1;
      } else if ((c & 0xf0) == 0xe0) {
        utf32 = c & 0x0f;
        extra = 2;
      } else if ((c & 0xf8) == 0xf0) {
        utf32 = c & 0x07;
        extra = 3;
      } else {
        break;
      }
      // Process continuation bytes
      for (i = 0; i < extra; i++) {
        utf32 <<= 6;
        ++idx;
        // Check for premature end of string
        if (idx == string.size()) {
          valid = 0;
          break;
        }
        c = static_cast<uint8_t>(string[idx]);
        // Validate continuation byte
        if ((c & 0xc0) != 0x80) {
          valid = 0;
          break;
        }
        utf32 |= c & 0x3f;
      }
      if (!valid) break;
      // Validate Unicode code point
      if (((utf32 >= 0xd800) && (utf32 <= 0xdfff)) || (utf32 >= 0x110000)) {
        break;
      }
      // Handle surrogate pairs for characters above 0xFFFF
      if (utf32 >= 0x10000) {
        utf32 -= 0x10000;
        EscapeUtf16(static_cast<uint16_t>(0xd800 | (utf32 >> 10)));
        EscapeUtf16(static_cast<uint16_t>(0xdc00 | (utf32 & 0x3ff)));
      } else {
        EscapeUtf16(static_cast<uint16_t>(utf32));
      }
    }
  }
  OutputChar('"');
}

// Handles opening of JSON containers (objects/arrays)
void JsonWriter::ContainerBegins(Json::Type type) {
  if (!got_key_) ValueEnd();
  OutputIndent();
  OutputChar(type == Json::Type::kObject ? '{' : '[');
  container_empty_ = true;
  got_key_ = false;
  depth_++;
}

// Handles closing of JSON containers (objects/arrays)
void JsonWriter::ContainerEnds(Json::Type type) {
  if (indent_ && !container_empty_) OutputChar('\n');
  depth_--;
  if (!container_empty_) OutputIndent();
  OutputChar(type == Json::Type::kObject ? '}' : ']');
  container_empty_ = false;
  got_key_ = false;
}

// Handles object keys (including quotes and colon)
void JsonWriter::ObjectKey(const std::string& string) {
  ValueEnd();
  OutputIndent();
  EscapeString(string);
  OutputChar(':');
  got_key_ = true;
}

// Outputs raw JSON values (numbers, booleans, null)
void JsonWriter::ValueRaw(const std::string& string) {
  if (!got_key_) ValueEnd();
  OutputIndent();
  OutputString(string);
  got_key_ = false;
}

// Outputs string values (with proper escaping)
void JsonWriter::ValueString(const std::string& string) {
  if (!got_key_) ValueEnd();
  OutputIndent();
  EscapeString(string);
  got_key_ = false;
}

// Dumps a JSON object (key-value pairs)
void JsonWriter::DumpObject(const Json::Object& object) {
  ContainerBegins(Json::Type::kObject);
  for (const auto& [key, value] : object) {
    ObjectKey(key);
    DumpValue(value);
  }
  ContainerEnds(Json::Type::kObject);
}

// Dumps a JSON array (sequence of values)
void JsonWriter::DumpArray(const Json::Array& array) {
  ContainerBegins(Json::Type::kArray);
  for (const auto& v : array) {
    DumpValue(v);
  }
  ContainerEnds(Json::Type::kArray);
}

// Dispatches to appropriate dump method based on JSON type
void JsonWriter::DumpValue(const Json& value) {
  switch (value.type()) {
    case Json::Type::kObject:
      DumpObject(value.object());
      break;
    case Json::Type::kArray:
      DumpArray(value.array());
      break;
    case Json::Type::kString:
      ValueString(value.string());
      break;
    case Json::Type::kNumber:
      ValueRaw(value.string());
      break;
    case Json::Type::kBoolean:
      if (value.boolean()) {
        ValueRaw(std::string("true", 4));
      } else {
        ValueRaw(std::string("false", 5));
      }
      break;
    case Json::Type::kNull:
      ValueRaw(std::string("null", 4));
      break;
    default:
      GPR_UNREACHABLE_CODE(abort());
  }
}

// Static method to create writer and dump JSON value
std::string JsonWriter::Dump(const Json& value, int indent) {
  JsonWriter writer(indent);
  writer.DumpValue(value);
  return std::move(writer.output_);
}

}  // namespace

// Public API function for dumping JSON
std::string JsonDump(const Json& json, int indent) {
  return JsonWriter::Dump(json, indent);
}

}  // namespace grpc_core
```