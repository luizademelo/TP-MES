Here's the commented version of the code snippet:

```c++
// Header guard to prevent multiple inclusions of this file
#ifndef GOOGLE_UPB_UPB_REFLECTION_DESCRIPTOR_BOOTSTRAP_H__
#define GOOGLE_UPB_UPB_REFLECTION_DESCRIPTOR_BOOTSTRAP_H__

// Bootstrap stage selection for protocol buffer descriptor loading
// Stage 0: Initial bootstrap phase
#if defined(UPB_BOOTSTRAP_STAGE) && UPB_BOOTSTRAP_STAGE == 0
    // Include the stage0 version of descriptor protobuf definitions
    #include "upb/reflection/stage0/google/protobuf/descriptor.upb.h"

// Stage 1: Intermediate bootstrap phase
#elif defined(UPB_BOOTSTRAP_STAGE) && UPB_BOOTSTRAP_STAGE == 1
    // Include the stage1 version of descriptor protobuf definitions
    #include "upb/reflection/stage1/google/protobuf/descriptor.upb.h"

// Default case: Final/stable version
#else
    // Include the standard/stable version of descriptor protobuf definitions
    #include "google/protobuf/descriptor.upb.h"
#endif

// End of header guard
#endif
```

The comments explain:
1. The purpose of the header guard
2. The bootstrap staging mechanism
3. The different stages (0, 1, and default) and their purposes
4. Which descriptor file is included in each case
5. The meaning of each include statement

The code appears to be part of a system that handles different versions or stages of protocol buffer descriptor definitions during a bootstrap process, likely for the upb (micro protobuf) library.