#include <cmath>
#include <iostream>

#include "Point.hh"

#define NUM_POINTS 3

/*! Computes the area of the triangle specified by points a, b, and c using
    Heron's formula. */
double computeArea(Point &a, Point &b, Point &c)
{
    double s, ab, bc, ac, area;

    /* Compute the three side lengths in the triangle. */
    ab = a.distanceTo(b);
    bc = b.distanceTo(c);
    ac = a.distanceTo(c);

    /* Compute the semiperimeter. */
    s = (ab + bc + ac) / 2.0;

    /* Compute the actual area. */
    area = sqrt(s * (s - ab) * (s - bc) * (s - ac));

    return area;
}

int main(int argc, char const *argv[])
{
    using namespace std;
    int i;
    double x, y, z, area;

    /* Allocate a buffer on the stack for the number of points we want. */
    Point buf[NUM_POINTS];

    for (i = 0; i < NUM_POINTS; i++)
    {
        cout << "Enter 3 coordinates separated by whitespace for point " <<
            i << ": " << endl;
        cin >> x >> y >> z;
        buf[i].setX(x);
        buf[i].setY(y);
        buf[i].setZ(z);
    }

    /* Compute the area of the triangle determined by the 3 points. */
    area = computeArea(buf[0], buf[1], buf[2]);

    /* Echo the points back to the user. */
    for (i = 0; i < NUM_POINTS; i++)
    {
        cout << "Point " << i << ":\t" << buf[i] << endl;
    }

    /* Print the computed area. */
    cout << "Area is:\t" << area << endl;

    return 0;
}
