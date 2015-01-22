cmake_minimum_required(VERSION 2.8.4)
project(cpp_wrapper)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_FILES
    example.cpp
    ug_cpp.cpp
    ug_cpp.h)

include_directories(.
    ${Boost_INCLUDE_DIR})

find_package( PythonLibs 2.7 REQUIRED )
include_directories( ${PYTHON_INCLUDE_DIRS} )

find_package( Boost COMPONENTS python REQUIRED )

add_executable(cpp_wrapper ${SOURCE_FILES})

target_link_libraries(cpp_wrapper
    python2.7
    ${Boost_LIBRARIES})