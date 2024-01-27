set(EXECUTABLE_NAME ${PROJECT_NAME}_OpenGL)

enable_testing()
find_package(GTest REQUIRED)

add_executable(${EXECUTABLE_NAME} Window.cpp VertexAttributes.cpp ShaderProgram.cpp PixelMap.cpp)
target_link_libraries(${EXECUTABLE_NAME} gtest::gtest chip8-emulator_OpenGL)
target_include_directories(${EXECUTABLE_NAME} PRIVATE ../../src/Utilities)

include(GoogleTest)
gtest_discover_tests(${EXECUTABLE_NAME})
