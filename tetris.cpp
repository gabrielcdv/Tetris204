#include "tetris.hpp"
#include "piece.hpp"
#include <thread>
#include <memory>
#include <cmath>
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
        matrix[lineIndex][i] = Empty;
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
        bool isFull=true;
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j]==Empty) {
                isFull=false;
            }
        }
        if (isFull) {// Si la ligne i est pleine
            std::cout << "On écrit dans matrix" << std::endl ;
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


Game::Game(Grid& grid) : grid(grid), level(0), score(0){
    piece = randomPiece() ;
    pieceIn1 = randomPiece() ;
    pieceIn2 = randomPiece() ;
    pieceIn3 = randomPiece() ;
    pieceIn4 = randomPiece() ;
    pieceIn5 = randomPiece() ;
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




                /*
                for (size_t i = 0; i < grid.getMatrix().size(); i++)
                {
                    for (size_t j = 0; j < grid.getMatrix()[i].size(); j++)
                    {
                        std::cout << i << "," << j << "->" << grid.getMatrix()[i][j] << std::endl;
                    };
                    
                }*/

                
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


        // Dessiner la fallingPiece si il y en a une
        if (gameWindow.displayFallingPiece)
        {
            FallingPiece& fallingPiece = gameWindow.getFallingPiece();
            std::vector<std::vector<int>> pointsInGrid = fallingPiece.getPointsInGrid();
            for (size_t k = 0; k < pointsInGrid.size(); k++)
            {
                int i = pointsInGrid[k][0];
                int j = pointsInGrid[k][1];
                int dimcase=30;
                sf::RectangleShape square(sf::Vector2f(dimcase, dimcase)); // TODO ne pas hardcoder le 30 (taille d'une case en pixel)
                square.setPosition(j * dimcase, i * dimcase);
                square.setFillColor(getSFMLColor(fallingPiece.getColor()));
                window.draw(square);

            }
            
        }
        

        // Afficher le contenu
        window.display();

        /*TODO Il faudra faire une fonction qui display le score*/

        if (isGameOver('L', {5,0})){
            std::cout << "Game Over" <<std::endl ;
        }

    }
}

void Game::updateLevel(){
    level = floor(counter)/10 ;
}

void Game::updateScore(){
    int lignesNumber = grid.checkForFullLines() ;
    counter += lignesNumber ;
    if (lignesNumber==1){
        score += 40*(level+1);
    }
    if (lignesNumber==2){
        score += 100*(level+1);
    }
    if (lignesNumber==3){
        score += 300*(level+1);
    }
    if (lignesNumber==4){
        score += 1200*(level+1);
    }
}

bool Game::isGameOver(char type, std::vector<int> centralPosition){
    Piece piece(type);
    return checkFit(grid, piece.getPoints(), centralPosition);
}
    

void spawnPieces(Game& game, GameWindow& gameWindow) {
    std::vector<int> centralPosition = {1,4}; //TODO ne pas harcoder la position centrale

    while(game.isGameOver(game.getPiece(), centralPosition)){
        FallingPiece fallingPiece(game.getGrid(), centralPosition, game.getPiece());
        auto fallingPiecePtr = std::make_unique<FallingPiece>(fallingPiece);
        
        gameWindow.setFallingPiece(std::move(fallingPiecePtr));
        gameWindow.displayFallingPiece = true;

        while (gameWindow.getFallingPiece().canMoveDown()) {
            // pause entre les déplacements :
            std::this_thread::sleep_for(std::chrono::milliseconds(800-(game.getLevel()*200)));
            // Déplace la pièce vers le bas
            gameWindow.getFallingPiece().moveDown();

            game.updateScore();
            game.updateLevel();
        }
        gameWindow.getFallingPiece().stamp();
        gameWindow.displayFallingPiece = false;
        //Modification des pièces par la pièce suivante et génération d'une nouvelle pièce aléatoirement
        game.getPiece() = game.getPieceIn1();
        game.getPieceIn1() = game.getPieceIn2();
        game.getPieceIn2() = game.getPieceIn3();
        game.getPieceIn3() = game.getPieceIn4();
        game.getPieceIn4() = game.getPieceIn5();
        game.getPieceIn5() = game.randomPiece();

    }
}

char Game::randomPiece(){
    /*Génère un type de pièce aléatoirement*/
    char type[] = {'I', 'O', 'T', 'L', 'J', 'Z', 'S'}; 
    int taille = sizeof(type) / sizeof(char); // Taille du tableau
    int index = std::rand() % taille;
    return type[index];
}


void Game::startGame() {
    //TODOLancement des threads éventuels 

    
    
    std::thread fallingPiecesThread(&spawnPieces, std::ref(*this), std::ref(gameWindow));

    // On détache le thread
    fallingPiecesThread.detach();
    


    //lancement de l'affichage
    animateWindow();
};

