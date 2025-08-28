# GoogleTest_Project

This is a small educational C++ project to learn how to use **Google Test** with **CMake**.  
It demonstrates how to write unit tests for a simple library using Google Test and Google Mock.

## Project Structure
.
├── CMakeLists.txt # CMake build script
├── LibraryCode.cpp # Example library implementation
├── LibraryCode.hpp # Example library header
├── main.cpp # Example main application
└── test.cpp # Google Test unit tests

## Prerequisites

- **CMake** >= 3.13  
- **C++ compiler** (GCC, Clang, or MSVC)  
- **Git** (for fetching Google Test)

> Note: Google Test will be automatically downloaded via CMake FetchContent.

## Build Instructions

```bash
mkdir build
cd build
cmake ..
cmake --build .
./mainApp
./testApp
```
