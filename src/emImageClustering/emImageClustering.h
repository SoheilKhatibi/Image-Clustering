#ifndef EMIMAGECLUSTERING_H
#define EMIMAGECLUSTERING_H

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include "abstractImageClustering.h"

class EMImageClustering : public AbstractImageClustering {
public:
    EMImageClustering(std::string imgAddr, int n);
    void cluster();
    bool converged();
    void EStep();
    void MStep();
    void initializeCovariances();
    void initializeHValues();
private:
    arma::mat* S;
    double *** h;
};

#endif // EMIMAGECLUSTERING_H
