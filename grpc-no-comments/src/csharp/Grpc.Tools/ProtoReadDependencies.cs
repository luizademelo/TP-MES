#region Copyright notice and license

// Copyright 2018 gRPC authors.

#endregion

using System.Collections.Generic;
using Microsoft.Build.Framework;
using Microsoft.Build.Utilities;

namespace Grpc.Tools
{
    public class ProtoReadDependencies : Task
    {

        [Required]
        public ITaskItem[] Protobuf { get; set; }

        [Required]
        public string ProtoDepDir { get; set; }

        [Output]
        public ITaskItem[] Dependencies { get; private set; }

        public override bool Execute()
        {

            if (ProtoDepDir != null)
            {
                var dependencies = new List<ITaskItem>();
                foreach (var proto in Protobuf)
                {
                    string[] deps = DepFileUtil.ReadDependencyInputs(ProtoDepDir, proto.ItemSpec, Log);
                    foreach (string dep in deps)
                    {
                        var ti = new TaskItem(dep);
                        ti.SetMetadata(Metadata.Source, proto.ItemSpec);
                        dependencies.Add(ti);
                    }
                }
                Dependencies = dependencies.ToArray();
            }
            else
            {
                Dependencies = new ITaskItem[0];
            }

            return !Log.HasLoggedErrors;
        }
    };
}
