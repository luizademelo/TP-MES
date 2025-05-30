
// Copyright 2015 gRPC authors.

#include <grpc/grpc_security.h>
#include <grpcpp/security/auth_context.h>
#include <grpcpp/support/string_ref.h>

#include <utility>

namespace grpc {

AuthPropertyIterator::AuthPropertyIterator()
    : property_(nullptr), ctx_(nullptr), index_(0), name_(nullptr) {}

AuthPropertyIterator::AuthPropertyIterator(
    const grpc_auth_property* property, const grpc_auth_property_iterator* iter)
    : property_(property),
      ctx_(iter->ctx),
      index_(iter->index),
      name_(iter->name) {}

AuthPropertyIterator::~AuthPropertyIterator() {}

AuthPropertyIterator& AuthPropertyIterator::operator++() {
  grpc_auth_property_iterator iter = {ctx_, index_, name_};
  property_ = grpc_auth_property_iterator_next(&iter);
  ctx_ = iter.ctx;
  index_ = iter.index;
  name_ = iter.name;
  return *this;
}

AuthPropertyIterator AuthPropertyIterator::operator++(int) {
  AuthPropertyIterator tmp(*this);
  operator++();
  return tmp;
}

bool AuthPropertyIterator::operator==(const AuthPropertyIterator& rhs) const {
  if (property_ == nullptr || rhs.property_ == nullptr) {
    return property_ == rhs.property_;
  } else {
    return index_ == rhs.index_;
  }
}

bool AuthPropertyIterator::operator!=(const AuthPropertyIterator& rhs) const {
  return !operator==(rhs);
}

AuthProperty AuthPropertyIterator::operator*() {
  return std::pair<grpc::string_ref, grpc::string_ref>(
      property_->name,
      grpc::string_ref(property_->value, property_->value_length));
}

}
