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

add_library(Game STATIC Game.cpp)
add_library(Physics STATIC Physics.cpp)
add_library(Background STATIC Background.cpp)
add_library(CrashedCar STATIC CrashedCar.cpp)
add_library(Bird STATIC Bird.cpp)
add_library(Wall STATIC Wall.cpp)
add_library(Player STATIC Player.cpp)
add_library(Enemy STATIC Enemy.cpp)

target_link_libraries(main PRIVATE Game Physics Background CrashedCar Bird Player Enemy Wall)

#g++ main.o -o sfml-app -L"linux/SFML-2.6.2/lib" -lsfml-graphics -lsfml-window -lsfml-system
