cmake_minimum_required(VERSION 4.0)
project(CURL_PING_PATCH)

set(CMAKE_CXX_STANDARD 23)

find_library(nghttp2_LIBRARY NAMES nghttp2)

add_subdirectory(third_party/curl)

add_executable(main main.cpp)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)
target_compile_options(main PRIVATE -fsanitize=address)
target_link_options(main PRIVATE -fsanitize=address)

target_link_libraries(main
    PRIVATE CURL::libcurl
    PUBLIC nghttp2)
