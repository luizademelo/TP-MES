Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_REFLECTION_FILE_DEF_H_
#define UPB_REFLECTION_FILE_DEF_H_

// Include necessary headers for file definition functionality
#include "upb/reflection/common.h"
#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

// Returns the name of the edition corresponding to the given edition number
UPB_API const char* upb_FileDef_EditionName(int edition);

// File Dependency Functions
// Returns the i-th dependency of the file definition
const upb_FileDef* upb_FileDef_Dependency(const upb_FileDef* f, int i);
// Returns the number of dependencies for the file definition
int upb_FileDef_DependencyCount(const upb_FileDef* f);

// Returns true if the file has options defined
bool upb_FileDef_HasOptions(const upb_FileDef* f);

// Basic File Information Functions
// Returns the name of the file
UPB_API const char* upb_FileDef_Name(const upb_FileDef* f);
// Returns the file options
const UPB_DESC(FileOptions) * upb_FileDef_Options(const upb_FileDef* f);
// Returns the resolved feature set for the file
const UPB_DESC(FeatureSet) * upb_FileDef_ResolvedFeatures(const upb_FileDef* f);
// Returns the package name for the file
const char* upb_FileDef_Package(const upb_FileDef* f);
// Returns the edition of the file
UPB_DESC(Edition) upb_FileDef_Edition(const upb_FileDef* f);
// Returns the def pool containing this file definition
UPB_API const upb_DefPool* upb_FileDef_Pool(const upb_FileDef* f);

// Public Dependency Functions
// Returns the i-th public dependency of the file definition
const upb_FileDef* upb_FileDef_PublicDependency(const upb_FileDef* f, int i);
// Returns the number of public dependencies for the file definition
int upb_FileDef_PublicDependencyCount(const upb_FileDef* f);

// Service Definition Functions
// Returns the i-th service defined in the file
const upb_ServiceDef* upb_FileDef_Service(const upb_FileDef* f, int i);
// Returns the number of services defined in the file
int upb_FileDef_ServiceCount(const upb_FileDef* f);

// Returns the syntax level of the file (proto2/proto3)
UPB_API upb_Syntax upb_FileDef_Syntax(const upb_FileDef* f);

// Top-Level Definition Functions
// Returns the i-th top-level enum defined in the file
const upb_EnumDef* upb_FileDef_TopLevelEnum(const upb_FileDef* f, int i);
// Returns the number of top-level enums defined in the file
int upb_FileDef_TopLevelEnumCount(const upb_FileDef* f);

// Returns the i-th top-level extension defined in the file
const upb_FieldDef* upb_FileDef_TopLevelExtension(const upb_FileDef* f, int i);
// Returns the number of top-level extensions defined in the file
int upb_FileDef_TopLevelExtensionCount(const upb_FileDef* f);

// Returns the i-th top-level message defined in the file
const upb_MessageDef* upb_FileDef_TopLevelMessage(const upb_FileDef* f, int i);
// Returns the number of top-level messages defined in the file
int upb_FileDef_TopLevelMessageCount(const upb_FileDef* f);

// Weak Dependency Functions
// Returns the i-th weak dependency of the file definition
const upb_FileDef* upb_FileDef_WeakDependency(const upb_FileDef* f, int i);
// Returns the number of weak dependencies for the file definition
int upb_FileDef_WeakDependencyCount(const upb_FileDef* f);

// Returns true if the file resolves the given symbol name
bool upb_FileDef_Resolves(const upb_FileDef* f, const char* symbol);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif  // UPB_REFLECTION_FILE_DEF_H_
```

The comments I've added:
1. Grouped related functions together with section headers
2. Added descriptions for each function's purpose
3. Clarified what each function returns
4. Maintained the original code structure while making it more understandable
5. Added a clear closing comment for the header guard

The comments follow these principles:
- Be concise but descriptive
- Explain the purpose of each function
- Group related functionality together
- Maintain consistency with existing style
- Avoid stating the obvious (like "this is a function")
- Focus on the "why" more than the "how" where appropriate