
/*
 *
 * Copyright 2018 gRPC authors.
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

#import "GRPCTypes.h"

NS_ASSUME_NONNULL_BEGIN

@protocol GRPCInterceptorFactory;

@interface GRPCCallOptions : NSObject <NSCopying, NSMutableCopying>

@property(nonatomic, copy, readonly, nullable) NSString *serverAuthority;

@property(nonatomic, readonly) NSTimeInterval timeout;

@property(nonatomic, readonly) BOOL flowControlEnabled;

@property(nonatomic, copy, readonly) NSArray<id<GRPCInterceptorFactory>> *interceptorFactories;

@property(nonatomic, copy, readonly, nullable) NSString *oauth2AccessToken;

@property(nonatomic, readonly, nullable) id<GRPCAuthorizationProtocol> authTokenProvider;

@property(nonatomic, copy, readonly, nullable) GRPCMetadataDictionary *initialMetadata;

@property(nonatomic, copy, readonly, nullable) NSString *userAgentPrefix;

@property(nonatomic, copy, readonly, nullable) NSString *userAgentSuffix;

@property(nonatomic, readonly) NSUInteger responseSizeLimit;

@property(nonatomic, readonly) GRPCCompressionAlgorithm compressionAlgorithm;

@property(nonatomic, readonly) BOOL retryEnabled;

@property(nonatomic, readonly) NSTimeInterval maxRetryInterval;

@property(nonatomic, readonly) NSTimeInterval minRetryInterval;

@property(readonly) double retryFactor;

@property(nonatomic, readonly) NSTimeInterval keepaliveInterval;
@property(nonatomic, readonly) NSTimeInterval keepaliveTimeout;

@property(nonatomic, readonly) NSTimeInterval connectMinTimeout;
@property(nonatomic, readonly) NSTimeInterval connectInitialBackoff;
@property(nonatomic, readonly) NSTimeInterval connectMaxBackoff;

@property(nonatomic, copy, readonly, nullable) GRPCMetadataDictionary *additionalChannelArgs;

@property(nonatomic, copy, readonly, nullable) NSString *PEMRootCertificates;

@property(nonatomic, copy, readonly, nullable) NSString *PEMPrivateKey;

@property(nonatomic, copy, readonly, nullable) NSString *PEMCertificateChain;

@property(nonatomic, readonly) GRPCTransportType transportType;

@property(nonatomic, readonly) GRPCTransportID transport;

@property(nonatomic, copy, readonly, nullable) NSString *hostNameOverride;

@property(nonatomic, copy, readonly, nullable) NSString *channelPoolDomain;

@property(nonatomic, readonly) NSUInteger channelID;

@property(nonatomic, readonly) NSUInteger channelOptionsHash;

- (BOOL)hasChannelOptionsEqualTo:(GRPCCallOptions *)callOptions;

@end

@interface GRPCMutableCallOptions : GRPCCallOptions <NSCopying, NSMutableCopying>

@property(nonatomic, copy, readwrite, nullable) NSString *serverAuthority;

@property(nonatomic, readwrite) NSTimeInterval timeout;

@property(nonatomic, readwrite) BOOL flowControlEnabled;

@property(nonatomic, copy, readwrite) NSArray<id<GRPCInterceptorFactory>> *interceptorFactories;

@property(nonatomic, copy, readwrite, nullable) NSString *oauth2AccessToken;

@property(nonatomic, readwrite, nullable) id<GRPCAuthorizationProtocol> authTokenProvider;

@property(nonatomic, nonatomic, copy, readwrite, nullable) GRPCMetadataDictionary *initialMetadata;

@property(nonatomic, copy, readwrite, nullable) NSString *userAgentPrefix;

@property(nonatomic, copy, readwrite, nullable) NSString *userAgentSuffix;

@property(nonatomic, readwrite) NSUInteger responseSizeLimit;

@property(nonatomic, readwrite) GRPCCompressionAlgorithm compressionAlgorithm;

@property(nonatomic, readwrite) BOOL retryEnabled;

@property(nonatomic, readwrite) NSTimeInterval maxRetryInterval;

@property(nonatomic, readwrite) NSTimeInterval minRetryInterval;

@property(nonatomic, readwrite) double retryFactor;

@property(nonatomic, readwrite) NSTimeInterval keepaliveInterval;
@property(nonatomic, readwrite) NSTimeInterval keepaliveTimeout;

@property(nonatomic, readwrite) NSTimeInterval connectMinTimeout;
@property(nonatomic, readwrite) NSTimeInterval connectInitialBackoff;
@property(nonatomic, readwrite) NSTimeInterval connectMaxBackoff;

@property(nonatomic, copy, readwrite, nullable) GRPCMetadataDictionary *additionalChannelArgs;

@property(nonatomic, copy, readwrite, nullable) NSString *PEMRootCertificates;

@property(nonatomic, copy, readwrite, nullable) NSString *PEMPrivateKey;

@property(nonatomic, copy, readwrite, nullable) NSString *PEMCertificateChain;

@property(nonatomic, readwrite) GRPCTransportType transportType;

@property(nonatomic, readwrite) GRPCTransportID transport;

@property(nonatomic, copy, readwrite, nullable) NSString *hostNameOverride;

@property(nonatomic, copy, readwrite, nullable) NSString *channelPoolDomain;

@property(nonatomic, readwrite) NSUInteger channelID;

@end

NS_ASSUME_NONNULL_END
