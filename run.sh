#!/bin/bash

APPLICATION_NAME=DaemonTemplate
CMAKE=/usr/bin/cmake

########################################################################################################
### Functions
function helpPage() {
    cat <<EOF

    -i, --initialize:           initialize the project and initialize the git submodules (gtest)

    -b, --build:               build the executables

    -c, --cleanProject:        clean the project

    -s, --startLoggingServer:  execute the logging server

    -t, --testLoggingServer:   execute the logging server unit tests
    
    -h, --help:                 print the help page

EOF
}

function projectInitialize() {
    git submodule init && git submodule update
    cmake . -B build
}

function cleanProject() {
    rm -rfv bin/
    rm -rfv build/
    rm -rfv $APPLICATION_NAME/include/*
    rm -rfv $APPLICATION_NAME/lib/*
}

function buildAll() {
    $CMAKE . -B build
    $CMAKE --build $PWD/build --config Debug --target all -- -j 14
    $CMAKE --build $PWD/build --config Debug --target install

}

function buildDaemon() {
    $CMAKE --build $PWD/build --config Debug --target $APPLICATION_NAME -- -j 14
    $CMAKE --build $PWD/build --config Debug --target install

}

function testDaemon() {
    $CMAKE --build $PWD/build --config Debug --target $APPLICATION_NAME -- -j 14
}

function run() {
    ./build/bin/$APPLICATION_NAME
}

########################################################################################################
### Main
case "$1" in
-i | --initialize)
    echo "projekt initialize"
    projectInitialize
    ;;

-b | --build)
    echo "projekt build"
    buildAll
    ;;

-c | --cleanProject)
    echo "clean the project"
    cleanProject
    ;;

-bD | --buildDaemon)
    echo "build daemon"
    buildDaemon
    ;;

-sD | --startLoggingServer)
    echo "start daemon"
    startLoggingServer
    ;;

-tD | --testDaemon)
    echo "test daemon"
    testDaemon
    ;;

-r | --run)
    echo "run daemon"
    run
    ;;

-h | --help | *)
    echo "help page: "
    helpPage
    ;;
esac
