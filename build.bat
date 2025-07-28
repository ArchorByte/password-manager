@echo off
cls

if not exist "build" (mkdir "build")
cd build

if not exist "win" (mkdir "win")
cd build

if not exist "cmake" (mkdir "cmake")
if not exist "out" (mkdir "out")
cd cbc_cmake

cmake ../../../ -G "MinGW Makefiles" -DCMAKE_C_COMPILER=C:/MinGW/bin/gcc.exe -DCMAKE_CXX_COMPILER=C:/MinGW/bin/g++.exe
C:/MinGW/bin/mingw32-make.exe

move pwd.exe ../out/
cd ../out

pause
start pwd.exe

cd ../../../
pause
