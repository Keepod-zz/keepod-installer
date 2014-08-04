#!/bin/bash

cd $(dirname "$0")
apt-get update
dpkg -i keepod-*.deb
apt-get -f -y install
dpkg -i keepod-*.deb
