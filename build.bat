@echo off
echo Building Hostel Outing & Leave Management System...
g++ main.cpp -o hostel_management.exe
if %errorlevel% == 0 (
    echo Build successful!
    echo Run hostel_management.exe to start the program.
) else (
    echo Build failed!
    pause
)

