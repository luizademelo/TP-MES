#region Copyright notice and license

// Copyright 2015 gRPC authors.

#endregion

using System;
using System.Linq;
using System.Threading.Tasks;
using Grpc.Core;
using GrpcCsharpDistribtest.Helloworld;

namespace TestGrpcPackage
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            CheckGreeterProtobufCodegenWorks();
            CheckGreeterGrpcProtobufPluginCodegenWorks();
            CheckDuplicateProtoFilesAreOk();
        }

        private static object CheckGreeterProtobufCodegenWorks()
        {
            return new HelloRequest { Name = "ABC" };
        }

        private static object CheckGreeterGrpcProtobufPluginCodegenWorks()
        {
            return typeof(GreeterImpl);
        }

        private static object CheckDuplicateProtoFilesAreOk()
        {
            return new GrpcCsharpDistribtest.DuplicateProto.MessageFromDuplicateProto();
        }
    }

    class GreeterImpl : Greeter.GreeterBase
    {

        public override Task<HelloReply> SayHello(HelloRequest request, ServerCallContext context)
        {
            return Task.FromResult(new HelloReply { Message = "Hello " + request.Name });
        }
    }
}
