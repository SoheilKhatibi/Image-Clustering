#ifndef Util_H
#define Util_H

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include "armadillo"
#include <math.h>

int loadImage(cv::Mat&, std::string);
void displayImage(cv::Mat&);

arma::Mat<int> opencv2arma(cv::Mat&);
cv::Mat arma2opencv(arma::Mat<int>&);
double distance(int* a, int* b);
int minimumDistanceIndex(int* a, int ** b, int sizeOfVector);

#endif
