
:by cmooony@gmail.com at 2014/08/12

@echo off

:echo 请修改 qmake 和 make 目录

set QT_DIR=E:\Qt\4.8.6
set QMAKE_DIR=%QT_DIR%\bin
set MAKE_DIR=E:\Qt\Qt5.3.1\Tools\mingw482_32\bin

set QMAKE="%QMAKE_DIR%\qmake.exe"
set MAKE="%MAKE_DIR%\mingw32-make.exe"


setx PATH "%PATH%;%MAKE_DIR%;%QMAKE_DIR%"

cd /d %~dp0windows

%QMAKE% ..\ -r -spec win32-g++ "CONFIG+=release DEFQTPATH" QT_PATH=%QT_DIR%
%MAKE% clean
%MAKE% 

cd ..

echo 编译完成 请到windows/bin目录下查看

pause


:exit