cmake_minimum_required(VERSION 3.13)
project(OpenGLTest)

set(CMAKE_CXX_STANDARD 11)
set(glfw3_DIR /usr/lib/x86_64-linux-gnu/cmake/glfw3)


add_executable(OpenGLTest lab1.cpp
        Shader.cpp)




find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories($(GLEW_INCLUDE_DIRS))
    message("not found")
endif (GLEW_FOUND)


include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${glfw3_INCLUDE_DIRS}  ${glm_INCLUDE_DIRS}  glfw)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES}   ${glm_LIBRARY}  /usr/lib/x86_64-linux-gnu/libglfw.so.3.2 )