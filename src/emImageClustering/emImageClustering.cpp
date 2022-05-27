#include "emImageClustering.h"

EMImageClustering::EMImageClustering(std::string imgAddr, int n) : AbstractImageClustering(imgAddr, n) {
    initializePValues();
    initializeCovariances();
    initializeHValues();
}

void EMImageClustering::cluster() {
    int i = 0;
    while (!converged()) {
        EStep();
        MStep();
        // inititalizeMeans();
        std::cout << "Iterate number " << i << std::endl;
        // printMeans();
        cv::imshow("Original", img);
        cv::Mat reconstructedImage = reconstructImage();
        displayImage(reconstructedImage);
        i++;
    }
}

bool EMImageClustering::converged() {
    return false;
}

void EMImageClustering::EStep() {
    double hSum;
    arma::mat x, m, xMinusM, xMinusMTrProductSIProductxMinusM;
    for (int k = 0; k < nClusters; k++) {
        hSum = 0;
        m = arma::mat(3, 1, arma::fill::zeros);
        m(0, 0) = means[k][0];
        m(1, 0) = means[k][1];
        m(2, 0) = means[k][2];
        for (int i = 0; i < img.rows; i++) {
            for (int j = 0; j < img.cols; j++) {
                x = arma::mat(3, 1, arma::fill::zeros);
                x(0, 0) = img.at<cv::Vec3b>(i, j)[0];
                x(1, 0) = img.at<cv::Vec3b>(i, j)[1];
                x(2, 0) = img.at<cv::Vec3b>(i, j)[2];

                xMinusM = x - m;
                xMinusMTrProductSIProductxMinusM = xMinusM.t() * S[k].i() * xMinusM;
                h[i][j][k] = P[k] * (1 / (sqrt(det(S[k])))) * exp((-1/2) * xMinusMTrProductSIProductxMinusM(0, 0));
                hSum += h[i][j][k];
            }
        }

        for (int i = 0; i < img.rows; i++) {
            for (int j = 0; j < img.cols; j++) {
                h[i][j][k] /= hSum;
            }
        }
    }
}

void EMImageClustering::MStep() {

}

void EMImageClustering::initializeCovariances() {
    S = new arma::mat [nClustering];

    for (int k = 0; k < nClusters; k++) {
        S[k] = arma::mat(3, 3, arma::fill::eye);
    }

    int XSumBlue, XSumGreen, XSumRed;
    int nTotal = img.rows * img.cols;
    for (int k = 0; k < nClusters; k++) {
        XSumBlue = 0;
        XSumGreen = 0;
        XSumRed = 0;
        // stdDev(xBlue)
        // stdDev(xGreen)
        // stdDev(xRed)
        for (int i = 0; i < img.rows; i++) {
            for (int j = 0; j < img.cols; j++) {
                XSumBlue += img.at<cv::Vec3b>(i, j)[0] - means[k][0];
                XSumGreen += img.at<cv::Vec3b>(i, j)[1] - means[k][1];
                XSumRed += img.at<cv::Vec3b>(i, j)[2] - means[k][2];
            }
        }

        //              E[(Xb - m)(Xg - m)]
        // S (B, G) = -------------------------
        //              stdDev(Xb).stdDev(Xg)

        // S(0, 0) = ;
        // S(0, 1) = ;
        // S(0, 2) = ;
        // S(1, 0) = ;
        // S(1, 1) = ;
        // S(1, 2) = ;
        // S(2, 0) = ;
        // S(2, 1) = ;
        // S(2, 2) = ;
    }
}

void EMImageClustering::initializeHValues() {
    h = new int** [img.rows];
    for (int i = 0; i < img.rows; i++) {
        h[i] = new int* [img.cols];
        for (int j = 0; j < img.cols; j++) {
            h[i][j] = new int [nClusters];
        }
    }

    EStep();
}

void EMImageClustering::initializePValues() {
    P = new double [nClusters];
    for (int k = 0; k < nClusters; k++) {
        P[k] = 1 / nClusters;
    }
}
