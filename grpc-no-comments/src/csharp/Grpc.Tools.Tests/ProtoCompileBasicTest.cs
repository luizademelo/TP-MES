#region Copyright notice and license

// Copyright 2018 gRPC authors.

#endregion

using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using Microsoft.Build.Framework;
using Moq;
using NUnit.Framework;

namespace Grpc.Tools.Tests
{
    public class ProtoCompileBasicTest
    {

        public class ProtoCompileTestable : ProtoCompile
        {
            public string LastPathToTool { get; private set; }
            public string[] LastResponseFile { get; private set; }
            public List<string> StdErrMessages { get; } = new List<string>();

            protected override int ExecuteTool(string pathToTool,
                                               string response,
                                               string commandLine)
            {

                Assert.That(commandLine, Is.Null | Is.Empty);

                Assert.That(pathToTool, Is.Not.Null & Is.Not.Empty);
                Assert.That(response, Is.Not.Null & Does.EndWith("\n"));

                LastPathToTool = pathToTool;
                LastResponseFile = response.Remove(response.Length - 1).Split('\n');

                foreach (string message in StdErrMessages)
                {
                    LogEventsFromTextOutput(message, MessageImportance.High);
                }

                return StdErrMessages.Any() ? -1 : 0;
            }
        };

        protected Mock<IBuildEngine> _mockEngine;
        protected ProtoCompileTestable _task;

        [SetUp]
        public void SetUp()
        {
            _mockEngine = new Mock<IBuildEngine>();
            _task = new ProtoCompileTestable {
                BuildEngine = _mockEngine.Object
            };
        }

        [TestCase("Protobuf")]
        [TestCase("Generator")]
        [TestCase("OutputDir")]
        [Description("We trust MSBuild to initialize these properties.")]
        public void RequiredAttributePresentOnProperty(string prop)
        {
            var pinfo = _task.GetType()?.GetProperty(prop);
            Assert.NotNull(pinfo);
            Assert.That(pinfo, Has.Attribute<RequiredAttribute>());
        }
    };
}
