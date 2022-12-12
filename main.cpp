#include <iostream>
#include <torch/script.h>

int main()
{
    torch::jit::script::Module net = torch::jit::load("../models/net.pt");
    torch::Tensor x = torch::randn({1, 100});
    std::cout << x << std::endl;
}