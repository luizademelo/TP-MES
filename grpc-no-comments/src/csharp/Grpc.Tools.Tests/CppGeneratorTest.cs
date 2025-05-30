#region Copyright notice and license

// Copyright 2018 gRPC authors.

#endregion

using System.IO;
using NUnit.Framework;

namespace Grpc.Tools.Tests
{
    public class CppGeneratorTest : GeneratorTest
    {
        GeneratorServices _generator;

        [SetUp]
        public new void SetUp()
        {
            _generator = GeneratorServices.GetForLanguage("Cpp", _log);
        }

        [TestCase("foo.proto", "", "foo")]
        [TestCase("foo.proto", ".", "foo")]
        [TestCase("foo.proto", "./", "foo")]
        [TestCase("sub/foo.proto", "", "sub/foo")]
        [TestCase("root/sub/foo.proto", "root", "sub/foo")]
        [TestCase("root/sub/foo.proto", "root", "sub/foo")]
        [TestCase("/root/sub/foo.proto", "/root", "sub/foo")]
        public void RelativeDirectoryCompute(string proto, string root, string expectStem)
        {
            if (Path.DirectorySeparatorChar == '\\')
                expectStem = expectStem.Replace('/', '\\');
            var poss = _generator.GetPossibleOutputs(Utils.MakeItem(proto, "ProtoRoot", root));
            Assert.AreEqual(2, poss.Length);
            Assert.Contains(expectStem + ".pb.cc", poss);
            Assert.Contains(expectStem + ".pb.h", poss);
        }

        [Test]
        public void NoGrpcTwoOutputs()
        {
            var poss = _generator.GetPossibleOutputs(Utils.MakeItem("foo.proto"));
            Assert.AreEqual(2, poss.Length);
        }

        [TestCase("false")]
        [TestCase("")]
        public void GrpcDisabledTwoOutput(string grpc)
        {
            var item = Utils.MakeItem("foo.proto", "grpcservices", grpc);
            var poss = _generator.GetPossibleOutputs(item);
            Assert.AreEqual(2, poss.Length);
        }

        [TestCase("true")]
        public void GrpcEnabledFourOutputs(string grpc)
        {
            var item = Utils.MakeItem("foo.proto", "grpcservices", grpc);
            var poss = _generator.GetPossibleOutputs(item);
            Assert.AreEqual(4, poss.Length);
            Assert.Contains("foo.pb.cc", poss);
            Assert.Contains("foo.pb.h", poss);
            Assert.Contains("foo.grpc.pb.cc", poss);
            Assert.Contains("foo.grpc.pb.h", poss);
        }

        [Test]
        public void OutputDirMetadataRecognized()
        {
            var item = Utils.MakeItem("foo.proto", "OutputDir", "out");
            var poss = _generator.GetPossibleOutputs(item);
            Assert.AreEqual(2, poss.Length);
            Assert.That(Path.GetDirectoryName(poss[0]), Is.EqualTo("out"));
        }
    };
}
