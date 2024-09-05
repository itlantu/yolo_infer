#include "cv_test.h"

void sample_test(){
    cv::Mat random_matrix(28, 28, CV_8UC3);
    cv::RNG rng;
    rng.fill(random_matrix, cv::RNG::UNIFORM, 0, 255);

    std::cout << "cv sample" << std::endl;
    std::cout << random_matrix << std::endl;
}

int main(){
    sample_test();
    return 0;
}