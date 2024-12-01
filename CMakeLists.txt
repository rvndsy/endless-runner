cmake_minimum_required(VERSION 3.10)
project(GAME)

add_subdirectory(src)
file(COPY ${CMAKE_SOURCE_DIR}/sprites DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/font DESTINATION ${CMAKE_BINARY_DIR})

#if (UNIX)
#    set(LD_LIBRARY_PATH "./linux/SFML-2.6.2/lib")
#    #add_subdirectory(linux/SFML-2.6.2/include/SFML/)
#    #add_subdirectory(linux/SFML-2.6.2/include/SFML/)
#endif()

## Compile commands from SFML tutorial:
# g++ -c main.cpp -I"linux/SFML-2.6.2/include" &&
# g++ main.o -o sfml-app -L"linux/SFML-2.6.2/lib" -lsfml-graphics -lsfml-window -lsfml-system
# export LD_LIBRARY_PATH="linux/SFML-2.6.2/lib" && ./sfml-app
