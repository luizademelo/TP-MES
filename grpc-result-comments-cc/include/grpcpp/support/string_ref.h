Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SUPPORT_STRING_REF_H
#define GRPCPP_SUPPORT_STRING_REF_H

#include <grpcpp/support/config.h>
#include <string.h>

#include <algorithm>
#include <iosfwd>
#include <iostream>
#include <iterator>

namespace grpc {

// A string_ref is a non-owning reference to a string or part of a string.
// It provides a lightweight way to pass strings around without copying.
// Similar to std::string_view in C++17.
class string_ref {
 public:
  // Iterator types
  typedef const char* const_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  // Special value indicating "not found" or "all remaining characters"
  const static size_t npos;

  // Constructors
  string_ref() : data_(nullptr), length_(0) {}  // Construct empty string_ref
  string_ref(const string_ref& other)           // Copy constructor
      : data_(other.data_), length_(other.length_) {}

  // Assignment operator
  string_ref& operator=(const string_ref& rhs) {
    data_ = rhs.data_;
    length_ = rhs.length_;
    return *this;
  }

  // Construct from null-terminated C string
  string_ref(const char* s) : data_(s), length_(strlen(s)) {}
  // Construct from character array with specified length
  string_ref(const char* s, size_t l) : data_(s), length_(l) {}
  // Construct from std::string
  string_ref(const std::string& s) : data_(s.data()), length_(s.length()) {}

  // Iterator functions
  const_iterator begin() const { return data_; }
  const_iterator end() const { return data_ + length_; }
  const_iterator cbegin() const { return data_; }
  const_iterator cend() const { return data_ + length_; }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }
  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(end());
  }
  const_reverse_iterator crend() const {
    return const_reverse_iterator(begin());
  }

  // Capacity functions
  size_t size() const { return length_; }
  size_t length() const { return length_; }
  size_t max_size() const { return length_; }
  bool empty() const { return length_ == 0; }

  // Data access
  const char* data() const { return data_; }

  // Comparison function
  // Returns:
  //  -1 if this string_ref is less than x
  //   0 if equal
  //   1 if this string_ref is greater than x
  int compare(string_ref x) const {
    size_t min_size = length_ < x.length_ ? length_ : x.length_;
    int r = memcmp(data_, x.data_, min_size);
    if (r < 0) return -1;
    if (r > 0) return 1;
    if (length_ < x.length_) return -1;
    if (length_ > x.length_) return 1;
    return 0;
  }

  // Checks if this string_ref starts with the given string_ref x
  bool starts_with(string_ref x) const {
    return length_ >= x.length_ && (memcmp(data_, x.data_, x.length_) == 0);
  }

  // Checks if this string_ref ends with the given string_ref x
  bool ends_with(string_ref x) const {
    return length_ >= x.length_ &&
           (memcmp(data_ + (length_ - x.length_), x.data_, x.length_) == 0);
  }

  // Finds the first occurrence of string_ref s within this string_ref
  // Returns npos if not found
  size_t find(string_ref s) const {
    auto it = std::search(cbegin(), cend(), s.cbegin(), s.cend());
    return it == cend() ? npos : std::distance(cbegin(), it);
  }

  // Finds the first occurrence of character c within this string_ref
  // Returns npos if not found
  size_t find(char c) const {
    auto it = std::find(cbegin(), cend(), c);
    return it == cend() ? npos : std::distance(cbegin(), it);
  }

  // Returns a substring of this string_ref
  // pos: starting position
  // n: number of characters (defaults to all remaining characters)
  string_ref substr(size_t pos, size_t n = npos) const {
    if (pos > length_) pos = length_;
    if (n > (length_ - pos)) n = length_ - pos;
    return string_ref(data_ + pos, n);
  }

 private:
  const char* data_;  // Pointer to the string data (not owned)
  size_t length_;     // Length of the referenced string
};

// Comparison operators
inline bool operator==(string_ref x, string_ref y) { return x.compare(y) == 0; }
inline bool operator!=(string_ref x, string_ref y) { return x.compare(y) != 0; }
inline bool operator<(string_ref x, string_ref y) { return x.compare(y) < 0; }
inline bool operator<=(string_ref x, string_ref y) { return x.compare(y) <= 0; }
inline bool operator>(string_ref x, string_ref y) { return x.compare(y) > 0; }
inline bool operator>=(string_ref x, string_ref y) { return x.compare(y) >= 0; }

// Output stream operator for string_ref
inline std::ostream& operator<<(std::ostream& out, const string_ref& string) {
  return out << std::string(string.begin(), string.end());
}

}

#endif
```

The comments explain:
1. The purpose of the string_ref class (non-owning string reference)
2. Each constructor and what it initializes
3. The iterator functionality
4. Capacity and access methods
5. Comparison operations
6. Search and substring operations
7. The private data members
8. All the free-standing comparison operators
9. The output stream operator

The comments are designed to help future developers understand both the high-level purpose and the detailed implementation of each method.