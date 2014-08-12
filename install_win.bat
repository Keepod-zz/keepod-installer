
:by cmooony@gmail.com at 2014/08/12

@echo on

@set ISCC="C:\Program Files (x86)\Inno Setup 5_han\ISCC.exe"

%ISCC% /qp windows/install_win.iss

@echo 打包成功 在 windows 目录下查看

@echo off
pause