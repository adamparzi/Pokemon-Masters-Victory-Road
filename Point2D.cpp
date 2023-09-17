#include <iostream>
#include <fstream> // for filestream, reading and writing to file
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <iomanip>

#include "Point2D.h"
#include "Vector2D.h"

using namespace std;

// friend ostream& operator << (ostream& out, Point2D& obj); NOT NEEDED, since all members are public

Point2D::Point2D()
{
    x = 0.0;
    y = 0.0;
}

Point2D::Point2D(double in_x, double in_y)
{
    x = in_x;
    y = in_y;
}

double GetDistanceBetween(const Point2D p1, const Point2D p2)
{
    return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}

ostream &operator<<(ostream &out, const Point2D &obj)
{
    out << "(" << obj.x << ", " << obj.y << ")";
    return out;
}

Point2D operator+(const Point2D &p1, const Vector2D &v1)
{
    return Point2D(p1.x + v1.x, p1.y + v1.y);
}

Vector2D operator-(const Point2D &p1, const Point2D &p2)
{
    return Vector2D(p1.x - p2.x, p1.y - p2.y);
}
