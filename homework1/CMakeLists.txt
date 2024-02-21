cmake_minimum_required( VERSION 3.12 )
project( commrank VERSION 1.0 )

find_package( MPI REQUIRED )
include_directories( ${MPI_INCLUDE_PATH} )

add_executable( commrank commrank.cxx )
target_link_libraries( commrank ${MPI_LIBRARIES} )
