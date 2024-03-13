cmake_minimum_required(VERSION 3.26)
project(PacManGame)

set(CMAKE_CXX_STANDARD 17)

add_executable(PacManGame main.cpp
        Labyrinth.h
        Labyrinth.cpp
        Directions.h
        Resources.cpp
        Resources.h)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:\\programming\\cpp\\lib\\sfml\\SFML-2.6.1\\lib\\cmake\\SFML")
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
include_directories(C:\\programming\\cpp\\lib\\sfml\\SFML-2.6.1\\include\\SFML)
include_directories(plugins, labyrinth)
if(SFML_FOUND)
    message(STATUS "SFML found")
    target_link_libraries(PacManGame sfml-system sfml-window sfml-graphics sfml-audio)
else()
    message(FATAL_ERROR "SFML not found")
endif()