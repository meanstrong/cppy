cmake_minimum_required(VERSION 3.13)

project(cppy CXX)
set(CPPY_VERSION 0.0.1)
set(WORKSPACE ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)
if(NOT CYGWIN AND NOT MSYS AND NOT ${CMAKE_SYSTEM_NAME} STREQUAL QNX)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
option(CPPY_CREATE_SHARED_LIBRARY "Build using shared libraries" ON)
# set(BUILD_SHARED_LIBS ON CACHE BOOL "Build using shared libraries" FORCE)

aux_source_directory(${WORKSPACE}/src CPPY_SRC_LIST)

include_directories(${WORKSPACE}/include)

if(BUILD_SHARED_LIBS)
  add_library(${PROJECT_NAME} SHARED ${CPPY_SRC_LIST})
  target_compile_definitions(${PROJECT_NAME} PUBLIC CPPY_CREATE_SHARED_LIBRARY=1)
  set(CPPY_CREATE_SHARED_LIBRARY ON CACHE BOOL "Build using shared libraries" FORCE)
else()
  add_library(${PROJECT_NAME} STATIC ${CPPY_SRC_LIST})
  set(CPPY_CREATE_SHARED_LIBRARY OFF CACHE BOOL "Build using shared libraries" FORCE)
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${WORKSPACE}/out/${PROJECT_NAME}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${WORKSPACE}/out/${PROJECT_NAME}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${WORKSPACE}/out/${PROJECT_NAME}/lib"
    PDB_OUTPUT_DIRECTORY "${WORKSPACE}/out/${PROJECT_NAME}/bin"
    COMPILE_PDB_OUTPUT_DIRECTORY "${WORKSPACE}/out/${PROJECT_NAME}/lib")
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(test)
