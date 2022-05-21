#ifndef Util_H
#define Util_H

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include "armadillo"

int loadImage(cv::Mat&, std::string);
void displayImage(cv::Mat&);

arma::Mat<int> opencv2arma(cv::Mat&);
cv::Mat arma2opencv(arma::Mat<int>&);

#endif
