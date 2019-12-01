cmake_minimum_required( VERSION 3.14.4 )

add_executable( part_02_memory_c ${CMAKE_CURRENT_LIST_DIR}/main.c ${CMAKE_CURRENT_LIST_DIR}/lookup_table.h)
set_target_properties( part_02_memory_c PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED TRUE )

add_executable( part_02_memory_cpp ${CMAKE_CURRENT_LIST_DIR}/main.cpp ${CMAKE_CURRENT_LIST_DIR}/lookup_table.h)
set_target_properties( part_02_memory_cpp PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED TRUE )