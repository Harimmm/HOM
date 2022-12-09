cmake_minimum_required(VERSION 3.0)
project(Client)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        Network
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC 
        Network
        pthread
        boost_system
)