Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_SUPPORT_STUB_OPTIONS_H
#define GRPCPP_SUPPORT_STUB_OPTIONS_H

namespace grpc {

// Class representing options for gRPC stubs
// Stubs are client-side objects that represent server-side services
class StubOptions {
 public:
  // Default constructor
  StubOptions() = default;

  // Constructor that initializes the stats suffix
  // @param suffix_for_stats: A string suffix to be used for statistics collection
  explicit StubOptions(const char* suffix_for_stats)
      : suffix_for_stats_(suffix_for_stats) {}

  // Setter for the statistics suffix
  // @param suffix_for_stats: The suffix string to be used for statistics
  void set_suffix_for_stats(const char* suffix_for_stats) {
    suffix_for_stats_ = suffix_for_stats;
  }

  // Getter for the statistics suffix
  // @return: The current statistics suffix string (may be nullptr)
  const char* suffix_for_stats() const { return suffix_for_stats_; }

 private:
  // Pointer to a string used as suffix for statistics collection
  // nullptr indicates no suffix is being used
  const char* suffix_for_stats_ = nullptr;
};

}  // namespace grpc

#endif  // GRPCPP_SUPPORT_STUB_OPTIONS_H
```

The comments explain:
1. The purpose of the header guard
2. The overall purpose of the StubOptions class
3. Each constructor and its parameters
4. Each method's purpose, parameters, and return values
5. The private member variable and its possible values
6. The namespace closure
7. The header guard closure

The comments follow a consistent style and provide enough information for future maintainers to understand the code's functionality without being overly verbose.