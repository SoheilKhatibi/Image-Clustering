#include "util.h"

int loadImage(cv::Mat& opencv_mat, std::string address) {

    opencv_mat = cv::imread(address, 0);

    if (opencv_mat.empty()){
        std::cout << "Could not open or find the image" << std::endl;
        std::cin.get();
        return -1;
    }
    return 0;
}

void displayImage(cv::Mat& opencv_mat) {

    std::string windowName = "Display";
    cv::namedWindow(windowName);

    cv::imshow(windowName, opencv_mat);
    cv::waitKey(0);

    cv::destroyWindow(windowName);
}
