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

FallingPiece::FallingPiece(Grid grid, std::vector<int> gridPosition, char type) : Piece(type), mGrid(grid), mGridPosition(gridPosition){};


std::vector<std::vector<int>> FallingPiece::getPointsInGrid() const {
    std::vector<std::vector<int>> pointsInGrid ;
    for (size_t i = 0; i < mPoints.size(); ++i){
        pointsInGrid.push_back({mPoints[i][0] + mGridPosition[0], mPoints[i][1] + mGridPosition[1]});
    }
    return pointsInGrid ;
};

bool FallingPiece::checkFit(){
    if (mGridPosition[0]+1>=mGrid.getGridWidth()){
        return false;
    }
    if (mGridPosition[1]+1>=mGrid.getGridHeight()){
        return false;
    }
    for (size_t i = 0; i < mPoints.size(); ++i){
        int newx = mPoints[i][0] + mGridPosition[0];
        int newy = mPoints[i][1] + mGridPosition[1];
        if (mGrid.getMatrix()[newx][newy]!=0){
            std::cout << "La case est déjà occupée" << std::endl ;
            return false ;
        }
    }
    return true ;
}


void FallingPiece::rotateLeft(){
    if (checkFit()){
        for (size_t i = 0; i < mPoints.size(); ++i) {
            int newx = mPoints[i][1];
            int newy = - mPoints[i][0];            
            mPoints[i][0] = newx ;
            mPoints[i][1] = newy;
        }
    }
}

void FallingPiece::rotateRight(){
    if (checkFit()){
        for (size_t i = 0; i < mPoints.size(); ++i) {
            int newx = - mPoints[i][1];
            int newy = mPoints[i][0];            
            mPoints[i][0] = newx ;
            mPoints[i][1] = newy;         
        }
    }
}

void FallingPiece::moveRight(){ 
    if (checkFit()){
        mGridPosition[0]= mGridPosition[0]+1;
    }
};

void FallingPiece::moveLeft(){
    if (checkFit()){
        mGridPosition[0]= mGridPosition[0]-1;
    }
};

void FallingPiece::moveDown(){
    if (checkFit()){
        mGridPosition[1]= mGridPosition[1]+1;
    }
};


void FallingPiece::stampPiece() {
    /*
    Cette fonction grave la FallingPiece dans la grille (i.e. modifie la matrice de jeu pour 
    y inscrire les blocs de couleur de la pièce)
    */
   for (size_t k = 0; k < mPoints.size(); k++)
   {
    int i = mPoints[k][0] + mGridPosition[0];
    int j = mPoints[k][1] + mGridPosition[1];
    mGrid.getMatrix()[i][j]=mColor;
   }
   
};
