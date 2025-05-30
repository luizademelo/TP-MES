#region Copyright notice and license

// Copyright 2018 gRPC authors.

#endregion

using System.Reflection;
using NUnitLite;

namespace Grpc.Tools.Tests
{
    static class NUnitMain
    {
        public static int Main(string[] args)
        {
            MsBuildAssemblyHelper.TweakAssemblyPathIfOnMono();
            return new AutoRun(typeof(NUnitMain).GetTypeInfo().Assembly).Execute(args);
        }
    }
}
