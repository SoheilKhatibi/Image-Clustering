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
    void initializePValues();
    void updateMeans();
    void updateCovariances();
    void updatePs();
    void printPs();
    void printCovariances();
private:
    arma::mat* S;
    double *** h;
    double* P;
};

#endif // EMIMAGECLUSTERING_H
