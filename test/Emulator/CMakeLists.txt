set(EXECUTABLE_NAME ${PROJECT_NAME}_Emulator)

enable_testing()
find_package(GTest REQUIRED)

add_executable(${EXECUTABLE_NAME} Blank.cpp)
target_link_libraries(${EXECUTABLE_NAME} gtest::gtest)
target_include_directories(${EXECUTABLE_NAME} PRIVATE ../../src/Utilities)

include(GoogleTest)
gtest_discover_tests(${EXECUTABLE_NAME})
