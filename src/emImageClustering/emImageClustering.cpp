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
                h[i][j][k] = P[k] * (1 / (sqrt(det(S[k])))) * exp((-0.5) * xMinusMTrProductSIProductxMinusM(0, 0));
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
    updateMeans();
    updateCovariances();
    updatePs();
}

void EMImageClustering::initializeCovariances() {
    S = new arma::mat [nClusters];

    for (int k = 0; k < nClusters; k++) {
        S[k] = arma::mat(3, 3, arma::fill::eye);
    }

    int XMinusMeanBlue, XMinusMeanGreen, XMinusMeanRed;
    long int BBDevSum, GGDevSum, RRDevSum, BGDevSum, BRDevSum, GRDevSum;
    int covBB, covGG, covRR, covBG, covBR, covGR;
    int nTotal = img.rows * img.cols;
    for (int k = 0; k < nClusters; k++) {
        BBDevSum = 0;
        GGDevSum = 0;
        RRDevSum = 0;
        BGDevSum = 0;
        BRDevSum = 0;
        GRDevSum = 0;

        for (int i = 0; i < img.rows; i++) {
            for (int j = 0; j < img.cols; j++) {
                XMinusMeanBlue = img.at<cv::Vec3b>(i, j)[0] - means[k][0];
                XMinusMeanGreen = img.at<cv::Vec3b>(i, j)[1] - means[k][1];
                XMinusMeanRed = img.at<cv::Vec3b>(i, j)[2] - means[k][2];
                BBDevSum += XMinusMeanBlue * XMinusMeanBlue;
                GGDevSum += XMinusMeanGreen * XMinusMeanGreen;
                RRDevSum += XMinusMeanRed * XMinusMeanRed;
                BGDevSum += XMinusMeanBlue * XMinusMeanGreen;
                BRDevSum += XMinusMeanBlue * XMinusMeanRed;
                GRDevSum += XMinusMeanGreen * XMinusMeanRed;
            }
        }

        covBB = BBDevSum / (nTotal - 1);
        covGG = GGDevSum / (nTotal - 1);
        covRR = RRDevSum / (nTotal - 1);
        covBG = BGDevSum / (nTotal - 1);
        covBR = BRDevSum / (nTotal - 1);
        covGR = GRDevSum / (nTotal - 1);

        S[k](0, 0) = covBB; // BB
        S[k](0, 1) = covBG; // BG
        S[k](0, 2) = covBR; // BR

        S[k](1, 0) = covBG; // GB
        S[k](1, 1) = covGG; // GG
        S[k](1, 2) = covGR; // GR

        S[k](2, 0) = covBR; // RB
        S[k](2, 1) = covGR; // RG
        S[k](2, 2) = covRR; // RR
    }
}

void EMImageClustering::initializeHValues() {
    h = new double** [img.rows];
    for (int i = 0; i < img.rows; i++) {
        h[i] = new double* [img.cols];
        for (int j = 0; j < img.cols; j++) {
            h[i][j] = new double [nClusters];
        }
    }

    EStep();
}

void EMImageClustering::initializePValues() {
    P = new double [nClusters];
    for (int k = 0; k < nClusters; k++) {
        P[k] = 1 / double(nClusters);
    }
}

void EMImageClustering::updateMeans() {
    double hSum;
    arma::mat hXSum, x;
    for (int k = 0; k < nClusters; k++) {
        hSum = 0;
        hXSum = arma::mat(3, 1, arma::fill::zeros);
        for (int i = 0; i < img.rows; i++) {
            for (int j = 0; j < img.cols; j++) {
                x = arma::mat(3, 1, arma::fill::zeros);
                x(0, 0) = img.at<cv::Vec3b>(i, j)[0];
                x(1, 0) = img.at<cv::Vec3b>(i, j)[1];
                x(2, 0) = img.at<cv::Vec3b>(i, j)[2];

                hSum += h[i][j][k];
                hXSum += h[i][j][k] * x;
            }
        }
        means[k][0] = hXSum(0, 0) / hSum;
        means[k][1] = hXSum(1, 0) / hSum;
        means[k][2] = hXSum(2, 0) / hSum;
    }
}

void EMImageClustering::updateCovariances() {
    double hSum;
    arma::mat x, m, SSum;
    for (int k = 0; k < nClusters; k++) {
        hSum = 0;

        m = arma::mat(3, 1, arma::fill::zeros);
        m(0, 0) = means[k][0];
        m(1, 0) = means[k][1];
        m(2, 0) = means[k][2];

        SSum = arma::mat(3, 3, arma::fill::zeros);
        for (int i = 0; i < img.rows; i++) {
            for (int j = 0; j < img.cols; j++) {
                x = arma::mat(3, 1, arma::fill::zeros);
                x(0, 0) = img.at<cv::Vec3b>(i, j)[0];
                x(1, 0) = img.at<cv::Vec3b>(i, j)[1];
                x(2, 0) = img.at<cv::Vec3b>(i, j)[2];

                hSum += h[i][j][k];
                SSum += h[i][j][k] * (x - m) * (x - m).t();
            }
        }
        S[k] = SSum / hSum;
    }
}

void EMImageClustering::updatePs() {
    int nTotal = img.rows * img.cols;
    double hSum;
    for (int k = 0; k < nClusters; k++) {
        hSum = 0;
        for (int i = 0; i < img.rows; i++) {
            for (int j = 0; j < img.cols; j++) {
                hSum += h[i][j][k];
            }
        }
        P[k] = hSum / nTotal;
    }
}

void EMImageClustering::printPs() {
    std::cout << "Component densities: " << std::endl;
    for (int i = 0; i < nClusters; i++) {
        std::cout << "P[" << i << "]: " << P[i] << std::endl;
    }
    std::cout << std::endl;
}

void EMImageClustering::printCovariances() {
    std::cout << "Covariances: " << std::endl;
    for (int i = 0; i < nClusters; i++) {
        S[i].print("S[" + std::to_string(i) + "]");
    }
    std::cout << std::endl;
}
