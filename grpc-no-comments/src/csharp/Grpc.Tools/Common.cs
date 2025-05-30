#region Copyright notice and license

// Copyright 2018 gRPC authors.

#endregion

using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Security;
using Grpc.Core.Internal;

namespace Grpc.Tools
{

    static class Metadata
    {

        public static string Source = "Source";

        public static string ProtoRoot = "ProtoRoot";
        public static string OutputDir = "OutputDir";
        public static string GrpcServices = "GrpcServices";
        public static string GrpcOutputDir = "GrpcOutputDir";
    };

    internal static class Platform
    {
        public static readonly CommonPlatformDetection.OSKind Os = CommonPlatformDetection.GetOSKind();

        public static readonly CommonPlatformDetection.CpuArchitecture Cpu = CommonPlatformDetection.GetProcessArchitecture();

        public static bool IsFsCaseInsensitive => Os == CommonPlatformDetection.OSKind.Windows;
        public static bool IsWindows => Os == CommonPlatformDetection.OSKind.Windows;
    };

    static class Exceptions
    {

        static public bool IsIoRelated(Exception ex) =>
            ex is IOException ||
            (ex is ArgumentException && !(ex is ArgumentNullException)) ||
            ex is SecurityException ||
            ex is UnauthorizedAccessException ||
            ex is NotSupportedException;
    };

    static class Strings
    {

        public static bool EqualNoCase(this string a, string b) =>
            string.Equals(a, b, StringComparison.OrdinalIgnoreCase);
    }
}
