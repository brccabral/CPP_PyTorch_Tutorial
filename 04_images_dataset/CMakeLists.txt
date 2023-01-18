cmake_minimum_required(VERSION 3.14)
project( ImagesDataset )
# set(CMAKE_PREFIX_PATH ../libtorch;../build_opencv)
set(CMAKE_INSTALL_PREFIX /usr/local)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(OpenCV REQUIRED)
find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "    OpenCV_LIB_COMPONENTS: ${OpenCV_LIB_COMPONENTS}")
message(STATUS "OPENCV_CXX_FLAGS: ${OPENCV_CXX_FLAGS}")
message(STATUS "TORCH_CXX_FLAGS: ${TORCH_CXX_FLAGS}")
message(STATUS "TORCH_LIBRARIES: ${TORCH_LIBRARIES}")

include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( "include" )
add_executable(main main.cpp
    include/dataset.h
    src/dataset.cpp
    )
target_link_libraries(main ${OpenCV_LIBS})
target_link_libraries(main "${TORCH_LIBRARIES}")
set_property(TARGET main PROPERTY CXX_STANDARD 17)
