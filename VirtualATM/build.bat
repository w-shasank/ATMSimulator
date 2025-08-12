@echo off
REM ATM Simulator Build Script for Windows
REM Authors: Sandesh Khatiwada, Shasank Wagle

echo ===============================================
echo      ATM Simulator Build Script v1.0
echo ===============================================

REM Check if CMake is installed
where cmake >nul 2>nul
if %errorlevel% neq 0 (
    echo ❌ CMake is not installed. Please install CMake 3.10 or higher.
    pause
    exit /b 1
)

REM Get CMake version
for /f "tokens=3" %%i in ('cmake --version ^| findstr "cmake version"') do set CMAKE_VERSION=%%i
echo ✓ Found CMake version: %CMAKE_VERSION%

REM Check for Visual Studio or Build Tools
where cl >nul 2>nul
if %errorlevel% equ 0 (
    echo ✓ Found Visual Studio C++ compiler
    set GENERATOR="Visual Studio 16 2019"
) else (
    REM Check for MinGW
    where g++ >nul 2>nul
    if %errorlevel% equ 0 (
        echo ✓ Found MinGW g++ compiler
        set GENERATOR="MinGW Makefiles"
    ) else (
        echo ❌ No suitable C++ compiler found.
        echo Please install Visual Studio 2019/2022 or MinGW-w64.
        pause
        exit /b 1
    )
)

REM Create build directory
echo.
echo 📁 Creating build directory...
if not exist build mkdir build
cd build

REM Configure project
echo ⚙️  Configuring project with CMake...
cmake -G %GENERATOR% -A x64 ..
if %errorlevel% neq 0 (
    echo ❌ Configuration failed
    pause
    exit /b 1
)
echo ✓ Configuration successful

REM Build project
echo 🔨 Building project...
cmake --build . --config Release
if %errorlevel% neq 0 (
    echo ❌ Build failed
    pause
    exit /b 1
)
echo ✓ Build successful

REM Create data directory
echo 📂 Setting up data directory...
if not exist data mkdir data

REM Create sample data if accounts.txt doesn't exist
if not exist "data\accounts.txt" (
    echo 📄 Creating sample account data...
    (
        echo 12345,1234,1500.750000
        echo 67890,5678,2750.000000
        echo 11111,1111,500.250000
        echo 22222,2222,10000.000000
        echo 33333,3333,0.000000
    ) > data\accounts.txt
    echo ✓ Sample data created
)

echo.
echo ===============================================
echo ✅ BUILD COMPLETED SUCCESSFULLY!
echo ===============================================
echo.
echo 🚀 To run the ATM Simulator:

REM Check if we built with Visual Studio or MinGW
if exist "Release\ATM_Simulator.exe" (
    echo    Release\ATM_Simulator.exe
) else (
    echo    ATM_Simulator.exe
)

echo.
echo 📋 Available test accounts:
echo    Account: 12345, PIN: 1234, Balance: $1,500.75
echo    Account: 67890, PIN: 5678, Balance: $2,750.00
echo    Account: 11111, PIN: 1111, Balance: $500.25
echo    Account: 22222, PIN: 2222, Balance: $10,000.00
echo    Account: 33333, PIN: 3333, Balance: $0.00
echo.
echo 💡 For clean build, delete build directory and run script again
echo 🗑️  To reset data, delete data\accounts.txt
echo.
pause