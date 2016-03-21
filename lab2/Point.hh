#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>

// A 3-dimensional point class!
// Coordinates are double-precision floating point.
class Point {

private:
  double x_coord;
  double y_coord;
  double z_coord;

public:
    // Constructors
    Point();                      // default constructor
    Point(double x, double y, double z);    // three-argument constructor

    // Destructor
    ~Point();

    // Mutator methods
    void setX(double val);
    void setY(double val);
    void setZ(double val);

    // Accessor methods
    double getX() const;
    double getY() const;
    double getZ() const;

    double distanceTo(const Point &p) const;
};

// Operator overload for convenience
inline std::ostream& operator << (std::ostream &os, const Point &p) {
    return os << "(" << p.getX() << ", " << p.getY() << ", " << p.getZ() << ")";
}

#endif /* End of include guard for Point.hh */
