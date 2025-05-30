#region Copyright notice and license

// Copyright 2018 gRPC authors.

#endregion

using System.Collections.Generic;
using Microsoft.Build.Framework;
using Microsoft.Build.Utilities;

namespace Grpc.Tools
{
    public class ProtoCompilerOutputs : Task
    {

        [Required]
        public string Generator { get; set; }

        [Required]
        public ITaskItem[] Protobuf { get; set; }

        [Output]
        public ITaskItem[] PatchedProtobuf { get; set; }

        [Output]
        public ITaskItem[] PossibleOutputs { get; private set; }

        public override bool Execute()
        {
            var generator = GeneratorServices.GetForLanguage(Generator, Log);
            if (generator == null)
            {

                return false;
            }

            var possible = new List<ITaskItem>();
            var patched = new List<ITaskItem>();
            foreach (var proto in Protobuf)
            {
                var patchedProto = generator.PatchOutputDirectory(proto);
                patched.Add(patchedProto);

                var outputs = generator.GetPossibleOutputs(patchedProto);
                foreach (string output in outputs)
                {
                    var ti = new TaskItem(output);
                    ti.SetMetadata(Metadata.Source, patchedProto.ItemSpec);
                    possible.Add(ti);
                }
            }

            PatchedProtobuf = patched.ToArray();
            PossibleOutputs = possible.ToArray();

            return !Log.HasLoggedErrors;
        }
    };
}
