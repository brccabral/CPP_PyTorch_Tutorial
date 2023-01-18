#include <iostream>
#include <vector>
#include <torch/script.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Wrong number of arguments passed" << std::endl;
        return EXIT_FAILURE;
    }
    torch::jit::script::Module net = torch::jit::load(argv[1]); //"../../models/net.pt"
    torch::Tensor x = torch::randn({1, 100});

    std::vector<torch::jit::IValue> input;
    input.push_back(x);

    for (int i = 0; i < 10; i++)
    {
        auto out = net.forward(input);
        std::cout << out << std::endl;
        // std::cout << typeid(out).name() << std::endl;
    }
}