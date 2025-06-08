Here's the commented version of the code snippet:

```c++
# Configuration module for gRPC build settings
module GrpcBuildConfig
  # Defines the path to the gRPC core Windows dynamic link library (DLL)
  # This constant points to the 64-bit optimized version (opt) of gRPC v48 DLL
  # stored in the temporary libs directory. The path is platform-specific for Windows.
  # Note: In a production environment, this would typically point to a more permanent location.
  CORE_WINDOWS_DLL = '/tmp/libs/opt/grpc-48.dll'
end
```

The comments explain:
1. The overall purpose of the module
2. The specific constant's purpose and what it represents
3. Details about the version and build type (optimized)
4. Platform specificity
5. A note about the temporary nature of the path