cmake_minimum_required( VERSION 3.12 )
project( evenodd VERSION 1.0 )

find_package( MPI REQUIRED )
include_directories( ${MPI_INCLUDE_PATH} )

add_executable( evenodd evenodd.cxx )
target_link_libraries( evenodd ${MPI_LIBRARIES} )
