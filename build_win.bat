
:: by cmooony@gmail.com at 2014/08/12

:: ensure QT_DIR is in system PATH.
:: ensure qmake and make are in system PATH.
:: 
:: example:
:: set QMAKE_DIR=E:\Qt\4.8.6\bin
:: set MAKE_DIR=E:\Qt\Qt5.3.1\Tools\mingw482_32\bin
:: setx PATH "%PATH%;%MAKE_DIR%;%QMAKE_DIR%"

@echo off

@set QMAKE=qmake.exe
@set MAKE=mingw32-make.exe
@set QMAKE_DIR=
@set MAKE_DIR=
@set COPY=cmd /c copy /y /B /N

@set b=1
:labelFor
	@for /f "tokens=%b% delims=;" %%s in ("%path%") do (	
		@echo %%s
		
		if not defined MAKE_DIR (
			if exist %%s\%MAKE% (
				@set "MAKE_DIR=%%s"
			)
		)
		
		if not defined QMAKE_DIR (
			if exist %%s\%QMAKE% (
				@set "QMAKE_DIR=%%s"
			)
		)
		
		
		@set /a b+=1	
	) && goto :labelFor

if not defined QMAKE_DIR  (
	@echo ERROR! %QMAKE% NOT FOUND!
	goto :exit
	)
	
if not defined MAKE_DIR (
	@echo ERROR! %MAKE% NOT FOUND!
	goto :exit
	)	

@echo OK! %MAKE% FOUND in %MAKE_DIR% 
@echo OK! %QMAKE% FOUND in %QMAKE_DIR%

@set QT_PATH=%QMAKE_DIR:~0,-4%
@echo %QT_PATH%
@set MAKE_PATH=%MAKE_DIR:~0,-4%
@echo %MAKE_PATH%

:: pause
	
:labelMake	
	cd /d %~dp0windows

	%QMAKE% ..\ -r -spec win32-g++ "CONFIG+=release static DEFQTPATH DEFMAKEPATH" QT_PATH=%QT_PATH% MAKE_PATH=%MAKE_PATH%
	%MAKE% clean
	%MAKE% 
	%MAKE% install

	cd ..

:exit
	@echo OK! build in directory %CD%\windows\bin
	pause