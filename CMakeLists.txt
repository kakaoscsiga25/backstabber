cmake_minimum_required(VERSION 2.8.12)

project(backstabber)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -fPIC")

#find_package(Qt5Widgets REQUIRED)
#include_directories(${Qt5Widgets_INCLUDE_DIRS})

find_package(Qt5Core REQUIRED)

find_package(Qt5Widgets)


include_directories(include)

file(GLOB backstabber_headers
    ${CMAKE_SOURCE_DIR}/include/*.h
    ${CMAKE_SOURCE_DIR}/include/*.hpp
    ${CMAKE_SOURCE_DIR}/include/cards/*.h
    )

add_library(core STATIC
    src/deck.cpp
    src/fight.cpp
    src/game_controll.cpp
    src/game_state.cpp
    src/monster.cpp
    src/player.cpp

    ${backstabber_headers}
    )
target_link_libraries(core Qt5::Core)


set(CMAKE_AUTOUIC ON)

file(GLOB gui_headers
    ${CMAKE_SOURCE_DIR}/include/gui/*.hpp
    ${CMAKE_SOURCE_DIR}/include/gui/*.h
    )
file(GLOB gui_uis
    ${CMAKE_SOURCE_DIR}/src/gui/*.ui
    )
add_library(gui STATIC
    src/gui/main_window.cpp

    ${gui_headers}
    ${gui_uis}
    )
target_link_libraries(gui Qt5::Widgets)


add_executable(${PROJECT_NAME} "src/executables/main_demo.cpp")
target_link_libraries(${PROJECT_NAME} core gui)

add_executable(run_test "src/executables/test.cpp")
target_link_libraries(run_test core)
