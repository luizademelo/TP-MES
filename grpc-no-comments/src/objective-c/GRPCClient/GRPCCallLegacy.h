
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

#import <RxLibrary/GRXWriter.h>
#import "GRPCTypes.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnullability-completeness"

@interface GRPCCall : GRXWriter

- (instancetype)init NS_UNAVAILABLE;

@property(atomic, readonly) NSMutableDictionary *requestHeaders;

@property(atomic, copy, readonly) NSDictionary *responseHeaders;

@property(atomic, copy, readonly) NSDictionary *responseTrailers;

- (instancetype)initWithHost:(NSString *)host
                        path:(NSString *)path
              requestsWriter:(GRXWriter *)requestWriter;

- (void)cancel;

+ (void)setCallSafety:(GRPCCallSafety)callSafety host:(NSString *)host path:(NSString *)path;
@property(atomic, copy, readwrite) NSString *serverName;
@property NSTimeInterval timeout;
- (void)setResponseDispatchQueue:(dispatch_queue_t)queue;

@end

#pragma mark Backwards compatibiity

DEPRECATED_MSG_ATTRIBUTE("Use NSDictionary or NSMutableDictionary instead.")
@protocol GRPCRequestHeaders <NSObject>
@property(nonatomic, readonly) NSUInteger count;

- (id)objectForKeyedSubscript:(id)key;
- (void)setObject:(id)obj forKeyedSubscript:(id)key;

- (void)removeAllObjects;
- (void)removeObjectForKey:(id)key;
@end

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated"

@interface NSMutableDictionary (GRPCRequestHeaders) <GRPCRequestHeaders>
@end
#pragma clang diagnostic pop
#pragma clang diagnostic pop
