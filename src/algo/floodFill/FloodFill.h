#ifndef FLOODFILL_H_
#define FLOODFILL_H_

#include "../IAlgorithm.h"
#include "Cell.h"

// Constants
static const int MAZE_SIZE = 16;
enum {NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3};

class FloodFill : public IAlgorithm{

public:
    void solve(sim::MouseInterface* mouse); // IAlgorithm interface method

private:
    sim::MouseInterface* m_mouse; // Mouse used to traverse and solve the maze
    Cell m_cells[MAZE_SIZE][MAZE_SIZE]; // Grid a cells to store maze information
    int m_x; // X position of the mouse
    int m_y; // Y position of the mouse
    int m_d; // Direction of the mouse

    void printDistances(); // Prints the distance values of the cells in the maze
    void printWalls(); // Prints the wall values of the cells in the maze
    void initializeCenter(); // Initializes distance values from the center of the maze

    void walls(); // Updates the walls surrounding the robot
    void flood(int x, int y); // Floods the maze corresponding to new walls
    void moveTowardsGoal(); // Moves the mouse one step towards the goal (lower distance value)
    bool inGoal(); // Returns true if the mouse is in the center

    void moveForward(); // Updates x and y and moves mouse
    void turnRight(); // Updates direction and turns mouse
    void turnLeft(); // Updates direction and turns mouse

    Cell* getFrontCell(); // Returns the cell in front of the mouse
    Cell* getLeftCell(); // Returns the cell to the right of the mouse
    Cell* getRightCell(); // Returns the cell to the left of the mouse
    Cell* getRearCell(); // Returns the cell in the rear of the mouse
    bool spaceFront(); // Returns true if there's a cell in front of the mouse
    bool spaceLeft(); // Returns true if there's a cell to the left of the mouse
    bool spaceRight(); // Returns true if there's a cell to the right of the mouse
    int min(int one, int two, int three, int four); // Returns the min of four ints

    // Explores the entire searchable maze and fills the walls and distances TODO: clean up
    void explore();

    // Is only valid if the target destination is one cell away // TODO: clean up
    void moveOneCell(int xDest, int yDest);

    // Can be used to set the destination to any cell // TODO: Remove this?
    void initializeDestinationTile(int x, int y);
};

#endif // FLOODFILL_H_