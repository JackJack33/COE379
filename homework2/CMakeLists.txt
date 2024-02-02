cmake_minimum_required( VERSION 3.12 )
project( jordan VERSION 1.0 )

find_package( MPI REQUIRED )
include_directories( ${MPI_INCLUDE_PATH} )

add_executable( jordan jordan.cxx )
target_link_libraries( jordan ${MPI_LIBRARIES} )
