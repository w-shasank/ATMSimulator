#!/bin/bash

# Debug Build Script for ATM Simulator
echo "==============================================="
echo "     ATM Simulator Debug Build Script"
echo "==============================================="

# Check current directory and files
echo "Current directory: $(pwd)"
echo ""
echo "Files in current directory:"
ls -la
echo ""

# Check if source directory exists
if [ -d "src" ]; then
    echo "✓ src/ directory found"
    echo "Files in src/:"
    ls -la src/
else
    echo "❌ src/ directory not found"
    echo "Creating src/ directory and files..."
    mkdir -p src
fi

echo ""

# Check for required source files
REQUIRED_FILES=("src/main.cpp" "src/Account.h" "src/Account.cpp" "src/Transaction.h" "src/Transaction.cpp" "src/ATM.h" "src/ATM.cpp" "src/FileManager.h" "CMakeLists.txt")

echo "Checking for required files:"
for file in "${REQUIRED_FILES[@]}"; do
    if [ -f "$file" ]; then
        echo "✓ $file exists"
    else
        echo "❌ $file missing"
    fi
done

echo ""

# Check if CMake is available
if command -v cmake &> /dev/null; then
    CMAKE_VERSION=$(cmake --version | head -n1 | cut -d' ' -f3)
    echo "✓ CMake found: $CMAKE_VERSION"
else
    echo "❌ CMake not found. Installing..."
    sudo apt update && sudo apt install cmake
fi

# Check for C++ compiler
if command -v g++ &> /dev/null; then
    GCC_VERSION=$(g++ --version | head -n1)
    echo "✓ g++ found: $GCC_VERSION"
else
    echo "❌ g++ not found. Installing..."
    sudo apt update && sudo apt install build-essential
fi

echo ""
echo "Debug information collected. Please run this script and share the output."