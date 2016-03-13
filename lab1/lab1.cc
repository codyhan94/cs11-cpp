#define NUM_POINTS 3

int main(int argc, char const *argv[])
{
    using namespace std;
    int i;
    double x, y, z;

    Point buf[NUM_POINTS];

    for (i = 0; i < NUM_POINTS; i++)
    {
        cout << "Enter 3 coordinates separated by whitespace for point " << i << ":";
        cin >> x >> y >> z;
        buf[i] = Point(x, y, z);
    }

    for (i = 0; i < NUM_POINTS; i++)
    {
        cout << buf[i] << endl;
    }

    return 0;
}