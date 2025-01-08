#pragma once
#include <vector>
#include <iostream>
#include "display.hpp"

class Game
{
private:
    Grid grid;

public:
    Game(Grid grid) : grid(grid) {};
    Grid& getGrid() {return grid;};
    
};

