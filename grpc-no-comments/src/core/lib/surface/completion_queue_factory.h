
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SURFACE_COMPLETION_QUEUE_FACTORY_H
#define GRPC_SRC_CORE_LIB_SURFACE_COMPLETION_QUEUE_FACTORY_H

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

typedef struct grpc_completion_queue_factory_vtable {
  grpc_completion_queue* (*create)(const grpc_completion_queue_factory*,
                                   const grpc_completion_queue_attributes*);
} grpc_completion_queue_factory_vtable;

struct grpc_completion_queue_factory {
  const char* name;
  void* data;
  grpc_completion_queue_factory_vtable* vtable;
};

#endif
