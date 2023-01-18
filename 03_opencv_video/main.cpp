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
    if (argc != 3)
    {
        std::cerr << "Wrong number of arguments passed" << std::endl;
        return EXIT_FAILURE;
    }
    // Set torch module
    torch::jit::script::Module module;
    // Open CV
    cv::VideoCapture cap;
    cv::Mat frame;
    cap.open(argv[1]); // "../../videos/driving.mp4"

    if (!cap.isOpened())
    {
        std::cerr << "\nCannot open video" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Press spacebar to terminate" << std::endl;

    // Load Model
    try
    {
        module = load_model(argv[2]); // "../../models/quantized_lanesNet.pt"
    }
    catch (const c10::Error &e)
    {
        std::cerr << "Error: MODEL DID NOT LOAD" << std::endl;
    }

    for (;;)
    {
        cap.read(frame);
        if (frame.empty())
        {
            std::cerr << "\nError: Blank Frame\n";
        }

        frame = frame_prediction(frame, module);

        cv::imshow("video", frame);
        if (cv::waitKey(1) >= 27)
        {
            break;
        }
    }
}

torch::jit::Module load_model(std::string model_path)
{
    torch::jit::Module module = torch::jit::load(model_path);
    //// module.to(torch::CUDA);
    module.eval();
    std::cout << "MODEL LOADED" << std::endl;
    return module;
}

cv::Mat frame_prediction(cv::Mat frame, torch::jit::Module model)
{
    // Needed for Overlay, layer on top of video frames
    // highlights road lanes with a blue shade
    double alpha = 0.4;
    double beta = (1 - alpha);
    cv::Mat frame_copy, dst;

    // Torch model input
    std::vector<torch::jit::IValue> input;

    // Mean and Stdev
    std::vector<double> mean = {0.406, 0.456, 0.485};  // in Python these values are reverse order
    std::vector<double> stdev = {0.225, 0.224, 0.229}; // in Python these values are reverse order

    cv::resize(frame, frame, cv::Size(IMG_SIZE, IMG_SIZE));
    frame_copy = frame;
    frame.convertTo(frame, CV_32FC3, 1.0f / 255.0f);

    // CV2 to Tensor
    torch::Tensor frame_tensor = torch::from_blob(frame.data, {1, IMG_SIZE, IMG_SIZE, 3});
    frame_tensor = frame_tensor.permute({0, 3, 1, 2}); // reshape tensor
    frame_tensor = torch::data::transforms::Normalize<>(mean, stdev)(frame_tensor);
    //// frame_tensor = frame_tensor.to(torch::CUDA);
    input.push_back(frame_tensor);

    // Forward pass
    //// auto pred = model.forward(input).toTensor().detach().to(torch::CUDA);
    auto pred = model.forward(input).toTensor().detach();
    pred = pred.mul(100).clamp(0.255).to(torch::kU8);

    // Tensor to CV2
    cv::Mat output_mat(cv::Size(IMG_SIZE, IMG_SIZE), CV_8UC1, pred.data_ptr());
    cv::cvtColor(output_mat, output_mat, cv::COLOR_GRAY2RGB);
    cv::applyColorMap(output_mat, output_mat, cv::COLORMAP_TWILIGHT_SHIFTED);

    // Overlay original frame and prediction
    cv::addWeighted(frame_copy, alpha, output_mat, beta, 0.0, dst);
    cv::resize(dst, dst, cv::Size(DEAFULT_WIDTH, DEAFULT_HEIGHT));
    return dst;
}