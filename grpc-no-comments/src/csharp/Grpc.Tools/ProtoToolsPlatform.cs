#region Copyright notice and license

// Copyright 2018 gRPC authors.

#endregion

using Microsoft.Build.Framework;
using Microsoft.Build.Utilities;
using Grpc.Core.Internal;

namespace Grpc.Tools
{

    public class ProtoToolsPlatform : Task
    {

        [Output]
        public string Os { get; set; }

        [Output]
        public string Cpu { get; set; }

        public override bool Execute()
        {
            switch (Platform.Os)
            {
                case CommonPlatformDetection.OSKind.Linux: Os = "linux"; break;
                case CommonPlatformDetection.OSKind.MacOSX: Os = "macosx"; break;
                case CommonPlatformDetection.OSKind.Windows: Os = "windows"; break;
                default: Os = ""; break;
            }

            switch (Platform.Cpu)
            {
                case CommonPlatformDetection.CpuArchitecture.X86: Cpu = "x86"; break;
                case CommonPlatformDetection.CpuArchitecture.X64: Cpu = "x64"; break;
                case CommonPlatformDetection.CpuArchitecture.Arm64: Cpu = "arm64"; break;
                default: Cpu = ""; break;
            }

            if (Os == "macosx" && Cpu == "arm64")
            {
                Cpu = "x64";
            }

            else if (Os == "windows" && Cpu == "arm64")
            {
                Cpu = "x86";
            }

            return true;
        }
    };
}
