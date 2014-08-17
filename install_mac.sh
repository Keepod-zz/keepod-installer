#! /bin/bash

# by cmooony@gmail.com at 2014/08/16
# you need macdeployqt


CUR_DIR=${0%/*}


cd $CUR_DIR/mac

install_name_tool -change /usr/lib/libstdc++.6.dylib @executable_path/../dylib/libstdc++.6.dylib bin/keepod-installer.app/Contents/MacOS/keepod-installer

install_name_tool -change /usr/lib/libSystem.B.dylib @executable_path/../dylib/libSystem.B.dylib bin/keepod-installer.app/Contents/MacOS/keepod-installer

install_name_tool -change /usr/lib/libgcc_s.1.dylib @executable_path/../dylib/libgcc_s.1.dylib bin/keepod-installer.app/Contents/MacOS/keepod-installer

macdeployqt ./bin/keepod-installer.app -dmg 

mv -f ./bin/keepod-installer.dmg ./bin/Keepod\ OS\ Installer.dmg

