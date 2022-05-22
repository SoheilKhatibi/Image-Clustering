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

    // std::string windowName = "Display";
    // cv::namedWindow(windowName);

    cv::imshow("Display", opencv_mat);
    cv::waitKey(0);

    // cv::destroyWindow(windowName);
}

arma::Mat<int> opencv2arma(cv::Mat& opencv_mat){

    // arma::Mat arma_mat(opencv_mat.data, opencv_mat.cols, opencv_mat.rows);
    arma::Mat<int> arma_mat(reinterpret_cast<int*>(opencv_mat.data), opencv_mat.cols, opencv_mat.rows);
    return arma_mat;
}

cv::Mat arma2opencv(arma::Mat<int>& arma_mat){

    cv::Mat opencv_mat2(arma_mat.n_cols, arma_mat.n_rows, CV_8UC1, arma_mat.memptr());
    return opencv_mat2;
}
