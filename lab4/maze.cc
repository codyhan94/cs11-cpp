#include <cassert>
#include <iostream>
#include <cstdio>

#include "maze.hh"

#define CELLS_SIZE(rows, cols) (((2 * rows) + 1) * ((2 * cols) + 1))

// Initialize a new maze of size rows x cols
Maze::Maze(int rows, int cols)
{
    numRows = rows;
    numCols = cols;

    cells = new MazeCell[CELLS_SIZE(rows, cols)];
    // std::cout << "allocated " << (2 * rows + 1) * (2 * cols + 1) << " maze cells." << std::endl;
    // std::cout << "rows: " << rows << "\tcols: " << cols << std::endl;
}

// Make a copy of an existing maze object
Maze::Maze(const Maze &m)
{
    // int cells_size = (2 * m.numRows + 1) * (2 * m.numCols + 1);
    int i;
    numRows = m.numRows;
    numCols = m.numCols;
    start   = m.start;
    end     = m.end;

    cells = new MazeCell[CELLS_SIZE(m.numRows, m.numCols)];

    for (i = 0; i < CELLS_SIZE(numRows, numCols); i++)
    {
        cells[i] = m.cells[i];
    }
}

// Maze destructor
Maze::~Maze()
{
    delete[] cells;
}

// Take 2D expanded coordinates and compute the corresponding 1D array index
int Maze::getArrayIndex(const Location &loc) const
{
    return (loc.row * (numCols * 2 + 1) + loc.col);
}

// Returns the expanded coordinates of the specified cell coordinates
Location Maze::getCellArrayCoord(int cellRow, int cellCol) const
{
    int r_exp = 2 * cellRow + 1;
    int c_exp = 2 * cellCol + 1;
    return Location(r_exp, c_exp);
}

// Returns the expanded coordinates of the wall on a specific side of a cell
// given in cell coordinates.
Location Maze::getWallArrayCoord(int cellRow, int cellCol, Direction dir) const
{
    Location cell = getCellArrayCoord(cellRow, cellCol);

    switch (dir)
    {
    case Direction::NORTH:
        cell.row -= 1;
        break;
    case Direction::SOUTH:
        cell.row += 1;
        break;
    case Direction::EAST:
        cell.col += 1;
        break;
    case Direction::WEST:
        cell.col -= 1;
        break;
    default:
        assert(false);
    }

    return cell;
}

// Returns the number of rows in the maze
int Maze::getNumRows() const
{
    return numRows;
}

// Returns the number of columns in the maze
int Maze::getNumCols() const
{
    return numCols;
}

// Maze assignment operator
Maze & Maze::operator=(const Maze &m)
{
    if (this != &m)
    {
        delete[] cells;

        int i;
        numRows = m.numRows;
        numCols = m.numCols;
        start   = m.start;
        end     = m.end;

        cells = new MazeCell[CELLS_SIZE(numRows, numCols)];

        for (i = 0; i < CELLS_SIZE(numRows, numCols); i++)
        {
            cells[i] = m.cells[i];
        }
    }
    return *this;
}

// Returns the starting point in the maze
Location Maze::getStart() const
{
    return start;
}

// Sets the starting point in the maze
void Maze::setStart(int row, int col)
{
    start = Location(row, col);
}

// Returns the ending point in the maze
Location Maze::getEnd() const
{
    return end;
}

// Sets the ending point in the maze
void Maze::setEnd(int row, int col)
{
    end = Location(row, col);
}

// Sets all cells and walls to be empty, so that the maze is
// completely cleared
void Maze::clear()
{
    int i;
    for (i = 0; i < CELLS_SIZE(numRows, numCols); i++)
    {
        cells[i] = MazeCell::EMPTY;
    }
}

/*! Places a wall at every location that there can be a wall in the maze, as well
    as the unused locations. Uses the fact that the actual maze cells are only
    found where the row and column coordinates are both odd.*/
void Maze::setAllWalls()
{
    int row, col;

    for (row = 0; row < 2 * numRows + 1; row++)
    {
        for (col = 0; col < 2 * numCols + 1; col++)
        {
            /* If at least one of row/col is even, set a wall. */
            if (!((row % 2) && (col % 2)))
            {
                cells[row * (2 * numCols + 1) + col] = MazeCell::WALL;
            }
        }
    }
}

// Returns the value of the specified row and column
MazeCell Maze::getCell(int cellRow, int cellCol) const
{
    int i = getArrayIndex(getCellArrayCoord(cellRow, cellCol));
    return cells[i];
}

void Maze::setCell(int cellRow, int cellCol, MazeCell val)
{
    int i = getArrayIndex(getCellArrayCoord(cellRow, cellCol));
    cells[i] = val;
}

// Returns the cell-coordinates of the neighboring cell in the specified
// direction.  Trips an assertion if the given cell has no neighbor in the
// specified direction (e.g. the NORTH neighbor of cell (0,5)).
Location Maze::getNeighborCell(int cellRow, int cellCol,
                               Direction direction) const
{
    /* Ensure that the passed row and column are valid. */
    assert(0 <= cellRow && cellRow <= numRows - 1);
    assert(0 <= cellCol && cellCol <= numCols - 1);

    /* Start the return location off where we are now. */
    Location loc(cellRow, cellCol);

    /*! Check each case and ensure that we do not let the row or column go out of
        bounds. */
    switch (direction)
    {
    case Direction::NORTH:
        assert(cellRow > 0);
        loc.row--;
        break;

    case Direction::SOUTH:
        assert(cellRow < (numRows - 1));
        loc.row++;
        break;

    case Direction::WEST:
        assert(cellCol > 0);
        loc.col--;
        break;

    case Direction::EAST:
        assert(cellCol < (numCols - 1));
        loc.col++;
        break;

    default:
        assert(false);
    }

    return loc;
}

// Returns true if there is a wall in the specified direction from the
// given cell, false otherwise
bool Maze::hasWall(int cellRow, int cellCol, Direction direction) const
{
    int i = getArrayIndex(getWallArrayCoord(cellRow, cellCol, direction));
    return (cells[i] == MazeCell::WALL);
}

// Puts a wall on the specified side of the given cell
void Maze::setWall(int cellRow, int cellCol, Direction direction)
{
    int i = getArrayIndex(getWallArrayCoord(cellRow, cellCol, direction));
    cells[i] = MazeCell::WALL;
}

// Removes a wall on the specified side of the given cell
void Maze::clearWall(int cellRow, int cellCol, Direction direction)
{
    int i = getArrayIndex(getWallArrayCoord(cellRow, cellCol, direction));
    cells[i] = MazeCell::EMPTY;
}

// Returns true if the specified maze cell has been visited.
bool Maze::isVisited(int cellRow, int cellCol) const
{
    int i = getArrayIndex(getCellArrayCoord(cellRow, cellCol));
    return cells[i] == MazeCell::VISITED;
}

// Changes the cell's value to VISITED
void Maze::setVisited(int cellRow, int cellCol)
{
    int i = getArrayIndex(getCellArrayCoord(cellRow, cellCol));
    cells[i] = MazeCell::VISITED;
}

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
void Maze::print(ostream &os) const
{
    /* Print the number of rows and the number of columns. */
    os << numRows << " " << numCols << std::endl;

    int r, c;

    for (r = 0; r < numRows; r++)
    {
        /* Print the walls above row r. */
        os << "+";
        for (c = 0; c < numCols; c++)
        {
            os << (hasWall(r, c, Direction::NORTH) ? "---+" : "   +");
        }

        os << std::endl;

        /* Print the contents of each cell in row r. */
        for (c = 0; c < numCols; c++)
        {
            os << (hasWall(r, c, Direction::WEST) ? "|" : " ");
            os << ((Location(r, c) == start) ? " S " :
                   (Location(r, c) == end)   ? " E " : "   ");
        }

        /* Finish the wall if there is one at the end of row r. */
        os << (hasWall(r, c - 1, Direction::EAST) ? "|" : " ");

        os << std::endl;
    }

    /* Print the walls below the last row. */
    os << "+";
    for (c = 0; c < numCols; c++)
    {
        os << (hasWall(r - 1, c, Direction::SOUTH) ? "---+" : "   +");
    }
}
