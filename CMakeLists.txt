# CMAKE CONFIGS
cmake_minimum_required(VERSION 3.16)

# PROJECT CONFGIS
project(3BC)
set(CMAKE_C_STANDARD 90)
add_executable (3bc programs/interpreter.c)

if (UNIX)
target_link_libraries(3bc m)
endif (UNIX)

# TOOLS FOR CONTAINTER DEVELOPMENT
option(DOCKER_ALL    "use docker in all targets" 0)
set(CMAKE_DOCKER_DIR "-v" "$(pwd):/app" "-w" "/app")
find_program(CMAKE_DOCKER docker)
if(DOCKER_ALL)
set(WEB_DOCKER 1)
endif(DOCKER_ALL)

# TOOLS FOR WEB DEVELOPMENT
option(WEB_TOOLS "official website tools (jekyll)" 0)
option(WEB_DOCKER "official website tools (jekyll)")

if(WEB_TOOLS)
    if(WEB_DOCKER)
    set(CMAKE_JEKYLL
        "${CMAKE_DOCKER}" "run"
        "${CMAKE_DOCKER_DIR}"
        "-it" "jekyll/jekyll"
        "jekyll"
    )
    else()
    find_program(CMAKE_JEKYLL jekyll REQUIRED)
    endif(WEB_DOCKER)

    add_custom_target(docs
        COMMAND cd docs && ${CMAKE_JEKYLL} build
    )
endif(WEB_TOOLS)
