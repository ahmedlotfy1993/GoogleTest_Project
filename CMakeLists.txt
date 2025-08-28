cmake_minimum_required(VERSION 3.13)
project(googletest_sample)

#######################################Google test#######################################
include(FetchContent)
FetchContent_Declare(googletest
	GIT_REPOSITORY https://github.com/google/googletest
	GIT_TAG v1.17.0)

FetchContent_GetProperties(googletest)
#googletest_POPULATED
#googletest_SOURCE_DIR
#googletest_BUILDDIR

if(NOT googletest_POPULATED)
	FetchContent_Populate(googletest)
	#GO TO SUB DIRECTORIES AND BUILD THEM
	add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BUILD_DIR})
endif()


#######################################STATIC LIBRARIES#######################################
add_library(SumLibrary STATIC LibraryCode.cpp LibraryCode.hpp)
add_library(databaseConnectionLibrary STATIC IDatabaseConnection.cpp)
add_library(employeeManagerLibrary STATIC EmployeeManager.cpp)
set(ACTUAL_LIBRARIES SumLibrary databaseConnectionLibrary employeeManagerLibrary)

#######################################TARGETS AND LINKS TO LIBRARIES#######################################
add_executable(mainApp main.cpp)
add_executable(testApp test.cpp)
target_link_libraries(mainApp ${ACTUAL_LIBRARIES})
target_link_libraries(testApp ${ACTUAL_LIBRARIES} gtest_main gmock_main pthread)
