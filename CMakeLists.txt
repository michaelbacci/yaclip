cmake_minimum_required(VERSION 3.2)

project(yaclip CXX)

##This is a C++11 project
##Setting up the right C++11 flag

include(CheckCXXCompilerFlag)
Set(ENABLE_CXXFLAGS_TO_CHECK
        -std=gnu++1z
        -std=c++1z
        -std=gnu++1y
        -std=c++1y
        -std=gnu++11
        -std=c++11
        -std=gnu++0x
        -std=c++0x)

Set(CXX_COMPILER_ENABLED FALSE)

foreach(flag ${ENABLE_CXXFLAGS_TO_CHECK})
    string(REPLACE "-std=" "_" flag_var ${flag})
    string(REPLACE "+" "x" flag_var ${flag_var})
    CHECK_CXX_COMPILER_FLAG("${flag}" COMPILER_HAS_CXX_FLAG${flag_var})
    if(COMPILER_HAS_CXX_FLAG${flag_var})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}")
        Set(CXX_COMPILER_ENABLED TRUE)
        break()
    endif()
endforeach()

if (NOT CXX_COMPILER_ENABLED)
    Mesage(FATAL_ERROR "The current CPP compiler does not support C++11: Please provide a good one.")
endif()


##Examples and Tests are used in order to develop and testing the yaclip.hpp file.
##If you want to use the yaclip.hpp in your program/library you have just to
##copy the yacl.hpp in your project's directory.
option(BUILD_EXAMPLES "Compile the examples ?" OFF)
option(BUILD_TESTS "Compile the test ?" ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if (BUILD_EXAMPLES)
    add_executable(subgroup ${CMAKE_CURRENT_SOURCE_DIR}/examples/subgroup.cpp)
endif()

if (BUILD_TESTS)

    if (NOT EXISTS "${PROJECT_SOURCE_DIR}/lib/googletest/CMakeLists.txt")
        message("Gooogle test library does not exist: downloading...")

        execute_process(
                COMMAND git submodule init
                COMMAND git submodule update
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                RESULT_VARIABLE git_result
                OUTPUT_VARIABLE git_output
                ERROR_VARIABLE git_error
        )

        if (NOT "${git_error}" STREQUAL "")
            message(FATAL_ERROR "Please, run:\ngit submodule init\ngit submodule update\nIn order to download the googletest library.")
        else()
            message(STATUS "Git result -> [${git_result}]")
            message(STATUS "Git output -> [${git_output}]")
        endif()
    endif()

    enable_testing()
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/googletest)
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
    file(GLOB source_test test/*.cpp test/*.hpp)
    add_executable(RunUnitTests ${source_test})
    target_link_libraries(RunUnitTests gtest gtest_main)
    add_test(run-all RunUnitTests)

endif()
