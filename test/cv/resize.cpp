#include "cv_test.h"
#include <cmath>

using namespace std;

const char* file_path = __FILE__;

bool _resize(cv::InputArray _src, cv::Mat& result, cv::Size dsize){
    constexpr const float esp = 1e-6;

    cv::Mat src = _src.getMat();
    if(result.cols < dsize.width || result.rows < dsize.height)
        return false;

    const auto w = static_cast<float>(src.cols);
    const auto h = static_cast<float>(src.rows);
    const float aw = w / static_cast<float>(dsize.width);
    const float ah = h / static_cast<float>(dsize.height);

    if(std::abs(aw - 1) < esp && std::abs(ah - 1) < esp)
        return true;

    float ratio = ah > aw ? (1 / ah) : (1 / aw);
    int rw = static_cast<int>(w * ratio);
    int rh = static_cast<int>(h * ratio);

    // 等比缩放
    cv::Mat resize_image(rw,  rh, CV_8UC3);
    cv::resize(src, resize_image, cv::Size(rw, rh),cv::INTER_LINEAR);
    // 将结果写回result
    resize_image.copyTo(result(cv::Rect(0, 0, resize_image.cols, resize_image.rows)));
    return true;
}

void resize_test(){
    cout << "cv resize test" << endl;
    cv::Mat image(300, 400, CV_8UC3, cv::Scalar(117, 134, 1));
    cv::Mat resize_image = cv::Mat::zeros(640, 640, CV_8UC3);

    _resize(image, resize_image, cv::Size(640, 640));
//    cv::imshow("original", image);
//    cv::imshow("resize", resize_image);
//    cv::waitKey(2000);
}