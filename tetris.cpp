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




void Game::animateWindow()
{
    sf::RenderWindow& window=gameWindow.getSFWindow();
    // Boucle principale
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Dessiner la grtille du jeu
        for (int row = 0; row < grid.getGridHeight(); ++row)
        {
            for (int col = 0; col < grid.getGridWidth(); ++col)
            {
                // Créer un carré
                int dimcase=30;
                sf::RectangleShape square(sf::Vector2f(dimcase, dimcase)); // TODO ne pas hardcoder le 30 (taille d'une case en pixel)
                square.setPosition(col * dimcase, row * dimcase);

                // Déterminer la couleur (alternance noir/blanc)
                if (grid.getMatrix()[row][col] == 0) // si case vide
                {
                    if ((row + col) % 2 == 0)
                        square.setFillColor(sf::Color::Black); // Noir
                    else
                        square.setFillColor(sf::Color(50,50,50,255)); // Noir moins foncé
                } else { // On remplit la case de la couleur correspondante
                    square.setFillColor(getSFMLColor(grid.getMatrix()[row][col]));
                }

                // Ajouter le carré à la fenêtre
                window.draw(square);
            }
        }

        // Afficher le contenu
        window.display();
    }
}


void Game::startGame() {
    //TODOLancement des threads éventuels 

    //lancement de l'affichage
    animateWindow();
};