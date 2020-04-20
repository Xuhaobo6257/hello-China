cmake_minimum_required(VERSION 2.7)
# The project name
project(Interstellar)

# Set C++ standard to c++11
set(CMAKE_CXX_STANDARD 11)

include_directories(.)

# Find OpenGL package
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLUT_INCLUDE_DIRS})

# Add all your .h/.cpp files here (just after "main.cpp",
# separated by a whiespace)
# Note: If you have a directory outside your code file,
# add the directory name, e.g: Graph/Figure.h
add_executable(Interstellar main.cpp)

# Link OpenGL library to the project.
# Note: This line must be after the "add_executable()"
target_link_libraries(Interstellar ${OPENGL_LIBRARY} ${GLUT_LIBRARY})
