#pragma once
#include <vector>
#include <iostream>

class Grid
{
private:
    int grid_height;
    int grid_width;
    std::vector<std::vector<int>> matrix;
    void moveLineDown(int lineIndex);

public:
    Grid() = default;
    Grid(int grid_height, int grid_width) : grid_height(grid_height),
                                            grid_width(grid_width), 
                                            matrix(grid_height, 
                                            std::vector<int>(grid_width, 0)) {};
    int getGridHeight() const { return grid_height; };
    int getGridWidth() const { return grid_width; };
    std::vector<std::vector<int>> &getMatrix() { return matrix; };

    int checkForFullLines();
    
};



class Game
{
private:
    Grid grid;

public:
    Game(Grid grid) : grid(grid) {};
    Grid& getGrid() {return grid;};
    
};

