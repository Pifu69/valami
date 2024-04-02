cmake_minimum_required(VERSION 3.26)
project(Genetika)

set(CMAKE_CXX_STANDARD 17)

add_executable(Genetika
        allapotgep.cpp
        allapotgep.h
        genetika_teszt.cpp
        gtest_lite.h
        memtrace.h
        memtrace.cpp
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME}
            PRIVATE
            -fsanitize=address
            -fno-omit-frame-pointer
    )
    target_link_options(${PROJECT_NAME}
            PRIVATE
            -fsanitize=address
    )
endif()