# Import a script Model

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
- Run `models.py` to create a scripted model and save it to the path passed as parameter
    ```shell
    python models.py ../models/net.pt
    ```
- Download `libtorch` : PyTorch C++ library C++ ABI
    - I downloaded CPU version 1.13.0, GPU is 1.8 GB compacted. Also, to use GPU need to install CUDA libs 7 GB.
    - https://pytorch.org/get-started/locally/
    - libtorch-cxx11-abi-shared-with-deps-1.13.0+cpu.zip
    - do NOT download the "pre-cxx11 ABI"
    - the CXX_FLAGS needs to have "-D_GLIBCXX_USE_CXX11_ABI=1", not 0
- Run `cmake` with the correct path to `libtorch`. Or set `CMAKE_PREFIX_PATH` in the CMakeLists.txt.

    ```shell
    mkdir -p build
    cd build
    cmake -DCMAKE_PREFIX_PATH=../libtorch ..
    make -j16
    ```
- Run `./main` passing the path to the model created above    

    ```shell
    ./main ../../models/net.pt
    ```