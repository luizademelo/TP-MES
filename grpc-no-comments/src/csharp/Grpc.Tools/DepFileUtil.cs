#region Copyright notice and license

// Copyright 2018 gRPC authors.

#endregion

using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using Microsoft.Build.Framework;
using Microsoft.Build.Utilities;

namespace Grpc.Tools
{
    internal static class DepFileUtil
    {

        public static string[] ReadDependencyInputs(string protoDepDir, string proto,
                                                    TaskLoggingHelper log)
        {
            string depFilename = GetDepFilenameForProto(protoDepDir, proto);
            string[] lines = ReadDepFileLines(depFilename, false, log);
            if (lines.Length == 0)
            {
                return lines;
            }

            var result = new List<string>();
            bool skip = true;
            foreach (string line in lines)
            {

                int ix = skip ? FindLineSeparator(line) : -1;
                skip = skip && ix < 0;
                if (skip) { continue; }
                string file = ExtractFilenameFromLine(line, ix + 1, line.Length);
                if (file == "")
                {
                    log.LogMessage(MessageImportance.Low,
              $"Skipping unparsable dependency file {depFilename}.\nLine with error: '{line}'");
                    return new string[0];
                }

                if (file != proto)
                {
                    result.Add(file);
                }
            }
            return result.ToArray();
        }

        public static string[] ReadDependencyOutputs(string depFilename,
                                                    TaskLoggingHelper log)
        {
            string[] lines = ReadDepFileLines(depFilename, true, log);
            if (lines.Length == 0)
            {
                return lines;
            }

            var result = new List<string>();
            foreach (string line in lines)
            {
                int ix = FindLineSeparator(line);
                string file = ExtractFilenameFromLine(line, 0, ix >= 0 ? ix : line.Length);
                if (file == "")
                {
                    log.LogError("Unable to parse generated dependency file {0}.\n" +
                                 "Line with error: '{1}'", depFilename, line);
                    return new string[0];
                }
                result.Add(file);

                if (ix >= 0) { break; }
            }
            return result.ToArray();
        }

        public static string GetDepFilenameForProto(string protoDepDir, string proto)
        {
            string dirhash = GetDirectoryHash(proto);
            string filename = Path.GetFileNameWithoutExtension(proto);
            return Path.Combine(protoDepDir, $"{dirhash}_{filename}.protodep");
        }

        public static string GetOutputDirWithHash(string outputDir, string proto)
        {
            string dirhash = GetDirectoryHash(proto);
            return Path.Combine(outputDir, dirhash);
        }

        private static string GetDirectoryHash(string proto)
        {
            string dirname = Path.GetDirectoryName(proto);
            if (Platform.IsFsCaseInsensitive)
            {
                dirname = dirname.ToLowerInvariant();
            }

            return HashString64Hex(dirname);
        }

        internal static string HashString64Hex(string str)
        {
            using (var sha1 = System.Security.Cryptography.SHA1.Create())
            {
                byte[] hash = sha1.ComputeHash(Encoding.UTF8.GetBytes(str));
                var hashstr = new StringBuilder(16);
                for (int i = 0; i < 8; i++)
                {
                    hashstr.Append(hash[i].ToString("x2"));
                }
                return hashstr.ToString();
            }
        }

        static string ExtractFilenameFromLine(string line, int beg, int end)
        {
            while (beg < end && char.IsWhiteSpace(line[beg])) beg++;
            if (beg < end && end == line.Length && line[end - 1] == '\\') end--;
            while (beg < end && char.IsWhiteSpace(line[end - 1])) end--;
            if (beg == end) return "";

            string filename = line.Substring(beg, end - beg);
            try
            {
                // Normalize file name.
                return Path.Combine(Path.GetDirectoryName(filename), Path.GetFileName(filename));
            }
            catch (Exception ex) when (Exceptions.IsIoRelated(ex))
            {
                return "";
            }
        }

        // Finds the index of the ':' separating dependency clauses in the line,
        // not taking Windows drive spec into account. Returns the index of the
        // separating ':', or -1 if no separator found.
        static int FindLineSeparator(string line)
        {
            // Mind this case where the first ':' is not separator:
            // C:\foo\bar\.pb.h: C:/protobuf/wrappers.proto\
            int ix = line.IndexOf(':');
            if (ix <= 0 || ix == line.Length - 1
                || (line[ix + 1] != '/' && line[ix + 1] != '\\')
                || !char.IsLetter(line[ix - 1]))
            {
                return ix;  // Not a windows drive: no letter before ':', or no '\' after.
            }
            for (int j = ix - 1; --j >= 0;)
            {
                if (!char.IsWhiteSpace(line[j]))
                {
                    return ix;  // Not space or BOL only before "X:/".
                }
            }
            return line.IndexOf(':', ix + 1);
        }

        // Read entire dependency file. The 'required' parameter controls error
        // logging behavior in case the file not found. We require this file when
        // compiling, but reading it is optional when computing dependencies.
        static string[] ReadDepFileLines(string filename, bool required,
                                         TaskLoggingHelper log)
        {
            try
            {
                var result = File.ReadAllLines(filename);
                if (!required)
                {
                    log.LogMessage(MessageImportance.Low, $"Using dependency file {filename}");
                }
                return result;
            }
            catch (Exception ex) when (Exceptions.IsIoRelated(ex))
            {
                if (required)
                {
                    log.LogError($"Unable to load {filename}: {ex.GetType().Name}: {ex.Message}");
                }
                else
                {
                    log.LogMessage(MessageImportance.Low, $"Skipping {filename}: {ex.Message}");
                }
                return new string[0];
            }
        }
    };
}
