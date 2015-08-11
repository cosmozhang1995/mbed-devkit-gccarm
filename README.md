# Simple Mbed development platform
This is a simple mbed development platform for Mac OSX / Linux, GCC-ARM. You can create mbed projects and manage the dependencies.
This platform is written in Python 2.7.

## Install
Make sure you have `gcc-arm` installed.
Clone this project. Add the path of the directory `sbin` to system variable `PATH`.
Copy `sbin/config.tpl.py` to `sbin/config.py`. Modify `sbin/config.py` to make your own configs.

## Tools
### mbed_create
Create a mbed project. Type `mbed_create -h` to see more details.
### mbed_import
Import or remove a lib denpendence. Type `mbed_import -h` to see more details.
### mbed_run
Compile and download the program. Then watch the UART outputs and send message using UART.

## Directories
### sbin
The python executable files.
### libs
Publically used libs
### rel
Board platform files. Each board has a directory named by the platform name (lower case). The directory contains:
    `mbed.bld`: The board file.
    `makefile_tpl`: The template of the `Makefile` of projects on this platform.
    `mbed`: Mbed implements directory.
You can get `mbed.bld` and `mbed` and a complete Makefile by exporting a mbed online complier project as a gcc-arm project. Modify the contents above the first parting line in the Makefile to make the `makefile_tpl` file
