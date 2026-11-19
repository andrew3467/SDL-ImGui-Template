cmake_minimum_required(VERSION 4.3)
project(SDL_ImGui_Template)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/SDL ${CMAKE_BINARY_DIR}/SDL)
add_subdirectory(external/imgui ${CMAKE_BINARY_DIR}/ImGui)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(
        SDL_ImGui_Template
        ${HEADERS}
        ${SRC}
)

target_link_libraries(
        SDL_ImGui_Template
        PUBLIC
        SDL3::SDL3
        ImGui
)

target_include_directories(
        SDL_ImGui_Template
        PUBLIC
        external/SDL/include
        external/imgui
)

add_custom_command(TARGET SDL_ImGui_Template POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3>
        $<TARGET_FILE_DIR:SDL_ImGui_Template>
)
