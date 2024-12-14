cmake_minimum_required(VERSION 3.30)
project(Quick C)

set(CMAKE_C_STANDARD 11)

include(cmake/CPM.cmake)

CPMAddPackage(
        NAME raylib
        GITHUB_REPOSITORY raysan5/raylib
        GIT_TAG 5.5
)
CPMAddPackage(
        NAME cglm
        GITHUB_REPOSITORY recp/cglm
        GIT_TAG v0.9.4
)

# include assets
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# if files arent in assets any more remove from the binary dir too
file(GLOB_RECURSE ASSETS RELATIVE ${CMAKE_SOURCE_DIR} assets/*)

add_executable(Quick src/main.c
        src/engine/game.h
        src/engine/game.c
        src/engine/camera.h
        src/engine/camera.c
        src/engine/world.h
        src/engine/world.c
        src/engine/terrain.h
        src/engine/terrain.c
        src/engine/object.h
        src/engine/object.c
        src/engine/player.h
        src/engine/player.c)

target_link_libraries(Quick PUBLIC raylib cglm)