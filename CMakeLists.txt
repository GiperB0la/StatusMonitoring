cmake_minimum_required(VERSION 3.10)
project(system_monitor)

set(CMAKE_CXX_STANDARD 17)

find_package(nlohmann_json REQUIRED)

set(SOURCES
    Main.cpp
    src/Config.cpp
    src/CPUMetric.cpp
    src/MemoryMetric.cpp
    src/StatusMonitoring.cpp
)

add_executable(system_monitor ${SOURCES})

target_include_directories(system_monitor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(system_monitor PRIVATE nlohmann_json::nlohmann_json)