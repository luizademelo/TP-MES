#region Copyright notice and license

// Copyright 2018 gRPC authors.

#endregion

using Microsoft.Build.Framework;
using Microsoft.Build.Utilities;
using Moq;
using NUnit.Framework;

namespace Grpc.Tools.Tests
{
    public class GeneratorTest
    {
        protected Mock<IBuildEngine> _mockEngine;
        protected TaskLoggingHelper _log;

        [SetUp]
        public void SetUp()
        {
            _mockEngine = new Mock<IBuildEngine>();
            _log = new TaskLoggingHelper(_mockEngine.Object, "phony");
        }

        [TestCase("csharp")]
        [TestCase("CSharp")]
        [TestCase("cpp")]
        public void ValidLanguages(string lang)
        {
            Assert.IsNotNull(GeneratorServices.GetForLanguage(lang, _log));
            _mockEngine.Verify(me => me.LogErrorEvent(It.IsAny<BuildErrorEventArgs>()), Times.Never);
        }

        [TestCase("")]
        [TestCase("COBOL")]
        public void InvalidLanguages(string lang)
        {
            Assert.IsNull(GeneratorServices.GetForLanguage(lang, _log));
            _mockEngine.Verify(me => me.LogErrorEvent(It.IsAny<BuildErrorEventArgs>()), Times.Once);
        }
    };
}
