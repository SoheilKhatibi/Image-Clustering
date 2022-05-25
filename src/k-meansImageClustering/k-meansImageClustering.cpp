#include "k-meansImageClustering.h"

KMeansImageClustering::KMeansImageClustering(std::string imgAddr, int n) : AbstractImageClustering(imgAddr, n) {
    img = cv::imread(imgAddr);
    inititalizeMeans();
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
