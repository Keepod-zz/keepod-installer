
:: by cmooony@gmail.com at 2014/08/12
:: ensure Inno Setup 5 is in system PATH
:: 
:: example:
:: set INNO_DIR=C:\Program Files (x86)\Inno Setup 5_han\
:: setx PATH "%PATH%;%INNO_DIR%"

@echo off

@set ISCC=ISCC.exe

@echo on
%ISCC% /qp windows/install_win.iss

@echo off
@echo pakage OK! %CD%\windows\Keepod OS Installer.exe

pause