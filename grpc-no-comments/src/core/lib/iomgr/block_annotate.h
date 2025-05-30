
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_BLOCK_ANNOTATE_H
#define GRPC_SRC_CORE_LIB_IOMGR_BLOCK_ANNOTATE_H

void gpr_thd_start_blocking_region();
void gpr_thd_end_blocking_region();

#ifdef GRPC_SCHEDULING_MARK_BLOCKING_REGION
#define GRPC_SCHEDULING_START_BLOCKING_REGION \
  do {                                        \
    gpr_thd_start_blocking_region();          \
  } while (0)
#define GRPC_SCHEDULING_END_BLOCKING_REGION     \
  do {                                          \
    gpr_thd_end_blocking_region();              \
    grpc_core::ExecCtx::Get()->InvalidateNow(); \
  } while (0)
#define GRPC_SCHEDULING_END_BLOCKING_REGION_NO_EXEC_CTX \
  do {                                                  \
    gpr_thd_end_blocking_region();                      \
  } while (0)

#else
#define GRPC_SCHEDULING_START_BLOCKING_REGION \
  do {                                        \
  } while (0)
#define GRPC_SCHEDULING_END_BLOCKING_REGION     \
  do {                                          \
    grpc_core::ExecCtx::Get()->InvalidateNow(); \
  } while (0)
#define GRPC_SCHEDULING_END_BLOCKING_REGION_NO_EXEC_CTX \
  do {                                                  \
  } while (0)
#endif

#endif
