cmake_minimum_required(VERSION 3.21.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(GrafxEngine VERSION 1.0)

find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
link_libraries(${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLUT_LIBRARY} )

add_executable(GrafxEngine main.cpp)