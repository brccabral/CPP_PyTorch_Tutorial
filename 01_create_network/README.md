# Create your own Network

- Download `libtorch` : PyTorch C++ library C++ ABI
    - I downloaded CPU version 1.13.0, GPU is 1.8 GB compacted. Also, to use GPU need to install CUDA libs 7 GB.
    - https://pytorch.org/get-started/locally/
    - libtorch-cxx11-abi-shared-with-deps-1.13.0+cpu.zip
    - do NOT download the "pre-cxx11 ABI"
    - the CXX_FLAGS needs to have "-D_GLIBCXX_USE_CXX11_ABI=1", not 0
- Run `cmake` with the correct path to `libtorch`  

    ```shell
    mkdir -p build
    cd build
    cmake -DCMAKE_PREFIX_PATH=../libtorch ..
    make -j16
    ./main
    ```
- Or set `CMAKE_PREFIX_PATH` in the CMakeLists.txt