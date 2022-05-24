#include "em.h"

EM::EM(std::string imgAddr, int n) : AbstractClustering(imgAddr, n) {
    img = cv::imread(imgAddr);
    inititalizeMeans();
}

void EM::cluster() {

}
