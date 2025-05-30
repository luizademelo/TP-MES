#region Copyright notice and license

// Copyright 2018 gRPC authors.

#endregion

using Microsoft.Build.Framework;
using Moq;
using NUnit.Framework;

namespace Grpc.Tools.Tests
{
    public class ProtoCompileCommandLinePrinterTest : ProtoCompileBasicTest
    {
        [SetUp]
        public new void SetUp()
        {
            _task.Generator = "csharp";
            _task.OutputDir = "outdir";
            _task.Protobuf = Utils.MakeSimpleItems("a.proto");

            _mockEngine
              .Setup(me => me.LogMessageEvent(It.IsAny<BuildMessageEventArgs>()))
              .Callback((BuildMessageEventArgs e) =>
                  Assert.Fail($"Error logged by build engine:\n{e.Message}"))
              .Verifiable("Command line was not output by the task.");
        }

        void ExecuteExpectSuccess()
        {
            _mockEngine
              .Setup(me => me.LogErrorEvent(It.IsAny<BuildErrorEventArgs>()))
              .Callback((BuildErrorEventArgs e) =>
                  Assert.Fail($"Error logged by build engine:\n{e.Message}"));
            bool result = _task.Execute();
            Assert.IsTrue(result);
        }
    };
}
