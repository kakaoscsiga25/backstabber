cmake_minimum_required(VERSION 2.8.12)

project(backstabber)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -fPIC")

#find_package(Qt5Widgets REQUIRED)
#include_directories(${Qt5Widgets_INCLUDE_DIRS})

find_package(Qt5Core REQUIRED)



INCLUDE_DIRECTORIES(include)

file(GLOB backstabber_headers
    ${CMAKE_SOURCE_DIR}/include/*.h
    ${CMAKE_SOURCE_DIR}/include/*.hpp
    ${CMAKE_SOURCE_DIR}/include/cards/*.h
    )

ADD_LIBRARY(core STATIC
    src/deck.cpp
    src/fight.cpp
    src/game_controll.cpp
    src/game_state.cpp
    src/monster.cpp
    src/player.cpp

    ${backstabber_headers}
    )
target_link_libraries(core Qt5::Core)


add_executable(${PROJECT_NAME} "src/executables/main_demo.cpp")
target_link_libraries(${PROJECT_NAME} core)

add_executable(run_test "src/executables/test.cpp")
target_link_libraries(run_test core)
