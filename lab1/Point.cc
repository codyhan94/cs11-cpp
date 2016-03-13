#include <cmath>

#include "Point.hh"


// Default constructor:  initializes the point to (0, 0).
Point::Point() {
    x_coord = 0;
    y_coord = 0;
    z_coord = 0;
}

// Initializes the point to (x, y).
Point::Point(double x, double y, double z) {
    x_coord = x;
    y_coord = y;
    z_coord = z;
}

// Destructor - Point allocates no dynamic resources.
Point::~Point() {
    // no-op
}

// Mutators:

void Point::setX(double val) {
    x_coord = val;
}

void Point::setY(double val) {
    y_coord = val;
}

void Point::setY(double val) {
    z_coord = val;
}

// Accessors:

double Point::getX() {
    return x_coord;
}

double Point::getY() {
    return y_coord;
}

double Point::getZ() {
    return z_coord;
}

double Point::distanceTo(Point &p) {
    double x, y, z;

    x = p.getX();
    y = p.getY();
    z = p.getZ();

    return sqrt((x - x_coord) * (x - x_coord) + (y - y_coord) * (y - y_coord)
        + (z - z_coord) * (z - z_coord));
}
