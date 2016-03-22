#include <iostream>

using namespace std;


// A simple class for representing locations in a 2D array.  The class also
// implements equality/inequality operators so that we can see if two
// locations are the same or not.
class Location {
public:
    // The row and column of the location
    int row;
    int col;

    // Constructors for initializing locations
    Location(int row, int col) : row(row), col(col) { }
    Location() : row(0), col(0) { }
    
    // Returns true if this location is the same as the specified location
    bool operator==(const Location &loc) const {
        return row == loc.row && col == loc.col;
    }
    
    // Returns true if this location is different from the specified location
    bool operator!=(const Location &loc) const {
        return !(*this == loc);
    }

    friend std::ostream &operator <<(std::ostream &os, const Location &loc)
    {
        return os << "(" << loc.row << ", " << loc.col << ")";
    }
};

// std::ostream &operator <<(std::ostream &os, const Location &loc)
// {
// }

// Possible values for maze cells
enum class MazeCell {
    EMPTY,
    WALL,
    VISITED
};


// Directions that we can go, relative to a given maze cell
enum class Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};


class Maze {
    // The number of rows with cells in them
    int numRows;
    
    // The number of columns with cells in them
    int numCols;
    
    // The maze's "expanded representation"
    MazeCell *cells;

    // The start of the maze, in cell coordinates
    Location start;
    
    // The end of the maze, in cell coordinates
    Location end;

    // Take 2D expanded coordinates and compute the corresponding 1D array index
    int getArrayIndex(const Location &loc) const;

    // Returns the expanded coordinates of the specified cell coordinates
    Location getCellArrayCoord(int cellRow, int cellCol) const;

    // Returns the expanded coordinates of the wall on a specific side of a cell
    // given in cell coordinates.
    Location getWallArrayCoord(int cellRow, int cellCol, Direction dir) const;

public:
    // Initialize a new maze of size rows x cols
    Maze(int rows, int cols);
    
    // Make a copy of an existing maze object
    Maze(const Maze &m);
    
    // Maze destructor
    ~Maze();
    
    // Maze assignment operator
    Maze & operator=(const Maze &m);

    // Returns the number of rows in the maze
    int getNumRows() const;
    
    // Returns the number of columns in the maze
    int getNumCols() const;

    // Returns the starting point in the maze
    Location getStart() const;

    // Sets the starting point in the maze    
    void setStart(int row, int col);
    
    // Returns the ending point in the maze    
    Location getEnd() const;
    
    // Sets the ending point in the maze
    void setEnd(int row, int col);
    
    // Sets all cells and walls to be empty, so that the maze is
    // completely cleared
    void clear();
    
    // Places a wall at every location that can be a wall in the maze
    void setAllWalls();

    // Returns the value of the specified
    MazeCell getCell(int cellRow, int cellCol) const;

    void setCell(int cellRow, int cellCol, MazeCell val);

    // Returns the cell-coordinates of the neighboring cell in the specified
    // direction.  Trips an assertion if the given cell has no neighbor in the
    // specified direction (e.g. the NORTH neighbor of cell (0,5)).
    Location getNeighborCell(int cellRow, int cellCol,
                             Direction direction) const;

    // Returns true if there is a wall in the specified direction from the
    // given cell, false otherwise
    bool hasWall(int cellRow, int cellCol, Direction direction) const;

    // Puts a wall on the specified side of the given cell
    void setWall(int cellRow, int cellCol, Direction direction);

    // Removes a wall on the specified side of the given cell
    void clearWall(int cellRow, int cellCol, Direction direction);


    // Returns true if the specified maze cell has been visited.
    bool isVisited(int cellRow, int cellCol) const;

    // Changes the cell's value to VISITED
    void setVisited(int cellRow, int cellCol);


    // Outputs the maze using simple ASCII-art to the specified output stream.
    // The output format is as follows, using the example maze from the
    // assignment write-up.  (The text to the right of the maze is purely
    // explanatory, and you don't need to output it.)
    //
    // 3 4                 (# of rows and then # of columns)
    // +---+---+---+---+   (each cell is 3 spaces wide, with a + at each corner)
    // | S     |       |   (walls indicated by --- or |)
    // +---+   +   +   +   (start indicated by S, end indicated by E)
    // |   |   |   |   |
    // +   +   +   +   +
    // |           | E |
    // +---+---+---+---+
    void print(ostream &os) const;
};
