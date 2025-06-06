
// Copyright 2015 gRPC authors.

#include "src/cpp/common/secure_auth_context.h"

#include <grpc/grpc_security.h>

#include <algorithm>

namespace grpc {

std::vector<grpc::string_ref> SecureAuthContext::GetPeerIdentity() const {
  if (ctx_ == nullptr) {
    return std::vector<grpc::string_ref>();
  }
  grpc_auth_property_iterator iter =
      grpc_auth_context_peer_identity(ctx_.get());
  std::vector<grpc::string_ref> identity;
  const grpc_auth_property* property = nullptr;
  while ((property = grpc_auth_property_iterator_next(&iter))) {
    identity.push_back(
        grpc::string_ref(property->value, property->value_length));
  }
  return identity;
}

std::string SecureAuthContext::GetPeerIdentityPropertyName() const {
  if (ctx_ == nullptr) {
    return "";
  }
  const char* name = grpc_auth_context_peer_identity_property_name(ctx_.get());
  return name == nullptr ? "" : name;
}

std::vector<grpc::string_ref> SecureAuthContext::FindPropertyValues(
    const std::string& name) const {
  if (ctx_ == nullptr) {
    return std::vector<grpc::string_ref>();
  }
  grpc_auth_property_iterator iter =
      grpc_auth_context_find_properties_by_name(ctx_.get(), name.c_str());
  const grpc_auth_property* property = nullptr;
  std::vector<grpc::string_ref> values;
  while ((property = grpc_auth_property_iterator_next(&iter))) {
    values.push_back(grpc::string_ref(property->value, property->value_length));
  }
  return values;
}

AuthPropertyIterator SecureAuthContext::begin() const {
  if (ctx_ != nullptr) {
    grpc_auth_property_iterator iter =
        grpc_auth_context_property_iterator(ctx_.get());
    const grpc_auth_property* property =
        grpc_auth_property_iterator_next(&iter);
    return AuthPropertyIterator(property, &iter);
  } else {
    return end();
  }
}

AuthPropertyIterator SecureAuthContext::end() const {
  return AuthPropertyIterator();
}

void SecureAuthContext::AddProperty(const std::string& key,
                                    const grpc::string_ref& value) {
  if (ctx_ == nullptr) return;
  grpc_auth_context_add_property(ctx_.get(), key.c_str(), value.data(),
                                 value.size());
}

bool SecureAuthContext::SetPeerIdentityPropertyName(const std::string& name) {
  if (ctx_ == nullptr) return false;
  return grpc_auth_context_set_peer_identity_property_name(ctx_.get(),
                                                           name.c_str()) != 0;
}

bool SecureAuthContext::IsPeerAuthenticated() const {
  if (ctx_ == nullptr) return false;
  return grpc_auth_context_peer_is_authenticated(ctx_.get()) != 0;
}

}
