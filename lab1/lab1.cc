#include <cmath>
#include <iostream>

#include "Point.hh"

#define NUM_POINTS 3

double computeArea(Point &a, Point &b, Point &c)
{
    double s, ab, bc, ac, area;

    ab = a.distanceTo(b);
    bc = b.distanceTo(c);
    ac = a.distanceTo(c);

    s = (ab + bc + ac) / 2.0;
    area = sqrt(s * (s - ab) * (s - bc) * (s - ac));

    return area;
}

int main(int argc, char const *argv[])
{
    using namespace std;
    int i;
    double x, y, z, area;

    Point buf[NUM_POINTS];

    for (i = 0; i < NUM_POINTS; i++)
    {
        cout << "Enter 3 coordinates separated by whitespace for point " << i << ": ";
        cin >> x >> y >> z;
        buf[i].setX(x);
        buf[i].setY(y);
        buf[i].setZ(z);
    }

    area = computeArea(buf[0], buf[1], buf[2]);

    for (i = 0; i < NUM_POINTS; i++)
    {
        cout << buf[i] << endl;
    }

    cout << "Area:\t" << area << endl;

    return 0;
}
