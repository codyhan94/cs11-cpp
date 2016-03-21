#include <algorithm>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unordered_set>

#include "tsp-ga.hh"
#include "print_vector.h"

static TSPGenome findAShortPath(const std::vector<Point> &points,
    int populationSize, int numGenerations, int keepPopulation,
    int numMutations);
static TSPGenome crosslink(const TSPGenome &g1, const TSPGenome &g2);
static void usage(const char *prog_name);

static void usage(const char *prog_name)
{
    std::cerr << "Usage: " << prog_name << " population generations keep mutate"
        << std::endl << "where" << std::endl << "\tpopulation specifies the population size"
        << std::endl << "\tgenerations specifies how many generations to run the GA for" << std::endl
        << "\tkeep is a floating point in [0, 1] specifying the percent of the population to preserve from generation to generation" << std::endl
        << "\tmutate is a non-negative floating point number specifying how many mutations to apply to each member of the population on average." << std::endl;
    exit(1);
}

int main(int argc, char const *argv[])
{
    using namespace std;

    if (argc != 5)
    {
        usage(argv[0]);
    }

    int population_size, num_generations;
    double keep, mutate;

    /* Read the arguments, checking that each is in-bounds. */
    population_size = atoi(argv[1]);
    if (population_size <= 0)
    {
        usage(argv[0]);
    }

    num_generations = atoi(argv[2]);
    if (num_generations <= 0)
    {
        usage(argv[0]);
    }

    keep = atof(argv[3]);
    if (keep < 0.0 || keep > 1.0)
    {
        usage(argv[0]);
    }

    mutate = atof(argv[4]);
    if (mutate < 0)
    {
        usage(argv[0]);
    }

    /* Seed the random number generator. */
    srand(time(nullptr));

    /* Prompt user for the number of points. */
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

    /* Find a short Hamiltonian cycle using our genetic algorithm. */
    TSPGenome g = findAShortPath(pts, population_size, num_generations,
        keep * population_size, mutate * population_size);

    /* Print the path and its cost to STDOUT. */
    cout << "Best order:\t" << g.getOrder() << endl;
    cout << "Shortest distance:\t" << g.getCircuitLength() << endl;

    return 0;
}

/*! Comparator function for comparing the fitnesses of two different genomes. */
static bool isShorterPath(const TSPGenome &g1, const TSPGenome &g2)
{
    return (g1.getCircuitLength() < g2.getCircuitLength());
}

/*! Genetic algorithm for finding a short Hamiltonian cycle in POINTS. */
static TSPGenome findAShortPath(const std::vector<Point> &points,
    int populationSize, int numGenerations, int keepPopulation, int numMutations)
{
    std::vector<TSPGenome> genomes;
    int i, gen;

    /*! Create an initial population of random genomes and record their
        fitnesses. */
    for (i = 0; i < populationSize; i++)
    {
        TSPGenome genome = TSPGenome(points.size());
        genomes.push_back(genome);
        genome.computeCircuitLength(points);
    }

    gen = 1;
    while (gen <= numGenerations)
    {
        /* Every 10 generations, print out the shortest distance found so far. */
        if (gen % 10 == 0)
        {
            std::cout << "Generation " << gen << ": shortest path is "
                << genomes[0].getCircuitLength() << std::endl;
        }

        /* Sort the population by fitness. */
        std::sort(genomes.begin(), genomes.end(), isShorterPath);

        /* Replace all but the top KEEP_POPULATION genomes in the population. */
        for (i = keepPopulation; i < populationSize; i++)
        {
            int g1, g2;
            g1 = g2 = 0;
            while (g1 == g2)
            {
                g1 = rand() % keepPopulation;
                g2 = rand() % keepPopulation;
            }

            /* Replace each inferior genome with a crosslink between two superior ones. */
            genomes[i] = crosslink(genomes[g1], genomes[g2]);
        }

        /* Apply the specified number of mutations to the population. */
        for (i = 0; i < numMutations; i++)
        {
            int mut_idx = 1 + rand() % (populationSize - 1);
            genomes[mut_idx].mutate();
        }

        /* Recompute all circuit lengths after mutation. */
        for (i = 0; i < populationSize; i++)
        {
            genomes[i].computeCircuitLength(points);
        }
        gen++;
    }

    /* Return the fittest genome. */
    return genomes[0];
}

/*! Crosses two genomes G1 and G2 and returns a new genome with an ordering that
    derives from both G1 and G2.*/
static TSPGenome crosslink(const TSPGenome &g1, const TSPGenome &g2)
{
    std::vector<int> new_order;
    std::unordered_set<int> g1_chosen;

    int i, j, elem;

    /* Choose a splitting point in the first genome. */
    i = rand() % g1.getOrder().size();

    for (j = 0; j <= i; j++)
    {
        elem = g1.getOrder()[j];
        new_order.push_back(elem);
        g1_chosen.insert(elem);
    }

    /*! Put all points in G2 into the new ordering that weren't already obtained
        from G1. */
    for (j = 0; j < g2.getOrder().size(); j++)
    {
        elem = g2.getOrder()[j];
        if (g1_chosen.find(elem) == g1_chosen.end())
        {
            /* This element was not inserted before, let's insert it. */
            new_order.push_back(elem);
        }
    }

    return TSPGenome(new_order);
}
