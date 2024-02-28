cmake_minimum_required( VERSION 3.12 )
project( stridescatter VERSION 1.0 )

find_package( MPI REQUIRED )
include_directories( ${MPI_INCLUDE_PATH} )

add_executable( stridescatter stridescatter.cxx )
target_link_libraries( stridescatter ${MPI_LIBRARIES} )
