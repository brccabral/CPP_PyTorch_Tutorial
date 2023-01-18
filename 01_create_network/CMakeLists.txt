cmake_minimum_required(VERSION 3.14)
project( CreateNetwork )
# set(CMAKE_PREFIX_PATH ../libtorch)
set(CMAKE_INSTALL_PREFIX /usr/local)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
message(STATUS "TORCH_LIBRARIES: ${TORCH_LIBRARIES}")

add_executable(main main.cpp
    network.h
    )
target_link_libraries(main "${TORCH_LIBRARIES}")
set_property(TARGET main PROPERTY CXX_STANDARD 17)
