#region Copyright notice and license

// Copyright 2018 gRPC authors.

#endregion

using System.Linq;
using Microsoft.Build.Framework;
using Microsoft.Build.Utilities;

namespace Grpc.Tools.Tests
{
    static class Utils
    {

        public static ITaskItem MakeItem(params string[] args)
        {
            var item = new TaskItem(args[0]);
            for (int i = 1; i < args.Length; i += 2)
            {
                item.SetMetadata(args[i], args[i + 1]);
            }
            return item;
        }

        public static ITaskItem[] MakeSimpleItems(params string[] specs)
        {
            return specs.Select(s => new TaskItem(s)).ToArray();
        }
    };
}
