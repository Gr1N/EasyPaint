@ECHO off
mkdir windows
cd..
cd..
C:\Qt\Qt5.0.1\5.0.1\mingw47_32\bin\qmake.exe -o distr\exe\windows .\sources\easypaint.pro -r -spec win32-g++
cd .\distr\exe\windows
C:\Qt\Qt5.0.1\Tools\MinGW\bin\mingw32-make.exe -f Makefile.Release
pause
rem mingw32-make.exe in C:\Users\Microsoft\Documents\GitHub\EasyPaint\easypaint-build-Desktop_Qt_5_0_1_MinGW_
rem "C:\Program Files\Inno Setup 5\ISCC.exe" make_exe.iss
rem copy mingwm10.dll
rem copy QtCore4.dll
rem copy libgcc_s_dw2-1.dll
rem copy QtGui4.dll