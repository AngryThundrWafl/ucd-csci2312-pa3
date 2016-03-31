//
// Created by Brian on 3/25/2016.
//
#include "Exceptions.h"
namespace Clustering {

//constructor for out of bounds exception
    Clustering::OutOfBoundsEx::OutOfBoundsEx(unsigned int c, int r):__current(c), __rhs(r) {
        __name = "OutOfBoundsEx";
    }

    unsigned int OutOfBoundsEx::getCurrent() const {
        return __current;
    }

    int OutOfBoundsEx::getRhs() const {
        return __rhs;
    }

    std::string OutOfBoundsEx::getName() const {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const OutOfBoundsEx &ex) {
        os << ex.getName() << ": " << ex.getCurrent() << ", " << ex.getRhs();                 //will print the exception message into the stream obj
        return os;
    }


    //dimenstionaliy exception
    //comstructor
    DimensionalityMismatchEx::DimensionalityMismatchEx(unsigned int c, unsigned int r) :__current(c), __rhs(r) {
        __name = "DimensionalityMismatchEx";
    }

    unsigned int DimensionalityMismatchEx::getCurrent() const {
        return __current;
    }

    unsigned int DimensionalityMismatchEx::getRhs() const {
        return __rhs;
    }

    std::string DimensionalityMismatchEx::getName() const {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const DimensionalityMismatchEx &ex) {
       return os << ex.getName() << ": " << ex.getCurrent() << ", " << ex.getRhs();                  ////will print the exception message into the stream obj
    }

    //zero cluster exception thrown in k means constructor
    ZeroClustersEx::ZeroClustersEx() {
        __name = "ZeroClustersEx";
    }

    std::string ZeroClustersEx::getName() const {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const ZeroClustersEx &ex) {
        return os << ex.getName();
    }

    //data file exception thrown by k means constructor when file canot be opened or file cannot be found with the same name
    DataFileOpenEx::DataFileOpenEx(std::string filename) {
        __filename = filename;
        __name = "DataFileOpenEx";

    }


    std::string DataFileOpenEx::getFilename() const {
        return __filename;
    }

    std::string DataFileOpenEx::getName() const {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const DataFileOpenEx &ex) {
        return os << ex.getName() <<": " << ex.getFilename();
    }

    //when there are no dimensions excdption is thrown in the point constructor when d = 0
    ZeroDimensionsEx::ZeroDimensionsEx() {
        __name = "ZeroDimensionsEx";
    }

    std::string ZeroDimensionsEx::getName() const {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const ZeroDimensionsEx &ex) {
        return os << ex.getName();
    }

    //when cluster is empty thrown by cluster::operator[] when cluster is empty
    EmptyClusterEx::EmptyClusterEx() {
        __name = "EmptyClusterEx";
    }

    std::string EmptyClusterEx::getName() const {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const EmptyClusterEx &ex) {
       return os << ex.getName();
    }
}