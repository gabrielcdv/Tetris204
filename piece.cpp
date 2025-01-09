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

FallingPiece::FallingPiece(Grid mGrid, std::vector<int> mGridPosition){
    for (size_t i = 0; i < mPoints.size(); ++i){
        mPointsInGrid[i][0] = mPoints[i][0] + mGridPosition[0];
        mPointsInGrid[i][1] = mPoints[i][1] + mGridPosition[1];
    }
};

bool FallingPiece::checkFit(int newx, int newy){
    if (newx<mGrid.getGridWidth()){
        return false;
    }
    if (newy<mGrid.getGridHeight()){
        return false;
    }
    if (mGrid.getMatrix()[newx][newy]!=0){
        std::cout << "La case est déjà occupée" << std::endl ;
        return false;
    }
    else {
        return true ;
    }
}

void FallingPiece::rotateRight(){
    for (size_t i = 0; i < mPointsInGrid.size(); ++i) {
        int newx = mPointsInGrid[i][1];
        int newy = mPointsInGrid[i][0];
        if (checkFit(newx, newy)){
            mPointsInGrid[i][0] = newx ;
            mPointsInGrid[i][1] = newy;
        };
    }
}

void FallingPiece::rotateLeft(){
    for (size_t i = 0; i < mPointsInGrid.size(); ++i) {
        int newx = mPointsInGrid[i][1];
        int newy = - mPointsInGrid[i][0];
        if (checkFit(newx, newy)){
            mPointsInGrid[i][0] = newx ;
            mPointsInGrid[i][1] = newy;
        };
    }
}

void FallingPiece::moveRight(){ 
    for (size_t i = 0; i < mPointsInGrid.size(); ++i) {
        int newx = mPointsInGrid[i][0]+1;
        int newy = mPointsInGrid[i][1];
        if (checkFit(newx, newy)){
            mPointsInGrid[i][0] = newx ;
            mPointsInGrid[i][1] = newy;
        };
    }
};

void FallingPiece::moveLeft(){
    for (size_t i = 0; i < mPointsInGrid.size(); ++i) {
        int newx = mPointsInGrid[i][0]-1;
        int newy = mPointsInGrid[i][1];
        if (checkFit(newx, newy)){
            mPointsInGrid[i][0] = newx ;
            mPointsInGrid[i][1] = newy;
        };
    }
};

void FallingPiece::moveDown(){
    for (size_t i = 0; i < mPointsInGrid.size(); ++i) {
        int newx = mPointsInGrid[i][0];
        int newy = mPointsInGrid[i][1]+1;
        if (checkFit(newx, newy)){
            mPointsInGrid[i][0] = newx ;
            mPointsInGrid[i][1] = newy;
        };
    }
};

