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

double distance(int* a, int* b) {
    double d[3], dist;
    d[0] = abs(a[0] - b[0]);
    d[1] = abs(a[1] - b[1]);
    d[2] = abs(a[2] - b[2]);
    dist = sqrt(pow(d[0], 2) + pow(d[1], 2) + pow(d[2], 2));
    return dist;
}

int minimumDistanceIndex(int* a, int ** b, int sizeOfVector) {
    int minimumIndex = 0;
    double minDistance = INFINITY;
    double dist;
    for (int i = 0; i < sizeOfVector; i++) {
        dist = distance(a, b[i]);
        if (dist < minDistance) {
            minimumIndex = i;
            minDistance = dist;
        }
    }
    return minimumIndex;
}
