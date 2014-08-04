#!/bin/bash

cd $(dirname "$0")
apt-get update
dpkg -i keepod-*.deb
apt-get -f -y install
apt-get install extlinux syslinux libicu48 libicu52 
dpkg -i keepod-*.deb
