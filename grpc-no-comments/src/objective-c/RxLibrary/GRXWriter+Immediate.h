
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

#import "GRXWriter.h"

@interface GRXWriter (Immediate)

+ (instancetype)writerWithEnumerator:(NSEnumerator *)enumerator;

+ (instancetype)writerWithValueSupplier:(id (^)(void))block;

+ (instancetype)writerWithContainer:(id<NSFastEnumeration>)container;

+ (instancetype)writerWithValue:(id)value;

+ (instancetype)writerWithError:(NSError *)error;

+ (instancetype)emptyWriter;

@end
