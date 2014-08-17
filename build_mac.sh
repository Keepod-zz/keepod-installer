#! /bin/bash

# by cmooony@gmail.com at 2014/08/16
# make sure qmake make are in /usr/bin
# Qt 4.8.6

CUR_DIR=${0%/*}

cd $CUR_DIR/mac

qmake ../ -r -spec unsupported/macx-clang CONFIG+=x86_64

make clean
make
make install