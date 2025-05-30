# Copyright 2020 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

function sed_gensub(regexp, replacement, how, target,         cmd_, ret_) {
    if (!target) {
        target = $0
    }
    gsub(/'/, "'\"'\"'", target);
    gsub(/\\\\/, "\\", regexp);

    cmd_ = "printf '" target "' | sed -nE 's/" regexp "/" replacement "/" tolower(how) "p'";
    if (cmd_ | getline ret_ != 1) {
        close(cmd_);
        error = "ERROR: running command: " cmd_ ", ret_: " ret_;
        exit;
    }
    close(cmd_);
    return ret_;
}

BEGIN {
    namespace = "Grpc";
    className = "";
    classDocComment = "";

    delete methodNames;
    delete methodArgs;
    delete methodDocs;
    delete methodStatics;
    methodsCount = 0;

    delete constantNames;
    delete constantDocs;
    constantsCount = 0;

    classLineRegex = "^ \\* class ([^ \t]+)$";

    paramLineRegex = "^.*@param[ \t]+[^ \t]+[ \t]+(\\$[^ \t]+([ \t]+=[ \t]+[^ \t]+)?)[ \t]+.*$";

    phpMethodLineRegex = "^PHP_METHOD\\(([^ \t]+),[ \t]*([^ \t]+)\\).*$";

    phpMeLineRegex = "^[ \t]*PHP_ME\\(([^ \t]+),[ \t]*([^ \t]+),.*$";

    phpConstantLineRegs = "^[ \t]*REGISTER_LONG_CONSTANT\\(\"Grpc\\\\\\\\([^ \t]+)\",.*$";

    error = "";

    hideMethods["Channel::getChannelInfo"] = 1;
    hideMethods["Channel::cleanPersistentList"] = 1;
    hideMethods["Channel::getPersistentList"] = 1;
}

/^[ \t]*\/\*\*/ {
    inDocComment = 1;
    docComment = "";
    delete args;
    argsCount = 0;
}

inDocComment==1 {
    docComment = docComment"\n"$0
}

inDocComment==1 && $0 ~ classLineRegex {
    className = sed_gensub(classLineRegex, "\\1", "g");
}

inDocComment==1 && /\*\// && className && classDocComment == "" {
    classDocComment = docComment;
    docComment = "";
}

inDocComment==1 && $0 ~ paramLineRegex {
    arg = sed_gensub(paramLineRegex, "\\1", "g");
    args[argsCount++]=arg;
}

inDocComment==1 && /\*\// {
    inDocComment = 0;
}

$0 ~ phpMethodLineRegex {
    class = sed_gensub(phpMethodLineRegex, "\\1", "g");
    if (class != className) {
        error = "ERROR: Missing or mismatch class names, in class comment block: " \
          className ", in PHP_METHOD: " class;
        exit;
    };

    method = sed_gensub(phpMethodLineRegex, "\\2", "g");
    methodNames[methodsCount++] = method;
    methodDocs[method] = docComment;

    if (argsCount > 0) {
        methodArgs[method] = args[0];
        for (i = 1; i < argsCount; i++) {
            methodArgs[method] = methodArgs[method] ", " args[i];
        }
    }

    docComment = "";
}

$0 ~ phpMeLineRegex {
    inPhpMe = 1;

    class = sed_gensub(phpMeLineRegex, "\\1", "g");
    if (class != className) {
        error = "ERROR: Missing or mismatch class names, in class comment block: " \
          className ", in PHP_ME: " class;
        exit;
    };
    method = sed_gensub(phpMeLineRegex, "\\2", "g");
}

inPhpMe && /ZEND_ACC_STATIC/ {
    methodStatics[method] = 1;
}

iinPhpMe && /\)$/ {
    inPhpMe = 0;
}

$0 ~ phpConstantLineRegs {
    inPhpConstant = 1;
    constant = sed_gensub(phpConstantLineRegs, "\\1", "g");
    constantNames[constantsCount++] = constant;
    constantDocs[constant] = docComment;
}

inPhpConstant && /\)[ \t]*;[ \t]*$/ {
    inPhpConstant = 0;
    docComment = "";
}

END {
    if (error) {
        print error > "/dev/stderr";
        exit 1;
    }

    print "<?php\n"
    print "namespace " namespace "{";

    if (className != "") {
        print classDocComment
        print "class " className " {";
        for (i = 0; i < methodsCount; i++) {
            m = methodNames[i];
            if (hideMethods[className"::"m]) continue;

            print methodDocs[m];
            printf "public"
            if (methodStatics[m]) printf " static"
            printf " function " m "("
            printf methodArgs[m];
            print ") {}";
        }
        print "\n}";
    }

    for (i = 0; i < constantsCount; i++) {
        print constantDocs[constantNames[i]];
        print "const " constantNames[i] " = 0;";
    }

    print "\n}";
}
