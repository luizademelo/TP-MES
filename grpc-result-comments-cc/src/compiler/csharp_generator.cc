Here's the commented version of the code:

```c++
/*
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
 */

#include "src/compiler/csharp_generator.h"

#include <cctype>
#include <map>
#include <sstream>
#include <vector>

#include "src/compiler/config.h"
#include "src/compiler/csharp_generator_helpers.h"

// Protobuf and gRPC namespace imports
using grpc::protobuf::Descriptor;
using grpc::protobuf::FileDescriptor;
using grpc::protobuf::MethodDescriptor;
using grpc::protobuf::ServiceDescriptor;
using grpc::protobuf::io::Printer;
using grpc::protobuf::io::StringOutputStream;
using grpc_generator::StringReplace;
using std::vector;

namespace grpc_csharp_generator {
namespace {

// Generates documentation comments from protobuf source location comments
// Escapes XML special characters and formats as C# documentation comments
bool GenerateDocCommentBodyImpl(grpc::protobuf::io::Printer* printer,
                                grpc::protobuf::SourceLocation location) {
  std::string comments = location.leading_comments.empty()
                             ? location.trailing_comments
                             : location.leading_comments;
  if (comments.empty()) {
    return false;
  }

  // Escape XML special characters
  comments = grpc_generator::StringReplace(comments, "&", "&amp;", true);
  comments = grpc_generator::StringReplace(comments, "<", "&lt;", true);

  std::vector<std::string> lines;
  grpc_generator::Split(comments, '\n', &lines);
  // TODO: We really should work out which part to put in the summary and which

  printer->Print("/// <summary>\n");
  bool last_was_empty = false;

  for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end();
       ++it) {
    std::string line = *it;
    if (line.empty()) {
      last_was_empty = true;
    } else {
      if (last_was_empty) {
        printer->Print("///\n");
      }
      last_was_empty = false;

      // Escape comment lines starting with '/'
      if (line[0] == '/') {
        line.replace(0, 1, "&#x2F;");
      }
      printer->Print("///$line$\n", "line", line);
    }
  }
  printer->Print("/// </summary>\n");
  return true;
}

// Generates the [GeneratedCode] attribute for generated C# code
void GenerateGeneratedCodeAttribute(grpc::protobuf::io::Printer* printer) {
  printer->Print(
      "[global::System.CodeDom.Compiler.GeneratedCode(\"grpc_csharp_plugin\", "
      "null)]\n");
}

// Generates the [Obsolete] attribute if the service/method is deprecated
void GenerateObsoleteAttribute(grpc::protobuf::io::Printer* printer,
                               bool is_deprecated) {
  if (is_deprecated) {
    printer->Print("[global::System.ObsoleteAttribute]\n");
  }
}

// Template function to generate documentation comments for descriptors
template <typename DescriptorType>
bool GenerateDocCommentBody(grpc::protobuf::io::Printer* printer,
                            const DescriptorType* descriptor) {
  grpc::protobuf::SourceLocation location;
  if (!descriptor->GetSourceLocation(&location)) {
    return false;
  }
  return GenerateDocCommentBodyImpl(printer, location);
}

// Generates documentation comments for server-side methods
void GenerateDocCommentServerMethod(grpc::protobuf::io::Printer* printer,
                                    const MethodDescriptor* method) {
  if (GenerateDocCommentBody(printer, method)) {
    if (method->client_streaming()) {
      printer->Print(
          "/// <param name=\"requestStream\">Used for reading requests from "
          "the client.</param>\n");
    } else {
      printer->Print(
          "/// <param name=\"request\">The request received from the "
          "client.</param>\n");
    }
    if (method->server_streaming()) {
      printer->Print(
          "/// <param name=\"responseStream\">Used for sending responses back "
          "to the client.</param>\n");
    }
    printer->Print(
        "/// <param name=\"context\">The context of the server-side call "
        "handler being invoked.</param>\n");
    if (method->server_streaming()) {
      printer->Print(
          "/// <returns>A task indicating completion of the "
          "handler.</returns>\n");
    } else {
      printer->Print(
          "/// <returns>The response to send back to the client (wrapped by a "
          "task).</returns>\n");
    }
  }
}

// Generates documentation comments for client-side methods
void GenerateDocCommentClientMethod(grpc::protobuf::io::Printer* printer,
                                    const MethodDescriptor* method,
                                    bool is_sync, bool use_call_options) {
  if (GenerateDocCommentBody(printer, method)) {
    if (!method->client_streaming()) {
      printer->Print(
          "/// <param name=\"request\">The request to send to the "
          "server.</param>\n");
    }
    if (!use_call_options) {
      printer->Print(
          "/// <param name=\"headers\">The initial metadata to send with the "
          "call. This parameter is optional.</param>\n");
      printer->Print(
          "/// <param name=\"deadline\">An optional deadline for the call. The "
          "call will be cancelled if deadline is hit.</param>\n");
      printer->Print(
          "/// <param name=\"cancellationToken\">An optional token for "
          "canceling the call.</param>\n");
    } else {
      printer->Print(
          "/// <param name=\"options\">The options for the call.</param>\n");
    }
    if (is_sync) {
      printer->Print(
          "/// <returns>The response received from the server.</returns>\n");
    } else {
      printer->Print("/// <returns>The call object.</returns>\n");
    }
  }
}

// Helper functions to generate class names for services and clients
std::string GetServiceClassName(const ServiceDescriptor* service) {
  return std::string(service->name());
}

std::string GetClientClassName(const ServiceDescriptor* service) {
  return std::string(service->name()) + "Client";
}

std::string GetServerClassName(const ServiceDescriptor* service) {
  return std::string(service->name()) + "Base";
}

// Determines the gRPC method type based on streaming characteristics
std::string GetCSharpMethodType(const MethodDescriptor* method) {
  if (method->client_streaming()) {
    if (method->server_streaming()) {
      return "grpc::MethodType.DuplexStreaming";
    } else {
      return "grpc::MethodType.ClientStreaming";
    }
  } else {
    if (method->server_streaming()) {
      return "grpc::MethodType.ServerStreaming";
    } else {
      return "grpc::MethodType.Unary";
    }
  }
}

// Determines the server method type based on streaming characteristics
std::string GetCSharpServerMethodType(const MethodDescriptor* method) {
  if (method->client_streaming()) {
    if (method->server_streaming()) {
      return "grpc::DuplexStreamingServerMethod";
    } else {
      return "grpc::ClientStreamingServerMethod";
    }
  } else {
    if (method->server_streaming()) {
      return "grpc::ServerStreamingServerMethod";
    } else {
      return "grpc::UnaryServerMethod";
    }
  }
}

// Field name constants
std::string GetServiceNameFieldName() { return "__ServiceName"; }

std::string GetMarshallerFieldName(const Descriptor* message) {
  return "__Marshaller_" +
         grpc_generator::StringReplace(std::string(message->full_name()), ".",
                                       "_", true);
}

std::string GetMethodFieldName(const MethodDescriptor* method) {
  return "__Method_" + std::string(method->name());
}

// Generates method request parameters with appropriate types
std::string GetMethodRequestParamMaybe(const MethodDescriptor* method,
                                       bool invocation_param = false) {
  if (method->client_streaming()) {
    return "";
  }
  if (invocation_param) {
    return "request, ";
  }
  return GRPC_CUSTOM_CSHARP_GETCLASSNAME(method->input_type()) + " request, ";
}

// Returns the access level modifier based on internal_access flag
std::string GetAccessLevel(bool internal_access) {
  return internal_access ? "internal" : "public";
}

// Determines the return type for client methods based on streaming characteristics
std::string GetMethodReturnTypeClient(const MethodDescriptor* method) {
  if (method->client_streaming()) {
    if (method->server_streaming()) {
      return "grpc::AsyncDuplexStreamingCall<" +
             GRPC_CUSTOM_CSHARP_GETCLASSNAME(method->input_type()) + ", " +
             GRPC_CUSTOM_CSHARP_GETCLASSNAME(method->output_type()) + ">";
    } else {
      return "grpc::AsyncClientStreamingCall<" +
             GRPC_CUSTOM_CSHARP_GETCLASSNAME(method->input_type()) + ", " +
             GRPC_CUSTOM_CSHARP_GETCLASSNAME(method->output_type()) + ">";
    }
  } else {
    if (method->server_streaming()) {
      return "grpc::AsyncServerStreamingCall<" +
             GRPC_CUSTOM_CSHARP_GETCLASSNAME(method->output_type()) + ">";
    } else {
      return "grpc::AsyncUnaryCall<" +
             GRPC_CUSTOM_CSHARP_GETCLASSNAME(method->output_type()) + ">";
    }
  }
}

// Generates server method request parameters with appropriate types
std::string GetMethodRequestParamServer(const MethodDescriptor* method) {
  if (method->client_streaming()) {
    return "grpc::IAsyncStreamReader<" +
           GRPC_CUSTOM_CSHARP_GETCLASSNAME(method->input_type()) +
           "> requestStream";
  }
  return GRPC_CUSTOM_CSHARP_GETCLASSNAME(method->input_type()) + " request";
}

// Determines the return type for server methods based on streaming characteristics
std::string GetMethodReturnTypeServer(const MethodDescriptor* method) {
  if (method->server_streaming()) {
    return "global::System.Threading.Tasks.Task";
  }
  return "global::System.Threading.Tasks.Task<" +
         GRPC_CUSTOM_CSHARP_GETCLASSNAME(method->output_type()) + ">";
}

// Generates response stream parameter for server streaming methods
std::string GetMethodResponseStreamMaybe(const MethodDescriptor* method) {
  if (method->server_streaming()) {
    return ", grpc::IServerStreamWriter<" +
           GRPC_CUSTOM_CSHARP_GETCLASSNAME(method->output_type()) +
           "> responseStream";
  }
  return "";
}

// Collects all message types used in a service
std::vector<const Descriptor*> GetUsedMessages(
    const ServiceDescriptor* service) {
  std::set<const Descriptor*> descriptor_set;
  std::vector<const Descriptor*> result;
  for (int i = 0; i < service->method_count(); i++) {
    const MethodDescriptor* method = service->method(i);
    if (descriptor_set.find(method->input_type()) == descriptor_set.end()) {
      descriptor_set.insert(method->input_type());
      result.push_back(method->input_type());
    }
    if (descriptor_set.find(method->output_type()) == descriptor_set.end()) {
      descriptor_set.insert(method->output_type());
      result.push_back(method->output_type());
    }
  }
  return result;
}

// Generates marshaller fields for all message types used in the service
void GenerateMarshallerFields(Printer* out, const ServiceDescriptor* service) {
  std::vector<const Descriptor*> used_messages = GetUsedMessages(service);
  if (used_messages.size() != 0) {
    // Generate helper methods for message serialization/deserialization
    GenerateGeneratedCodeAttribute(out);
    out->Print(
        "static void __Helper_SerializeMessage("
        "global::Google.Protobuf.IMessage message, "
        "grpc::SerializationContext context)\n"
        "{\n");
    out->Indent();
    out->Print(
        "#if !GRPC_DISABLE_PROTOBUF_BUFFER_SERIALIZATION\n"
        "if (message is global::Google.Protobuf.IBufferMessage)\n"
        "{\n");
    out->Indent();
    out->Print(
        "context.SetPayloadLength(message.CalculateSize());\n"
        "global::Google.Protobuf.MessageExtensions.WriteTo(message, "
        "context.GetBufferWriter());\n"
        "context.Complete();\n"
        "return;\n");
    out->Outdent();
    out->Print(
        "}\n"
        "#endif\n");
    out->Print(
        "context.Complete("
        "global::Google.Protobuf.MessageExtensions.ToByteArray(message));\n");
    out->Outdent();
    out->Print("}\n\n");

    // Generate message cache helper class
    GenerateGeneratedCodeAttribute(out);
    out->Print(
        "static class __Helper_MessageCache<T>\n"
        "{\n");
    out->Indent();
    out->Print(
        "public static readonly bool IsBufferMessage = "
        "global::System.Reflection.IntrospectionExtensions.GetTypeInfo(typeof("
        "global::Google.Protobuf.IBufferMessage)).IsAssignableFrom(typeof(T));"
        "\n");
    out->Outdent();
    out->Print("}\n\n");

    // Generate helper method for message deserialization
    GenerateGeneratedCodeAttribute(out);
    out->Print(
        "static T __Helper_DeserializeMessage<T>("
        "grpc::DeserializationContext context, "
        "global::Google.Protobuf.MessageParser<T> parser) "
        "where T : global::Google.Protobuf.IMessage<T>\n"
        "{\n");
    out->Indent();
    out->Print(
        "#if !GRPC_DISABLE_PROTOBUF_BUFFER_SERIALIZATION\n"
        "if (__Helper_MessageCache<T>.IsBufferMessage)\n"
        "{\n");
    out->Indent();
    out->Print(
        "return parser.ParseFrom(context.PayloadAsReadOnlySequence());\n");
    out->Outdent();
    out->Print(
        "}\n"
        "#endif\n");
    out->Print("return parser.ParseFrom(context.PayloadAsNewBuffer());\n");
    out->Outdent();
    out->Print("}\n\n");
  }

  // Generate marshaller fields for each message type
  for (size_t i = 0; i < used_messages.size(); i++) {
    const Descriptor* message = used_messages[i];
    GenerateGeneratedCodeAttribute(out);
    out->Print(
        "static readonly grpc::Marshaller<$type$> $fieldname$ = "
        "grpc::Marshallers.Create(__Helper_SerializeMessage, "
        "context => __Helper_DeserializeMessage(context, $type$.Parser));\n",
        "fieldname", GetMarshallerFieldName(message), "type",
        GRPC_CUSTOM_CSHARP_GETCLASSNAME(message));
  }
  out->Print("\n");
}

// Generates static method fields for gRPC methods
void GenerateStaticMethodField(Printer* out, const MethodDescriptor* method) {
  GenerateGeneratedCodeAttribute(out);
  out->Print(
      "static readonly grpc::Method<$request$, $response$> $fieldname$ = new "
      "grpc::Method<$request$, $response$>(\n",
      "fieldname", GetMethodFieldName(method), "request",
      GRPC_CUSTOM_CSHARP_GETCLASSNAME(method->input_type()), "response",
      GRPC_CUSTOM_CSHARP_GETCLASSNAME(method->output_type()));
  out->Indent();
  out->Indent();
  out->Print("$methodtype$,\n", "methodtype", GetCSharpMethodType(method));
  out->Print("$servicenamefield$,\n", "servicenamefield",
             GetServiceNameFieldName());
  out->Print("\"$methodname$\",\n", "methodname", method->name());
  out->Print("$requestmarshaller$,\n", "requestmarshaller",
             GetMarshallerFieldName(method->input_type()));
  out->Print("$responsemarshaller$);\n", "responsemarshaller",
             GetMarshallerFieldName(method->output_type()));
  out->Print("\n");
  out->Outdent();
  out->Outdent();
}

// Generates the service descriptor property
void GenerateServiceDescriptorProperty(Printer* out,
                                       const ServiceDescriptor* service) {
  std::ostringstream index;
  index << service->index();
  out->Print("/// <summary>Service descriptor</summary>\n");
  out->Print(
      "public static global::Google.Protobuf.Reflection.ServiceDescriptor "
      "Descriptor\n");
  out->Print("{\n");
  out->Print("  get { return $umbrella$.Descriptor.Services[$index$]; }\n",
             "umbrella",
             GRPC_CUSTOM_CSHARP_GETREFLECTIONCLASSNAME(service->file()),
             "index", index.str());
  out->Print("}\n");
  out->Print("\n");
}

// Generates the server base class with virtual methods for service implementation
void GenerateServerClass(Pr