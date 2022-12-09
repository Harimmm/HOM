cmake_minimum_required(VERSION 3.0)
project(Network)

set(CMAKE_CXX_STANDARD 20)

#file(GLOB SOURCES src/*.cpp src/*/* src/*/*/*)
file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        ${Boost_INCLUDE_DIRS}
    PRIVATE
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
            ${Boost_LIBRARIES}
)   