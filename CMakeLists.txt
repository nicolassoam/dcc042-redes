cmake_minimum_required(VERSION 3.10)
project(REDES)

# include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SOURCES "*.cpp")
add_library(library ${SOURCES})

# configure_file(${PROJECT_SOURCE_DIR}/include/config.h.in ${PROJECT_SOURCE_DIR}/include/config.h)

add_executable(main ${SOURCES})

add_compile_options(-std=c++20 -Ofast -fPIC -march=native)