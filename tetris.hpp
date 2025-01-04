#pragma once
#include <vector>
#include <iostream>
class Game
{
private:
    int grid_height;
    int grid_width;
    std::vector<std::vector<int>> grid;

public:
    Game(int height, int width) : grid_height(height), grid_width(width), grid(grid_height, std::vector<int>(grid_width, 0)) {};
    int getGridHeight() const {return grid_height;};
    int getGridWidth() const {return grid_width;};
    std::vector<std::vector<int>>& getGrid() {return grid;};
};

