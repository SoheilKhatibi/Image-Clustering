#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include "armadillo"

using namespace cv;
using namespace std;

int main(int argc, char** argv){

    Mat opencv_mat = imread("Lenna.png", 0);

    if (opencv_mat.empty()){
        cout << "Could not open or find the image" << endl;
        cin.get();
        return -1;
    }

    arma::Mat arma_mat(opencv_mat.data, opencv_mat.cols, opencv_mat.rows);

    cv::Mat opencv_mat2(arma_mat.n_cols, arma_mat.n_rows, CV_8UC1, arma_mat.memptr());

    String windowName = "Lenna";

    namedWindow(windowName);

    imshow(windowName, opencv_mat2);

    waitKey(0);

    destroyWindow(windowName);

    return 0;
}