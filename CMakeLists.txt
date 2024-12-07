cmake_minimum_required(VERSION 3.0)

project(cpp_perf_opti VERSION 1.0.0)

message(STATUS Build Type:  ${CMAKE_BUILD_TYPE})

include_directories(./include)

add_subdirectory(./src)

aux_source_directory(. SRC_DIR)

add_executable(cpp_perf_opti ${SRC_DIR})

target_link_libraries(cpp_perf_opti
    utils
)

