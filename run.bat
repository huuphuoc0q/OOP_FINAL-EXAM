
@echo off
cd /d "%~dp0"

"C:\msys64\ucrt64\bin\g++.exe" -std=c++17 -Iinclude src/main.cpp src/VuKhi.cpp src/Sung.cpp src/Kiem.cpp src/PhepThuat.cpp src/NhanVat.cpp -o SatThuongNhanVat.exe

if errorlevel 1 (
    echo.
    echo BIEN DICH THAT BAI.
    pause
    exit /b 1
)

SatThuongNhanVat.exe
pause
