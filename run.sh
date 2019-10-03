#!/bin/bash

APPLICATION_NAME=daemon
CMAKE=/usr/bin/cmake

########################################################################################################
### Functions
function helpPage() {
    cat <<EOF

    -i, --initialize:           initialize the project and initialize the git submodules (gtest)

    -b, --buildDaemon:          build the all executables

    -bD, --buildDaemon:         build the daemon executables

    -cP, --cleanProject:        clean the project

    -cS, --cleanSystem:         clean the system

    -s, --startLoggingServer:   execute the logging server

    -tD, --testDaemon:          execute the daemon unit tests

    -r, --run:                  start daemon in the terminal session

    -s, --start:                start the daeman about systemd (systemctl) 
    
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
    echo "run daemon in the terminal session"
    ./build/bin/$APPLICATION_NAME
}

function startDaemon() {
    buildDaemon
    echo "start daemon"
    systemctl stop $APPLICATION_NAME
    sleep 1

    echo "copy file: $APPLICATION_NAME to /usr/bin/ "
    sudo cp $PWD/build/bin/$APPLICATION_NAME /usr/bin/

    echo "copy file: $APPLICATION_NAME.service to /usr/lib/systemd/system"
    sudo cp $PWD/$APPLICATION_NAME/$APPLICATION_NAME.service /usr/lib/systemd/system

    echo "copy file: $APPLICATION_NAME.config to /etc/$APPLICATION_NAME"
    sudo rm -vfr /etc/daemon
    sudo mkdir /etc/daemon
    sudo cp $PWD/$APPLICATION_NAME/$APPLICATION_NAME.service /etc/daemon/

    systemctl start $APPLICATION_NAME &
    sleep 3

    systemctl status $APPLICATION_NAME
    sleep 3
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
    echo "start the daeman about systemd (systemctl) "
    startDaemon
    ;;

-h | --help | *)
    echo "help page: "
    helpPage
    ;;
esac
