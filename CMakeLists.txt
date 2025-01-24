cmake_minimum_required(VERSION 3.29)
project(doom-fire)

set(CMAKE_CXX_STANDARD 23)

find_package(SDL3 REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)
set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/Application.cpp
    ${PROJECT_SOURCE_DIR}/src/Window.cpp
    ${PROJECT_SOURCE_DIR}/src/Fire.cpp
)
set(MAIN
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)

add_executable(${PROJECT_NAME} ${MAIN} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3-shared)