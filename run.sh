#!/bin/bash

APPLICATION_NAME=daemon
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

function cleanSystem() {
    systemctl stop $APPLICATION_NAME
    sudo rm -rfv /usr/bin/$APPLICATION_NAME
    sudo rm -rfv /usr/lib/systemd/system/$APPLICATION_NAME.service
    sudo rm -rfv /var/log/$APPLICATION_NAME
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
    $CMAKE --build $PWD/build --config Debug --target install

    ./build/bin/${APPLICATION_NAME}Tests
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

-cP | --cleanProject)
    echo "clean the project"
    cleanProject
    ;;

-cS | --cleanSystem)
    echo "clean the project"
    cleanSystem
    ;;

-bD | --buildDaemon)
    echo "build daemon"
    buildDaemon
    ;;

-tD | --testDaemon)
    echo "test daemon"
    testDaemon
    ;;

-r | --run)
    echo "run daemon"
    run
    ;;

-s | --start)
    echo "start daemon"
    echo "copy file: $APPLICATION_NAME to /usr/bin/ "
    sudo cp $PWD/build/bin/$APPLICATION_NAME /usr/bin/

    echo "copy file: $APPLICATION_NAME.service to /usr/lib/systemd/system"
    sudo cp $PWD/$APPLICATION_NAME/$APPLICATION_NAME.service /usr/lib/systemd/system

    echo "copy file: $APPLICATION_NAME.config to /etc/$APPLICATION_NAME"
    sudo cp $PWD/$APPLICATION_NAME/$APPLICATION_NAME.service /usr/lib/systemd/system

    systemctl start $APPLICATION_NAME
    sleep 3
    systemctl status $APPLICATION_NAME
    sleep 3
    systemctl reload $APPLICATION_NAME
    sleep 3
    systemctl stop $APPLICATION_NAME
    ;;

-h | --help | *)
    echo "help page: "
    helpPage
    ;;
esac
