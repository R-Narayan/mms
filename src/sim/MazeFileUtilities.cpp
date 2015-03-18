#include "MazeFileUtilities.h"

#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

#include "Assert.h"
#include "Directions.h"
#include "SimUtilities.h"

namespace sim {

std::pair<int, int> getMazeSize(const std::string& mazeFilePath) {

    // Note: This function should only be called on maze files that have been validated.
    // In particular, we assuming that the dimensions of the maze are given in the last,
    // line of the file, which might not be the case if the lines are properly sorted.

    // Read the last, non-empty line of the file
    std::ifstream file(mazeFilePath.c_str());
    std::string line("");
    std::string prevLine("");
    while (getline(file, line)) {
        if (!line.empty()) {
            prevLine = line;
        }
    }
    file.close();

    // Put the tokens in a vector
    std::istringstream iss(prevLine);
    std::vector<std::string> tokens;
    copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(),
         std::back_inserter<std::vector<std::string>>(tokens));

    // Extract the width and height values, adding 1 because we started counting at 0
    int width = strToInt(tokens.at(0)) + 1;
    int height = strToInt(tokens.at(1)) + 1;
    return std::make_pair(width, height);
}

bool validMaze(const std::string& mazeFilePath) {

    // TODO: This should ensure a PHYSICALLY POSSIBLE MAZE
    // TODO: SOM
    // Format requires that:
    // - File exists
    // - The correct number of rows and columns
    // - rows and cols are in expected order
    // - The rows and columns labeled correctly
    // - Walls are all valid
    // - The maze is surrounded by walls
    // This means that the maze can be unsolvable and any size and shape

    // TODO: Do we want to perform maze validation on autogenerated mazes? probably, just for safe keeping and consistency

    // First, make sure we've been given a file
    if (!isFile(mazeFilePath)) {
        print("Error: \"" + mazeFilePath + "\" is not a file");
        return false;
    }

    // Create the file object
    std::ifstream file(mazeFilePath.c_str());

    // Error opening file
    if (!file.is_open()) {
        print("Error: Could not open \"" + mazeFilePath + "\" for maze validation");
        return false;
    }

    // Initialize a string variable
    std::string line("");

    // Current x and y position
    int x = 0;
    int y = 0;

    // A vector to hold all tiles' values
    std::vector<std::vector<BasicTile>> maze;

    while (std::getline(file, line)) {

        // Extract the whitespace separated tokens
        std::vector<std::string> tokens = tokenize(line);

        // Check to see that there are exactly six entries...
        if (6 != tokens.size()) {
            print("Error: \"" + mazeFilePath + "\" does not contain six entries on each line");
            return false;
        }

        // ... all of which are numeric
        for (int i = 0; i < tokens.size(); i += 1) {
            if (!isInt(tokens.at(i))) {
                print("Error: \"" + mazeFilePath + "\" contains non-numeric entries");
                return false;
            }
        }

        BasicTile tile;
        tile.x = strToInt(tokens.at(0));
        tile.y = strToInt(tokens.at(1));
        for (Direction direction : DIRECTIONS) {
            tile.walls[direction] = strToInt(tokens.at(2+direction));
        }

        // TODO: Much more validation here
    }

    return true;
}

// TODO: Returns true if the maze file input follows all rules
// necessary to be an official micromouse maze, false otherwise
// NOTE: This function should only be called on valid mazes - that is,
// we can assume mazes are valid if this function is called
bool officialMaze(const std::string& mazeFilePath) {
    // TODO: SOM
    // Conditions:
    // 1.) Has a path to the center
    // 2.) No wall following robot can solve
    // Lots more...
    //
    // NOTE: It's probably a *really* good idea to make a helper function for each requirement, as in:
    // bool hasPathToCenter();
    // bool unsolvableByWallFollower();
    // bool hasOneEntrance(maze); 
    // bool eachPostHasWall(maze)
    // bool threeStartingWalls(maze); 
    //
    // etc.
   
    std::vector<std::vector<BasicTile>> maze;
    maze = loadMaze(mazeFilePath);

    //Check for path to center
    if(!hasPathToCenter(maze, 0, 0)) {
        return false;
    }

    //Check for one entrance to center tiles
    if(!hasOneEntrance(maze)) {
        return false;
    }

    //Check that each post has walls
    if(!eachPostHasWall(maze, 1, 1)) {
        return false;
    }
    
    //Check that the starting position has exactly three walls
    if(!threeStartingWalls(maze)) {
        return false;
    }

    return true;
}

bool hasPathToCenter(const std::vector<std::vector<BasicTile>>& maze, int x, int y) {
    static std::vector<bool> checkRow(16, false);
    static std::vector<std::vector<bool>> checkTiles(16, checkRow);
    checkTiles.at(x).at(y) = true;
    bool eastCheck = false, southCheck = false, westCheck = false, northCheck = false;
    
    //Check for center tile
    if((x==7||x==8)&&(y==7||y==8)) {
        return true;
    }

    //Check north tile
    if(y != 15 && !maze.at(x).at(y).walls.at(NORTH) && !checkTiles.at(x).at(y+1)) {
        northCheck = hasPathToCenter(maze, x, y+1);
    }

    //Check east tile
    if(x != 15 && !maze.at(x).at(y).walls.at(EAST) && !checkTiles.at(x+1).at(y)) {
        eastCheck = hasPathToCenter(maze, x+1, y);
    }
    //Check south tile
    if(y != 0 && !maze.at(x).at(y).walls.at(SOUTH) && !checkTiles.at(x).at(y-1)) { 
        southCheck = hasPathToCenter(maze, x, y-1);
    }
    //Check west tile
    if(x != 0 && !maze.at(x).at(y).walls.at(WEST) && !checkTiles.at(x-1).at(y)) {
        westCheck = hasPathToCenter(maze, x-1, y);
    }

    return eastCheck || southCheck || westCheck || northCheck;
}

bool hasOneEntrance(const std::vector<std::vector<BasicTile>>& maze) {
    int entranceCounter = 0;
    
    //Check lower left entrances
    entranceCounter += !maze.at(7).at(7).walls.at(SOUTH);
    entranceCounter += !maze.at(7).at(7).walls.at(WEST);
    //Check upper left entrances
    entranceCounter += !maze.at(7).at(8).walls.at(NORTH);
    entranceCounter += !maze.at(7).at(8).walls.at(WEST);
    //Check lower right entrances
    entranceCounter += !maze.at(8).at(7).walls.at(SOUTH);
    entranceCounter += !maze.at(8).at(7).walls.at(EAST);
    //Check upper right entrances
    entranceCounter += !maze.at(8).at(8).walls.at(NORTH);
    entranceCounter += !maze.at(8).at(8).walls.at(EAST);

    return entranceCounter == 1;
}

bool eachPostHasWall(const std::vector<std::vector<BasicTile>>& maze, int x, int y) {
    static std::vector<bool> checkRow(16, false);
    static std::vector<std::vector<bool>> checkTiles(16, checkRow);
    bool northCheck = true, eastCheck = true;    

    checkTiles.at(x).at(y) = true;
    
    //Check if upper right tile
    if(x == 15 && y == 15) {
        return true;
    }  

    int wallCount = 0;
    //Check bottom left post
    wallCount += maze.at(x).at(y).walls.at(WEST);
    wallCount += maze.at(x).at(y).walls.at(SOUTH);   
    if(x != 0) {
        wallCount += maze.at(x-1).at(y).walls.at(SOUTH);
    }
    if(y != 0) {
        wallCount += maze.at(x).at(y-1).walls.at(WEST);
    }

    if(wallCount == 0 && (x != 8 || y != 8)) {
        return false;
    }
    else {
        if(y != 15 && checkTiles.at(x).at(y+1) == false) {
            northCheck = eachPostHasWall(maze, x, y + 1);
        }
        if(x != 15 && checkTiles.at(x+1).at(y) == false) {
            eastCheck = eachPostHasWall(maze, x + 1, y);
        }
        return northCheck && eastCheck;
    }
}

bool threeStartingWalls(const std::vector<std::vector<BasicTile>>& maze) {
    int wallCount = 0;
    wallCount += (maze.at(0).at(0).walls.at(NORTH) ? 1 : 0);
    wallCount += (maze.at(0).at(0).walls.at(EAST)  ? 1 : 0);
    wallCount += (maze.at(0).at(0).walls.at(SOUTH) ? 1 : 0);
    wallCount += (maze.at(0).at(0).walls.at(WEST)  ? 1 : 0);
    return wallCount == 3;
}

void saveMaze(const std::vector<std::vector<BasicTile>>& maze, const std::string& mazeFilePath) {

    // Create the stream
    std::ofstream file(mazeFilePath.c_str());

    // Make sure the file is open
    if (!file.is_open()) {
        print("Error: Unable to save maze to \"" + mazeFilePath + "\"");
        return;
    }

    // Write to the file
    for (int x = 0; x < maze.size(); x += 1) {
        for (int y = 0; y < maze.at(x).size(); y += 1) {
            file << x << " " << y;
            for (Direction direction : DIRECTIONS) {
                // Note: We use to use this ugly syntax here since walls[direction] is non-const
                file << " " << (maze.at(x).at(y).walls.find(direction)->second ? 1 : 0);
            }
            file << std::endl;
        }
    }

    file.close();
}

std::vector<std::vector<BasicTile>> loadMaze(const std::string& mazeFilePath) {

    // This should only be called on mazes that have been validated. In particular,
    // we assume that the file exists and has the proper format.
    ASSERT(validMaze(mazeFilePath));

    // The maze to be returned
    std::vector<std::vector<BasicTile>> maze;

    // First, determine the dimensions of the maze
    std::pair<int, int> mazeSize = getMazeSize(mazeFilePath);
    int width = mazeSize.first;
    int height = mazeSize.second;

    // Then, create the individual tile objects
    for (int x = 0; x < width; x += 1) {
        std::vector<BasicTile> col;
        for (int y = 0; y < height; y += 1) {
            BasicTile tile;
            tile.x = x;
            tile.y = y;
            col.push_back(tile);
        }
        maze.push_back(col);
    }

    // Lastly, read the file and populate the wall values
    std::ifstream file(mazeFilePath.c_str());
    std::string line("");
    while (getline(file, line)) {

        // Put the tokens in a vector
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(),
             std::back_inserter<std::vector<std::string>>(tokens));

        // Set the values of all of the walls
        for (Direction direction : DIRECTIONS) {
            BasicTile* tile = &maze.at(strToInt(tokens.at(0))).at(strToInt(tokens.at(1)));
            tile->walls[direction] = (1 == strToInt(tokens.at(2 + direction)));
        }
    }
    file.close();
  
    return maze;
}

} //namespace sim
