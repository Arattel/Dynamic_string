cmake_minimum_required(VERSION 3.5)
project(prog2 C)

set(CMAKE_C_STANDARD 99)
# set(bin_dir bin/)

link_directories(../library/bin)
add_library(my_string SHARED IMPORTED)

add_executable(prog2 prog2.c)
target_include_directories(prog2 PUBLIC ../library)
target_link_libraries(prog2 _my_string)

file(MAKE_DIRECTORY bin/)

add_custom_command(TARGET prog2 POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy prog2 ../bin/)