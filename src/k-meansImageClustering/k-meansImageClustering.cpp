#include "k-meansImageClustering.h"

KMeansImageClustering::KMeansImageClustering(std::string imgAddr, int n) : AbstractImageClustering(imgAddr, n) {
    initializeBValues();
}

void KMeansImageClustering::cluster() {
    while (!converged()) {
        BStep();
        MStep();
    }
}

bool KMeansImageClustering::converged() {
    return false;
}

void KMeansImageClustering::BStep() {

}

void KMeansImageClustering::MStep() {

}

void KMeansImageClustering::initializeBValues() {
    b = new int** [img.rows];
    for (int i = 0; i < img.rows; i++) {
        b[i] = new int* [img.cols];
        for (int j = 0; j < img.cols; j++) {
            b[i][j] = new int [nClusters];
        }
    }
    BStep();
}
