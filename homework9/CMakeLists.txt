cmake_minimum_required( VERSION 3.12 )
project( fibtask VERSION 1.0 )

add_executable( fibtask fibtask.cxx )

find_package( OpenMP REQUIRED )

target_link_libraries( fibtask PUBLIC OpenMP::OpenMP_CXX )
