cmake_minimum_required(VERSION 3.15)

project(pub_sub_cpp)

add_library(pub_sub INTERFACE)
target_include_directories(pub_sub INTERFACE include)
target_link_libraries(pub_sub INTERFACE atomic)

add_subdirectory(example)
