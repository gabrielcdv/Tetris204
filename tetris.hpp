#pragma once
#include <vector>
#include <iostream>
#include <mutex>
#include <SFML/Network.hpp>
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
    int counter ; // Compteur pour connaître le nombre de lignes retirées depuis le début de la partie
    char piece ;
    char pieceIn1 ;
    char pieceIn2 ;
    char pieceIn3 ;
    char pieceIn4 ;
    char pieceIn5 ;
    bool multiplayer;
    std::string enemyGrid;
    std::mutex enemyGridMutex; // Mutex pour éviter lecture/écriture simultanée
    sf::TcpSocket& enemySocket;
public:
    Game(Grid& grid, bool multiplayer, sf::TcpSocket& enemySocket);
    Game(Grid& grid) : Game(grid, false, enemySocket) {};
    Grid& getGrid() {return grid;};
    GameWindow& getWindow() {return gameWindow;};
    void startGame();
    const void animateWindow();
    void updateScore();
    int getLevel(){return level;};
    void updateLevel();
    char& getPiece(){return piece ;};
    char& getPieceIn1(){return pieceIn1 ;};
    char& getPieceIn2(){return pieceIn2 ;};
    char& getPieceIn3(){return pieceIn3 ;};
    char& getPieceIn4(){return pieceIn4 ;};
    char& getPieceIn5(){return pieceIn5 ;};
    char randomPiece();
    bool isGameOver(char type, std::vector<int> mGridPosition);
    bool isMultiplayer() {return multiplayer;};
    void setEnemyGrid(std::string str);
    std::string getEnemyGrid();
    
};

