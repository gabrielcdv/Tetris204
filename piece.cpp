#include "piece.hpp"
#include <iostream>

Piece::Piece(char type) : mType(type){
    /*Constructeur qui permet de définir les pièces à partir de son type*/
    switch (type){ //on définit les coordonnées 0 pour la case que l'on considère être le milieu de la pièce
        case 'I':
            mColor = Cyan;
            mPoints = { {-1, 0}, {0, 0}, {1, 0}, {2, 0}};
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




std::vector<std::vector<int>> FallingPiece::getPointsInGrid() const {
    /*Cette fonction permet de récupérer les coordonnées dans la grille d'une FallingPiece à un instant donné*/
    std::vector<std::vector<int>> pointsInGrid ;
    for (size_t i = 0; i < mPoints.size(); ++i){
        pointsInGrid.push_back({mPoints[i][0] + mGridPosition[0], mPoints[i][1] + mGridPosition[1]});
    }
    return pointsInGrid ;
};


bool checkFit(Grid& grid, std::vector<std::vector<int>> points, std::vector<int> gridPosition) {
    /*Cette fonction permet de vérifier si une pièce (représentée par un ensemble de points placés
    dans une grille grâce à la position du centre de cet ensemble) rentre dans cette grille et ne 
    se superpose pas avec une autre pièce déjà présente dans la grille*/
    for (size_t k = 0; k < points.size(); k++)
    {
        int i = points[k][0] + gridPosition[0];
        int j = points[k][1] + gridPosition[1];
        if (i<0 || i>=grid.getGridHeight() || j<0 || j>=grid.getGridWidth())
        {
            return false;
        }
    }
    
    for (size_t i = 0; i < points.size(); ++i){
        int newi = points[i][0] + gridPosition[0];
        int newj = points[i][1] + gridPosition[1];
        if (grid.getMatrix()[newi][newj]!=0){
            std::cout << "La case est déjà occupée" << std::endl ;
            return false ;
        }
    }
    return true ;
}


void FallingPiece::rotateRight(){ //TODO vérifier que c'est pas le carré
    std::vector<std::vector<int>> newPoints=mPoints;
    // On fait la rotation sur la copie
    for (size_t i = 0; i < newPoints.size(); ++i) {
            int newi = newPoints[i][1];
            int newj = - newPoints[i][0];            
            newPoints[i][0] = newi ;
            newPoints[i][1] = newj;
        }
    if (checkFit(mGrid, newPoints, mGridPosition)){
        //On fait vraiment la rotation
        for (size_t i = 0; i < mPoints.size(); ++i) {
            int newi = mPoints[i][1];
            int newj = - mPoints[i][0];            
            mPoints[i][0] = newi ;
            mPoints[i][1] = newj;
        }
    }
}

void FallingPiece::rotateLeft(){ //TODO vérifier que c'est pas le carré
    std::vector<std::vector<int>> newPoints=mPoints;
    // On fait la rotation sur la copie
    for (size_t i = 0; i < newPoints.size(); ++i) {
            int newi = - newPoints[i][1];
            int newj = newPoints[i][0];            
            newPoints[i][0] = newi ;
            newPoints[i][1] = newj;
        }

    if (checkFit(mGrid, newPoints, mGridPosition)){
        for (size_t i = 0; i < mPoints.size(); ++i) {
            int newi = - mPoints[i][1];
            int newj = mPoints[i][0];            
            mPoints[i][0] = newi ;
            mPoints[i][1] = newj;         
        }
    }
}

void FallingPiece::moveRight(){ 
    std::vector<int> newPosition = {mGridPosition[0], mGridPosition[1] + 1};
    if (checkFit(mGrid, mPoints, newPosition)){
        mGridPosition[1]= mGridPosition[1]+1;
    }
};

void FallingPiece::moveLeft(){
    std::vector<int> newPosition = {mGridPosition[0], mGridPosition[1] - 1};
    if (checkFit(mGrid, mPoints, newPosition)){
        mGridPosition[1]= mGridPosition[1]-1;
    }
};

void FallingPiece::moveDown(){
    std::vector<int> newPosition = {mGridPosition[0] + 1, mGridPosition[1]};
    if (checkFit(mGrid, mPoints, newPosition)){
        mGridPosition[0]= mGridPosition[0]+1;
    }
};


void FallingPiece::stamp() {
    std::cout << "START" << std::endl;
    /*
    Cette fonction grave la FallingPiece dans la grille (i.e. modifie la matrice de jeu pour 
    y inscrire les blocs de couleur de la pièce)
    */
   for (size_t k = 0; k < mPoints.size(); k++)
   {
    int i = mPoints[k][0] + mGridPosition[0];
    int j = mPoints[k][1] + mGridPosition[1];
    std::cout << "On change " << mGrid.getMatrix()[i][j] << std::endl;
    mGrid.getMatrix()[i][j]=mColor;
    std:: cout << "résultat : " << mGrid.getMatrix()[i][j] << std::endl;
    
   }
   std::cout << "END" << std::endl;
   
};


bool FallingPiece::canMoveDown(){
    std::vector<int> newPosition = {mGridPosition[0] + 1, mGridPosition[1]};
    return checkFit(mGrid, mPoints, newPosition) ;
}