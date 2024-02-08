cmake_minimum_required( VERSION 3.12 )
project( scangather VERSION 1.0 )

find_package( MPI REQUIRED )
include_directories( ${MPI_INCLUDE_PATH} )

add_executable( scangather scangather.cxx )
target_link_libraries( scangather ${MPI_LIBRARIES} )
