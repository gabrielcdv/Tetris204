#include "window.hpp"
#include "tetris.hpp"
#include "color.hpp"
void GameWindow::animate(Game& game)
{
    std::vector<std::vector<int>> &grid = game.getGrid();

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
        for (int row = 0; row < game.getGridHeight(); ++row)
        {
            for (int col = 0; col < game.getGridWidth(); ++col)
            {
                // Créer un carré
                int dimcase=30;
                sf::RectangleShape square(sf::Vector2f(dimcase, dimcase)); // TODO ne pas hardcoder le 30 (taille d'une case en pixel)
                square.setPosition(col * dimcase, row * dimcase);

                // Déterminer la couleur (alternance noir/blanc)
                if (grid[row][col] == 0) // si case vide
                {
                    if ((row + col) % 2 == 0)
                        square.setFillColor(sf::Color::Black); // Blanc
                    else
                        square.setFillColor(sf::Color(50,50,50,255)); // Noir
                }//TODO: else remplir la case de la couleur correspondant à grid[row][col]

                // Ajouter le carré à la fenêtre
                window.draw(square);
            }
        }

        // Afficher le contenu
        window.display();
    }
}

