#include "window.hpp"
#include "tetris.hpp"
#include "piece.hpp"
#include <vector>
#include <iostream>


int main() {
    Grid gamegrid(22,10);
    Game game(gamegrid);
    GameWindow fenetre=GameWindow();
    

    Piece test_piece('L');
    int color = test_piece.getColor();
    std::cout << "La couleur est : " << color << std::endl;
    char type = test_piece.getType();
    std::cout << "Le type de pièce est" << type << std::endl ;
    std::vector<std::vector<int>> points = test_piece.getPoints();

    std::cout << "Les coordonnées des points sont" << std::endl ;
    for (const auto& point : points) {
    std::cout << "(";
    for (size_t i = 0; i < point.size(); ++i) {
        std::cout << point[i];
        if (i < point.size() - 1) std::cout << ", ";
    }
    std::cout << ")" << std::endl;
    }

    FallingPiece test_piece_falling(gamegrid, {3,2}, 'L');

    std::vector<int> position_dans_grille = test_piece_falling.getGridPosition();
    std::cout << "Les coordonnées du centre dans la grille sont" << std::endl ;
    std::cout << "(";
    for (size_t i = 0; i < position_dans_grille.size(); ++i) {
        std::cout << position_dans_grille[i];
        if (i < position_dans_grille.size() - 1) std::cout << ", ";
    }
    std::cout << ")" << std::endl;

    std::vector<std::vector<int>> pointsInGrid = test_piece_falling.getPointsInGrid();

    std::cout << "Les coordonnées des points dans la grille sont :" << std::endl;

    for (const auto& point : pointsInGrid) {
    std::cout << "(";
        for (size_t i = 0; i < point.size(); ++i) {
            std::cout << point[i];
            if (i < point.size() - 1) std::cout << ", ";
        }
    std::cout << ")" << std::endl;
    }

    test_piece_falling.moveRight();

    pointsInGrid = test_piece_falling.getPointsInGrid();

    std::cout << "Les coordonnées des points dans la grille sont :" << std::endl;

    for (const auto& point : pointsInGrid) {
    std::cout << "(";
        for (size_t i = 0; i < point.size(); ++i) {
            std::cout << point[i];
            if (i < point.size() - 1) std::cout << ", ";
        }
    std::cout << ")" << std::endl;
    }

    test_piece_falling.moveLeft();

    pointsInGrid = test_piece_falling.getPointsInGrid();

    std::cout << "Les coordonnées des points dans la grille sont :" << std::endl;

    for (const auto& point : pointsInGrid) {
    std::cout << "(";
        for (size_t i = 0; i < point.size(); ++i) {
            std::cout << point[i];
            if (i < point.size() - 1) std::cout << ", ";
        }
    std::cout << ")" << std::endl;
    }

    test_piece_falling.moveDown();

    pointsInGrid = test_piece_falling.getPointsInGrid();

    std::cout << "Les coordonnées des points dans la grille sont :" << std::endl;

    for (const auto& point : pointsInGrid) {
    std::cout << "(";
        for (size_t i = 0; i < point.size(); ++i) {
            std::cout << point[i];
            if (i < point.size() - 1) std::cout << ", ";
        }
    std::cout << ")" << std::endl;
    }

    test_piece_falling.rotateRight();

    pointsInGrid = test_piece_falling.getPointsInGrid();

    std::cout << "Les coordonnées des points dans la grille sont :" << std::endl;

    for (const auto& point : pointsInGrid) {
    std::cout << "(";
        for (size_t i = 0; i < point.size(); ++i) {
            std::cout << point[i];
            if (i < point.size() - 1) std::cout << ", ";
        }
    std::cout << ")" << std::endl;
    }

    test_piece_falling.rotateLeft();


    return 0;
}