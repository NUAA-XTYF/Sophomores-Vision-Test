cmake_minimum_required(VERSION 3.16.3)

project(vision_final_test)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE Release)
message(STATUS "--------------------CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}--------------------")

find_package(OpenCV REQUIRED)
find_package(fmt REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(spdlog REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(nlohmann_json REQUIRED)

if(NOT DEFINED OpenVINO_DIR)
    set(OpenVINO_DIR "/opt/intel/openvino_2024.6.0/runtime/cmake/")
endif()
find_package(OpenVINO REQUIRED)
if(NOT DEFINED FASTCDR_DIR)
    set(FASTCDR_DIR "/opt/ros/humble/lib/cmake/fastcdr/")
endif()
find_package(fastcdr QUIET)

include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${FASTCDR_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(tools)
add_subdirectory(io)
add_subdirectory(tasks/auto_aim)
add_subdirectory(tasks/omniperception)

####################src###################
# List of source files
set(targets 
    standard_test
)

foreach(target ${targets})
    add_executable(${target} src/${target}.cpp)
    target_link_libraries(${target} ${OpenCV_LIBS} fmt::fmt yaml-cpp auto_aim tools io)
endforeach()




