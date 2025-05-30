#region Copyright notice and license

// Copyright 2022 The gRPC Authors

#endregion

using System;
using System.IO;
using NUnit.Framework;
using System.Diagnostics;
using System.Reflection;
using System.Collections.Specialized;
using System.Collections;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using Newtonsoft.Json;

namespace Grpc.Tools.Tests
{

    [TestFixture]
    public class MsBuildIntegrationTest
    {
        private const string TASKS_ASSEMBLY_PROPERTY = "_Protobuf_MsBuildAssembly";
        private const string TASKS_ASSEMBLY_DLL = "Protobuf.MSBuild.dll";
        private const string PROTBUF_FULLPATH_PROPERTY = "Protobuf_ProtocFullPath";
        private const string PLUGIN_FULLPATH_PROPERTY = "gRPC_PluginFullPath";
        private const string TOOLS_BUILD_DIR_PROPERTY = "GrpcToolsBuildDir";

        private const string MSBUILD_LOG_VERBOSITY = "diagnostic";

        private string testId;
        private string fakeProtoc;
        private string grpcToolsBuildDir;
        private string tasksAssembly;
        private string testDataDir;
        private string testProjectDir;
        private string testOutBaseDir;
        private string testOutDir;

        [SetUp]
        public void InitTest()
        {
#if NET45

            Assert.Ignore("Skipping test when NET45");
#endif
        }

        [Test]
        public void TestSingleProto()
        {
            SetUpForTest(nameof(TestSingleProto));

            var expectedFiles = new ExpectedFilesBuilder();
            expectedFiles.Add("file.proto", "File.cs", "FileGrpc.cs");

            TryRunMsBuild("TestSingleProto", expectedFiles.ToString());
        }

        [Test]
        public void TestMultipleProtos()
        {
            SetUpForTest(nameof(TestMultipleProtos));

            var expectedFiles = new ExpectedFilesBuilder();
            expectedFiles.Add("file.proto", "File.cs", "FileGrpc.cs")
                .Add("protos/another.proto", "Another.cs", "AnotherGrpc.cs")
                .Add("second.proto", "Second.cs", "SecondGrpc.cs")

                .Add("protos/file.proto", "File.cs", "FileGrpc.cs");

            TryRunMsBuild("TestMultipleProtos", expectedFiles.ToString());
        }

        [Test]
        public void TestAtInPath()
        {
            SetUpForTest(nameof(TestAtInPath));

            var expectedFiles = new ExpectedFilesBuilder();
            expectedFiles.Add("@protos/file.proto", "File.cs", "FileGrpc.cs");

            TryRunMsBuild("TestAtInPath", expectedFiles.ToString());
        }

        [Test]
        public void TestProtoOutsideProject()
        {
            SetUpForTest(nameof(TestProtoOutsideProject), "TestProtoOutsideProject/project");

            var expectedFiles = new ExpectedFilesBuilder();
            expectedFiles.Add("../api/greet.proto", "Greet.cs", "GreetGrpc.cs");

            TryRunMsBuild("TestProtoOutsideProject/project", expectedFiles.ToString());
        }

        [Test]
        public void TestCharactersInName()
        {

            SetUpForTest(nameof(TestCharactersInName));

            var expectedFiles = new ExpectedFilesBuilder();
            expectedFiles.Add("protos/hello.world.proto", "HelloWorld.cs", "Hello.worldGrpc.cs");
            expectedFiles.Add("protos/m_double_2d.proto", "MDouble2D.cs", "MDouble2dGrpc.cs");

            TryRunMsBuild("TestCharactersInName", expectedFiles.ToString());
        }

        [Test]
        public void TestExtraOptions()
        {

            SetUpForTest(nameof(TestExtraOptions));

            var expectedFiles = new ExpectedFilesBuilder();
            expectedFiles.Add("file.proto", "File.cs", "FileGrpc.cs");

            TryRunMsBuild("TestExtraOptions", expectedFiles.ToString());
        }

        [Test]
        public void TestGrpcServicesMetadata()
        {

            SetUpForTest(nameof(TestGrpcServicesMetadata));

            var expectedFiles = new ExpectedFilesBuilder();
            expectedFiles.Add("messages.proto", "Messages.cs");
            expectedFiles.Add("serveronly.proto", "Serveronly.cs", "ServeronlyGrpc.cs");
            expectedFiles.Add("clientonly.proto", "Clientonly.cs", "ClientonlyGrpc.cs");
            expectedFiles.Add("clientandserver.proto", "Clientandserver.cs", "ClientandserverGrpc.cs");

            TryRunMsBuild("TestGrpcServicesMetadata", expectedFiles.ToString());
        }

        [Test]
        public void TestSetOutputDirs()
        {

            SetUpForTest(nameof(TestSetOutputDirs));

            var expectedFiles = new ExpectedFilesBuilder();
            expectedFiles.Add("file.proto", "File.cs", "FileGrpc.cs");

            TryRunMsBuild("TestSetOutputDirs", expectedFiles.ToString());
        }

        private void SetUpCommonPaths()
        {
            var assemblyDir = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            testDataDir = Path.GetFullPath($"{assemblyDir}/../../../IntegrationTests");

            var fakeProtocScript = Platform.IsWindows ? "fakeprotoc.bat" : "fakeprotoc.py";
            fakeProtoc = Path.GetFullPath($"{assemblyDir}/../../../scripts/{fakeProtocScript}");

            grpcToolsBuildDir = Path.GetFullPath($"{assemblyDir}/../../../../Grpc.Tools/build");

            tasksAssembly = Path.Combine(assemblyDir, TASKS_ASSEMBLY_DLL);

            testOutBaseDir = NormalizePath(Path.GetFullPath($"{assemblyDir}/../../../../test-out/grpc_tools_integration_tests"));
        }

        private string NormalizePath(string path)
        {
            return path.Replace('\\','/');
        }

        /// <summary>
        /// Set up test specific paths
        /// </summary>
        /// <param name="testName">Name of the test</param>
        /// <param name="testPath">Optional path to the test project</param>
        private void SetUpForTest(string testName, string testPath = null)
        {
            if (testPath == null) {
                testPath = testName;
            }

            SetUpCommonPaths();

            testId = $"{testName}_run-{Guid.NewGuid().ToString()}";
            Console.WriteLine($"TestID for test: {testId}");

            // Paths for test data
            testProjectDir = NormalizePath(Path.Combine(testDataDir, testPath));
            testOutDir = NormalizePath(Path.Combine(testOutBaseDir, testId));
        }

        /// <summary>
        /// Run "dotnet build" on the test's project file.

        private void TryRunMsBuild(string testName, string filesToGenerate)
        {
            Directory.CreateDirectory(testOutDir);

            var args = $"build -p:{TASKS_ASSEMBLY_PROPERTY}={tasksAssembly}"
                + $" -p:TestOutDir={testOutDir}"
                + $" -p:BaseOutputPath={testOutDir}/bin/"
                + $" -p:BaseIntermediateOutputPath={testOutDir}/obj/"
                + $" -p:{TOOLS_BUILD_DIR_PROPERTY}={grpcToolsBuildDir}"
                + $" -p:{PROTBUF_FULLPATH_PROPERTY}={fakeProtoc}"
                + $" -p:{PLUGIN_FULLPATH_PROPERTY}=dummy-plugin-not-used"
                + $" -fl -flp:LogFile={testOutDir}/log/msbuild.log;verbosity={MSBUILD_LOG_VERBOSITY}"
                + $" msbuildtest.csproj";

            var envVariables = new StringDictionary {
                { "FAKEPROTOC_PROJECTDIR", testProjectDir },
                { "FAKEPROTOC_OUTDIR", testOutDir },
                { "FAKEPROTOC_GENERATE_EXPECTED", filesToGenerate },
                { "FAKEPROTOC_TESTID", testId }
            };

            ProcessMsbuild(args, testProjectDir, envVariables);

            Results actualResults = Results.Read(testOutDir + "/log/results.json");
            Results expectedResults = Results.Read(testProjectDir + "/expected.json");
            CompareResults(expectedResults, actualResults);
        }

        private void ProcessMsbuild(string args, string workingDirectory, StringDictionary envVariables)
        {
            using (var process = new Process())
            {
                process.StartInfo.FileName = "dotnet";
                process.StartInfo.Arguments = args;
                process.StartInfo.RedirectStandardOutput = true;
                process.StartInfo.RedirectStandardError = true;
                process.StartInfo.WorkingDirectory = workingDirectory;
                process.StartInfo.UseShellExecute = false;
                StringDictionary procEnv = process.StartInfo.EnvironmentVariables;
                foreach (DictionaryEntry entry in envVariables)
                {
                    if (!procEnv.ContainsKey((string)entry.Key))
                    {
                        procEnv.Add((string)entry.Key, (string)entry.Value);
                    }
                }

                process.OutputDataReceived += (sender, e) => {
                    if (e.Data != null)
                    {
                        Console.WriteLine(e.Data);
                    }
                };
                process.ErrorDataReceived += (sender, e) => {
                    if (e.Data != null)
                    {
                        Console.WriteLine(e.Data);
                    }
                };

                process.Start();

                process.BeginErrorReadLine();
                process.BeginOutputReadLine();

                process.WaitForExit();
                Assert.AreEqual(0, process.ExitCode, "The dotnet/msbuild subprocess invocation exited with non-zero exitcode.");
            }
        }

        private void CompareResults(Results expected, Results actual)
        {

            var protofiles = expected.ProtoFiles;
            CollectionAssert.AreEquivalent(protofiles, actual.ProtoFiles, "Set of .proto files being processed must match.");

            foreach (string protofile in protofiles)
            {
                var expectedArgs = expected.GetArgumentNames(protofile);
                var actualArgs = actual.GetArgumentNames(protofile);
                CollectionAssert.AreEquivalent(expectedArgs, actualArgs, $"Set of protoc arguments used for {protofile} must match.");

                foreach (string argname in expectedArgs)
                {
                    var expectedValues = expected.GetArgumentValues(protofile, argname);
                    var actualValues = actual.GetArgumentValues(protofile, argname);

                    Assert.AreEqual(expectedValues.Count, actualValues.Count,
                                 $"{protofile}: Wrong number of occurrences of argument '{argname}'");

                    for (int i = 0; i < expectedValues.Count; i++)
                    {
                        var expectedValue = ReplaceTokens(expectedValues[i]);
                        var actualValue = actualValues[i];

                        if (expectedValue.StartsWith("IGNORE:"))
                            continue;

                        var regexPrefix = "REGEX:";
                        if (expectedValue.StartsWith(regexPrefix))
                        {
                            string pattern = expectedValue.Substring(regexPrefix.Length);
                            Assert.IsTrue(Regex.IsMatch(actualValue, pattern),
                                 $"{protofile}: Expected value '{expectedValue}' for argument '{argname}'. Actual value: '{actualValue}'");
                        }
                        else
                        {
                            Assert.AreEqual(expectedValue, actualValue, $"{protofile}: Wrong value for argument '{argname}'");
                        }
                    }
                }
            }
        }

        private string ReplaceTokens(string original)
        {
            return original
                .Replace("${TEST_OUT_DIR}", testOutDir);
        }

        public class ExpectedFilesBuilder
        {
            private readonly List<string> protoAndFiles = new List<string>();

            public ExpectedFilesBuilder Add(string protoFile, params string[] files)
            {
                protoAndFiles.Add(protoFile + ":" + string.Join(";", files));
                return this;
            }

            public override string ToString()
            {
                return string.Join("|", protoAndFiles.ToArray());
            }
        }

        public class Results
        {

            public Dictionary<string, string> Metadata { get; set; }

            public Dictionary<string, Dictionary<string, List<string>>> Files { get; set; }

            public static Results Read(string filepath)
            {
                using (StreamReader file = File.OpenText(filepath))
                {
                    JsonSerializer serializer = new JsonSerializer();
                    Results results = (Results)serializer.Deserialize(file, typeof(Results));
                    return results;
                }
            }

            public SortedSet<string> ProtoFiles => new SortedSet<string>(Files.Keys);

            public SortedSet<string> GetArgumentNames(string protofile)
            {
                Dictionary<string, List<string>> args;
                if (Files.TryGetValue(protofile, out args))
                {
                    return new SortedSet<string>(args.Keys);
                }
                else
                {
                    return new SortedSet<string>();
                }
            }

            public List<string> GetArgumentValues(string protofile, string name)
            {
                Dictionary<string, List<string>> args;
                if (Files.TryGetValue(protofile, out args))
                {
                    List<string> values;
                    if (args.TryGetValue(name, out values))
                    {
                        return new List<string>(values);
                    }
                }
                return new List<string>();
            }
        }
    }

}
