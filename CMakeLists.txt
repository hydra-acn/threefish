project(threefish C)

cmake_minimum_required (VERSION 2.8.12)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include)

set(threefish_src
    src/threefish1024.c
)

add_library(threefish STATIC ${threefish_src})
install(TARGETS threefish ARCHIVE DESTINATION lib)

