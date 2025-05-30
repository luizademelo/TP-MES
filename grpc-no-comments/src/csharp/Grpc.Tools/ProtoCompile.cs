#region Copyright notice and license

// Copyright 2018 gRPC authors.

#endregion

using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;
using Microsoft.Build.Framework;
using Microsoft.Build.Utilities;

namespace Grpc.Tools
{

    public class ProtoCompile : ToolTask
    {

        static string[] s_supportedGenerators = new[] { "cpp", "csharp", "java",
                                                        "javanano", "js", "objc",
                                                        "php", "python", "ruby" };

        static readonly TimeSpan s_regexTimeout = TimeSpan.FromSeconds(1);

        static readonly List<ErrorListFilter> s_errorListFilters = new List<ErrorListFilter>()
        {

            new ErrorListFilter
            {
                Pattern = new Regex(
                    pattern: "^(?'FILENAME'.+?)\\((?'LINE'\\d+)\\) ?: ?warning in column=(?'COLUMN'\\d+) ?: ?(?'TEXT'.*)",
                    options: RegexOptions.Compiled | RegexOptions.IgnoreCase,
                    matchTimeout: s_regexTimeout),
                LogAction = (log, match) =>
                {
                    int.TryParse(match.Groups["LINE"].Value, out var line);
                    int.TryParse(match.Groups["COLUMN"].Value, out var column);

                    log.LogWarning(
                        subcategory: null,
                        warningCode: null,
                        helpKeyword: null,
                        file: match.Groups["FILENAME"].Value,
                        lineNumber: line,
                        columnNumber: column,
                        endLineNumber: 0,
                        endColumnNumber: 0,
                        message: match.Groups["TEXT"].Value);
                }
            },

            new ErrorListFilter
            {
                Pattern = new Regex(
                    pattern: "^(?'FILENAME'.+?)\\((?'LINE'\\d+)\\) ?: ?error in column=(?'COLUMN'\\d+) ?: ?(?'TEXT'.*)",
                    options: RegexOptions.Compiled | RegexOptions.IgnoreCase,
                    matchTimeout: s_regexTimeout),
                LogAction = (log, match) =>
                {
                    int.TryParse(match.Groups["LINE"].Value, out var line);
                    int.TryParse(match.Groups["COLUMN"].Value, out var column);

                    log.LogError(
                        subcategory: null,
                        errorCode: null,
                        helpKeyword: null,
                        file: match.Groups["FILENAME"].Value,
                        lineNumber: line,
                        columnNumber: column,
                        endLineNumber: 0,
                        endColumnNumber: 0,
                        message: match.Groups["TEXT"].Value);
                }
            },

            new ErrorListFilter
            {
                Pattern = new Regex(
                    pattern: "^(?'FILENAME'.+?): ?warning: ?(?'TEXT'.*)",
                    options: RegexOptions.Compiled | RegexOptions.IgnoreCase,
                    matchTimeout: s_regexTimeout),
                LogAction = (log, match) =>
                {
                    log.LogWarning(
                        subcategory: null,
                        warningCode: null,
                        helpKeyword: null,
                        file: match.Groups["FILENAME"].Value,
                        lineNumber: 0,
                        columnNumber: 0,
                        endLineNumber: 0,
                        endColumnNumber: 0,
                        message: match.Groups["TEXT"].Value);
                }
            },

            new ErrorListFilter
            {
                Pattern = new Regex(
                    pattern: "^\\[.+? WARNING (?'FILENAME'.+?):(?'LINE'\\d+?)\\] ?(?'TEXT'.*)",
                    options: RegexOptions.Compiled | RegexOptions.IgnoreCase,
                    matchTimeout: s_regexTimeout),
                LogAction = (log, match) =>
                {

                    int.TryParse(match.Groups["LINE"].Value, out var line);
                    log.LogWarning(
                        subcategory: null,
                        warningCode: null,
                        helpKeyword: null,
                        file: match.Groups["FILENAME"].Value,
                        lineNumber: line,
                        columnNumber: 0,
                        endLineNumber: 0,
                        endColumnNumber: 0,
                        message: match.Groups["TEXT"].Value);
                }
            },

            new ErrorListFilter
            {
                Pattern = new Regex(
                    pattern: "^\\[.+? (?'LEVEL'ERROR|FATAL) (?'FILENAME'.+?):(?'LINE'\\d+?)\\] ?(?'TEXT'.*)",
                    options: RegexOptions.Compiled | RegexOptions.IgnoreCase,
                    matchTimeout: s_regexTimeout),
                LogAction = (log, match) =>
                {

                    int.TryParse(match.Groups["LINE"].Value, out var line);
                    log.LogError(
                        subcategory: null,
                        errorCode: null,
                        helpKeyword: null,
                        file: match.Groups["FILENAME"].Value,
                        lineNumber: line,
                        columnNumber: 0,
                        endLineNumber: 0,
                        endColumnNumber: 0,
                        message: match.Groups["LEVEL"].Value + " " + match.Groups["TEXT"].Value);
                }
            },

            new ErrorListFilter
            {
                Pattern = new Regex(
                    pattern: "^(?'FILENAME'.+?): ?(?'TEXT'.*)",
                    options: RegexOptions.Compiled | RegexOptions.IgnoreCase,
                    matchTimeout: s_regexTimeout),
                LogAction = (log, match) =>
                {
                    log.LogError(
                        subcategory: null,
                        errorCode: null,
                        helpKeyword: null,
                        file: match.Groups["FILENAME"].Value,
                        lineNumber: 0,
                        columnNumber: 0,
                        endLineNumber: 0,
                        endColumnNumber: 0,
                        message: match.Groups["TEXT"].Value);
                }
            }
        };

        [Required]
        public string Generator { get; set; }

        [Required]
        public ITaskItem[] Protobuf { get; set; }

        public string ProtoDepDir { get; set; }

        [Output]
        public string DependencyOut { get; set; }

        public string[] ProtoPath { get; set; }

        [Required]
        public string OutputDir { get; set; }

        public string[] OutputOptions { get; set; }

        public string[] AdditionalProtocArguments { get; set; }

        public string GrpcPluginExe { get; set; }

        public string GrpcOutputDir { get; set; }

        public string[] GrpcOutputOptions { get; set; }

        [Output]
        public ITaskItem[] AdditionalFileWrites { get; private set; }

        [Output]
        public ITaskItem[] GeneratedFiles { get; private set; }

        private new bool UseCommandProcessor { get; set; }

        protected override string ToolName => Platform.IsWindows ? "protoc.exe" : "protoc";

        protected override string GenerateFullPathToTool() => ToolExe;

        protected override MessageImportance StandardErrorLoggingImportance => MessageImportance.High;

        protected override bool ValidateParameters()
        {

            Generator = Generator.ToLowerInvariant();
            if (!System.Array.Exists(s_supportedGenerators, g => g == Generator))
            {
                Log.LogError("Invalid value for Generator='{0}'. Supported generators: {1}",
                             Generator, string.Join(", ", s_supportedGenerators));
            }

            if (ProtoDepDir != null && DependencyOut != null)
            {
                Log.LogError("Properties ProtoDepDir and DependencyOut may not be both specified");
            }

            if (Protobuf.Length > 1 && (ProtoDepDir != null || DependencyOut != null))
            {
                Log.LogError("Proto compiler currently allows only one input when " +
                             "--dependency_out is specified (via ProtoDepDir or DependencyOut). " +
                             "Tracking issue: https://github.com/protocolbuffers/protobuf/pull/3959");
            }

            if (ProtoDepDir != null)
            {
                DependencyOut = DepFileUtil.GetDepFilenameForProto(ProtoDepDir, Protobuf[0].ItemSpec);
            }

            if (GrpcPluginExe == null)
            {
                GrpcOutputOptions = null;
                GrpcOutputDir = null;
            }
            else if (GrpcOutputDir == null)
            {

                GrpcOutputDir = OutputDir;
            }

            return !Log.HasLoggedErrors && base.ValidateParameters();
        }

        static readonly Encoding s_utf8WithoutBom = new UTF8Encoding(false);
        protected override Encoding ResponseFileEncoding => s_utf8WithoutBom;

        class ProtocResponseFileBuilder
        {
            StringBuilder _data = new StringBuilder(1000);
            public override string ToString() => _data.ToString();

            public void AddSwitchMaybe(string name, string value)
            {
                if (!string.IsNullOrEmpty(value))
                {
                    _data.Append("--").Append(name).Append("=")
                         .Append(value).Append('\n');
                }
            }

            public void AddSwitchMaybe(string name, string[] values)
            {
                if (values?.Length > 0)
                {
                    _data.Append("--").Append(name).Append("=")
                         .Append(string.Join(",", values)).Append('\n');
                }
            }

            public void AddArg(string arg)
            {
                _data.Append(arg).Append('\n');
            }
        };

        protected override string GenerateResponseFileCommands()
        {
            var cmd = new ProtocResponseFileBuilder();
            cmd.AddSwitchMaybe(Generator + "_out", TrimEndSlash(OutputDir));
            cmd.AddSwitchMaybe(Generator + "_opt", OutputOptions);
            cmd.AddSwitchMaybe("plugin=protoc-gen-grpc", GrpcPluginExe);
            cmd.AddSwitchMaybe("grpc_out", TrimEndSlash(GrpcOutputDir));
            cmd.AddSwitchMaybe("grpc_opt", GrpcOutputOptions);
            if (ProtoPath != null)
            {
                foreach (string path in ProtoPath)
                {
                    cmd.AddSwitchMaybe("proto_path", TrimEndSlash(path));
                }
            }
            cmd.AddSwitchMaybe("dependency_out", DependencyOut);
            cmd.AddSwitchMaybe("error_format", "msvs");

            if (AdditionalProtocArguments != null)
            {
                foreach (var additionalProtocOption in AdditionalProtocArguments)
                {
                    cmd.AddArg(additionalProtocOption);
                }
            }

            foreach (var proto in Protobuf)
            {
                cmd.AddArg(proto.ItemSpec);
            }
            return cmd.ToString();
        }

        static string TrimEndSlash(string dir)
        {
            if (dir == null || dir.Length <= 1)
            {
                return dir;
            }
            string trim = dir.TrimEnd('/', '\\');
            // Do not trim the root slash, drive letter possible.
            if (trim.Length == 0)
            {
                // Slashes all the way down.
                return dir.Substring(0, 1);
            }
            if (trim.Length == 2 && dir.Length > 2 && trim[1] == ':')
            {
                // We have a drive letter and root, e. g. 'C:\'
                return dir.Substring(0, 3);
            }
            return trim;
        }

        // Called by the base class to log tool's command line.

        protected override void LogToolCommand(string cmd)
        {
            var printer = new StringBuilder(1024);

            var quotable = new[] { ' ', '!', '$', '&', '\'', '^' };
            void PrintQuoting(string str, int start, int count)
            {
                bool wrap = count == 0 || str.IndexOfAny(quotable, start, count) >= 0;
                if (wrap) printer.Append('"');
                printer.Append(str, start, count);
                if (wrap) printer.Append('"');
            }

            for (int ib = 0, ie; (ie = cmd.IndexOf('\n', ib)) >= 0; ib = ie + 1)
            {

                if (ib == 0)
                {
                    int iep = cmd.IndexOf(" --");
                    if (iep > 0)
                    {
                        PrintQuoting(cmd, 0, iep);
                        ib = iep + 1;
                    }
                }
                printer.Append(' ');
                if (cmd[ib] == '-')
                {

                    int iarg = cmd.IndexOf('=', ib, ie - ib);
                    if (iarg < 0)
                    {

                        printer.Append(cmd, ib, ie - ib);
                        continue;
                    }
                    printer.Append(cmd, ib, iarg + 1 - ib);
                    ib = iarg + 1;
                }

                PrintQuoting(cmd, ib, ie - ib);
            }

            base.LogToolCommand(printer.ToString());
        }

        protected override void LogEventsFromTextOutput(string singleLine, MessageImportance messageImportance)
        {
            foreach (ErrorListFilter filter in s_errorListFilters)
            {
                try
                {
                    Match match = filter.Pattern.Match(singleLine);

                    if (match.Success)
                    {
                        filter.LogAction(Log, match);
                        return;
                    }
                } catch (RegexMatchTimeoutException)
                {
                    Log.LogWarning("Unable to parse output from protoc. Regex timeout.");
                }
            }

            base.LogEventsFromTextOutput(singleLine, messageImportance);
        }

        public override bool Execute()
        {
            base.UseCommandProcessor = false;

            bool ok = base.Execute();
            if (!ok)
            {
                return false;
            }

            if (DependencyOut != null)
            {
                string[] outputs = DepFileUtil.ReadDependencyOutputs(DependencyOut, Log);
                if (HasLoggedErrors)
                {
                    return false;
                }

                GeneratedFiles = new ITaskItem[outputs.Length];
                for (int i = 0; i < outputs.Length; i++)
                {
                    GeneratedFiles[i] = new TaskItem(outputs[i]);
                }
                AdditionalFileWrites = new ITaskItem[] { new TaskItem(DependencyOut) };
            }

            return true;
        }

        class ErrorListFilter
        {
            public Regex Pattern { get; set; }
            public Action<TaskLoggingHelper, Match> LogAction { get; set; }
        }
    };
}
