cmake_minimum_required(VERSION 3.1)

project(main)

set(CMAKE_PREFIX_PATH /media/brccabral/Data/CPP_Projects/CPP_PyTorch_Tutorial/libtorch)

find_package(Torch REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(main main.cpp)

target_link_libraries(main "${TORCH_LIBRARIES}")

set_property(TARGET main PROPERTY CXX_STANDARD 14)