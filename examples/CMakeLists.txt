cmake_minimum_required(VERSION 3.14.4)

add_subdirectory( ${CMAKE_CURRENT_LIST_DIR}/part_00_types )
add_subdirectory( ${CMAKE_CURRENT_LIST_DIR}/part_01_generic_programming )
add_subdirectory( ${CMAKE_CURRENT_LIST_DIR}/part_02_memory )

add_subdirectory( ${CMAKE_CURRENT_LIST_DIR}/legacy/01_sort )
add_subdirectory( ${CMAKE_CURRENT_LIST_DIR}/legacy/02_sort )
add_subdirectory( ${CMAKE_CURRENT_LIST_DIR}/legacy/03_sort )