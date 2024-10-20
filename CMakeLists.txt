cmake_minimum_required(VERSION 3.26)

include(cmake/modules.cmake)
include(GitVersion)

project(dmon
    VERSION ${GIT_VERSION_ABBREV}
    DESCRIPTION "C++ library for building daemon processes"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS NO)

include(packages.cmake)

add_library(dmon "")
add_library(dmon::dmon ALIAS dmon)

target_sources(dmon PUBLIC FILE_SET HEADERS BASE_DIRS include)
target_link_libraries(dmon
    PUBLIC
        ext::ext
    PRIVATE
        timber::timber
)

add_subdirectory(include)
add_subdirectory(src)

include(Sanitizers)
enable_asan()

include(EasyInstall)
easy_install(TARGETS dmon DEPENDENCIES ext)

if(PROJECT_IS_TOP_LEVEL)
    add_custom_target(docker
        docker build --progress=plain --no-cache .
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        USES_TERMINAL
    )
endif()
