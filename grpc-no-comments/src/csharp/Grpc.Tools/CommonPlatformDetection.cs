#region Copyright notice and license

// Copyright 2021 The gRPC Authors

#endregion

using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Grpc.Core.Internal
{

    internal static class CommonPlatformDetection
    {
        public enum OSKind { Unknown, Windows, Linux, MacOSX };
        public enum CpuArchitecture { Unknown, X86, X64, Arm64 };

        public static OSKind GetOSKind()
        {
#if NETSTANDARD || NETCORE
            if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
            {
                return OSKind.Windows;
            }
            else if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux))
            {
                return OSKind.Linux;
            }
            else if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
            {
                return OSKind.MacOSX;
            }
            else
            {
                return OSKind.Unknown;
            }
#else
            var platform = Environment.OSVersion.Platform;
            if (platform == PlatformID.Win32NT || platform == PlatformID.Win32S || platform == PlatformID.Win32Windows)
            {
                return OSKind.Windows;
            }
            else if (platform == PlatformID.Unix && GetUname() == "Darwin")
            {

                return OSKind.MacOSX;
            }
            else if (platform == PlatformID.Unix)
            {

                return OSKind.Linux;
            }
            else
            {
                return OSKind.Unknown;
            }
#endif
        }

        public static CpuArchitecture GetProcessArchitecture()
        {
#if NETSTANDARD || NETCORE
            switch (RuntimeInformation.ProcessArchitecture)
            {
                case Architecture.X86:
                    return CpuArchitecture.X86;
                case Architecture.X64:
                    return CpuArchitecture.X64;
                case Architecture.Arm64:
                    return CpuArchitecture.Arm64;

                default:
                   return CpuArchitecture.Unknown;
            }
#else

            return Environment.Is64BitProcess ? CpuArchitecture.X64 : CpuArchitecture.X86;
#endif
        }

        [DllImport("libc")]
        static extern int uname(IntPtr buf);

        static string GetUname()
        {
            var buffer = Marshal.AllocHGlobal(8192);
            try
            {
                if (uname(buffer) == 0)
                {
                    return Marshal.PtrToStringAnsi(buffer);
                }
                return string.Empty;
            }
            catch
            {
                return string.Empty;
            }
            finally
            {
                if (buffer != IntPtr.Zero)
                {
                    Marshal.FreeHGlobal(buffer);
                }
            }
        }
    }
}
