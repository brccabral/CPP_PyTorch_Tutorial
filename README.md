
Tutorial from **Alan Tessier** [Getting Started with Pytorch C++](https://www.youtube.com/watch?v=IOv9X5q9lf0&list=PLZAGo22la5t4UWx37MQDpXPFX3rTOGO3k)

- Download `libtorch` : PyTorch C++ library C++ ABI
    - I downloaded CPU version 1.13.0, GPU is 1.8 GB compacted. Also, to use GPU need to install CUDA libs 7 GB.
    - https://pytorch.org/get-started/locally/
    - libtorch-cxx11-abi-shared-with-deps-1.13.0+cpu.zip
    - do NOT download the "pre-cxx11 ABI"
    - the CXX_FLAGS needs to have "-D_GLIBCXX_USE_CXX11_ABI=1", not 0
    - Unzip to this workspace (`./workspace/libtorch`), or somewhere in your path (`/usr/local` or `$HOME/.local`)
- Create a python venv and activate
- Install pytorch and numpy
    - `pip3 install torch torchvision torchaudio --extra-index-url https://download.pytorch.org/whl/cpu`
    - `pip install numpy`
- run `02_import_model/models.py` to create a custom model from python to be imported in C++
- also, run `torchvision_models.py` to create a `resnet18.pt` model
- another script to create a model `05_torchvision_helloworld/save_script_model.py`
- Download OpenCV and compile. Don't need to install on your system, but feel free to do it  
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
    cmake  -DCMAKE_INSTALL_PREFIX=$HOME/.local ../opencv-4.x
    ```
    - Compile will take some time
    ```shell
    # Build
    cmake --build .
    # or using make
    make -j16
    # install if needed
    make install
    # if installing at default location (/usr/local), need to use sudo
    sudo make install
    ```
- Download OpenCV models from **Alan Tessier** other project
    - https://github.com/alantess/vigilantV2
    - https://github.com/alantess/vigilantV2/raw/main/get_models.sh
- The `driving.mp4` video is in Lesson 2 of **Alan Tessier** repo
    - https://github.com/alantess/learntorch/tree/main/torchscript/L2/videos
- The cats/dogs dataset are from Lesson 3 of **Alan Tessier** repo, but they can be found online on other websites
    - https://github.com/alantess/learntorch/tree/main/torchscript/L3/dataset
    - the lesson 04 needs C++17
- Download torchVision, I downloaded v0.14.1
    - https://github.com/pytorch/vision
    - build and install on your system. Can be in `$HOME/.local`. I couldn't use it just from the build folder
    - to build, need to indicate `libtorch` location if it is not on your path
- create a build dir for each lesson, run cmake for each lesson indicating the installation path of each dependency, `libtorch`, `opencv` or `torchvision`
    ```shell
    mkdir build
    cd build
    cmake -DCMAKE_PREFIX_PATH="../libtorch;../build_opencv" ..
    ```
    - when building any project, use `make -j16` (`-j16` adds more threads to the compiler).
    - `make -j16` # or
    - `cmake --build . --config Release`
