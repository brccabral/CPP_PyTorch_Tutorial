# Images Dataset


- Download `libtorch` : PyTorch C++ library C++ ABI  
    - I downloaded CPU version 1.13.0, GPU is 1.8 GB compacted. Also, to use GPU need to install CUDA libs 7 GB.  
    - https://pytorch.org/get-started/locally/  
    - libtorch-cxx11-abi-shared-with-deps-1.13.0+cpu.zip  
    - do NOT download the "pre-cxx11 ABI"  
    - the CXX_FLAGS needs to have "-D_GLIBCXX_USE_CXX11_ABI=1", not 0  
- Download OpenCV and compile. Don't need to install, but you can  
    - I downloaded 4.6.0  
    - I had to install some packages  

    ```shell
    apt install libgstreamer1.0-dev
    apt install libgstreamer-plugins-base1.0-dev
    ```
    - https://docs.opencv.org/4.6.0/d7/d9f/tutorial_linux_install.html  
    ```shell
    # Install minimal prerequisites (Ubuntu 18.04 as reference)
    sudo apt update && sudo apt install -y cmake g++ wget unzip
    # Download and unpack sources
    wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
    unzip opencv.zip
    # Create build directory
    mkdir -p build_opencv && cd build_opencv
    # Configure
    cmake  ../opencv-4.x
    # Build
    cmake --build .
    ```
- Download the dataset. A dataset containing images of Cats and Dogs can be found online.
    - Folder structure:
        - `dataset/test/cats`
        - `dataset/test/dogs`
        - `dataset/train/cats`
        - `dataset/train/dogs`
- Run `cmake` with the correct path to `libtorch` and `opencv`. Or set `CMAKE_PREFIX_PATH` in the CMakeLists.txt.

    ```shell
    mkdir -p build
    cd build
    cmake -DCMAKE_PREFIX_PATH="../libtorch;../build_opencv" ..
    make -j16
    ```
- Run `./main` passing the path to dataset root folder  

    ```shell
    ./main ../../dataset
    ```