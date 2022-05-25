#include "k-means.h"

KMeans::KMeans(std::string imgAddr, int n) : AbstractClustering(imgAddr, n) {
    img = cv::imread(imgAddr);
    inititalizeMeans();
}

void KMeans::cluster() {
    while (!converged()) {
        BStep();
        MStep();
    }
}

bool KMeans::converged() {
    return false;
}

void KMeans::BStep() {

}

void KMeans::MStep() {

}
