cmake_minimum_required(VERSION 3.13)

project(TestCppy)

aux_source_directory(${WORKSPACE}/test SRC_LIST)

include_directories(${WORKSPACE}/include)

# find_library(CPPY_LIB cppy ${WORKSPACE}/lib)

set(EXECUTABLE_OUTPUT_PATH ${WORKSPACE}/out)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} cppy)
