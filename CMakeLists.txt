cmake_minimum_required(VERSION 2.6)

project("Sokoban 3d" C)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLEE REQUIRED gl)
pkg_search_module(GLEE REQUIRED glee)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories("include")
include_directories(${GL_INCLUDE_DIRS})
include_directories(${GLEE_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})

add_executable(sokoban-3d
    "src/vec.c"
    "src/gl.c"
    "src/main.c"
)

target_link_libraries(sokoban-3d ${GL_LIBRARIES})
target_link_libraries(sokoban-3d ${GLEE_LIBRARIES})
target_link_libraries(sokoban-3d ${GLFW_LIBRARIES})
