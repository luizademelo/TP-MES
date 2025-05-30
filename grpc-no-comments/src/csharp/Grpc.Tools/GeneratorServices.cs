#region Copyright notice and license

// Copyright 2018 gRPC authors.

#endregion

using System.IO;
using System.Text;
using Microsoft.Build.Framework;
using Microsoft.Build.Utilities;

namespace Grpc.Tools
{

    internal abstract class GeneratorServices
    {
        protected readonly TaskLoggingHelper Log;
        protected GeneratorServices(TaskLoggingHelper log) { Log = log; }

        public static GeneratorServices GetForLanguage(string lang, TaskLoggingHelper log)
        {
            if (lang.EqualNoCase("csharp")) { return new CSharpGeneratorServices(log); }
            if (lang.EqualNoCase("cpp")) { return new CppGeneratorServices(log); }

            log.LogError("Invalid value '{0}' for task property 'Generator'. " +
                "Supported generator languages: CSharp, Cpp.", lang);
            return null;
        }

        protected bool GrpcOutputPossible(ITaskItem proto)
        {
            string gsm = proto.GetMetadata(Metadata.GrpcServices);
            return !gsm.EqualNoCase("") && !gsm.EqualNoCase("none")
                && !gsm.EqualNoCase("false");
        }

        public virtual ITaskItem PatchOutputDirectory(ITaskItem protoItem)
        {

            return protoItem;
        }

        public abstract string[] GetPossibleOutputs(ITaskItem protoItem);

        protected static string GetRelativeDir(string root, string proto, TaskLoggingHelper log)
        {
            string protoDir = Path.GetDirectoryName(proto);
            string rootDir = EndWithSlash(Path.GetDirectoryName(EndWithSlash(root)));
            if (rootDir == s_dotSlash)
            {

                return protoDir;
            }
            if (Platform.IsFsCaseInsensitive)
            {
                protoDir = protoDir.ToLowerInvariant();
                rootDir = rootDir.ToLowerInvariant();
            }
            protoDir = EndWithSlash(protoDir);
            if (!protoDir.StartsWith(rootDir))
            {
                log.LogWarning("Protobuf item '{0}' has the ProtoRoot metadata '{1}' " +
                               "which is not prefix to its path. Cannot compute relative path.",
                    proto, root);
                return "";
            }
            return protoDir.Substring(rootDir.Length);
        }

        protected static string s_dotSlash = "." + Path.DirectorySeparatorChar;

        protected static string EndWithSlash(string str)
        {
            if (str == "")
            {
                return s_dotSlash;
            }

            if (str[str.Length - 1] != '\\' && str[str.Length - 1] != '/')
            {
                return str + Path.DirectorySeparatorChar;
            }

            return str;
        }
    };

    // C# generator services.
    internal class CSharpGeneratorServices : GeneratorServices
    {
        public CSharpGeneratorServices(TaskLoggingHelper log) : base(log) { }

        public override ITaskItem PatchOutputDirectory(ITaskItem protoItem)
        {
            var outputItem = new TaskItem(protoItem);
            string root = outputItem.GetMetadata(Metadata.ProtoRoot);
            string proto = outputItem.ItemSpec;
            string relative = GetRelativeDir(root, proto, Log);

            string outdir = outputItem.GetMetadata(Metadata.OutputDir);
            string pathStem = Path.Combine(outdir, relative);
            outputItem.SetMetadata(Metadata.OutputDir, pathStem);

            // Override outdir if GrpcOutputDir present, default to proto output.
            string grpcdir = outputItem.GetMetadata(Metadata.GrpcOutputDir);
            if (grpcdir != "")
            {
                pathStem = Path.Combine(grpcdir, relative);
            }
            outputItem.SetMetadata(Metadata.GrpcOutputDir, pathStem);
            return outputItem;
        }

        public override string[] GetPossibleOutputs(ITaskItem protoItem)
        {
            bool doGrpc = GrpcOutputPossible(protoItem);
            var outputs = new string[doGrpc ? 2 : 1];
            string proto = protoItem.ItemSpec;
            string basename = Path.GetFileNameWithoutExtension(proto);
            string outdir = protoItem.GetMetadata(Metadata.OutputDir);
            string filename = LowerUnderscoreToUpperCamelProtocWay(basename);
            outputs[0] = Path.Combine(outdir, filename) + ".cs";

            if (doGrpc)
            {
                string grpcdir = protoItem.GetMetadata(Metadata.GrpcOutputDir);
                filename = LowerUnderscoreToUpperCamelGrpcWay(basename);
                outputs[1] = Path.Combine(grpcdir, filename) + "Grpc.cs";
            }
            return outputs;
        }

        // This is how the gRPC codegen currently construct its output filename.
        // See src/compiler/generator_helpers.h:118.
        string LowerUnderscoreToUpperCamelGrpcWay(string str)
        {
            var result = new StringBuilder(str.Length, str.Length);
            bool cap = true;
            foreach (char c in str)
            {
                if (c == '_')
                {
                    cap = true;
                }
                else if (cap)
                {
                    result.Append(char.ToUpperInvariant(c));
                    cap = false;
                }
                else
                {
                    result.Append(c);
                }
            }
            return result.ToString();
        }

        // This is how the protoc codegen constructs its output filename.
        // See protobuf/compiler/csharp/csharp_helpers.cc:137.
        // Note that protoc explicitly discards non-ASCII letters.
        string LowerUnderscoreToUpperCamelProtocWay(string str)
        {
            var result = new StringBuilder(str.Length, str.Length);
            bool cap = true;
            foreach (char c in str)
            {
                char upperC = char.ToUpperInvariant(c);
                bool isAsciiLetter = 'A' <= upperC && upperC <= 'Z';
                if (isAsciiLetter || ('0' <= c && c <= '9'))
                {
                    result.Append(cap ? upperC : c);
                }
                cap = !isAsciiLetter;
            }
            return result.ToString();
        }
    };

    // C++ generator services.
    internal class CppGeneratorServices : GeneratorServices
    {
        public CppGeneratorServices(TaskLoggingHelper log) : base(log) { }

        public override string[] GetPossibleOutputs(ITaskItem protoItem)
        {
            bool doGrpc = GrpcOutputPossible(protoItem);
            string root = protoItem.GetMetadata(Metadata.ProtoRoot);
            string proto = protoItem.ItemSpec;
            string filename = Path.GetFileNameWithoutExtension(proto);
            // E. g., ("foo/", "foo/bar/x.proto") => "bar"
            string relative = GetRelativeDir(root, proto, Log);

            var outputs = new string[doGrpc ? 4 : 2];
            string outdir = protoItem.GetMetadata(Metadata.OutputDir);
            string fileStem = Path.Combine(outdir, relative, filename);
            outputs[0] = fileStem + ".pb.cc";
            outputs[1] = fileStem + ".pb.h";
            if (doGrpc)
            {
                // Override outdir if GrpcOutputDir present, default to proto output.
                outdir = protoItem.GetMetadata(Metadata.GrpcOutputDir);
                if (outdir != "")
                {
                    fileStem = Path.Combine(outdir, relative, filename);
                }
                outputs[2] = fileStem + ".grpc.pb.cc";
                outputs[3] = fileStem + ".grpc.pb.h";
            }
            return outputs;
        }
    }
}
