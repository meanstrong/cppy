cmake_minimum_required(VERSION 3.13)

project(cppy)
set(CPPY_VERSION 0.0.1)
set(WORKSPACE ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)
if(NOT CYGWIN AND NOT MSYS AND NOT ${CMAKE_SYSTEM_NAME} STREQUAL QNX)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

aux_source_directory(${WORKSPACE}/src SRC_LIST)

include_directories(${WORKSPACE}/include)

add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
set(LIBRARY_OUTPUT_PATH ${WORKSPACE}/lib)

add_subdirectory(test)
