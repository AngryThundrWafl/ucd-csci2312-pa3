// File: Point.h
//
// Created by Ivo Georgiev on 9/14/15.
//

#ifndef CLUSTERING_POINT_H
#define CLUSTERING_POINT_H

#include <iostream>

namespace Clustering {

    class Point {
        unsigned int __id;
        unsigned int __dim;        // number of dimensions of the point
        double *__values; // values of the point's dimensions

        static unsigned int __idGen; // id generator

    public:
        static const char POINT_VALUE_DELIM;                            //this was added not from the other project

        static void rewindIdGen();                                      //this was added

        Point(unsigned int);                                            //default constructor now takes a unsigned int
        Point(unsigned int, double *);                                  //constructor takes a unsigned int and a double

        // Big three: cpy ctor, overloaded operator=, dtor
        Point(const Point &);
        Point &operator=(const Point &);
        ~Point();

        // Accessors & mutators
        int getId() const;
        unsigned int getDims() const;                                   //get dims now gets a unsigned int
        void setValue(unsigned int, double);                            //set value takes a unsigned int now
        double getValue(unsigned int) const;                            //get values takes a unsigned int
        // Functions
        double distanceTo(const Point &) const;

        // Overloaded operators

        // Members
        Point &operator*=(double); // p *= 6; p.operator*=(6);
        Point &operator/=(double);
        const Point operator*(double) const; // prevent (p1 * 2) = p2;
        const Point operator/(double) const; // p3 = p2 / 2;

        double &operator[](unsigned int index);                         //operator overload now takes a unsigned int
        const double &operator[](unsigned int index) const;             //const of same overaload operator takes a unsigned int as well

        // Friends
        friend Point &operator+=(Point &, const Point &);
        friend Point &operator-=(Point &, const Point &);
        friend const Point operator+(const Point &, const Point &);
        friend const Point operator-(const Point &, const Point &);

        friend bool operator==(const Point &, const Point &);
        friend bool operator!=(const Point &, const Point &);

        friend bool operator<(const Point &, const Point &);
        friend bool operator>(const Point &, const Point &);
        friend bool operator<=(const Point &, const Point &);
        friend bool operator>=(const Point &, const Point &);

        friend std::ostream &operator<<(std::ostream &os, const Point &p);
        friend std::istream &operator>>(std::istream &is, Point &p);
    };

}
#endif //CLUSTERING_POINT_H
