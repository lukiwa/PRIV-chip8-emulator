cmake_minimum_required(VERSION 3.23)
project(chip8-emulator)

set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

#debug / release
if (CMAKE_BUILD_TYPE MATCHES Debug)
    message(">CMake in Debug mode")
    add_compile_definitions(DEBUG)
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    message(">CMake in Release mode")
endif ()

#allowing wsl display
if (WSL1)
    message(">Allowing WSL1 display by setting env variable")
    add_compile_definitions(WSL1)
else ()
    message(">NOT in WSL1")
endif ()

set(CMAKE_CXX_FLAGS_DEBUG "-g")

#Project target
add_subdirectory(src)

#Tests
if (BUILD_TESTS)
    message(">Building tests")
    add_subdirectory(test)
endif ()









