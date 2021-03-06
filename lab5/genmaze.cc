#include <cstdlib>
#include <ctime>
#include <cstdio>

#include <iostream>
#include <vector>

#include "maze.hh"

static void addDirectionOption(const Maze &m, const Location &current,
                               Direction dir, vector<Direction> &v);
static Maze generateMaze(int numRows, int numCols);
static void usage(const char *prog_name);

static void usage(const char *prog_name)
{
    std::cerr << prog_name << " numRows numCols" << std::endl
        << "\tnumRows is the number of rows in the maze" << std::endl
        << "\tnumCols is the number of columns in the maze" << std::endl;

    exit(1);
}

int main(int argc, char const *argv[])
{
    using namespace std;

    if (argc != 3)
        usage(argv[0]);

    int numRows, numCols;
    numRows = atoi(argv[1]);
    numCols = atoi(argv[2]);

    srand(time(nullptr));

    /* Generate the desired maze and print it out. */
    Maze m = generateMaze(numRows, numCols);
    m.print(cout);
    cout << endl;

    return 0;
}

/*! Generates a maze with NUMROWS rows and NUMCOLS columns.

    Uses a DFS approach to generate a path that satisfies the following
    conditions:

    1. The exterior of the maze is enclosed in walls.
    2. The maze contains no loops.
    3. The starting cell and ending cell each have three walls around them.
    4. The maze contains no empty regions.

    The maze generated will always start at the top left and end at the bottom
    right. */
static Maze generateMaze(int numRows, int numCols)
{
    Maze m(numRows, numCols);
    std::vector<Location> path;

    /* Set up the maze with all walls to start. */
    m.clear();
    m.setAllWalls();

    /* Top left is the start, bottom right is the end. */
    m.setStart(0, 0);
    m.setEnd(numRows - 1, numCols - 1);

    /* Seed the algorithm with our starting location. */
    m.setVisited(0, 0);
    path.push_back(Location(0, 0));

    while (!path.empty())
    {
        Location current = path.back();

        if ((current.row == numRows - 1) && (current.col = numCols - 1))
        {
            path.pop_back();
            continue;
        }

        vector<Direction> options;
        if (current.row > 0)
            addDirectionOption(m, current, Direction::NORTH, options);

        if (current.row < numRows - 1)
            addDirectionOption(m, current, Direction::SOUTH, options);

        if (current.col > 0)
            addDirectionOption(m, current, Direction::WEST, options);

        if (current.col < numCols - 1)
            addDirectionOption(m, current, Direction::EAST, options);

        if (options.empty())
        {
            /* No directions we can reach from this cell, need to backtrack. */
            path.pop_back();
            continue;
        }

        /* Clear a wall in one of the available directions. */
        Direction d = options[rand() % options.size()];

        m.clearWall(current.row, current.col, d);

        /* Move ourselves to the neighbor cell in the chosen direction. */
        Location next = m.getNeighborCell(current.row, current.col, d);
        m.setVisited(next.row, next.col);
        path.push_back(next);
    }

    return m;
}

/*! Adds DIR to V if the neighbor in direction DIR from CURRENT is unvisited
    in M. */
static void addDirectionOption(const Maze &m, const Location &current,
                               Direction dir, vector<Direction> &v)
{
    Location n = m.getNeighborCell(current.row, current.col, dir);
    if (!m.isVisited(n.row, n.col))
    {
        v.push_back(dir);
    }
}
