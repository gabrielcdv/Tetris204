#pragma once
#include "color.hpp"
#include <vector>

class Piece{
    protected :
        std::vector<std::vector<int>> mPoints ;
        char mType ;
        Color mColor ;
    public :
        std::vector<std::vector<int>> getPoints() const {return mPoints ;};
        char getType() const {return mType ;};
        Color getColor() const {return mColor ;};
        Piece(char type);
        void rotateRight();
        void rotateLeft();
};

class FallingPiece : public Piece {
    private :
        int width = 10 ;
        int height = 22 ;
        std::vector<int> mGridPosition; //position du centre de la pièce dans la grille - on imagine une grille (10, 22) avec le coin en haut à gauche à (0,0) donc numérotation d'en bas à droite (9, 21)
    public :    
        std::vector<int> getGridPosition() const {return mGridPosition ;};
        void moveRight();
        void moveLeft();
        void moveDown();
};

//Pour une rotation vers la droite, l'abscisse de chaque point devient l'ordonnée et inversement
//Pour une rotation vers la gauche