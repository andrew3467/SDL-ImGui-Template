cmake_minimum_required(VERSION 4.3)
project(PLACEHOLDER_PROJECT)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(SDL_ImGui_Template)

file(GLOB_RECURSE HEADERS src/*.h)
file(GLOB_RECURSE SRC src/*.cpp)

add_executable(
        PLACEHOLDER_PROJECT
        ${HEADERS}
        ${SRC}
)

target_link_libraries(
        PLACEHOLDER_PROJECT
        PRIVATE
        SDL_ImGui_Template
)

target_include_directories(
        PLACEHOLDER_PROJECT
        PRIVATE
        SDL_ImGui_Template
        src
)
