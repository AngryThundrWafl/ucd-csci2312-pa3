//
// Created by Brian on 3/25/2016.
//
#include "KMeans.h"

namespace  Clustering{


    KMeans::KMeans(unsigned int dim, unsigned int k, std::string filename, unsigned int maxIter) {

    }

    KMeans::~KMeans() {

    }

    unsigned int KMeans::getMaxIter() {
        return 0;
    }

    unsigned int KMeans::getNumIters() {
        return 0;
    }

    unsigned int KMeans::getNumNonemptyClusters() {
        return 0;
    }

    unsigned int KMeans::getNumMovesLastIter() {
        return 0;
    }

    Cluster &KMeans::operator[](unsigned int u) {

    }

    const Cluster &KMeans::operator[](unsigned int u) const {

    }

    std::ostream &operator<<(std::ostream &os, const KMeans &kmeans) {

    }

    void KMeans::run() {

    }
}

