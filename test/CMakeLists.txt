project(TestCppy)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

aux_source_directory(${WORKSPACE}/test SRC_LIST)

include_directories(${WORKSPACE}/include)

SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
find_library(CPPY_LIB NAMES cppy PATHS ${WORKSPACE}/out)
message(STATUS "find library cppy path: ${CPPY_LIB} ${WORKSPACE}/out")

set(EXECUTABLE_OUTPUT_PATH ${WORKSPACE}/out)

enable_testing()
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest_main cppy)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
