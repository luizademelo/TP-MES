#region Copyright notice and license

// Copyright 2018 gRPC authors.

#endregion

using System.Reflection;
using NUnitLite;
using System;
using System.IO;
using System.Runtime.InteropServices;

namespace Grpc.Tools.Tests
{
    static class MsBuildAssemblyHelper
    {
        [DllImport("__Internal")]
	    extern static void mono_set_assemblies_path(string path);

        public static void TweakAssemblyPathIfOnMono()
        {

#if NET45

            bool isMono = Type.GetType("Mono.Runtime") != null;
            if (isMono)
            {
               var mscorlibDir = Path.GetDirectoryName(typeof(Array).Assembly.Location);

               var msbuildToolPath = Path.Combine(mscorlibDir, "..", "msbuild", "Current", "bin");

               if (!Directory.Exists(msbuildToolPath))
               {

                   msbuildToolPath = Path.Combine(mscorlibDir, "..", "msbuild", "15.0", "bin");
               }

               foreach(var assemblyName in new [] {"Microsoft.Build.Framework.dll", "Microsoft.Build.Utilities.v4.0.dll", "Microsoft.Build.Utilities.Core.dll"})
               {
                   if (!File.Exists(Path.Combine(msbuildToolPath, assemblyName)))
                   {
                       throw new InvalidOperationException($"Could not locate assembly {assemblyName} under {msbuildToolPath}");
                   }
               }

               mono_set_assemblies_path(msbuildToolPath);
            }
#endif
        }
    }
}
