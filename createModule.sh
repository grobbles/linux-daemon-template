#!/bin/bash

############################################################################################################
## Constant Block

############################################################################################################
## Description Function Block
function usage() {
    cat <<EOF

Usage: $0 <arguments>

Arguments:
    -h | --help         : print the help description

    -b | --build        : build the python package

    -i | --install      : install the package to your system

    -u | --uninstall    : uninstall the package from your system

    -c | --cleanProject : clean the project

    -d | --docker       : docker stuff
              -> parmeter: path to mount in the work directory

EOF
}

function createModuleDirectory() {
    moduleName=$1

    if [ ! -d $moduleName ]; then
        echo "Directory $moduleName DOES NOT exists."
        mkdir $moduleName
    else
        echo "Directory $moduleName exists."
    fi
}

function createModuleHeaderFile() {
    moduleName=$1
    cat >${moduleName}/${moduleName}.hpp <<EOF
#pragma once

#include <set>
#include <string>

#include "../Logging/Logger.hpp"

using namespace std;

class ${moduleName} {
  private:
    const string logtag = "${moduleName}";

  public:
    ${moduleName}();
    ~${moduleName}();
};
EOF
}

function createModuleSourceFile() {
    moduleName=$1
    cat >${moduleName}/${moduleName}.cpp <<EOF

#include "${moduleName}.hpp"

${moduleName}::${moduleName}() {
}

${moduleName}::~${moduleName}() {
}
EOF
}

############################################################################################################
## Start Function Block
function build() {
    moduleName=$1

    createModuleDirectory $moduleName
    createModuleHeaderFile $moduleName
    createModuleSourceFile $moduleName
}

############################################################################################################
## Start Main Block
case "$1" in
-b | --build)
    echo "build the python package"
    build ${@:2}
    exit $?
    ;;

-h | --help)
    echo "Help Page for : $IMAGE_NAME"
    usage
    exit $?
    ;;

*)
    usage
    exit $?
    ;;
esac
## End Main Block
############################################################################################################
