project(TestCppy)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

aux_source_directory(${WORKSPACE}/test TESTCPPY_SRC_LIST)

include_directories(${WORKSPACE}/include)

#find_library(CPPY_LIB NAMES cppy PATHS ${WORKSPACE}/out/cppy/lib)

set(EXECUTABLE_OUTPUT_PATH ${WORKSPACE}/out)

enable_testing()
add_executable(${PROJECT_NAME} ${TESTCPPY_SRC_LIST})
target_link_libraries(${PROJECT_NAME} PRIVATE cppy GTest::gtest_main)
if(CPPY_CREATE_SHARED_LIBRARY)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:cppy> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:GTest::gtest> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:GTest::gtest_main> $<TARGET_FILE_DIR:${PROJECT_NAME}>
  )
  target_compile_definitions(${PROJECT_NAME} PUBLIC CPPY_LINKED_AS_SHARED_LIBRARY=1)
endif()

include(GoogleTest)
# Use simple add_test instead of gtest_discover_tests/gtest_add_tests
# to avoid Windows DLL loading issues during test discovery
add_test(NAME AllTests COMMAND ${PROJECT_NAME})

