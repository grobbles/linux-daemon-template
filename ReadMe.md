# Linux Daemon Template

## Sources

-   Deamon - https://github.com/jirihnidek/daemon

## Description

This a simple linux daemon with the following functions:

-   this daemon create a own log file in /var/log/daemon
-   read the configration from /etc/daemon/daemon.conf
-   the daemon start automaticlley with systemd

## ToDo's

-   Add sort function for log messages
-   save all log messages in a data base (SQLite, MySQL)
-   AdminLTE as Frontand
-   Resorces delete after shutdown
-   Create e one log file for server
-   Add a interface to modify the client log level
-   Create a new Log file handler with a virtuell file
-   Add a kernel client
-   Added a storage for configuration
-   Add a Logging lib for JAVA
-   added unit tests
