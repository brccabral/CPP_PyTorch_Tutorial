#include <iostream>
#include <memory>
#include <stdio.h>
// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
// Torch
#include <torch/script.h>
#include <torch/torch.h>

#define DEAFULT_HEIGHT 720
#define DEAFULT_WIDTH 1280
#define IMG_SIZE 512

// PROTOTYPES
cv::Mat frame_prediction(cv::Mat frame, torch::jit::Module model);
torch::jit::Module load_model(std::string model_name);

int main(int argc, char *argv[])
{
    // Set torch module
    torch::jit::script::Module module;
    // Open CV
    cv::VideoCapture cap;
    cv::Mat frame;
    cap.open("../videos/driving.mp4");

    if (!cap.isOpened())
    {
        std::cerr << "\nCannot open video" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Press spacebar to terminate" << std::endl;

    // Load Model
    try
    {
        module = load_model("quantized_lanesNet.pt");
    }
    catch (const c10::Error &e)
    {
        std::cerr << "Error: MODEL DID NOT LOAD" << std::endl;
    }
}

torch::jit::Module load_model(std::string model_name)
{
    std::string directory = "../models/" + model_name;
    torch::jit::Module module = torch::jit::load(directory);
    // module.to(torch::CUDA);
    module.eval();
    std::cout << "MODEL LOADED" << std::endl;
    return module;
}