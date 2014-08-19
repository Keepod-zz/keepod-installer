keepod-installer
================

A cross-platform installer for Keepod OS

User manual of Linux version:
http://start.keepod.org/question/keepod-installer-user-guide-linux/

# Coding Style

Be consistent with existing code.

# Implementation

The workflow of this program is very simple:

1. download an clone file from web or choose one local file;
2. extract the zip file;
3. write all data to USB disks according to file 'changed.index';

# Commit code

1. Fork this project;
2. Create an branch;
3. Commit your code and test;
4. Create a "pull request";

# Auto test

this the the auto test intro for keepod-installer based on autopilot 

1. download the pre-required software, including python and autopilot-desktop;

    * apt-based GNU/Linux Distribution (debian, ubuntu, mint, etc)
    
        $ sudo apt-get install autopilot-desktop

2. download source code from github;
3. build the keepod-installer from source;
   
    $ cd path/to/source/of/keepod-installer
    $ ./build-nonstatic
   
4. launch auto test;

    $ cd ./test/autopilot
    $ ./launch_test.sh
    
5. check the software proceeding situation 

