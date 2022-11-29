#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

using namespace std;

class Vector2D 
{
    public:

    double x;
    double y;

    Vector2D();
    Vector2D(double, double);

};

Vector2D operator*(const Vector2D&, const double);
Vector2D operator/(const Vector2D&, const double);

ostream& operator << (ostream&, const Vector2D&);




#endif