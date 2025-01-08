#include "piece.hpp"
#include <iostream>

Piece::Piece(char type) : mType(type){
    //Faire un switch case pour les différents cas de lettres
    switch (type){ //on définit les coordonnées 0 pour la case que l'on considère être le milieu de la pièce
        case 'I':
            mColor = Cyan;
            mPoints = { {-2, 0}, {-1, 0}, {0, 0}, {1, 0}};
            break;
        
        case 'O':
            mColor = Orange; 
            mPoints = { {-1, 1}, {0, 1}, {-1, 0}, {0, 0}};
            break;
        
        case 'T':
            mColor = Yellow;
            mPoints = { {-1, 0}, {0, 0}, {1, 0}, {0, -1}};
            break;
        case 'L':
            mColor = Purple;
            mPoints = { {-1, -1}, {-1, 0}, {0, 0}, {1, 0}};
            break;
        case 'J':
            mColor = Blue;
            mPoints = { {-1, 0}, {0, 0}, {1, 0}, {1, -1}};
            break;
        case 'Z':
            mColor = Red;
            mPoints = { {-1, 0}, {0, 0}, {0, -1}, {1, -1}};
            break;
        case 'S':
            mColor = Green;
            mPoints = { {-1, 0}, {0, 0}, {0, 1}, {1, 1}};
            break;
    }
};

void Piece::rotateRight(){
    for (size_t i = 0; i < mPoints.size(); ++i) {
        int x = mPoints[i][0];
        mPoints[i][0] = mPoints[i][1] ;
        mPoints[i][1] = x;
    }
} //A REVOIR POUR VOIR SI CA SORT DE LA GRILLE, METTRE DANS FALLINGPIECE ??

void FallingPiece::moveRight(){
    if (mGridPosition[0] + 1 < width){
        mGridPosition[0] = mGridPosition[0] + 1;
    }
    else {
        std::cout << "La pièce ne peut sortir de la grille" << std::endl ;
    }
};

void FallingPiece::moveLeft(){
    if (mGridPosition[0] - 1 > 0){
        mGridPosition[0] = mGridPosition[0] - 1;
    }
    else {
        std::cout << "La pièce ne peut sortir de la grille" << std::endl ;
    }
};

void FallingPiece::moveDown(){
    if (mGridPosition[1] + 1 < height){
        mGridPosition[0] = mGridPosition[0] + 1;
    }
    else {
        std::cout << "La pièce ne peut sortir de la grille" << std::endl ;
        //REDIRIGER VERS L'IMPRESSION DE LA GRILLE ?
    }
};

