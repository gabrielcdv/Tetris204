#include "tetris.hpp"


void Grid::moveLineDown(int lineIndex)
{
    /*
    Permet de décaler la ligne d'indice lineIndex de 1 vers le bas en écrasant la ligne du dessous.
    */
    if (lineIndex >= int(matrix.size()))
    {
        std::cout << "Problème d'indice. Impossible de décaler la ligne." << std::endl;
        return;
    }

    for (size_t i = 0; i < matrix[lineIndex].size(); i++)
    {
        matrix[lineIndex + 1][i] = matrix[lineIndex][i];
    }
};
int Grid::checkForFullLines()
{
    /*
    Cherche les lignes pleines dans la matrice de jeu (aucune case vide dans la ligne)
    et les supprime en décalant les lignes d'au dessus vers le bas.
    Renvoie le nombre de lignes pleines.
    */
    int nbFullLines=0;
    for (size_t i = 0; i < matrix.size(); i++)
    {
        int isNull=1;
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j]!=0) {
                isNull=0;
            }
        }
        if (isNull) {// Si la ligne i est nulle
            // Alors on décale toutes les lignes d'au dessus vers le bas
            for (size_t k = 0; k < i; k++)
            {
                moveLineDown(k);
            }
                       
            nbFullLines++;
        }
        
    }
    
    return nbFullLines;
};