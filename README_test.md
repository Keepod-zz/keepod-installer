# AUTOTEST 

this is the simple auto test intro for testing keepod-installer based on autopilot.

## Pre-Required software

the softwares we need for auto test includes autopilot and python.

## APT-based GNU/Linux Distribution (debian, ubuntu, mint, etc)

Here are the packages to install on Debian/Ubuntu/Mint, command as below:

    sudo apt-get install autopilot-desktop

## Usage

* build the keepod-installer from source
    
    cd path/to/source/of/keeplod-installer
    ./build-nostatic
    
* start auto test, but we have to check if we have previous building success.
    cd ./test/autopilot
    ./launch_test.sh
    
* check whether the software proceeds correctly according to operation if mouse.

## Issues

* now we just have the auto test for basic operation


    
    
