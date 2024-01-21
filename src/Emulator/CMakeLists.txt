set(EMULATOR_SOURCES Emulation.cpp)
add_library(${PROJECT_NAME}_Emulator STATIC ${EMULATOR_SOURCES})
target_include_directories(${PROJECT_NAME}_Emulator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME}_Emulator PRIVATE ../Utilities)
