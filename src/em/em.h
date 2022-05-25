#ifndef EM_H
#define EM_H

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include "abstractClustering.h"

class EM : public AbstractClustering {
public:
    EM(std::string imgAddr, int n);
    void cluster();
    bool converged();
    void EStep();
    void MStep();
    cv::Mat reconstructImage();
private:
    cv::Mat img;
    int nClusters;
    int **means;
};

#endif // EM_H