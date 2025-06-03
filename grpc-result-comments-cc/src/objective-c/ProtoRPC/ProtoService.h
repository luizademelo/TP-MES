Here's the commented version of the code:

```c++
/*
 *
 * Copyright 2015 gRPC authors.
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

// Import necessary Foundation and gRPC client headers
#import <Foundation/Foundation.h>
#import <GRPCClient/GRPCCallOptions.h>
#import "ProtoRPC.h"

// Forward declarations for protocols and classes used in the interface
@protocol GRXWriteable;
@class GRXWriter;
@class GRPCCallOptions;

// Temporarily suppress nullability completeness warnings for this section
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnullability-completeness"

// ProtoService interface marked as deprecated, with suggestion to use GRPCProtoService instead
__attribute__((deprecated("Please use GRPCProtoService.")))
@interface ProtoService : NSObject

/**
 * Designated initializer for ProtoService
 * @param host The host address for the gRPC service
 * @param packageName The proto package name
 * @param serviceName The proto service name
 * @param callOptions Configuration options for the gRPC calls (nullable)
 * @return An initialized instance of ProtoService
 */
- (nullable instancetype)initWithHost:(nonnull NSString *)host
                          packageName:(nonnull NSString *)packageName
                          serviceName:(nonnull NSString *)serviceName
                          callOptions:(nullable GRPCCallOptions *)callOptions
    NS_DESIGNATED_INITIALIZER;

/**
 * Creates and returns a unary gRPC call
 * @param method The RPC method name to call
 * @param message The proto message to send
 * @param handler The response handler for the call
 * @param callOptions Configuration options for the call (nullable)
 * @param responseClass The expected class of the response message
 * @return A configured GRPCUnaryProtoCall instance
 */
- (nullable GRPCUnaryProtoCall *)RPCToMethod:(nonnull NSString *)method
                                     message:(nonnull id)message
                             responseHandler:(nonnull id<GRPCProtoResponseHandler>)handler
                                 callOptions:(nullable GRPCCallOptions *)callOptions
                               responseClass:(nonnull Class)responseClass;

/**
 * Creates and returns a streaming gRPC call
 * @param method The RPC method name to call
 * @param handler The response handler for the call
 * @param callOptions Configuration options for the call (nullable)
 * @param responseClass The expected class of the response messages
 * @return A configured GRPCStreamingProtoCall instance
 */
- (nullable GRPCStreamingProtoCall *)RPCToMethod:(nonnull NSString *)method
                                 responseHandler:(nonnull id<GRPCProtoResponseHandler>)handler
                                     callOptions:(nullable GRPCCallOptions *)callOptions
                                   responseClass:(nonnull Class)responseClass;

@end

// Legacy interface extension for backward compatibility
@interface ProtoService (Legacy)

/**
 * Legacy initializer without call options
 */
- (instancetype)initWithHost:(NSString *)host
                 packageName:(NSString *)packageName
                 serviceName:(NSString *)serviceName;

/**
 * Legacy method for creating RPC calls with writers
 * @param method The RPC method name to call
 * @param requestsWriter The writer for request messages
 * @param responseClass The expected class of the response messages
 * @param responsesWriteable The writeable for receiving responses
 * @return A configured GRPCProtoCall instance
 */
- (GRPCProtoCall *)RPCToMethod:(NSString *)method
                requestsWriter:(GRXWriter *)requestsWriter
                 responseClass:(Class)responseClass
            responsesWriteable:(id<GRXWriteable>)responsesWriteable;

@end

// Restore compiler diagnostics
#pragma clang diagnostic pop

// Temporarily suppress deprecation warnings for this section
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

/**
 * GRPCProtoService interface that inherits from ProtoService
 * This is the recommended replacement for ProtoService
 */
@interface GRPCProtoService : ProtoService
#pragma clang diagnostic pop

@end
```

The comments added:
1. Explain the purpose of each interface and method
2. Document parameters and return values
3. Note deprecation warnings and recommended alternatives
4. Explain the use of compiler diagnostic pragmas
5. Provide context for legacy methods
6. Use consistent formatting for documentation

The comments follow standard Objective-C documentation style and provide clear explanations for future maintainers while preserving all the original code functionality.