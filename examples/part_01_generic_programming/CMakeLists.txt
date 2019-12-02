cmake_minimum_required(VERSION 3.14.4)

add_executable( part_01_generic_programming_c ${CMAKE_CURRENT_LIST_DIR}/main.c )
set_target_properties( part_01_generic_programming_c PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED TRUE )

add_executable( part_01_generic_programming_cpp ${CMAKE_CURRENT_LIST_DIR}/main.cpp )
set_target_properties( part_01_generic_programming_cpp PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED TRUE )