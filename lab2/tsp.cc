#include <cassert>

#include <algorithm>
#include <iostream>
#include <vector>

#include "Point.hh"
#include "print_vector.h"

double circuitLength(const std::vector<Point> &points, const std::vector<int> &order);
std::vector<int> findShortestPath(const std::vector<Point> &points);

int main(int argc, char const *argv[])
{
    using namespace std;

    int num_points, i;
    double x, y, z;

    cout << "How many points?" << endl;
    cin >> num_points;

    std::vector<Point> pts;

    /* Read in the specified number of points from STDIN. */
    for (i = 0; i < num_points; i++)
    {
        cout << "Point " << i << ":" << endl;
        cin >> x >> y >> z;
        pts.push_back(Point(x, y, z));
    }

    /* Compute the shortest path through the points and print it and its cost. */
    std::vector<int> shortest_path = findShortestPath(pts);
    cout << "Best order:\t" << shortest_path << endl;
    cout << "Shortest distance:\t" << circuitLength(pts, shortest_path) << endl;

    return 0;
}

/*! Returns the distance traveled in the points vector by traversing them in the
    order specified by a given order vector. */
double circuitLength(const std::vector<Point> &points, const std::vector<int> &order)
{
    int i;
    double dist = 0.0;

    assert(points.size() > 0);

    for (i = 0; i < order.size() - 1; i++)
    {
        dist += points[order[i]].distanceTo(points[order[i+1]]);
    }

    dist += points[order[order.size() - 1]].distanceTo(points[order[0]]);

    return dist;
}

/*! Finds the shortest Hamiltonian cycle in the passed vector of points.

    Uses a naive algorithm that checks every possible path.

    Complexity: O(n!) where n is the number of points.

    Returns a vector containing the order to travel through points for the
    shortest path. */
std::vector<int> findShortestPath(const std::vector<Point> &points)
{
    std::vector<int> best_path;
    double shortest_distance, cur_distance;
    int i;
    std::vector<int> path(points.size());

    /* Initial order of [0, 1, ... N - 1]. */
    for (i = 0; i < path.size(); i++)
    {
        path[i] = i;
    }

    /* Seed the shortest distance and path variables. */
    shortest_distance = circuitLength(points, path);
    best_path = path;

    /* Loop through all permutations of the n points. */
    while (next_permutation(path.begin(), path.end()))
    {
        cur_distance = circuitLength(points, path);
        // std::cout << path << "\t" << cur_distance << std::endl;

        /* If we found a shorter path, update the shortest distance and path. */
        if (cur_distance < shortest_distance)
        {
            shortest_distance = cur_distance;
            best_path = path;
        }
    }

    return best_path;
}
