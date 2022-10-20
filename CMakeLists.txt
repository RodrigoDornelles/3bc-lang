# CMAKE CONFIGS
cmake_minimum_required(VERSION 3.20)

# PROJECT CONFGIS
project(3BC)
set(CMAKE_C_STANDARD 90)
add_executable (3bc programs/interpreter.c)

if (UNIX)
target_link_libraries(3bc m)
endif (UNIX)

# TOOLS FOR CONTAINTER DEVELOPMENT
option(DOCKER_ALL    "use docker in all targets" OFF)
option(DOCKER_CC     "use docker for c compiler" OFF)
find_program(CMAKE_DOCKER docker)
set(CMAKE_DOCKER_DIR "-v ${CMAKE_SOURCE_DIR}:${CMAKE_SOURCE_DIR} -w ${CMAKE_SOURCE_DIR}")
set(CMAKE_DOCKER_CMD "${CMAKE_DOCKER} run ${CMAKE_DOCKER_DIR}")
set(CMAKE_DOCKER_EXE "${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles")

if(DOCKER_ALL)
set(WEB_DOCKER ON)
set(CC_DOCKER ON)
endif(DOCKER_ALL)

if(CC_DOCKER)
    set(CMAKE_DOCKER_CMD_CC "gcc")
    set(CMAKE_DOCKER_IMG_CC "gcc:11.3")
    set(CMAKE_C_COMPILER "${CMAKE_DOCKER_EXE}/docker_cc")
    set(CMAKE_C_COMPILER_VERSION "${CMAKE_DOCKER_IMG_CC}")
    file(
        GENERATE OUTPUT "${CMAKE_C_COMPILER}"
        CONTENT "${CMAKE_DOCKER_CMD} -it ${CMAKE_DOCKER_IMG_CC} ${CMAKE_DOCKER_CMD_CC} $@"
        FILE_PERMISSIONS OWNER_READ OWNER_EXECUTE
    )
endif(CC_DOCKER)

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
