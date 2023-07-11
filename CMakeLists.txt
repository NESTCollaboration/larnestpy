set (CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 2.8.12)
project(larnestpy)

# Set source directory
set(SOURCE_DIR "vendor/larnest/src")
# Tell CMake that headers are also in SOURCE_DIR
include_directories(
    "vendor/larnest/include/"
)

###############        Get LArNEST version from git        #####################
execute_process(COMMAND git describe --tag
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vendor/larnest/
        OUTPUT_VARIABLE LARNEST_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE)

function(get_versions versionString version)
    if ("${versionString}" STREQUAL "")
        set(version "0.0.0" PARENT_SCOPE)
        return()
    endif ()

    string(REGEX REPLACE "v([0-9]*)([.][0-9]*[.][0-9]*-?.*)$" "\\1" numbers ${versionString})
    set(major ${numbers})
    string(REGEX REPLACE "v([0-9]*[.])([0-9]*)([.][0-9]*-?.*)$" "\\2" numbers ${versionString})
    set(minor ${numbers})
    string(REGEX REPLACE "v([0-9]*[.][0-9]*[.])([0-9]*)(-?.*)$" "\\2" numbers ${versionString})
    set(patch ${numbers})
    set(version "${major}.${minor}.${patch}" PARENT_SCOPE)
endfunction()

get_versions("${LARNEST_VERSION}" version)
set(LARNEST_VERSION ${version})

set(SOURCES 
    "${SOURCE_DIR}/LArNEST.cxx" 
    "${SOURCE_DIR}/Logger.cxx" 
    "${SOURCE_DIR}/RandomGen.cxx"  
)

# Generate Python module
add_subdirectory(vendor/pybind11)
pybind11_add_module(larnestpy ${SOURCES} "src/larnestpy/bindings.cxx")

target_compile_definitions(
    larnestpy PRIVATE 
    LARNESTPY_VERSION=${LARNESTPY_VERSION_INFO} 
    LARNEST_VERSION=${LARNEST_VERSION}
)

