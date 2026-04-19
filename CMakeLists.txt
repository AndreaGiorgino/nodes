cmake_minimum_required(VERSION 3.11)

project(nodes
    VERSION 1.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Target executable

file(GLOB_RECURSE SOURCE_FILES
    CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx)

add_executable(${PROJECT_NAME}
    ${SOURCE_FILES})

target_compile_options(${PROJECT_NAME}
    PRIVATE -Wextra -Wall -pedantic)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
