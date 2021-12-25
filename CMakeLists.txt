cmake_minimum_required(VERSION 3.12...3.22)

project(
    "The Coding Train"
    LANGUAGES "C"
    VERSION "0.1.0"
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(PushDirectory)

function(coding_challenge TARGET_NAME)
    cmake_parse_arguments(PARSE_ARGV 0 "CC" "" "" "SOURCES;LIBS")
    push_directory_executable(
        TARGET_NAME "${TARGET_NAME}"
        SOURCE_FILES ${CC_SOURCES}
        LINKED_LIBRARIES "csfml-graphics" "csfml-window" "csfml-system"
                         ${CC_LIBS}
    )
endfunction(coding_challenge)

push_directory_library(
    TARGET_NAME "toolbox"
    SOURCE_FILES "math.c" "random.c" "util.c"
    INCLUDED_DIRECTORIES "toolbox/include"
    LINKED_LIBRARIES "m" "sodium"
)

coding_challenge(
    "c001_starfield"
    SOURCES "main.c" "star.c"
    LIBS "toolbox"
)
coding_challenge(
    "c003_snake"
    SOURCES "main.c" "food.c" "snake.c"
    LIBS "toolbox"
)
coding_challenge(
    "c004_purple_rain"
    SOURCES "drop.c" "main.c"
    LIBS "toolbox"
)
coding_challenge(
    "c005_space_invaders"
    SOURCES "main.c" "ship.c" "flower.c" "drop.c"
    LIBS "toolbox"
)
coding_challenge(
    "c010_maze_generator"
    SOURCES "main.c" "cell.c"
    LIBS "toolbox"
)
coding_challenge(
    "c030_phyllotaxis"
    SOURCES "main.c"
    LIBS "toolbox"
)
