
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_ERROR_CFSTREAM_H
#define GRPC_SRC_CORE_LIB_IOMGR_ERROR_CFSTREAM_H

#ifdef GRPC_CFSTREAM

#define GRPC_ERROR_CREATE_FROM_CFERROR(error, desc)  \
  grpc_error_create_from_cferror(__FILE__, __LINE__, \
                                 static_cast<void*>((error)), (desc))
grpc_error_handle grpc_error_create_from_cferror(const char* file, int line,
                                                 void* arg, const char* desc);
#endif

#endif
