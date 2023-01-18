#pragma once

#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <torch/torch.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

namespace fs = std::filesystem;

struct CatDog : torch::data::datasets::Dataset<CatDog>
{
public:
    enum Mode
    {
        kTrain,
        kTest
    };
    explicit CatDog(const std::string &root, Mode mode = Mode::kTrain);

    // Retrieves the example at an index
    torch::data::Example<> get(size_t index) override;

    // Returns size of the dataset
    torch::optional<size_t> size() const override;

    // Return true if this is the training subset
    bool is_train() const noexcept;

    // Returns Images and Labels
    const torch::Tensor &images() const;
    const torch::Tensor &targets() const;

private:
    torch::Tensor images_;
    torch::Tensor targets_;
    Mode mode_;
};