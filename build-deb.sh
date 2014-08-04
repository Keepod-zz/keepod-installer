#!/bin/bash

cd $(dirname "$0")
fakeroot debian/rules clean
fakeroot debian/rules binary
