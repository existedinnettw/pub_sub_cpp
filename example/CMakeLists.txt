

add_executable(example example_usage.cpp)

target_include_directories(example PRIVATE .)
target_link_libraries(example PRIVATE pub_sub)