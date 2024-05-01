cmake_minimum_required( VERSION 3.12 )
project( raymarch VERSION 1.0 )

add_executable( raymarch main.cxx raymarch.h raymarch.cxx)

find_package( OpenMP REQUIRED )
target_link_libraries( raymarch PUBLIC OpenMP::OpenMP_CXX )
