//
// Created by Brian on 3/25/2016.
//


#include "Point.h"
#include <cmath>
#include "Exceptions.h"

namespace Clustering {

    unsigned int Point::__idGen = 0;
    const char Point::POINT_VALUE_DELIM = ',';

    Point::Point(unsigned int d){
        if(d <= 0)ZeroDimensionsEx();

        __id = __idGen++;
        __dim = d;
        __values = new double[__dim];


        for(int i = 0; i < __dim; ++i){
            __values[i] = 0;
        }
    }

    Point::Point(unsigned int dim, double * value){
        __id = __idGen++;
        __values = value;
        __dim = dim;
    }

    Point::Point(const Point & point1){
        __id = point1.__id;
        __dim = point1.getDims();
        __values = new double[__dim];
        for(int i = 0; i < point1.__dim; ++i){
            __values[i] = point1.__values[i];
        }

    }

    Point& Point::operator=(const Point & yeezy){

            if(yeezy != __dim)throw OutOfBoundsEx(yeezy.__dim, __dim);
            __id = yeezy.__id;
            delete[] __values;
            __dim = yeezy.getDims();
        for(int i = 0; i <yeezy.__dim;i++)
            __values[i] = yeezy.__values[i];
        return *this;
    }
    //nothing is needed it should delete it might need a destructor to do
    Point::~Point(){
    }

    int Point::getId() const{
        return __id;
    }
    unsigned int Point::getDims() const{
        return __dim;
    }


    void Point::setValue(unsigned int d, double value){
        if(d >__dim)throw OutOfBoundsEx(__dim, d);
        __values[d] = value;
    }
    double Point::getValue(unsigned int d) const{
        if(d > __dim)throw OutOfBoundsEx(__dim, d);
       return __values[d];
    }
    double Point::distanceTo(const Point & yeezy) const{
        double dist = 0.0;
        for (int i = 0; i < __dim; ++i){
            dist = dist + ((__values[i]-yeezy.getValue(i)) * (__values[i]-yeezy.getValue(i)));
        }
        return sqrt(dist);
    }

    const Point Point::operator*(double multiple) const { // prevent (p1 * 2) = p2;
        Point *newPoint = new Point(__dim);

        for (int i = 0; i < __dim; ++i) {
            newPoint->__values[i] = __values[i] * multiple;
        }

        return *newPoint;
    }


    const Point Point::operator/(double division) const{ // p3 = p2 / 2;
        Point *newP = new Point(__dim);

        for (int i = 0; i < __dim; ++i) {
            newP->__values[i] = __values[i] / division;
        }

        return *newP;
    }

    double& Point::operator[](unsigned int index){
        //to do
        return __values[index];
    }

    bool operator==(const Point & Point1, const Point & Point2){
        bool pass = true;

        if(Point1.__id != Point2.__id){
            return false;
        }

        if (Point1.__dim != Point2.__dim){
            return false;
        }

        for (int i = 0; i < Point1.getDims(); ++i){
            if(Point1.__values[i] != Point2.__values[i]){
                pass = false;
            }
        }
       //return pass;
    }

    bool operator!=(const Point & Point1, const Point & Point2){
        return !(Point1 == Point2);
    }

    bool operator<(const Point & Point1, const Point & Point2) {

        if (Point1.__dim < Point2.__dim) {
            return true;
        }
        if (Point1.__dim > Point2.__dim) {
            return false;
        }

        for (int i = 0; i < Point1.getDims(); ++i) {
            if (Point1.__values[i] < Point2.__values[i]) {
                return true;
            }else if(Point1.__values[i] > Point2.__values[i]){
                return false;
            }
        }
        return false;

    }

    bool operator>(const Point & Point1, const Point &Point2){

        if(Point1.__dim > Point2.__dim){
            return true;
        }
        if(Point1.__dim < Point2.__dim){
            return false;
        }

        for(int i = 0; i < Point1.getDims(); ++i){
            if(Point1.__values[i] > Point2.__values[i]){
                return true;
            }else if(Point1.__values[i] < Point2.__values[i]){
                return false;
            }
        }
        return false;
    }

    bool operator<=(const Point & Point1, const Point &Point2){
        if (Point1<Point2) {
            return true;
        }
        if (Point1>Point2) {
            return false;
        }
        return true;
    }

    bool operator>=(const Point & Point1, const Point &Point2){
        if (Point1>Point2) {
            return true;
        }
        if (Point1<Point2) {
            return false;
        }
        return true;
    }

    Point& operator+=(Point & Point1, const Point & Point2){
        Point *newP = new Point(Point2);

        for (int i = 0; i < Point1.__dim; ++i){
            Point1.__values[i] = Point1.__values[i] + newP->getValue(i);
        }
        delete newP;
        return Point1;
    }

    Point &operator-=(Point & Point1, const Point & Point2){
        Point *newPoint = new Point(Point2);

        for (int i = 0; i < Point1.__dim; ++i){
            Point1.__values[i] = Point1.__values[i] - newPoint->getValue(i);
        }
        delete newPoint;
        return Point1;
    }

    Point & Point::operator*=(double multiple){ // p *= 6; p.operator*=(6);
        for (int i = 0; i < __dim; ++i){
            __values[i] = __values[i] * multiple;
        }
        return *this;
    }

    Point & Point::operator/=(double division){
        for (int i = 0; i < __dim; ++i){
            __values[i] = __values[i] / division;
        }
        return *this;
    }
    const Point operator+(const Point & Point1, const Point & Point2){
        Point *newPoint = new Point(Point1);
        *newPoint += Point2;
        return *newPoint;
    }
    const Point operator-(const Point & Point1, const Point & Point2){
        Point *newPoint = new Point(Point1);
        *newPoint -= Point2;
        return *newPoint;
    }

    std::ostream &operator<<(std::ostream &out, const Point &Point1){
        int i = 0;
        for( ; i < Point1.getDims()-1; ++i){
            out << Point1.getValue(i);
            out << ", ";
        }
        out << Point1.getValue(i);

        return out;
    }

    std::istream &operator>>(std::istream &in, Point &Point1){
        int index = 0;

        while ((in.peek() != '\n') || (in.peek() != '\r')){
            in >> Point1[index];
            if((in.peek() == '\n') || (in.peek() == '\r') || (in.eof())){
                return in;
            }
            in.ignore(100, ',');
            index++;
        }
        return in;
    }

    void Point::rewindIdGen() {
        __idGen-= 1;
    }

    const double &Point::operator[](unsigned int index) const {
        if(__dim < index)throw OutOfBoundsEx(__dim,index);
            return __values[index];
    }
}