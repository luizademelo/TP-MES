#ifndef GOOGLE_UPB_UPB_REFLECTION_DESCRIPTOR_BOOTSTRAP_H__
#define GOOGLE_UPB_UPB_REFLECTION_DESCRIPTOR_BOOTSTRAP_H__

#if defined(UPB_BOOTSTRAP_STAGE) && UPB_BOOTSTRAP_STAGE == 0

#include "upb/reflection/stage0/google/protobuf/descriptor.upb.h"
#elif defined(UPB_BOOTSTRAP_STAGE) && UPB_BOOTSTRAP_STAGE == 1

#include "upb/reflection/stage1/google/protobuf/descriptor.upb.h"
#else

#include "google/protobuf/descriptor.upb.h"
#endif

#endif
