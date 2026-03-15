cmake_minimum_required(VERSION 3.16)

# Binary name
set(BINARY astdst)

# Project (C + C++)
project(${BINARY} LANGUAGES C CXX)

# Detect OS
if(WIN32)
    set(TARGET_OS "windows")
    set(BINARY "${BINARY}.exe")
elseif(APPLE)
    set(TARGET_OS "macos")
elseif(UNIX)
    set(TARGET_OS "linux")
endif()

# Size optimization toggle
option(SIZE_OPTIMIZATION "Enable size optimization (removes unused code)" ON)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Size optimization: ${SIZE_OPTIMIZATION}")

# Enable Link-Time Optimization for size optimization (via target property)
if(SIZE_OPTIMIZATION AND CMAKE_BUILD_TYPE STREQUAL "Release")
    include(CheckIPOSupported)
    if(CMAKE_IPOS_SUPPORTED)
        message(STATUS "IPO / LTO enabled")
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    else()
        message(STATUS "IPO not supported by compiler")
    endif()
endif()

 
# Source root
set(SRC_ROOT ${CMAKE_SOURCE_DIR}/src)

 
# Collect all .c and .cpp files recursively
file(GLOB_RECURSE SOURCE_FILES
    ${SRC_ROOT}/*.c
    ${SRC_ROOT}/*.cpp
)

 
# Create executable
add_executable(${BINARY} ${SOURCE_FILES})

 
# Include directories
target_include_directories(${BINARY}
    PRIVATE
        ${SRC_ROOT}
)

 
# Language standards
set_target_properties(${BINARY} PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

 
# Compiler warnings and options
if(WIN32)
    target_compile_options(${BINARY}
        PRIVATE
            /W4
    )
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${BINARY} PRIVATE /Od /Zi)
    elseif(SIZE_OPTIMIZATION)
        target_compile_options(${BINARY} PRIVATE
            /Os
            /GL
            /MP
            /Gy
            /permissive-
        )
    else()
        target_compile_options(${BINARY} PRIVATE /O2)
    endif()
else()
    target_compile_options(${BINARY}
        PRIVATE
            -Wall
            -Wextra
    )
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${BINARY} PRIVATE -g -O0)
    elseif(SIZE_OPTIMIZATION)
        target_compile_options(${BINARY} PRIVATE
            -Os
            -fno-exceptions
            -fno-rtti
            -ffunction-sections
            -fdata-sections
        )
    else()
        target_compile_options(${BINARY} PRIVATE -O2)
    endif()
endif()

 
# Find and link SDL3 properly
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

target_link_libraries(${BINARY}
    PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
)

if(UNIX AND NOT APPLE)
    target_link_libraries(${BINARY} PRIVATE m)
endif()

# Size optimization linker flags
if(SIZE_OPTIMIZATION AND CMAKE_BUILD_TYPE STREQUAL "Release")
    if(WIN32)
        set_target_properties(${BINARY} PROPERTIES
            LINK_FLAGS "/LTCG /OPT:REF /OPT:ICF /INCREMENTAL:NO /DYNAMICBASE:NO"
        )
    elseif(UNIX)
        target_link_options(${BINARY} PRIVATE
            -Wl,--gc-sections
            -s
        )
    endif()
endif()

# Output binary in project root
set_target_properties(${BINARY}
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)
