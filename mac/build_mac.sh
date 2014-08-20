#! /bin/bash

#CUR_DIR=`pwd`
#PRO_PATH=${CUR_DIR%/*}

cd mac

qmake ../ -r -spec unsupported/macx-clang CONFIG+=x86_64

make clean
make
make install