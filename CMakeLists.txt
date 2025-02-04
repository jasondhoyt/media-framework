# Copyright (c) 2025-present, Jason Hoyt
# Distributed under the MIT License (http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 3.10...3.21)

include(cmake/utilities.cmake)

extract_mf_version()

project(media-framework VERSION ${MF_VERSION} LANGUAGES CXX)
message(STATUS "Build media framework: ${MF_VERSION}")

#
# Setup the C++ compiler
#

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#
# Setup various build option defaults.
#

option(MF_BUILD_SHARED "Build shared library" OFF)
option(MF_BUILD_PIC "Build position independent code (-fPIC)" OFF)
option(MF_BUILD_TESTS "Build tests" OFF)
option(MF_BUILD_EXAMPLES "Build examples" OFF)

if(MF_BUILD_PIC)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

#
# Build tests if enabled.
#

# if(MF_BUILD_TESTS)
#     message(STATUS "Generating tests")
#     enable_testing()
#     add_subdirectory(tests)
# endif()

#
# Check for dependencies.
#

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)

#
# Build the library (static or shared)
#

set(MF_SOURCES  
    src/event/handler.cpp
    src/event/run_loop.cpp
    src/gpu/command_buffer.cpp
    src/gpu/device.cpp
    src/gpu/render_pass.cpp
    src/gpu/texture.cpp
    src/context.cpp
    src/window.cpp
)

if(MF_BUILD_SHARED OR BUILD_SHARED_LIBS)
    if(WIN32)
        #
        # Setup information for Windows shared library.
        #
        configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.rc.in" "${CMAKE_CURRENT_BINARY_DIR}/version.rc" @ONLY)
        list(APPEND MF_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/version.rc")
    endif()

    add_library(mf SHARED ${MF_SOURCES})

    target_compile_definitions(mf PUBLIC MF_SHARED_LIB)
else()
    add_library(mf STATIC ${MF_SOURCES})
endif()

add_library(jhoyt::mf ALIAS mf)

target_include_directories(mf PUBLIC 
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(mf PUBLIC
    $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image-static>
    SDL3::SDL3
)

set_target_properties(mf PROPERTIES VERSION ${MF_VERSION} SOVERSION ${MF_VERSION_MAJOR}.${MF_VERSION_MINOR})

#
# Build examples if enabled.
#

if(MF_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
