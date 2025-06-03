Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions
#ifndef GRPCPP_SECURITY_AUTH_CONTEXT_H
#define GRPCPP_SECURITY_AUTH_CONTEXT_H

// Include necessary headers
#include <grpcpp/support/config.h>
#include <grpcpp/support/string_ref.h>

#include <iterator>
#include <vector>

// Forward declarations of C structs used in the implementation
struct grpc_auth_context;
struct grpc_auth_property;
struct grpc_auth_property_iterator;

namespace grpc {

// Forward declaration of SecureAuthContext class
class SecureAuthContext;

// Type alias for authentication properties (key-value pairs)
typedef std::pair<string_ref, string_ref> AuthProperty;

// Iterator class for accessing authentication properties
class AuthPropertyIterator {
 public:
  // Standard iterator type definitions
  using iterator_category = std::forward_iterator_tag;
  using value_type = const AuthProperty;
  using pointer = void;
  using reference = void;
  using difference_type = std::ptrdiff_t;

  // Destructor
  ~AuthPropertyIterator();
  
  // Iterator operations
  AuthPropertyIterator& operator++();    // Prefix increment
  AuthPropertyIterator operator++(int);  // Postfix increment
  
  // Comparison operators
  bool operator==(const AuthPropertyIterator& rhs) const;
  bool operator!=(const AuthPropertyIterator& rhs) const;
  
  // Dereference operator
  AuthProperty operator*();

 protected:
  // Constructors
  AuthPropertyIterator();  // Default constructor
  AuthPropertyIterator(const grpc_auth_property* property,
                       const grpc_auth_property_iterator* iter);

 private:
  // Only SecureAuthContext can create these iterators
  friend class SecureAuthContext;
  
  // Current property being pointed to
  const grpc_auth_property* property_;
  
  // Context and state for iteration
  const grpc_auth_context* ctx_;
  size_t index_;      // Current index in iteration
  const char* name_;  // Property name being filtered for (if any)
};

// Abstract base class representing authentication context
class AuthContext {
 public:
  virtual ~AuthContext() {}

  // Checks if the peer was authenticated
  virtual bool IsPeerAuthenticated() const = 0;

  // Gets the peer's identity as a list of properties
  virtual std::vector<grpc::string_ref> GetPeerIdentity() const = 0;
  
  // Gets the name of the property that represents the peer's identity
  virtual std::string GetPeerIdentityPropertyName() const = 0;

  // Finds all property values with the given name
  virtual std::vector<grpc::string_ref> FindPropertyValues(
      const std::string& name) const = 0;

  // Iterator interface for accessing all properties
  virtual AuthPropertyIterator begin() const = 0;
  virtual AuthPropertyIterator end() const = 0;

  // Adds a new property to the context
  virtual void AddProperty(const std::string& key, const string_ref& value) = 0;
  
  // Sets the property name that represents the peer's identity
  virtual bool SetPeerIdentityPropertyName(const std::string& name) = 0;
};

}  // namespace grpc

#endif  // GRPCPP_SECURITY_AUTH_CONTEXT_H
```

The comments explain:
1. The overall purpose of each component (header guard, includes, forward declarations)
2. The AuthPropertyIterator class and its iterator semantics
3. The abstract AuthContext interface and its methods
4. The relationships between components
5. The purpose of each method and member variable

The comments are designed to help future developers understand:
- How to use these classes
- The design patterns being employed
- The expected behavior of each component
- The relationships between different parts of the code