#ifndef KMEANS_H
#define KMEANS_H

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include "abstractClustering.h"

class KMeans : public AbstractClustering {
public:
    KMeans(std::string imgAddr, int n);
    void cluster();
    bool converged();
    void BStep();
    void MStep();
private:
    cv::Mat img;
    int nClusters;
    int **means;
};

#endif // KMEANS_H
