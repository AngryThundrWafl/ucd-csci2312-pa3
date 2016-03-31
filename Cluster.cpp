//
// Created by Brian on 3/25/2016.
//

#include <algorithm>
#include "Cluster.h"
#include "Exceptions.h"
#include <sstream>

namespace Clustering {

    unsigned int Cluster:: __idGenerator = 0;
    const char Cluster::POINT_CLUSTER_ID_DELIM = ':';

    LNode::LNode(const Point &p, LNodePtr n) : point(p), next(n){
    }


    Cluster::Cluster(const Cluster &Cluster1) : Cluster(Cluster1.getDimensionality()) {
        __id = Cluster1.__id;
        for (int i = 0; i < Cluster1.getSize(); i++) {
            add(Cluster1[i]);
        }

        centroid.compute();
    }

    Cluster& Cluster::operator=(const Cluster & other) {
        if(*this == other){
            __id = other.__id;
            return *this;
        }
        else
        {
            if(__points != nullptr)
            {
                __del();
            }
            __size = 0;
            __id = other.__id;
            for(int i = 0; i < other.getSize(); i++)
            {
                add(other[i]);
            }
        }
        return *this;
    }

    Cluster::~Cluster(){
        __del();
    }

    unsigned  int Cluster::getSize() const{
        return __size;
    }

    void Cluster::__del(){
        LNodePtr curr = __points;

        LNodePtr next;

        for(int i = 0; i < __size; ++i){

                next = curr->next;
                delete curr;
                curr = next;
        }
    }

    void Cluster::__cpy(LNodePtr pts){
        if(pts == nullptr)
        {
          __points = nullptr;
            return;
        }
        LNodePtr  temp = pts;
        LNode *other = new LNode(pts->point, nullptr);
        LNode *head = other;
        temp = temp->next;
        while(temp != nullptr)
        {
            other = other->next = new LNode(temp->point, nullptr);
            temp = temp->next;
        }
        __points = head;

    }

    bool Cluster::__in(const Point &point1) const{
        return true;
    }

    void Cluster::add(const Point & pointNew) {
        //addee exception
        if(__dimensionality != pointNew.getDims())
        {
            throw DimensionalityMismatchEx(__dimensionality, pointNew.getDims());
        }
        LNode *temp = new LNode(pointNew, nullptr);
        LNodePtr  temp2 = __points;
        LNodePtr previous = nullptr;
        if(__size == 0)
        {
            __points == temp;
            ++__size;
            centroid.setValid(false);
            return;
        }
        else
        {
            while(temp2 != nullptr)
            {
                if(pointNew <temp2->point)
                {
                    temp->next = temp2;
                    __points = temp;
                }
                else
                {
                    previous->next = temp;
                    temp->next = temp2;
                }
                ++__size;
                centroid.setValid(false);
                return;
            }
            previous->next = temp;
            ++__size;
            centroid.setValid(false);
            return;
        }
    }


    const Point & Cluster::remove(const Point &Point1) {
        // Check if the given point exists in the cluster.
        if(__dimensionality!= Point1.getDims())
        {
            throw DimensionalityMismatchEx(__dimensionality, Point1.getDims());
        }
        int i = 0;
        bool value = false;
        LNodePtr temp = __points;
        LNodePtr previous = nullptr;

        if (temp == nullptr)
        {
            return Point1;
        }

        if (temp->next == nullptr)
        {
            if(temp->point == Point1)
            {
                __size = 0;
                delete temp;
                __points = nullptr;
            }
        }

        else
        {
            previous = __points;
             temp = __points->next;
            if(__points->point ==Point1)
            {
                __points =temp;
                --__size;
                delete previous;
                delete temp;
                centroid.setValid(false);
                return Point1;
            }
            for(; !value && temp != nullptr; temp = temp->next)
            {
                if(temp->point == Point1)
                {
                    previous->next = temp->next;
                    --__size;
                    value = true;
                    centroid.setValid(false);
                    return Point1;
                }
                previous = temp;
            }
        }
        centroid.setValid(false);
        return Point1;
    }

    bool Cluster::contains(const Point & Point1)const {
        bool value = false;
        LNodePtr temp = __points;
        while(temp != nullptr)
        {
            if(temp->point == Point1)
            {
                value = true;
            }
            temp = temp->next;
        }
        return value;
    }

    const Point &Cluster::operator[](unsigned int index) const{
        if(__size == 0)
        {
            throw EmptyClusterEx();
        }
        if(index >= __size)
        {
            throw OutOfBoundsEx(__size, index);
        }

        LNodePtr temp;
        temp = __points;

        if(__points != nullptr) {
            for (int i = 0; i < index; ++i)
            {
                temp = temp->next;
            }
        }
        return temp->point;
    }

    bool operator==(const Cluster & Cluster1, const Cluster &Cluster2){
        if(Cluster1.getDimensionality() != Cluster2.getDimensionality())
        {
            throw DimensionalityMismatchEx(Cluster1.getDimensionality(),Cluster2.getDimensionality());
        }
        if(Cluster1.getSize() != Cluster2.getSize())
        {
            return false;
        }

        for(int i = 0; i < Cluster1.__size; ++i){
            if(Cluster1[i] != Cluster2[i]){
                return false;
            }
        }
        return true;
    }


    bool operator!=(const Cluster & Cluster1, const Cluster & Cluster2){
        return !(Cluster1 == Cluster2);
    }

    Cluster & Cluster::operator+=(const Point & P1){
        if(__dimensionality != P1.getDims())
        {
            throw DimensionalityMismatchEx(__dimensionality, P1.getDims());
        }
        if(this->contains(P1))
        {
            return *this;
        }
        add(P1);
        return *this;
    }
    Cluster & Cluster::operator-=(const Point & P1){
        if(__dimensionality != P1.getDims())
        {
            throw DimensionalityMismatchEx(__dimensionality, P1.getDims());
        }
        if(!this->contains(P1))
        {
            return *this;
        }
        remove(P1);
        return *this;
    }

    // Members: Compound assignment (Cluster argument)
    Cluster &Cluster::operator+=(const Cluster & Cluster2) { // union
        if(__dimensionality != Cluster2.getDimensionality())
        {
            throw DimensionalityMismatchEx(__dimensionality, Cluster2.getDimensionality());
        }

        for(int i = 0; i < Cluster2.getSize(); ++i){
            if(!this->contains(Cluster2[i])){
                this->add(Cluster2[i]);
            }
        }

        return *this;
    }

    Cluster &Cluster::operator-=(const Cluster & Cluster2){ // (asymmetric) difference
        if(__dimensionality != Cluster2.getDimensionality())
        {
            throw DimensionalityMismatchEx(__dimensionality, Cluster2.getDimensionality());
        }
        for(int i = 0; i < Cluster2.getSize(); ++i){
            if(this->contains(Cluster2[i])){
                this->remove(Cluster2[i]);
            }
        }
        return *this;
    }
    // Friends: Arithmetic (Cluster and Point)
    const Cluster operator+(const Cluster &Cluster1, const Point &P1){
        return Cluster(Cluster1) += P1;
    }
    const Cluster operator-(const Cluster &Cluster1, const Point &P1){
       return Cluster(Cluster1) -= P1;
    }

    // Friends: Arithmetic (two Clusters)
    const Cluster operator+(const Cluster &Cluster1, const Cluster &Cluster2){
        return Cluster(Cluster1) += Cluster2;
    }

    const Cluster operator-(const Cluster &Cluster1, const Cluster &Cluster2){
        return Cluster(Cluster1) -= Cluster2;
    }

    std::ostream &operator<<(std::ostream & out, const Cluster & Cluster1){
        LNodePtr temp = Cluster1.__points;
        for(int i = 0; i < Cluster1.__size; ++i){
            out << temp->point << std::endl;
            temp = temp->next;
        }
        return out;
    }

    // Function is messy, and probably has a lot of unnecessary stuff, but works.
    std::istream &operator>>(std::istream & in, Cluster& Cluster1) {

        std::string temp;
        std::getline(in, temp);
        std::stringstream s;
        s.str(temp);

        int dim = 0;
        double tempD = 0;
        while (!s.eof()) {
            s >> tempD;
            s.ignore(10, ',');
            dim++;
        }

        bool run = false;
        int index = 0;
        while (in.peek() != EOF) {
            Point *nPoint = new Clustering::Point(dim);
            if (run) {
                temp = "";
                std::getline(in, temp);
                temp.erase(remove_if(temp.begin(), temp.end(), isspace), temp.end());
            }
            s.str("");
            s.clear();
            s.str(temp);

            while ((s.peek() != '\n') || (s.peek() != '\r') || (s.peek() != EOF)) {
                s >> tempD;
                nPoint->setValue(index, tempD);
                if ((s.peek() == '\n') || (s.peek() == '\r') || (s.peek() == EOF)) {
                    run = true;
                    Cluster1.add(*nPoint);
                    index = 0;
                    delete nPoint;
                    break;
                } else {
                    s.ignore();
                    index++;
                }
            }
        }
        return in;
    }

    Cluster::Centroid::Centroid(unsigned int d, const Cluster &cluster1): __dimensions(d), __c(cluster1), __p(d) {        //initiallizes c and p
        __valid = false;
        if(__c.getSize() == 0){
            toInfinity();
        }
    }


    const Point Cluster::Centroid::get() const {
        return __p;                                         //not sure if i have to return p or p.......
    }

    void Cluster::Centroid::set(const Point &p) {
        __p = p;                                            //same as return p not sure yet..
        __valid = true;
    }

    bool Cluster::Centroid::isValid() const {
        return __valid;                                        //will just return valid
    }

    void Cluster::Centroid::setValid(bool valid) {
        __valid = valid;                                    //will set the value for valid from the parameter that is passed
    }

//Centroid Functions
    void Cluster::Centroid::compute() {
        int i = __c.getSize();
        int dim = __dimensions;
        double avg = 0;
        double total = 0;
        if(i == 1)
        {
            __p = __c[0];
        }
        else if(dim > 0 && i >0)
        {
            for(int x = 0; x < dim; i++)
            {
                for(int y = 0; y < i; ++y)
                {
                    Point temp(__c[y]);
                    total += temp[x];
                }
                avg = total / i;
                __p.setValue(x,avg);
                total =0;
            }
        }
        else
            toInfinity();
        setValid(true);
    }

    bool Cluster::Centroid::equal(const Point &point1) const {
        for (int i = 0; i < __dimensions; i++) {
            if (__p[i] != point1[i])
            {
                return false;
            }//else
            //return true;
        }
        return true;
    }

    void Cluster::Centroid::toInfinity() {
        for (unsigned int i = 0; i < __dimensions; i++) {
            __p[i] = std::numeric_limits<double>::max();
        }
    }

    Cluster::Cluster(unsigned int dim):centroid(dim, *this) {                  //need to see how to initialize centriod
        __dimensionality = dim;                           //now needs a dimensionality variable
        __size = 0;
        __points = nullptr;
        __id = __idGenerator;
        __idGenerator++;
    }

    unsigned int Cluster::getDimensionality() const {
        return __dimensionality;
    }

    unsigned int Cluster::getId() const {
        return __id;
    }


    void Cluster::pickCentroids(unsigned int k, Point **pointArray) {
        if(k >= __size)
        {
            for(int i = 0; i <k ; ++i) {
                if (i < __size) {
                    *pointArray[i] = (*this)[i];
                }
                else
                    for (unsigned int i = 0; i < pointArray[i]->getDims(); i++)
                        pointArray[i]->setValue(i, std::numeric_limits<double>::max());
            }
        }
        else
        {
            float temp = static_cast<float>(__size) / k;
            for(int i = 0; i < k; ++i)
            {
                *pointArray[i] = (*this)[static_cast<int>(i * temp)];
            }
        }
    }

    Cluster::Move::Move(const Point &p, Cluster &from, Cluster &to):__p(p), __from(from), __to(to) {

    }

    void Cluster::Move::perform() {
        if(__from.contains(__p))
        {
            __to.add((__from.remove(__p)));
        }
        if(__from.getSize() == 0)
        {
            __from.centroid.toInfinity();
        }
        if(__to.getSize() == 0)
        {
            __to.centroid.toInfinity();
        }
    }
}