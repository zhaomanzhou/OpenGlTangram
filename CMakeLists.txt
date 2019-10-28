cmake_minimum_required(VERSION 3.13)
project(lab1)

set(CMAKE_CXX_STANDARD 11)


add_executable(lab1 main.cpp)




find_package(OpenGL REQUIRED)


find_package(GLEW REQUIRED)



include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS}

        /usr/local/Cellar/glfw/3.3/include/
        /usr/local/Cellar/glew/2.1.0/include/
        /usr/local/Cellar/glm/0.9.9.5/include/
        )

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES}
        /usr/local/Cellar/glfw/3.3/lib/libglfw.3.dylib
        /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.0.dylib )
