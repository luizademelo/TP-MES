
// Copyright 2023 gRPC authors.

#pragma warning disable 0414, 1591, 8981, 0612
#region Designer generated code

using grpc = global::Grpc.Core;

namespace Test.Csharp.Codegen.Simple.Proto.Helloworld {

  public static partial class Greeter
  {
    static readonly string __ServiceName = "test.csharp.codegen.simple.proto.helloworld.Greeter";

    [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
    static void __Helper_SerializeMessage(global::Google.Protobuf.IMessage message, grpc::SerializationContext context)
    {
      #if !GRPC_DISABLE_PROTOBUF_BUFFER_SERIALIZATION
      if (message is global::Google.Protobuf.IBufferMessage)
      {
        context.SetPayloadLength(message.CalculateSize());
        global::Google.Protobuf.MessageExtensions.WriteTo(message, context.GetBufferWriter());
        context.Complete();
        return;
      }
      #endif
      context.Complete(global::Google.Protobuf.MessageExtensions.ToByteArray(message));
    }

    [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
    static class __Helper_MessageCache<T>
    {
      public static readonly bool IsBufferMessage = global::System.Reflection.IntrospectionExtensions.GetTypeInfo(typeof(global::Google.Protobuf.IBufferMessage)).IsAssignableFrom(typeof(T));
    }

    [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
    static T __Helper_DeserializeMessage<T>(grpc::DeserializationContext context, global::Google.Protobuf.MessageParser<T> parser) where T : global::Google.Protobuf.IMessage<T>
    {
      #if !GRPC_DISABLE_PROTOBUF_BUFFER_SERIALIZATION
      if (__Helper_MessageCache<T>.IsBufferMessage)
      {
        return parser.ParseFrom(context.PayloadAsReadOnlySequence());
      }
      #endif
      return parser.ParseFrom(context.PayloadAsNewBuffer());
    }

    [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
    static readonly grpc::Marshaller<global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloRequest> __Marshaller_test_csharp_codegen_simple_proto_helloworld_HelloRequest = grpc::Marshallers.Create(__Helper_SerializeMessage, context => __Helper_DeserializeMessage(context, global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloRequest.Parser));
    [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
    static readonly grpc::Marshaller<global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloReply> __Marshaller_test_csharp_codegen_simple_proto_helloworld_HelloReply = grpc::Marshallers.Create(__Helper_SerializeMessage, context => __Helper_DeserializeMessage(context, global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloReply.Parser));

    [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
    static readonly grpc::Method<global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloRequest, global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloReply> __Method_SayHello = new grpc::Method<global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloRequest, global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloReply>(
        grpc::MethodType.Unary,
        __ServiceName,
        "SayHello",
        __Marshaller_test_csharp_codegen_simple_proto_helloworld_HelloRequest,
        __Marshaller_test_csharp_codegen_simple_proto_helloworld_HelloReply);

    [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
    static readonly grpc::Method<global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloRequest, global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloReply> __Method_SayHelloStreamReply = new grpc::Method<global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloRequest, global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloReply>(
        grpc::MethodType.ServerStreaming,
        __ServiceName,
        "SayHelloStreamReply",
        __Marshaller_test_csharp_codegen_simple_proto_helloworld_HelloRequest,
        __Marshaller_test_csharp_codegen_simple_proto_helloworld_HelloReply);

    public static global::Google.Protobuf.Reflection.ServiceDescriptor Descriptor
    {
      get { return global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloworldReflection.Descriptor.Services[0]; }
    }

    [grpc::BindServiceMethod(typeof(Greeter), "BindService")]
    public abstract partial class GreeterBase
    {

      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      public virtual global::System.Threading.Tasks.Task<global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloReply> SayHello(global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloRequest request, grpc::ServerCallContext context)
      {
        throw new grpc::RpcException(new grpc::Status(grpc::StatusCode.Unimplemented, ""));
      }

      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      public virtual global::System.Threading.Tasks.Task SayHelloStreamReply(global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloRequest request, grpc::IServerStreamWriter<global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloReply> responseStream, grpc::ServerCallContext context)
      {
        throw new grpc::RpcException(new grpc::Status(grpc::StatusCode.Unimplemented, ""));
      }

    }

    public partial class GreeterClient : grpc::ClientBase<GreeterClient>
    {

      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      public GreeterClient(grpc::ChannelBase channel) : base(channel)
      {
      }

      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      public GreeterClient(grpc::CallInvoker callInvoker) : base(callInvoker)
      {
      }

      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      protected GreeterClient() : base()
      {
      }

      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      protected GreeterClient(ClientBaseConfiguration configuration) : base(configuration)
      {
      }

      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      public virtual global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloReply SayHello(global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloRequest request, grpc::Metadata headers = null, global::System.DateTime? deadline = null, global::System.Threading.CancellationToken cancellationToken = default(global::System.Threading.CancellationToken))
      {
        return SayHello(request, new grpc::CallOptions(headers, deadline, cancellationToken));
      }

      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      public virtual global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloReply SayHello(global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloRequest request, grpc::CallOptions options)
      {
        return CallInvoker.BlockingUnaryCall(__Method_SayHello, null, options, request);
      }

      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      public virtual grpc::AsyncUnaryCall<global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloReply> SayHelloAsync(global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloRequest request, grpc::Metadata headers = null, global::System.DateTime? deadline = null, global::System.Threading.CancellationToken cancellationToken = default(global::System.Threading.CancellationToken))
      {
        return SayHelloAsync(request, new grpc::CallOptions(headers, deadline, cancellationToken));
      }

      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      public virtual grpc::AsyncUnaryCall<global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloReply> SayHelloAsync(global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloRequest request, grpc::CallOptions options)
      {
        return CallInvoker.AsyncUnaryCall(__Method_SayHello, null, options, request);
      }
      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      public virtual grpc::AsyncServerStreamingCall<global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloReply> SayHelloStreamReply(global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloRequest request, grpc::Metadata headers = null, global::System.DateTime? deadline = null, global::System.Threading.CancellationToken cancellationToken = default(global::System.Threading.CancellationToken))
      {
        return SayHelloStreamReply(request, new grpc::CallOptions(headers, deadline, cancellationToken));
      }
      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      public virtual grpc::AsyncServerStreamingCall<global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloReply> SayHelloStreamReply(global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloRequest request, grpc::CallOptions options)
      {
        return CallInvoker.AsyncServerStreamingCall(__Method_SayHelloStreamReply, null, options, request);
      }

      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      protected override GreeterClient NewInstance(ClientBaseConfiguration configuration)
      {
        return new GreeterClient(configuration);
      }
    }

    [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
    public static grpc::ServerServiceDefinition BindService(GreeterBase serviceImpl)
    {
      return grpc::ServerServiceDefinition.CreateBuilder()
          .AddMethod(__Method_SayHello, serviceImpl.SayHello)
          .AddMethod(__Method_SayHelloStreamReply, serviceImpl.SayHelloStreamReply).Build();
    }

    /// Note: this method is part of an experimental API that can change or be removed without any prior notice.</summary>

    [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
    public static void BindService(grpc::ServiceBinderBase serviceBinder, GreeterBase serviceImpl)
    {
      serviceBinder.AddMethod(__Method_SayHello, serviceImpl == null ? null : new grpc::UnaryServerMethod<global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloRequest, global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloReply>(serviceImpl.SayHello));
      serviceBinder.AddMethod(__Method_SayHelloStreamReply, serviceImpl == null ? null : new grpc::ServerStreamingServerMethod<global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloRequest, global::Test.Csharp.Codegen.Simple.Proto.Helloworld.HelloReply>(serviceImpl.SayHelloStreamReply));
    }

  }
}
#endregion
