
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

typedef NS_ENUM(NSUInteger, GRPCErrorCode) {

  GRPCErrorCodeCancelled = 1,

  GRPCErrorCodeUnknown = 2,

  GRPCErrorCodeInvalidArgument = 3,

  GRPCErrorCodeDeadlineExceeded = 4,

  GRPCErrorCodeNotFound = 5,

  GRPCErrorCodeAlreadyExists = 6,

  GRPCErrorCodePermissionDenied = 7,

  GRPCErrorCodeUnauthenticated = 16,

  GRPCErrorCodeResourceExhausted = 8,

  GRPCErrorCodeFailedPrecondition = 9,

  GRPCErrorCodeAborted = 10,

  GRPCErrorCodeOutOfRange = 11,

  GRPCErrorCodeUnimplemented = 12,

  GRPCErrorCodeInternal = 13,

  GRPCErrorCodeUnavailable = 14,

  GRPCErrorCodeDataLoss = 15,
};

typedef NS_ENUM(NSUInteger, GRPCCallSafety) {

  GRPCCallSafetyDefault = 0,
};

typedef NS_ENUM(NSUInteger, GRPCCompressionAlgorithm) {
  GRPCCompressNone = 0,
  GRPCCompressDeflate,
  GRPCCompressGzip,
  GRPCStreamCompressGzip,
};

typedef GRPCCompressionAlgorithm GRPCCompressAlgorithm;

typedef NS_ENUM(NSUInteger, GRPCTransportType) {
  GRPCTransportTypeDefault = 0,

  GRPCTransportTypeChttp2BoringSSL = 0,

  GRPCTransportTypeInsecure,
};

extern NSString* _Nonnull const kGRPCErrorDomain;

extern NSString* _Nonnull const kGRPCHeadersKey;
extern NSString* _Nonnull const kGRPCTrailersKey;

typedef const char* _Nonnull GRPCTransportID;

@protocol GRPCAuthorizationProtocol

- (void)getTokenWithHandler:(void (^_Nonnull)(NSString* _Nullable token))handler;

@end

typedef NSDictionary<NSString*, id> GRPCMetadataDictionary;
