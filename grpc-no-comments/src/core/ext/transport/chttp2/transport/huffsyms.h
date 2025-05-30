
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_HUFFSYMS_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_HUFFSYMS_H

#define GRPC_CHTTP2_NUM_HUFFSYMS 257

struct grpc_chttp2_huffsym {
  unsigned bits;
  unsigned length;
};
extern const grpc_chttp2_huffsym grpc_chttp2_huffsyms[GRPC_CHTTP2_NUM_HUFFSYMS];

#endif
