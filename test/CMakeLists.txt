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
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${WORKSPACE}/out/${PROJECT_NAME}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${WORKSPACE}/out/${PROJECT_NAME}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${WORKSPACE}/out/${PROJECT_NAME}/lib"
    PDB_OUTPUT_DIRECTORY "${WORKSPACE}/out/${PROJECT_NAME}/bin"
    COMPILE_PDB_OUTPUT_DIRECTORY "${WORKSPACE}/out/${PROJECT_NAME}/lib")
if(CPPY_CREATE_SHARED_LIBRARY)
  add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${WORKSPACE}/out/cppy/bin/cppy.dll ${WORKSPACE}/out/TestCppy/bin/cppy.dll
  )
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/bin/gtest.dll ${WORKSPACE}/out/TestCppy/bin/gtest.dll
  )
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/bin/gtest_main.dll ${WORKSPACE}/out/TestCppy/bin/gtest_main.dll
  )
  target_compile_definitions(${PROJECT_NAME} PUBLIC CPPY_LINKED_AS_SHARED_LIBRARY=1)
endif()

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

