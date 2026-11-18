cmake_minimum_required(VERSION 4.3)
project(SDL_ImGui_Template)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/imgui)

file(GLOB_RECURSE HEADERS src/*.h)
file(GLOB_RECURSE SRC src/*.cpp)

add_executable(
        SDL_ImGui_Template
        ${HEADERS}
        ${SRC}
)

target_link_libraries(
        SDL_ImGui_Template
        PRIVATE
        SDL3::SDL3
        ImGui
)

target_include_directories(
        SDL_ImGui_Template
        PRIVATE
        external/SDL/include
        external/imgui/
)
