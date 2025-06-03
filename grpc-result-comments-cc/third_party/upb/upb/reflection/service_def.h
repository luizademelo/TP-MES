Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

// Header guard to prevent multiple inclusions of this header file
#ifndef UPB_REFLECTION_SERVICE_DEF_H_
#define UPB_REFLECTION_SERVICE_DEF_H_

// Include necessary headers
#include "upb/reflection/common.h"  // Common definitions for upb reflection
#include "upb/port/def.inc"         // Platform-specific definitions

// C++ compatibility: if compiled as C++, use C linkage
#ifdef __cplusplus
extern "C" {
#endif

// Returns the FileDef that contains this service definition
UPB_API const upb_FileDef* upb_ServiceDef_File(const upb_ServiceDef* s);

// Looks up a method by name within the service. Returns NULL if not found.
const upb_MethodDef* upb_ServiceDef_FindMethodByName(const upb_ServiceDef* s,
                                                     const char* name);

// Returns the fully qualified name of the service (e.g., "package.Service")
UPB_API const char* upb_ServiceDef_FullName(const upb_ServiceDef* s);

// Returns true if the service has custom options defined
bool upb_ServiceDef_HasOptions(const upb_ServiceDef* s);

// Returns the index of this service within its file
int upb_ServiceDef_Index(const upb_ServiceDef* s);

// Returns the i-th method in the service (0-based). Returns NULL if out of bounds.
UPB_API const upb_MethodDef* upb_ServiceDef_Method(const upb_ServiceDef* s,
                                                   int i);

// Returns the number of methods in the service
UPB_API int upb_ServiceDef_MethodCount(const upb_ServiceDef* s);

// Returns the unqualified name of the service (without package)
const char* upb_ServiceDef_Name(const upb_ServiceDef* s);

// Returns the service options message, or NULL if none
UPB_API const UPB_DESC(ServiceOptions) *
    upb_ServiceDef_Options(const upb_ServiceDef* s);

// Returns the resolved feature set for this service
const UPB_DESC(FeatureSet) *
    upb_ServiceDef_ResolvedFeatures(const upb_ServiceDef* s);

// End of C++ linkage section
#ifdef __cplusplus
}
#endif

// Undefine platform-specific macros
#include "upb/port/undef.inc"

#endif  // UPB_REFLECTION_SERVICE_DEF_H_
```

The comments explain:
1. The purpose of header guards and includes
2. The C++ compatibility section
3. Each function's purpose, parameters, and return values
4. Special cases like NULL returns
5. The closing of the C++ linkage section
6. The undefinition of platform-specific macros
7. The closing header guard

The comments are concise but provide enough information for developers to understand the interface without needing to examine the implementation.