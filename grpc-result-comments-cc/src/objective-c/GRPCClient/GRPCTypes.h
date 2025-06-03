Here's the commented version of the code:

```c++
/*
 *
 * Copyright 2019 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#import <Foundation/Foundation.h>

// Enumeration defining gRPC error codes that map to standard gRPC status codes
typedef NS_ENUM(NSUInteger, GRPCErrorCode) {
  GRPCErrorCodeCancelled = 1,            // Operation was cancelled
  GRPCErrorCodeUnknown = 2,              // Unknown error
  GRPCErrorCodeInvalidArgument = 3,      // Invalid argument provided
  GRPCErrorCodeDeadlineExceeded = 4,     // Operation timed out
  GRPCErrorCodeNotFound = 5,             // Requested entity not found
  GRPCErrorCodeAlreadyExists = 6,        // Entity already exists
  GRPCErrorCodePermissionDenied = 7,     // Permission denied
  GRPCErrorCodeUnauthenticated = 16,     // Request not authenticated
  GRPCErrorCodeResourceExhausted = 8,    // Resource exhausted
  GRPCErrorCodeFailedPrecondition = 9,   // Operation rejected by system state
  GRPCErrorCodeAborted = 10,             // Operation aborted
  GRPCErrorCodeOutOfRange = 11,          // Operation out of valid range
  GRPCErrorCodeUnimplemented = 12,       // Operation not implemented
  GRPCErrorCodeInternal = 13,            // Internal error
  GRPCErrorCodeUnavailable = 14,         // Service unavailable
  GRPCErrorCodeDataLoss = 15,            // Unrecoverable data loss
};

// Enumeration defining call safety options
typedef NS_ENUM(NSUInteger, GRPCCallSafety) {
  GRPCCallSafetyDefault = 0,  // Default call safety level
};

// Enumeration defining supported compression algorithms
typedef NS_ENUM(NSUInteger, GRPCCompressionAlgorithm) {
  GRPCCompressNone = 0,       // No compression
  GRPCCompressDeflate,        // DEFLATE compression
  GRPCCompressGzip,           // GZIP compression
  GRPCStreamCompressGzip,     // GZIP compression for streams
};

// Type alias for compression algorithm
typedef GRPCCompressionAlgorithm GRPCCompressAlgorithm;

// Enumeration defining transport types
typedef NS_ENUM(NSUInteger, GRPCTransportType) {
  GRPCTransportTypeDefault = 0,         // Default transport type
  GRPCTransportTypeChttp2BoringSSL = 0, // HTTP/2 with BoringSSL (same as default)
  GRPCTransportTypeInsecure,            // Insecure transport (no encryption)
};

// Error domain for gRPC errors
extern NSString* _Nonnull const kGRPCErrorDomain;

// Keys for accessing headers and trailers in response metadata
extern NSString* _Nonnull const kGRPCHeadersKey;
extern NSString* _Nonnull const kGRPCTrailersKey;

// Type definition for transport identifiers
typedef const char* _Nonnull GRPCTransportID;

// Protocol for authorization token providers
@protocol GRPCAuthorizationProtocol
/**
 * Requests an authorization token asynchronously
 * @param handler Completion block that receives the token or nil if unavailable
 */
- (void)getTokenWithHandler:(void (^_Nonnull)(NSString* _Nullable token))handler;
@end

// Type definition for metadata dictionary (headers/trailers)
typedef NSDictionary<NSString*, id> GRPCMetadataDictionary;
```

Key improvements in the comments:
1. Added descriptions for each enum value explaining what they represent
2. Added documentation for the authorization protocol method
3. Added explanations for type aliases and constants
4. Grouped related constants and types together in comments
5. Used consistent comment style throughout
6. Added context about how some values map to gRPC concepts

The comments now provide clear explanations of:
- The purpose of each enumeration
- The meaning of specific error codes
- The role of each type definition
- The functionality of the authorization protocol
- The significance of the constants