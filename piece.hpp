#pragma once
#include "color.hpp"
#include "tetris.hpp"
#include <vector>

class Piece{
    protected :
        std::vector<std::vector<int>> mPoints ;
        char mType ;
        Color mColor ; 
    public :
        std::vector<std::vector<int>> getPoints() const {return mPoints ;};
        char getType() const {return mType ;};
        int getColor() const {return mColor ;};
        Piece(char type);
};

class FallingPiece : public Piece {
    private :
        Grid mGrid ;
        std::vector<int> mGridPosition; //position du centre de la pièce dans la grille - on imagine une grille (10, 22) avec le coin en haut à gauche à (0,0) donc numérotation d'en bas à droite (9, 21)
        std::vector<std::vector<int>> mPointsInGrid ;
    public :    
        //ajouter constructeurs
        FallingPiece(Grid mGrid, std::vector<int> mGridPosition);
        std::vector<int> getGridPosition() const {return mGridPosition ;};
        bool checkFit(int newx, int newy);
        void moveRight();
        void moveLeft();
        void moveDown();
        void rotateRight();
        void rotateLeft();
};