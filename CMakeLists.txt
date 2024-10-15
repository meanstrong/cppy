cmake_minimum_required(VERSION 3.13)

project(cppy CXX)
set(CPPY_VERSION 0.0.1)
set(WORKSPACE ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)
if(NOT CYGWIN AND NOT MSYS AND NOT ${CMAKE_SYSTEM_NAME} STREQUAL QNX)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

set(LIBRARY_OUTPUT_PATH ${WORKSPACE}/out)
option(CPPY_CREATE_SHARED_LIBRARY "Build using shared libraries" ON)
# set(CPPY_CREATE_SHARED_LIBRARY ON CACHE BOOL "Build using shared libraries" FORCE)

aux_source_directory(${WORKSPACE}/src CPPY_SRC_LIST)

include_directories(${WORKSPACE}/include)

if(CPPY_CREATE_SHARED_LIBRARY)
  message(STATUS "build shared library")
  add_library(${PROJECT_NAME} SHARED ${CPPY_SRC_LIST})
  target_compile_definitions(${PROJECT_NAME} PRIVATE "CPPY_CREATE_SHARED_LIBRARY")
else()
  message(STATUS "build static library")
  add_library(${PROJECT_NAME} STATIC ${CPPY_SRC_LIST})
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

add_subdirectory(test)
