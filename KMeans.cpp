//
// Created by Brian on 3/25/2016.
//
#include "KMeans.h"
#include "Exceptions.h"
#include <limits>
#include <cstdlib>

namespace  Clustering{


    KMeans::KMeans(unsigned int dim, unsigned int k, std::string filename, unsigned int maxIter) :__dimensionality(dim), __k(k), __iFileName(filename), __maxIter(maxIter), __numIter(0), __numNonempty(1){
        if( k == 0)
        {
            throw ZeroClustersEx();
        }
        std::ifstream file(__iFileName);           //Initializes the ifstream object in teh class

        if(!file.is_open())
        {
            throw DataFileOpenEx(__iFileName);
        }

        //make an array of clusters and an array of centroids
        __clusters = new Cluster *[__k];
        __initCentroids = new Point*[__k];

        //intitializes the arrays
        for(int i = 0; i < __k; ++i)
        {
            __clusters[i] = new Cluster(dim);
            __initCentroids[i] = new Point(dim);
        }
        file >> *__clusters[0];
        file.close();

        __clusters[0]->pickCentroids(__k,__initCentroids);
    }

    KMeans::~KMeans() {
        //will delete the array fo clusters and array of centrods
        for(int i = 0; i < __k;i++ )
        {
            delete __clusters[i];
        }

        for(int i =0; i < __k; i++)
        {
            delete __initCentroids[i];
        }
    }

    unsigned int KMeans::getMaxIter() {
        return __maxIter;
    }

    unsigned int KMeans::getNumIters() {
        return __numIter;
    }

    unsigned int KMeans::getNumNonemptyClusters() {
        return __numNonempty;
    }

    unsigned int KMeans::getNumMovesLastIter() {
        return __numMovesLastIter;
    }

    Cluster &KMeans::operator[](unsigned int u) {
        return * __clusters[u];
    }

    const Cluster &KMeans::operator[](unsigned int u) const {
        return *__clusters[u];
    }

    std::ostream &operator<<(std::ostream &os, const KMeans &kmeans) {
        for(int i =0; i < kmeans.__k; i++)
        {
            os << kmeans[i];
        }
        return os;
    }

    void KMeans::run() {
        int mov = 100, iteration = 0, closest = NULL;
        double x1, y1, final;
        for(int i =0; i < __k; i++)
        {
            Cluster::Move temp(*(__initCentroids[i]), *(__clusters[0]), *(__clusters[i]));
            temp.perform();
        }
        while(mov > 0 && iteration < __maxIter)
        {
            mov = 0;
            for(int i =0; i < __k; i++) {
                for (int x = 0; x < __clusters[i]->getSize(); x++) {
                    x1 = (*__clusters[i])[x].distanceTo(__clusters[i]->centroid.get());
                    if (x1 > y1) {
                        closest = i;
                        final = y1;
                    }

                if (closest != NULL) {
                    Cluster::Move temp((*(__clusters[i]))[x],*(__clusters[i]),*(__clusters[closest]));
                    temp.perform();
                    mov++;
                }

            }
        }
            for(int i = 0; i < __k; i++)
            {
                __clusters[i]->centroid.compute();
            }
            iteration++;
        }
        __numNonempty=0;
        for(int i =0; i< __k; i++)
        {
            if(__clusters[i]->getSize() >0){
                ++ __numNonempty;
            }
        }
        __numMovesLastIter = mov;
        __numIter = iteration;
    }
}

