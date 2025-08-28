# GoogleTest_Project

This is a small educational C++ project to learn how to use **Google Test** with **CMake**.  
It demonstrates how to write unit tests for a simple library using Google Test and Google Mock.

## Project Structure
.
- CMakeLists.txt: **CMake build script**
- LibraryCode.cpp: **Example library implementation**
- LibraryCode.hpp: **Example library header**
- IDatabaseConnection.cpp: **Example defination for lower layer interface to be inherited for mocking**
- IDatabaseConnection.hpp: **Example Interface header**
- EmployeeManager.cpp: **Example defination for upper layer object which composite one child class from IDatabaseConnection as a dependacy**
- EmployeeManager.hpp: **Example header for upper layer class**
- main.cpp: **Example dummy main application**
- test.cpp: **Google Test unit tests using gtest & gmock**

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
