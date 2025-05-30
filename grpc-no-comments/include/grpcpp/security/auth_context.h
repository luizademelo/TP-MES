
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SECURITY_AUTH_CONTEXT_H
#define GRPCPP_SECURITY_AUTH_CONTEXT_H

#include <grpcpp/support/config.h>
#include <grpcpp/support/string_ref.h>

#include <iterator>
#include <vector>

struct grpc_auth_context;
struct grpc_auth_property;
struct grpc_auth_property_iterator;

namespace grpc {
class SecureAuthContext;

typedef std::pair<string_ref, string_ref> AuthProperty;

class AuthPropertyIterator {
 public:
  using iterator_category = std::forward_iterator_tag;
  using value_type = const AuthProperty;
  using pointer = void;
  using reference = void;
  using difference_type = std::ptrdiff_t;

  ~AuthPropertyIterator();
  AuthPropertyIterator& operator++();
  AuthPropertyIterator operator++(int);
  bool operator==(const AuthPropertyIterator& rhs) const;
  bool operator!=(const AuthPropertyIterator& rhs) const;
  AuthProperty operator*();

 protected:
  AuthPropertyIterator();
  AuthPropertyIterator(const grpc_auth_property* property,
                       const grpc_auth_property_iterator* iter);

 private:
  friend class SecureAuthContext;
  const grpc_auth_property* property_;

  const grpc_auth_context* ctx_;
  size_t index_;
  const char* name_;
};

class AuthContext {
 public:
  virtual ~AuthContext() {}

  virtual bool IsPeerAuthenticated() const = 0;

  virtual std::vector<grpc::string_ref> GetPeerIdentity() const = 0;
  virtual std::string GetPeerIdentityPropertyName() const = 0;

  virtual std::vector<grpc::string_ref> FindPropertyValues(
      const std::string& name) const = 0;

  virtual AuthPropertyIterator begin() const = 0;
  virtual AuthPropertyIterator end() const = 0;

  virtual void AddProperty(const std::string& key, const string_ref& value) = 0;
  virtual bool SetPeerIdentityPropertyName(const std::string& name) = 0;
};

}

#endif
