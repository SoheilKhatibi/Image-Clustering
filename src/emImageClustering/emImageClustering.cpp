#include "emImageClustering.h"

EMImageClustering::EMImageClustering(std::string imgAddr, int n) : AbstractImageClustering(imgAddr, n) {
}

void EMImageClustering::cluster() {
    while (!converged()) {
        EStep();
        MStep();
    }
}

bool EMImageClustering::converged() {
    return false;
}

void EMImageClustering::EStep() {

}

void EMImageClustering::MStep() {

}
