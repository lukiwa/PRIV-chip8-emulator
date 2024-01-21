project(chip8-emulator)

set(ROOT_SOURCES main.cpp)
add_executable(${PROJECT_NAME} ${ROOT_SOURCES})


add_subdirectory(OpenGL)
add_subdirectory(Emulator)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_OpenGL ${PROJECT_NAME}_Emulator)
target_include_directories(${PROJECT_NAME} PRIVATE ./Utilities)
