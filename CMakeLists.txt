# Copyright (c) 2025-present, Jason Hoyt
# Distributed under the MIT License (http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 3.10...3.21)

include(cmake/utils.cmake)
include(cmake/ide.cmake)

mf_extract_version()

project(media-framework VERSION ${MF_VERSION} LANGUAGES CXX)
message(STATUS "Build asl: ${MF_VERSION}")

# TODO : download this package if necessary
find_package(SDL3 CONFIG REQUIRED)

#
# Set default build to release
#

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    # Set CMAKE_BUILD_TYPE only if this project is top-level
    if ((DEFINED PROJECT_IS_TOP_LEVEL AND PROJECT_IS_TOP_LEVEL)
            OR (NOT DEFINED PROJECT_IS_TOP_LEVEL AND CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR))
        set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
    endif ()
endif ()

#
# Compiler configuration
#

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)

#
# Setup primary project if this library is being built
#

if (NOT DEFINED MF_PRIMARY_PROJECT)
    if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(MF_PRIMARY_PROJECT ON)
    else ()
        set(MF_PRIMARY_PROJECT OFF)
    endif ()
endif ()

#
# Setup various build options
#

option(MF_BUILD_SHARED "Build shared library" OFF)
option(MF_BUILD_PIC "Build position independent code (-fPIC)" OFF)
set(MF_DEBUG_POSTFIX "d" CACHE STRING "Filename postfix for libraries in debug builds")
option(MF_BUILD_TESTS "Build tests" OFF)
option(MF_BUILD_MOCKS "Build mocks" OFF)
option(MF_BUILD_WARNINGS "Enable compiler warnings" OFF)

# TODO : install options

if (MF_BUILD_PIC)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif ()

#
# The library itself
#

set(MF_SOURCES
        src/blend_mode.cpp
        src/context.cpp
        src/display.cpp
        src/display_properties.cpp
        src/palette.cpp
        src/properties.cpp
        src/surface.cpp
        src/window.cpp
        src/window_create_properties.cpp
        src/window_properties.cpp
)

if (MF_BUILD_SHARED OR BUILD_SHARED_LIBS)
    if (WIN32)
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.rc.in ${CMAKE_CURRENT_BINARY_DIR}/version.rc @ONLY)
        list(APPEND MF_SOURCES ${CMAKE_CURRENT_BINARY_DIR}/version.rc)
    endif ()

    add_library(mf SHARED ${MF_SOURCES} ${MF_ALL_HEADERS})
else ()
    add_library(mf STATIC ${MF_SOURCES} ${MF_ALL_HEADERS})
endif ()

add_library(jhoyt::mf ALIAS mf)

target_include_directories(mf PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>")

target_link_libraries(mf PUBLIC SDL3::SDL3)

set_target_properties(mf PROPERTIES VERSION ${MF_VERSION} SOVERSION ${MF_VERSION_MAJOR}.${MF_VERSION_MINOR})

set_target_properties(mf PROPERTIES DEBUG_POSTFIX ${MF_DEBUG_POSTFIX})

#
# Tests
#

if (MF_BUILD_TESTS OR MF_BUILD_ALL)
    message(STATUS "Generating tests")
    enable_testing()
    #add_subdirectory(tests)
endif ()

#
# Mocks
#

if (MF_BUILD_MOCKS OR MF_BUILD_ALL)
    message(STATUS "Building mocks")
    #add_subdirectory(mocks)
endif ()
