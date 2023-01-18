# TorchVision Hello-World

This hello-world just checks for TorchVision dependency, but the `main.cpp` doesn't use any of its features.

- Create a python venv and activate  

```shell
python -m venv .venv
source .venv/bin/activate
```
- Install pytorch  

```shell
pip install torch torchvision torchaudio --extra-index-url https://download.pytorch.org/whl/cpu
pip install numpy
```
- Run `save_script_model.py` to create a scripted model and save it to the path passed as parameter
    ```shell
    python save_script_model.py ../models/resnet18.pt
    ```
- Download `libtorch` : PyTorch C++ library C++ ABI  
    - I downloaded CPU version 1.13.0, GPU is 1.8 GB compacted. Also, to use GPU need to install CUDA libs 7 GB.  
    - https://pytorch.org/get-started/locally/  
    - libtorch-cxx11-abi-shared-with-deps-1.13.0+cpu.zip  
    - do NOT download the "pre-cxx11 ABI"  
    - the CXX_FLAGS needs to have "-D_GLIBCXX_USE_CXX11_ABI=1", not 0  
    - Unzip to this workspace (`./workspace/libtorch`), or somewhere in your path (`/usr/local` or `$HOME/.local`)
- Download torchVision, I downloaded v0.14.1
    - https://github.com/pytorch/vision
    - build and install on your system. Can be in `$HOME/.local`. I couldn't use it just from the build folder
    - to build, need to indicate `libtorch` location if it is not on your path
        ```shell
        wget -O vision-0.14.1.zip https://github.com/pytorch/vision/archive/refs/tags/v0.14.1.zip
        unzip vision-0.14.1.zip
        cd vision-0.14.1
        mkdir build
        cd build
        cmake -DCMAKE_INSTALL_PREFIX=$HOME/.local -DCMAKE_PREFIX_PATH="/path/to/libtorch" ..
        make -j16
        make install
        ```
- Run `cmake` with the correct path to `libtorch` and `torchVision`. Or set `CMAKE_PREFIX_PATH` in the CMakeLists.txt.

    ```shell
    mkdir -p build
    cd build
    cmake -DCMAKE_PREFIX_PATH="../libtorch;$HOME/.local" ..
    make -j16
    ```
- Run `./hello-world` passing the path to script model  

    ```shell
    ./hello-world ../../models/resnet18.pt
    ```