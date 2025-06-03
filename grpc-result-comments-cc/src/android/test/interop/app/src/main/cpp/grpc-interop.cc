Here's the commented version of the code:

```c++
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

#include <jni.h>

#include "absl/strings/str_format.h"

#include <grpcpp/grpcpp.h>

#include "test/cpp/interop/interop_client.h"

/**
 * Creates and returns a shared pointer to an InteropClient instance.
 * 
 * @param host The server host address to connect to
 * @param port The server port number
 * @param use_tls Boolean flag indicating whether to use TLS encryption
 * @return std::shared_ptr<grpc::testing::InteropClient> The created client instance
 */
std::shared_ptr<grpc::testing::InteropClient> GetClient(const char* host,
                                                        int port,
                                                        bool use_tls) {
  std::shared_ptr<grpc::ChannelCredentials> credentials;
  if (use_tls) {
    credentials = grpc::SslCredentials(grpc::SslCredentialsOptions());
  } else {
    credentials = grpc::InsecureChannelCredentials();
  }
  // Format host:port string for the channel
  std::string host_port = absl::StrFormat("%s:%d", host, port);
  return std::make_shared<grpc::testing::InteropClient>(
      [host_port, credentials](grpc::ChannelArguments args) {
        return grpc::CreateCustomChannel(host_port, credentials, args);
      },
      true, false);
}

/**
 * JNI wrapper for performing an empty RPC call.
 * 
 * @param env JNI environment pointer
 * @param obj_this Java object reference
 * @param host_raw Java string containing server host address
 * @param port_raw Server port number
 * @param use_tls_raw Boolean flag for TLS usage
 * @return jboolean Result of the empty RPC call
 */
extern "C" JNIEXPORT jboolean JNICALL
Java_io_grpc_interop_cpp_InteropActivity_doEmpty(JNIEnv* env, jobject obj_this,
                                                 jstring host_raw,
                                                 jint port_raw,
                                                 jboolean use_tls_raw) {
  const char* host = env->GetStringUTFChars(host_raw, (jboolean*)0);
  int port = static_cast<int>(port_raw);
  bool use_tls = static_cast<bool>(use_tls_raw);

  jboolean result = GetClient(host, port, use_tls)->DoEmpty();
  env->ReleaseStringUTFChars(host_raw, host);
  return result;
}

/**
 * JNI wrapper for performing a large unary RPC call.
 * 
 * @param env JNI environment pointer
 * @param obj_this Java object reference
 * @param host_raw Java string containing server host address
 * @param port_raw Server port number
 * @param use_tls_raw Boolean flag for TLS usage
 * @return jboolean Result of the large unary RPC call
 */
extern "C" JNIEXPORT jboolean JNICALL
Java_io_grpc_interop_cpp_InteropActivity_doLargeUnary(JNIEnv* env,
                                                      jobject obj_this,
                                                      jstring host_raw,
                                                      jint port_raw,
                                                      jboolean use_tls_raw) {
  const char* host = env->GetStringUTFChars(host_raw, (jboolean*)0);
  int port = static_cast<int>(port_raw);
  bool use_tls = static_cast<bool>(use_tls_raw);

  jboolean result = GetClient(host, port, use_tls)->DoLargeUnary();
  env->ReleaseStringUTFChars(host_raw, host);
  return result;
}

/**
 * JNI wrapper for performing an empty stream RPC call.
 * 
 * @param env JNI environment pointer
 * @param obj_this Java object reference
 * @param host_raw Java string containing server host address
 * @param port_raw Server port number
 * @param use_tls_raw Boolean flag for TLS usage
 * @return jboolean Result of the empty stream RPC call
 */
extern "C" JNIEXPORT jboolean JNICALL
Java_io_grpc_interop_cpp_InteropActivity_doEmptyStream(JNIEnv* env,
                                                       jobject obj_this,
                                                       jstring host_raw,
                                                       jint port_raw,
                                                       jboolean use_tls_raw) {
  const char* host = env->GetStringUTFChars(host_raw, (jboolean*)0);
  int port = static_cast<int>(port_raw);
  bool use_tls = static_cast<bool>(use_tls_raw);

  jboolean result = GetClient(host, port, use_tls)->DoEmptyStream();
  env->ReleaseStringUTFChars(host_raw, host);
  return result;
}

/**
 * JNI wrapper for performing a request streaming RPC call.
 * 
 * @param env JNI environment pointer
 * @param obj_this Java object reference
 * @param host_raw Java string containing server host address
 * @param port_raw Server port number
 * @param use_tls_raw Boolean flag for TLS usage
 * @return jboolean Result of the request streaming RPC call
 */
extern "C" JNIEXPORT jboolean JNICALL
Java_io_grpc_interop_cpp_InteropActivity_doRequestStreaming(
    JNIEnv* env, jobject obj_this, jstring host_raw, jint port_raw,
    jboolean use_tls_raw) {
  const char* host = env->GetStringUTFChars(host_raw, (jboolean*)0);
  int port = static_cast<int>(port_raw);
  bool use_tls = static_cast<bool>(use_tls_raw);

  jboolean result = GetClient(host, port, use_tls)->DoRequestStreaming();
  env->ReleaseStringUTFChars(host_raw, host);
  return result;
}

/**
 * JNI wrapper for performing a response streaming RPC call.
 * 
 * @param env JNI environment pointer
 * @param obj_this Java object reference
 * @param host_raw Java string containing server host address
 * @param port_raw Server port number
 * @param use_tls_raw Boolean flag for TLS usage
 * @return jboolean Result of the response streaming RPC call
 */
extern "C" JNIEXPORT jboolean JNICALL
Java_io_grpc_interop_cpp_InteropActivity_doResponseStreaming(
    JNIEnv* env, jobject obj_this, jstring host_raw, jint port_raw,
    jboolean use_tls_raw) {
  const char* host = env->GetStringUTFChars(host_raw, (jboolean*)0);
  int port = static_cast<int>(port_raw);
  bool use_tls = static_cast<bool>(use_tls_raw);

  jboolean result = GetClient(host, port, use_tls)->DoResponseStreaming();
  env->ReleaseStringUTFChars(host_raw, host);
  return result;
}

/**
 * JNI wrapper for performing a ping-pong (bidirectional streaming) RPC call.
 * 
 * @param env JNI environment pointer
 * @param obj_this Java object reference
 * @param host_raw Java string containing server host address
 * @param port_raw Server port number
 * @param use_tls_raw Boolean flag for TLS usage
 * @return jboolean Result of the ping-pong RPC call
 */
extern "C" JNIEXPORT jboolean JNICALL
Java_io_grpc_interop_cpp_InteropActivity_doPingPong(JNIEnv* env,
                                                    jobject obj_this,
                                                    jstring host_raw,
                                                    jint port_raw,
                                                    jboolean use_tls_raw) {
  const char* host = env->GetStringUTFChars(host_raw, (jboolean*)0);
  int port = static_cast<int>(port_raw);
  bool use_tls = static_cast<bool>(use_tls_raw);

  jboolean result = GetClient(host, port, use_tls)->DoPingPong();
  env->ReleaseStringUTFChars(host_raw, host);
  return result;
}
```

Key improvements in the comments:
1. Added detailed function-level documentation for each method
2. Documented parameters and return values
3. Explained the purpose of each JNI wrapper function
4. Added note about the host:port string formatting in GetClient
5. Maintained consistent comment style throughout
6. Included information about the credential selection logic in GetClient

The comments now provide clear guidance about what each function does, its parameters, and its return value, making the code much more maintainable.