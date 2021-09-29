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

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -static -shared -Werror=cpp -Wall -Wextra -pedantic -fmax-errors=3 -Wundef -Wnull-dereference -Wduplicated-cond -Wduplicated-branches -Wshadow -Wswitch -Wswitch-enum -Wstrict-overflow=5 -Wconversion -Wfloat-equal -Wdouble-promotion -Wwrite-strings -Wpointer-arith -Wcast-qual -Wformat=2 -Wformat-signedness -Wformat-y2k -Wformat-overflow=2 -Wold-style-cast -Wnon-virtual-dtor -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override -Wsized-deallocation -Wextra-semi -Wmultiple-inheritance -Wzero-as-null-pointer-constant -Werror" CACHE INTERNAL "") #-fuse-linker-plugin -flto -fno-fat-lto-objects")
elseif(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -shared -fPIC -Werror=cpp -Wall -Wextra -pedantic -fmax-errors=3 -Wundef -Wnull-dereference -Wduplicated-cond -Wduplicated-branches -Wshadow -Wswitch -Wswitch-enum -Wstrict-overflow=5 -Wconversion -Wfloat-equal -Wdouble-promotion -Wwrite-strings -Wpointer-arith -Wcast-qual -Wformat=2 -Wformat-signedness -Wformat-y2k -Wformat-overflow=2 -Wold-style-cast -Wnon-virtual-dtor -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override -Wsized-deallocation -Wextra-semi -Wmultiple-inheritance -Wzero-as-null-pointer-constant -Werror" CACHE INTERNAL "") #-fuse-linker-plugin -flto -fno-fat-lto-objects")
endif()
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
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/patch/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/patch/")
file(COPY "${CMAKE_SOURCE_DIR}/hydrusCXXPatch/PatchedClient.py" DESTINATION "${CMAKE_SOURCE_DIR}/patch/")

include_directories(${SOURCE_DIR})

file(GLOB_RECURSE SOURCES
    "${SOURCE_DIR}/*.cpp"
)
##SETUP DLL##
include(GenerateExportHeader)
if(WIN32)
    add_library(HydrusPatch SHARED ${SOURCES})
elseif(UNIX)
    add_library(HydrusPatch SHARED ${SOURCES})
endif()

target_include_directories(HydrusPatch PRIVATE ${SOURCE_DIR})

file(COPY "${CMAKE_SOURCE_DIR}/hydrusCXXPatch/PatchedClient.py" DESTINATION "${CMAKE_SOURCE_DIR}/patch/")

install(CODE "if(EXISTS \"hydrus/hydrus\")
    message(\"Detected what looks to be hydrus source. Adding patch files\")
        if(WIN32)
            file(COPY \"${CMAKE_SOURCE_DIR}/patch/libHydrusPatch.dll\" DESTINATION \"{$CMAKE_SOURCE_DIR}/hydrus/\")
        elseif(UNIX)
            file(COPY \"${CMAKE_SOURCE_DIR}/patch/libHydrusPatch.so\" DESTINATION \"${CMAKE_SOURCE_DIR}/hydrus/\")
        endif()
    file(COPY \"${CMAKE_SOURCE_DIR}/patch/PatchedClient.py\" DESTINATION \"${CMAKE_SOURCE_DIR}/hydrus/\")
    file(REMOVE \"${CMAKE_SOURCE_DIR}/hydrus/client.py\")
    message(\"You can now build hydrus and the patches will be applied.\")
endif()")

#    file(RENAME \"${CMAKE_SOURCE_DIR}/patch/PatchedClient.py\" \"${CMAKE_SOURCE_DIR}/hydrus/client.py\")

