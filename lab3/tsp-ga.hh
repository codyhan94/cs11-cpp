#ifndef _TSP_GA_H_
#define _TSP_GA_H_

#include <vector>

#include "Point.hh"

class TSPGenome
{

private:
    std::vector<int> order;
    double circuit_length;

public:
    // Constructors
    TSPGenome(int num_points);
    TSPGenome(const std::vector<int> &order);

    // Destructor
    ~TSPGenome(void);

    // Accessors
    std::vector<int> getOrder(void) const;
    double getCircuitLength(void) const;

    void computeCircuitLength(const std::vector<Point> &points);
    void mutate(void);
};


#endif /* End of include guard for tsp-ga.hh */
