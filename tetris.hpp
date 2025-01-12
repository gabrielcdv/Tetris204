#pragma once
#include <vector>
#include <iostream>
#include "window.hpp"
#include "color.hpp"


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
    std::vector<std::vector<Color>>& getMatrix() { return matrix; };
    

    int checkForFullLines();
    
};



class Game
{
private:
    Grid& grid;
    GameWindow gameWindow;
    int level ;
    int score ;
    int counter ; //compteur pour connaître le nombre de lignes retirées depuis le début de la partie
public:
    Game(Grid& grid) : grid(grid), score(0), level(0){};
    Grid& getGrid() {return grid;};
    void startGame();
    void animateWindow();
    void updateScore();
    void updateLevel();

    bool isGameOver(char type, std::vector<int> mGridPosition);
    
};

