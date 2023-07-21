set(OPENGL_SOURCES ShaderProgram.cpp VertexBuffer.cpp IndexBuffer.cpp VertexAttributes.cpp VertexArray.cpp Texture.cpp Window.cpp PixelBufferObject.cpp PixelBufferObject.cpp PixelMap.cpp Renderer.cpp PixelMapBuilder.cpp Engine.cpp)
add_library(${PROJECT_NAME}_OpenGL STATIC ${OPENGL_SOURCES})
target_include_directories(${PROJECT_NAME}_OpenGL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME}_OpenGL PRIVATE ../Utilities)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(${PROJECT_NAME}_OpenGL PUBLIC glfw OpenGL::GL GLEW::GLEW)
#target_include_directories(${PROJECT_NAME}_OpenGL PUBLIC ${glfw3_INCLUDE_DIRS})
#target_include_directories(${PROJECT_NAME}_OpenGL PUBLIC ${GLEW_INCLUDE_DIRS})
