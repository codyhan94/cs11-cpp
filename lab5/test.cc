#include <cstdlib>
#include <ctime>

#include <iostream>
#include <vector>

#include "../print_vector.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    srand(time(nullptr));

    int i, chosen;
    vector<int> v;
    for (i = 0; i < 10; i++)
        v.push_back(i);

    chosen = rand() % v.size();
    cout << "chose " << chosen << endl;

    v.erase(v.begin() + chosen);

    cout << v << endl;

    return 0;
}
