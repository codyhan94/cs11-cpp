#include <iostream>

#include "Point.hh"

#define NUM_POINTS 3

int main(int argc, char const *argv[])
{
    using namespace std;
    int i;
    double x, y, z;

    Point buf[NUM_POINTS];

    for (i = 0; i < NUM_POINTS; i++)
    {
        cout << "Enter 3 coordinates separated by whitespace for point " << i << ": ";
        cin >> x >> y >> z;
        buf[i].setX(x);
        buf[i].setY(y);
        buf[i].setZ(z);
    }

    for (i = 0; i < NUM_POINTS; i++)
    {
        cout << buf[i] << endl;
    }

    return 0;
}
