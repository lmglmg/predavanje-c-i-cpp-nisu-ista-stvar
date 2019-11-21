cmake_minimum_required( VERSION 3.14.4 )

add_executable( test_03_sort ${CMAKE_CURRENT_LIST_DIR}/sort.cpp )

set_target_properties( test_03_sort PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED TRUE )