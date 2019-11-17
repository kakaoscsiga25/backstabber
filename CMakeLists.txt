cmake_minimum_required(VERSION 2.8.12)

project(backstabber)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall")

INCLUDE_DIRECTORIES(include)

file(GLOB backstabber_headers
    ${CMAKE_SOURCE_DIR}/include/*.h
    ${CMAKE_SOURCE_DIR}/include/*.hpp
    ${CMAKE_SOURCE_DIR}/include/cards/*.h
    )

ADD_LIBRARY(core STATIC
    src/deck.cpp
    src/game_controll.cpp
    src/player.cpp
    src/turn_controll.cpp

    ${backstabber_headers}
    )


add_executable(${PROJECT_NAME} "main_demo.cpp")
target_link_libraries(${PROJECT_NAME} core)
