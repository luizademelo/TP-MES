
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

class string_ref {
 public:

  typedef const char* const_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  const static size_t npos;

  string_ref() : data_(nullptr), length_(0) {}
  string_ref(const string_ref& other)
      : data_(other.data_), length_(other.length_) {}

  string_ref& operator=(const string_ref& rhs) {
    data_ = rhs.data_;
    length_ = rhs.length_;
    return *this;
  }

  string_ref(const char* s) : data_(s), length_(strlen(s)) {}
  string_ref(const char* s, size_t l) : data_(s), length_(l) {}

  string_ref(const std::string& s) : data_(s.data()), length_(s.length()) {}

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

  size_t size() const { return length_; }
  size_t length() const { return length_; }
  size_t max_size() const { return length_; }
  bool empty() const { return length_ == 0; }

  const char* data() const { return data_; }

  int compare(string_ref x) const {
    size_t min_size = length_ < x.length_ ? length_ : x.length_;
    int r = memcmp(data_, x.data_, min_size);
    if (r < 0) return -1;
    if (r > 0) return 1;
    if (length_ < x.length_) return -1;
    if (length_ > x.length_) return 1;
    return 0;
  }

  bool starts_with(string_ref x) const {
    return length_ >= x.length_ && (memcmp(data_, x.data_, x.length_) == 0);
  }

  bool ends_with(string_ref x) const {
    return length_ >= x.length_ &&
           (memcmp(data_ + (length_ - x.length_), x.data_, x.length_) == 0);
  }

  size_t find(string_ref s) const {
    auto it = std::search(cbegin(), cend(), s.cbegin(), s.cend());
    return it == cend() ? npos : std::distance(cbegin(), it);
  }

  size_t find(char c) const {
    auto it = std::find(cbegin(), cend(), c);
    return it == cend() ? npos : std::distance(cbegin(), it);
  }

  string_ref substr(size_t pos, size_t n = npos) const {
    if (pos > length_) pos = length_;
    if (n > (length_ - pos)) n = length_ - pos;
    return string_ref(data_ + pos, n);
  }

 private:
  const char* data_;
  size_t length_;
};

inline bool operator==(string_ref x, string_ref y) { return x.compare(y) == 0; }
inline bool operator!=(string_ref x, string_ref y) { return x.compare(y) != 0; }
inline bool operator<(string_ref x, string_ref y) { return x.compare(y) < 0; }
inline bool operator<=(string_ref x, string_ref y) { return x.compare(y) <= 0; }
inline bool operator>(string_ref x, string_ref y) { return x.compare(y) > 0; }
inline bool operator>=(string_ref x, string_ref y) { return x.compare(y) >= 0; }

inline std::ostream& operator<<(std::ostream& out, const string_ref& string) {
  return out << std::string(string.begin(), string.end());
}

}

#endif
