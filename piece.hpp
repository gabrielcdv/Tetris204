#pragma once
#include "color.hpp"
#include "tetris.hpp"
#include <vector>

class Piece{
    protected :
        std::vector<std::vector<int>> mPoints ;
        char mType ;
        Color mColor ;
        bool rotateForPreview; // Faut-il tourner la pièce pour qu'elle soit horizontale pour l'aperçu (next pieces)
        int width = 2; //Largeur en blocs quand la pièce est verticale
    public :
        Piece()=default;
        std::vector<std::vector<int>> getPoints() const {return mPoints ;};
        char getType() const {return mType ;};
        Color getColor() const {return mColor ;};
        Piece(char type);
        bool getRotateForPreview() {return rotateForPreview;};
        void rotateLeftNoCheck();// Effectue une rotation (distinct de FallingPiece::rotateLeft d'ou le NoCheck)
        int getWidth() {return width;};
};

class FallingPiece : public Piece {
    private :
        Grid& mGrid ;
        std::vector<int> mGridPosition; //position du centre de la pièce dans la grille - on imagine une grille (10, 22) avec le coin en haut à gauche à (0,0) donc numérotation d'en bas à droite (9, 21)
        bool anchor;
        void checkReachedBottom();
    public :    
        FallingPiece()= default;
        FallingPiece(Grid& grid, std::vector<int> gridPosition, char type) : Piece(type), mGrid(grid), mGridPosition(gridPosition){};
        std::vector<int> getGridPosition() const {return mGridPosition ;};
        std::vector<std::vector<int>> getPointsInGrid() const ;
        
        bool getAnchor() {return anchor;};
        void setAnchor(bool anc) {anchor=anc;};
        void moveRight();
        void moveLeft();
        void moveDown();
        void rotateRight();
        void rotateLeft();
        void stamp();
        bool canMoveDown();
};

bool checkFit(Grid& grid, std::vector<std::vector<int>> points, std::vector<int> gridPosition);