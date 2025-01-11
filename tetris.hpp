#pragma once
#include <vector>
#include <iostream>
#include "window.hpp"
#include "color.hpp"
#include "piece.hpp"

class Grid
{
private:
    int grid_height;
    int grid_width;
    std::vector<std::vector<Color>> matrix;
    void moveLineDown(int lineIndex);

public:
    Grid() = default;
    Grid(int grid_height, int grid_width) : grid_height(grid_height),
                                            grid_width(grid_width), 
                                            matrix(grid_height, 
                                            std::vector<Color>(grid_width, Empty)) {};
    int getGridHeight() const { return grid_height; };
    int getGridWidth() const { return grid_width; };
    std::vector<std::vector<Color>> &getMatrix() { return matrix; };
    void stampPiece(FallingPiece piece);

    int checkForFullLines();
    
};



class Game
{
private:
    Grid grid;
    GameWindow gameWindow;

public:
    Game(Grid grid) : grid(grid) {};
    Grid& getGrid() {return grid;};
    void startGame();
    void animateWindow();
    
};

