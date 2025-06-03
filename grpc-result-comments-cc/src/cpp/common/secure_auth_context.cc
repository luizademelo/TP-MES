Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include "src/cpp/common/secure_auth_context.h"
#include <grpc/grpc_security.h>
#include <algorithm>

namespace grpc {

// Returns a vector of string_refs representing the peer's identity properties
// Returns an empty vector if the auth context is null
std::vector<grpc::string_ref> SecureAuthContext::GetPeerIdentity() const {
  if (ctx_ == nullptr) {
    return std::vector<grpc::string_ref>();
  }
  // Get iterator for peer identity properties
  grpc_auth_property_iterator iter =
      grpc_auth_context_peer_identity(ctx_.get());
  std::vector<grpc::string_ref> identity;
  const grpc_auth_property* property = nullptr;
  // Iterate through all identity properties and add them to the result vector
  while ((property = grpc_auth_property_iterator_next(&iter))) {
    identity.push_back(
        grpc::string_ref(property->value, property->value_length));
  }
  return identity;
}

// Returns the name of the peer identity property
// Returns empty string if context is null or property name is null
std::string SecureAuthContext::GetPeerIdentityPropertyName() const {
  if (ctx_ == nullptr) {
    return "";
  }
  const char* name = grpc_auth_context_peer_identity_property_name(ctx_.get());
  return name == nullptr ? "" : name;
}

// Finds and returns all property values matching the given name
// Returns empty vector if context is null or no properties found
std::vector<grpc::string_ref> SecureAuthContext::FindPropertyValues(
    const std::string& name) const {
  if (ctx_ == nullptr) {
    return std::vector<grpc::string_ref>();
  }
  // Get iterator for properties with matching name
  grpc_auth_property_iterator iter =
      grpc_auth_context_find_properties_by_name(ctx_.get(), name.c_str());
  const grpc_auth_property* property = nullptr;
  std::vector<grpc::string_ref> values;
  // Iterate through matching properties and add values to result vector
  while ((property = grpc_auth_property_iterator_next(&iter))) {
    values.push_back(grpc::string_ref(property->value, property->value_length));
  }
  return values;
}

// Returns an iterator pointing to the first authentication property
// Returns end() iterator if context is null
AuthPropertyIterator SecureAuthContext::begin() const {
  if (ctx_ != nullptr) {
    // Get property iterator and advance to first property
    grpc_auth_property_iterator iter =
        grpc_auth_context_property_iterator(ctx_.get());
    const grpc_auth_property* property =
        grpc_auth_property_iterator_next(&iter);
    return AuthPropertyIterator(property, &iter);
  } else {
    return end();
  }
}

// Returns an end iterator for authentication properties
AuthPropertyIterator SecureAuthContext::end() const {
  return AuthPropertyIterator();
}

// Adds a new property to the authentication context
// Does nothing if context is null
void SecureAuthContext::AddProperty(const std::string& key,
                                    const grpc::string_ref& value) {
  if (ctx_ == nullptr) return;
  grpc_auth_context_add_property(ctx_.get(), key.c_str(), value.data(),
                                 value.size());
}

// Sets the peer identity property name
// Returns false if context is null or operation fails
bool SecureAuthContext::SetPeerIdentityPropertyName(const std::string& name) {
  if (ctx_ == nullptr) return false;
  return grpc_auth_context_set_peer_identity_property_name(ctx_.get(),
                                                           name.c_str()) != 0;
}

// Checks if the peer is authenticated
// Returns false if context is null or peer is not authenticated
bool SecureAuthContext::IsPeerAuthenticated() const {
  if (ctx_ == nullptr) return false;
  return grpc_auth_context_peer_is_authenticated(ctx_.get()) != 0;
}

}  // namespace grpc
```

The comments explain:
1. The purpose of each method
2. The handling of null contexts
3. The flow of operations within each method
4. Return value explanations
5. Important conditions and edge cases

The comments are concise yet informative, providing enough context for future maintainers to understand the code's functionality without being overly verbose.