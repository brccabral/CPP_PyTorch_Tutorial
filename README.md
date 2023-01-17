
Tutorial from **Alan Tessier** [Getting Started with Pytorch C++](https://www.youtube.com/watch?v=IOv9X5q9lf0&list=PLZAGo22la5t4UWx37MQDpXPFX3rTOGO3k)

- Download PyTorch C++ library C++ ABI (I downloaded CPU version 1.13.0, GPU is 1.8 GB compacted)
    - https://pytorch.org/get-started/locally/
    - do NOT download the "pre-cxx11 ABI"
    - the CXX_FLAGS needs to have "-D_GLIBCXX_USE_CXX11_ABI=1", not 0
- Unzip
    - ./workspace/libtorch
- create build dir
    - `mkdir -p build` # ./workspace/build
- cd into build and run cmake
    - `cd build`
    - `cmake ..` # with two dots
- compile
    - `make` # or
    - `cmake --build . --config Release`
- Create a python venv and activate
- Install pytorch and numpy
    - `pip3 install torch torchvision torchaudio --extra-index-url https://download.pytorch.org/whl/cpu`
    - `pip install numpy`
- run models.py to create a model from python to be imported in C++
- Install OpenCV
    - https://docs.opencv.org/4.6.0/d7/d9f/tutorial_linux_install.html
    - Download .tar.gz
    - Unzip (inside the project or outside, remember the location $opencv=$workspace/opencv-4.x)
    - create a build cv directory $build_opencv=$workspace/build_opencv
    - enter $build_opencv, `cd $build_opencv`
    - I had to install some packages
    ```shell
    apt install libgstreamer1.0-dev
    apt install libgstreamer-plugins-base1.0-dev
    ```
    - `cmake $opencv` # or `cmake ../opencv-4.x`
    - build `cmake --build .`
    - this will take a long time
- create a build dir for this project, run cmake for this project
    ```shell
    mkdir build
    cd build
    cmake ..
    ```
    - at the end it will show the values of `$OpenCV_INCLUDE_DIRS`. It is a long list, but remind to include all these directories in your project, as well as `$OpenCV_LIBS`.
    - when building this project, use `make -j16`.

- Download OpenCV models from **Alan Tessier** other project
    - https://github.com/alantess/vigilantV2
    - https://github.com/alantess/vigilantV2/raw/main/get_models.sh
- The video is in Lesson 2 of **Alan Tessier** repo
    - https://github.com/alantess/learntorch/tree/main/torchscript/L2/videos
