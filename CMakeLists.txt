cmake_minimum_required(VERSION 3.10)
project(GAME)

add_subdirectory(src)
file(COPY ${CMAKE_SOURCE_DIR}/sprites DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/font DESTINATION ${CMAKE_BINARY_DIR})
