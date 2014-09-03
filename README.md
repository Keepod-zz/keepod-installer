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

## Pre-required software

download the pre-required software, including python and autopilot-desktop;

* apt-based GNU/Linux Distribution (debian, ubuntu, mint, etc)
    
        $ sudo apt-get install autopilot-desktop

## Build

get source from github, commands as below:

    $ git clone https://github.com/Keepod/keepod-installer.git

build the keepod-installer from source;
   
    $ cd path/to/source/of/keepod-installer
    
    $ ./build-nostatic
   
## Test

out auto test is based on autopilot, and we can make tests all by once, 
and we can get the list of test routines, and make one test one time.

### All Test

we can launch the test script and then all the tests will be executed one by one.
Below is the commands that we need:

    $ cd ./test/autopilot
    
    $ ./launch_test.sh

### Manually Test

If we want to test one routine one time, first we have to know all the test routines, 
and then we can launch one each time.

* list all the test routines:
    
        $ cd ./test/autopilot
        $ autopilot list installer
    
    and the results will be as below:

        installer.tests.test_basic_process.BasicProcessTests.test_multi_udisk_installing_with_local_img
        installer.tests.test_basic_process.BasicProcessTests.test_single_udisk_downloading_cancel_and_continue_with_net_image
        installer.tests.test_basic_process.BasicProcessTests.test_single_udisk_installing_with_local_img
        installer.tests.test_basic_process.BasicProcessTests.test_single_udisk_md5_check
        installer.tests.test_basic_process.BasicProcessTests.test_single_udisk_writting_cancel_and_continue_with_local_img
        
        5 total tests.


* lanch the test we want, we launch **installer.tests.test_basic_process.BasicProcessTests.test_single_udisk_installing_with_local_img** as example:

        $ autopilot run installer.tests.test_basic_process.BasicProcessTests.test_single_udisk_installing_with_local_img
    
**Note**:

* for all the tests, we have at least one udisk mounted.
* when we launch  **xxxx_with_local_img** routine, we have to copy the image file (**keepod-latest.zip**) to /test/autopilot/installer/tests .
