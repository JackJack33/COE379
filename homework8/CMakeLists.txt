cmake_minimum_required( VERSION 3.12 )
project( jacobi VERSION 1.0 )

add_executable( jacobi jacobi.cxx )

find_package( OpenMP REQUIRED )

target_link_libraries( jacobi PUBLIC OpenMP::OpenMP_CXX )
