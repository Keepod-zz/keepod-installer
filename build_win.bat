
:: by cmooony@gmail.com at 2014/08/12

:: ensure qmake and make are in system PATH.
:: ensure QT_DIR is in system envirement.
:: 
:: example:
:: set QT_DIR=E:\Qt\4.8.6
:: set QMAKE_DIR=%QT_DIR%\bin
:: set MAKE_DIR=E:\Qt\Qt5.3.1\Tools\mingw482_32\bin
:: setx PATH "%PATH%;%MAKE_DIR%;%QMAKE_DIR%"

@echo off

@set QMAKE=qmake.exe
@set MAKE=mingw32-make.exe
@set QT_DIR=

@set b=1
:labelFor
@for /f "tokens=%b% delims=;" %%s in ("%path%") do (
	@set QT_DIR=
	@set /a b+=1
	if exist %%s\%QMAKE% (
		@set "QT_DIR=%%s"
		goto :labelQtFound
	)
) && goto :labelFor

if defined QT_DIR ( goto :labelQtFound ) else (goto :labelQtNotFound)

:labelQtFound
	@set QT_DIR=%QT_DIR:~0,-4%
	echo OK! QT_DIR FOUND %QT_DIR%
	::pause

:make	
	cd /d %~dp0windows

	%QMAKE% ..\ -r -spec win32-g++ "CONFIG+=release DEFQTPATH" QT_PATH=%QT_DIR%
	%MAKE% clean
	%MAKE% 

	cd ..
	goto :exit


:labelQtNotFound
	@echo ERROR! qmake NOT FOUND!	

:exit
	@echo build in directory %CD%\windows\bin exit
	:pause