#ifndef POINT2D_H
#define POINT2D_H

#include <iostream>
#include "Vector2D.h"

using namespace std;

class Point2D 
{
    public:

    double x;
    double y;

    Point2D();
    Point2D(double, double);

};

double GetDistanceBetween(Point2D, Point2D); //don't REALLY need consts, since not ref!

ostream& operator << (ostream&, const Point2D&); // keep objects const, ostream NOT const (it changes)
Point2D operator+(const Point2D&, const Vector2D&);
Vector2D operator-(const Point2D&, const Point2D&);





#endif
