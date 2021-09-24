cmake_minimum_required(VERSION 3.0.0)
project(HydrusPatch VERSION 0.1.0)


if(WIN32)
    project(HydrusPatch LANGUAGES CXX)
elseif(UNIX)
    project(HydrusPatch)
endif()

set(CMAKE_CONFIGURATION_TYEPS "Release;Dev" CACHE STRING "" FORCE)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
# -fsanitize=address 
# -fmodules-ts

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Werror=cpp -Wall -Wextra -pthread -pedantic -fmax-errors=3 -Wundef -Wnull-dereference -Wduplicated-cond -Wduplicated-branches -Wshadow -Wswitch -Wswitch-enum -Wstrict-overflow=5 -Wconversion -Wfloat-equal -Wdouble-promotion -Wwrite-strings -Wpointer-arith -Wcast-qual -Wformat=2 -Wformat-signedness -Wformat-y2k -Wformat-overflow=2 -Wold-style-cast -Wnon-virtual-dtor -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override -Wsized-deallocation -Wextra-semi -Wmultiple-inheritance -Wzero-as-null-pointer-constant -Werror") #-fuse-linker-plugin -flto -fno-fat-lto-objects")
#-fanalyzer 

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -Og")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -s")


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MAKE_PROGRAM make)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#inclusion of project files#
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/hydrusCXXPatch/src")
set(FGL_DIR "${CMAKE_SOURCE_DIR}/fglheaders")

#Set export dirs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/archive/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/library/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/runtime/lib")
file(COPY "${CMAKE_SOURCE_DIR}/hydrusCXXPatch/PatchedClient.py" DESTINATION "${CMAKE_BINARY_DIR}/build")



include_directories(${FORMS_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})
include_directories(${FGL_DIR})


file(GLOB_RECURSE SOURCES
    "${INCLUDE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
    "${FGL_DIR}/*.cpp"
    "${FGL_DIR}/*.hpp"
)
##SETUP DLL##
include(GenerateExportHeader)
if(WIN32)
    add_library(HydrusPatch SHARED ${SOURCES})
elseif(UNIX)
    add_library(HydrusPatch SHARED ${SOURCES})
endif()

target_include_directories(HydrusPatch PRIVATE ${FORMS_DIR})
target_include_directories(HydrusPatch PRIVATE ${INCLUDE_DIR})
target_include_directories(HydrusPatch PRIVATE ${SOURCE_DIR})
target_include_directories(HydrusPatch PRIVATE ${FLG_DIR})
