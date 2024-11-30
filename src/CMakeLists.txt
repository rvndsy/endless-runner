set(LIBS
    Game
    Background
    Player
    Entity
)
set(INCLUDE
    ${CMAKE_SOURCE_DIR}/include
)
set(UNIX_INCLUDE
    "../linux/SFML-2.6.2/include/SFML/"
)

add_executable(main Main.cpp)

if(UNIX)
    target_include_directories(main PRIVATE ${UNIX_INCLUDE})
endif()
target_link_libraries(main PRIVATE sfml-graphics sfml-window sfml-system)

target_include_directories(main PRIVATE ${INCLUDE})
foreach(lib IN LISTS LIBS)
    add_library(${lib} STATIC "${lib}.cpp")
endforeach()
target_link_libraries(main PRIVATE ${LIBS})

#g++ main.o -o sfml-app -L"linux/SFML-2.6.2/lib" -lsfml-graphics -lsfml-window -lsfml-system
