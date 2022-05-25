#ifndef KMEANSIMAGECLUSTERING_H
#define KMEANSIMAGECLUSTERING_H

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include "abstractImageClustering.h"

class KMeansImageClustering : public AbstractImageClustering {
public:
    KMeansImageClustering(std::string imgAddr, int n);
    void cluster();
    bool converged();
    void BStep();
    void MStep();
};

#endif // KMEANSIMAGECLUSTERING_H