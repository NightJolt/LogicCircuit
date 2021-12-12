cmake_minimum_required(VERSION 3.22.0)

set(PROJECT_NAME LogicCircuit)
set(CMAKE_CXX_STANDARD 20)

if (UNIX)

    # NEEDS UPDATE!

elseif (WIN32)

    project(${PROJECT_NAME} LANGUAGES CXX)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

    include_directories(header)
    include_directories(source)

    file (
        GLOB_RECURSE SOURCE_FILES

        main.cpp

        header/*.h
        source/*.cpp
    )

    add_executable(${PROJECT_NAME} ${SOURCE_FILES})

    add_subdirectory(FunEngine2D)

elseif (APPLE)

    # ewww

endif()