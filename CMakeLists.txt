cmake_minimum_required(VERSION 3.25)
project(modules_exp CXX)

set(CMAKE_CXX_STANDARD 20)

include(modules.cmake)

set(GAME_NAME "foo")

if (NINTENDO_DS)
    function(platform_defaults target)
        target_link_libraries(${target} filesystem)
        target_link_libraries(${target} slim)
        target_link_libraries(${target} nds9)
        target_compile_definitions(${target} PRIVATE -D__16M__)

        target_compile_definitions(${target} PRIVATE -DGAME_NAME=\"${GAME_NAME}\")
    endfunction()
elseif (NINTENDO_GBA)
    function(platform_defaults target)
        target_compile_definitions(${target} PRIVATE -DGAME_NAME=\"${GAME_NAME}\")
    endfunction()
elseif (WIN32)
    function(platform_defaults target)
        target_compile_definitions(${target} PRIVATE -DGAME_NAME=\"${GAME_NAME}\")
    endfunction()
elseif (UNIX)
    function(platform_defaults target)
        target_compile_definitions(${target} PRIVATE -DGAME_NAME=\"${GAME_NAME}\")
    endfunction()
else()
    function(platform_defaults target)
        target_compile_definitions(${target} PRIVATE -DGAME_NAME=\"${GAME_NAME}\")
    endfunction()
endif()

include_directories(Headers)

add_module_library(modules_exp_module test.cpp)
platform_defaults(modules_exp_module)

add_module_library(Commonlib Source/Commonlib/Common.cpp)
platform_defaults(Commonlib)

add_executable(modules_exp_exe main.cpp )
platform_defaults(modules_exp_exe)
target_link_libraries(modules_exp_exe modules_exp_module Commonlib)

if (NINTENDO_GBA)
    gba_create_rom(modules_exp_exe)
endif()

if (NINTENDO_DS)
    nds_create_rom(modules_exp_exe)
endif()
