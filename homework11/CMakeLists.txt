cmake_minimum_required( VERSION 3.12 )
project( vectorsum VERSION 1.0 )

add_executable( vectorsum vectorsum.cxx )

find_package(OpenMP REQUIRED)

target_link_libraries(vectorsum PUBLIC OpenMP::OpenMP_CXX)
