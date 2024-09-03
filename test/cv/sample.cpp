#include <iostream>
#include <opencv2/opencv.hpp>

int main(){
    cv::Mat random_matrix(28, 28, CV_8UC3);
    cv::RNG rng;
    rng.fill(random_matrix, cv::RNG::UNIFORM, 0, 255);

    std::cout << "cv sample" << std::endl;
    std::cout << random_matrix << std::endl;

    return 0;
}