cmake_minimum_required(VERSION 3.14.4)

add_executable( part_01_generic_programming_c_qsort ${CMAKE_CURRENT_LIST_DIR}/main_qsort.c ${CMAKE_CURRENT_LIST_DIR}/common_constants.h )
set_target_properties( part_01_generic_programming_c_qsort PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED TRUE )

add_executable( part_01_generic_programming_c_manual_sort ${CMAKE_CURRENT_LIST_DIR}/main_manual_sort.c ${CMAKE_CURRENT_LIST_DIR}/common_constants.h )
set_target_properties( part_01_generic_programming_c_manual_sort PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED TRUE )

add_executable( part_01_generic_programming_cpp_std_sort ${CMAKE_CURRENT_LIST_DIR}/main_std_sort.cpp ${CMAKE_CURRENT_LIST_DIR}/common_constants.h )
set_target_properties( part_01_generic_programming_cpp_std_sort PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED TRUE )