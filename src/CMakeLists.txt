project(chip8-emulator)

set(ROOT_SOURCES main.cpp)
add_executable(${PROJECT_NAME} ${ROOT_SOURCES})


add_subdirectory(OpenGL)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_OpenGL)
target_include_directories(${PROJECT_NAME} PRIVATE ./Utilities)
