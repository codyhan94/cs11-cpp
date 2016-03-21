#include <iostream>
#include <vector>
#include <utility>

#include <cstdlib>

#include "tsp-ga.hh"

/*! Constructs an instance of TSPGenome with a random ordering of NUM_POINTS. */
TSPGenome::TSPGenome(int num_points)
{
    int i;

    for (i = 0; i < num_points; i++)
    {
        order.push_back(i);
    }

    random_shuffle(order.begin(), order.end());

    circuit_length = 1e9;
}

/*! Constructs an instance of TSPGenome with a specified ORDER. */
TSPGenome::TSPGenome(const std::vector<int> &order)
{
    this->order = order;

    circuit_length = 1e9;
}

TSPGenome::~TSPGenome(void)
{
    // no-op
}

/*! Getters for the order and circuit lengths. */
std::vector<int> TSPGenome::getOrder(void) const
{
    return order;
}

double TSPGenome::getCircuitLength(void) const
{
    return circuit_length;
}

/*! Computes the length of a circuit using the ORDER in this class on the passed
    POINTS vector. Stores the computed length in the CIRCUIT_LENGTH variable.

    Returns nothing. */
void TSPGenome::computeCircuitLength(const std::vector<Point> &points)
{
    int i;
    circuit_length = 0.0;

    for (i = 0; i < order.size() - 1; i++)
    {
        circuit_length += points[order[i]].distanceTo(points[order[i+1]]);
    }

    circuit_length += points[order[order.size() - 1]].distanceTo(points[order[0]]);
    return;
}

/*! Randomly swaps two elements in the ORDER vector. */
void TSPGenome::mutate(void)
{
    int i, j;
    i = j = 0;

    while (i == j)
    {
        i = rand() % order.size();
        j = rand() % order.size();
    }

    std::swap(order[i], order[j]);
}
