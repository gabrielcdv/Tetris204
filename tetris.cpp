#include "tetris.hpp"
#include "piece.hpp"
#include "network.hpp"
#include <thread>
#include <memory>
#include <cmath>
#include <queue>

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
    std::cout << "Ligne descendue" << lineIndex << std::endl;
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
    int nbFullLines = 0;
    for (int i = matrix.size() - 1; i >= 0; i--)
    {
        bool isFull = true;
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j] == Empty)
            {
                isFull = false;
                break;
            }
        }

        if (isFull)
        {
            // Si la ligne est pleine, on décale toutes les lignes au-dessus
            // d'une position vers le bas
            for (int k = i; k >= 1; k--)
            {
                for (size_t j = 0; j < matrix[k].size(); j++)
                {
                    matrix[k][j] = matrix[k - 1][j];
                }
            }
            // On vide la ligne du haut (ne pas oublier)
            for (size_t j = 0; j < matrix[0].size(); j++)
            {
                matrix[0][j] = Empty;
            }
            nbFullLines++;
            // Comme on a décalé les lignes vers le bas, il faut revérifier la ligne courante !
            i++;
        }
    }
    return nbFullLines;
}
Game::Game(Grid &grid, bool multiplayer, sf::TcpSocket &socket) : grid(grid), level(0), score(0), enemyScore(0), counter(0), multiplayer(multiplayer), enemyGrid(grid.getGridWidth() * grid.getGridHeight(), '0'), enemySocket(socket)
{
    /*
    Le but de ce morceau de code est de maximiser l'espace pris par la fenêtre de jeu en tenant
    compte du fait que les cases doivent avoir la même dimension en pixels.
    */
    piece = randomPiece();
    pieceIn1 = randomPiece();
    pieceIn2 = randomPiece();
    pieceIn3 = randomPiece();
    pieceIn4 = randomPiece();
    pieceIn5 = randomPiece();

    // calcul de la bonne taille de fenêtre
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    // int width_pxl = desktop.width;
    int height_pxl = desktop.height;

    // marge en haut et en bas de la fenetre de jeu
    float margin_height = 0.02;

    int dimCase = floor(height_pxl * (1 - 2 * margin_height) / grid.getGridHeight());
    gameWindow.setDimCase(dimCase);
    int window_height = round(dimCase * grid.getGridHeight() / (1 - 2 * margin_height));
    int window_width = window_height;

    if (multiplayer)
        window_width = 1.5 * window_width;

    // On met à jour la taille de fenêtre
    // gameWindow.getSFWindow().setSize(sf::Vector2u(window_width,window_height));
    gameWindow.getSFWindow().create(sf::VideoMode(window_width, window_height), "Tetris204", sf::Style::Default);
};

void initScoreBox(sf::Font &font, sf::Text &scoreDisplay, sf::Text &enemyScoreDisplay, sf::Text &levelDisplay, int xd, int windowWidth)
{
    if (!font.loadFromFile("resources/font.ttf")) // Chemin par rapport à l'exécutable !
    {
        throw std::runtime_error("Failed to load font");
    }

    scoreDisplay.setFont(font);
    scoreDisplay.setString("SCORE: 0");
    scoreDisplay.setCharacterSize(40);
    scoreDisplay.setFillColor(sf::Color::White);
    scoreDisplay.setPosition(xd, 100); // TODO : centrer avec getGlobalBounds().width

    enemyScoreDisplay.setFont(font);
    enemyScoreDisplay.setString("SCORE: 0");
    enemyScoreDisplay.setCharacterSize(30);
    enemyScoreDisplay.setFillColor(sf::Color::White);
    enemyScoreDisplay.setPosition(xd + windowWidth, 100);

    levelDisplay.setFont(font);
    levelDisplay.setString("LEVEL: 0");
    levelDisplay.setCharacterSize(40);
    levelDisplay.setFillColor(sf::Color::White);
    levelDisplay.setPosition(xd, 200); // TODO : centrer avec getGlobalBounds().width
}
void initNextPieces(sf::Font &font, sf::Text &label, int xd)
{

    label.setFont(font);
    label.setString("NEXT PIECES :");
    label.setCharacterSize(40);
    label.setFillColor(sf::Color::White);
    label.setPosition(xd, 100);
}
void drawPreviewPiece(Game &game, GameWindow &gameWindow, Piece &piece, int dimcase, int currentX, int currentY, int &drawnCasesHeight)
{
    // On la met à l'horizontale si besoin :
    if (piece.getRotateForPreview())
        piece.rotateLeftNoCheck();
    // On dessine
    for (size_t k = 0; k < piece.getPoints().size(); k++)
    {
        int i = piece.getPoints()[k][0];
        int j = piece.getPoints()[k][1];
        sf::RectangleShape square(sf::Vector2f(dimcase, dimcase));
        square.setPosition(currentX + j * dimcase, currentY + i * dimcase);
        square.setFillColor(getSFMLColor(piece.getColor()));
        gameWindow.getSFWindow().draw(square);
    }
    drawnCasesHeight += piece.getWidth() + 1;
}

void drawNextPieces(Game &game, GameWindow &gameWindow, int remainingHeightRight, int width_right, int windowHeight, int WindowWidth)
{
    // On va calculer la plus grande taille de case possible, en largeur et en hauteur et garder le minimum

    // En largeur :
    float margin_width = 0.025;
    int dimcase = ((1 - 2 * margin_width) * width_right) / 6; // Il faut 6 cases de large (4 max de large pour les pieces sur le coté, plus 2 pour centrer)

    // En hauteur :
    float margin_height = 0.025;
    int dimcase2 = ((1 - 2 * margin_height) * remainingHeightRight) / 16; // 2 de haut*5 + 6 d'espacement

    if (dimcase2 < dimcase)
        dimcase = dimcase2; // On utilise maintenant dimcase

    // Dessin des pièces
    int xOrigin = WindowWidth - (1 - 2 * margin_width) * width_right;
    int yOrigin = windowHeight - (1 - 2 * margin_height) * remainingHeightRight;
    int drawnCasesHeight = 0; // Compteur du nombre de cases imprimées en hauteur (pour espacer régulièrement les pièces)

    // Ces variables serviront de curseur :
    int currentX = xOrigin + 2 * dimcase;
    int currentY = yOrigin + dimcase;

    // Première pièce
    Piece piece1 = Piece(game.getPieceIn1());
    drawPreviewPiece(game, gameWindow, piece1, dimcase, currentX, currentY, drawnCasesHeight);

    // Deuxième pièce :
    currentY = yOrigin + dimcase * (1 + drawnCasesHeight);
    Piece piece2 = Piece(game.getPieceIn2());
    drawPreviewPiece(game, gameWindow, piece2, dimcase, currentX, currentY, drawnCasesHeight);

    // Troixème pièce :
    currentY = yOrigin + dimcase * (1 + drawnCasesHeight);
    Piece piece3 = Piece(game.getPieceIn3());
    drawPreviewPiece(game, gameWindow, piece3, dimcase, currentX, currentY, drawnCasesHeight);

    // Quatrième pièce :
    currentY = yOrigin + dimcase * (1 + drawnCasesHeight);
    Piece piece4 = Piece(game.getPieceIn4());
    drawPreviewPiece(game, gameWindow, piece4, dimcase, currentX, currentY, drawnCasesHeight);

    // Cinquième pièce :
    currentY = yOrigin + dimcase * (1 + drawnCasesHeight);
    Piece piece5 = Piece(game.getPieceIn5());
    drawPreviewPiece(game, gameWindow, piece5, dimcase, currentX, currentY, drawnCasesHeight);
};

void initEndDisplays(sf::RectangleShape &band, sf::RenderWindow &window, sf::Font &font, sf::Text &gameOverText, sf::Text &wonText, sf::Text &lostText)
{
    band.setSize(sf::Vector2f(window.getSize().x, window.getSize().y * 0.2));
    band.setPosition(0, window.getSize().y * 0.4);
    band.setFillColor(sf::Color(0, 0, 0, 200)); // Noir semi-transparent

    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(120);
    gameOverText.setFillColor(sf::Color::White);

    // Centrer le texte dans la bande
    sf::FloatRect textBounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textBounds.left + textBounds.width * 0.5f,
                           textBounds.top + textBounds.height * 0.5f);
    gameOverText.setPosition(window.getSize().x * 0.5f,
                             window.getSize().y * 0.5f);

    wonText.setFont(font);
    wonText.setString("YOU WIN");
    wonText.setCharacterSize(120);
    wonText.setFillColor(sf::Color::White);

    // Centrer le texte dans la bande
    textBounds = wonText.getLocalBounds();
    wonText.setOrigin(textBounds.left + textBounds.width * 0.5f,
                      textBounds.top + textBounds.height * 0.5f);
    wonText.setPosition(window.getSize().x * 0.5f,
                        window.getSize().y * 0.5f);

    lostText.setFont(font);
    lostText.setString("YOU LOOSE");
    lostText.setCharacterSize(120);
    lostText.setFillColor(sf::Color::White);

    // Centrer le texte dans la bande
    textBounds = lostText.getLocalBounds();
    lostText.setOrigin(textBounds.left + textBounds.width * 0.5f,
                       textBounds.top + textBounds.height * 0.5f);
    lostText.setPosition(window.getSize().x * 0.5f,
                         window.getSize().y * 0.5f);
}

const void Game::animateWindow()
{

    sf::RenderWindow &window = gameWindow.getSFWindow();

    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // gameWindow.getSFWindow().setView(gameWindow.getSFWindow().getDefaultView());
    //  Calcul des offset pour l'interface
    sf::Vector2u windowSize = window.getSize();
    unsigned int windowWidth = windowSize.x;
    if (multiplayer)
        windowWidth = (0.66667) * windowWidth;
    unsigned int windowHeight = windowSize.y;
    unsigned int gridHeight = gameWindow.getDimCase() * getGrid().getGridHeight();
    unsigned int gridWidth = gameWindow.getDimCase() * getGrid().getGridWidth();

    // Il faut afficher la grille de jeu au milieu.
    int gridOffsetX = (windowWidth - gridWidth) / 2;
    int gridOffsetY = (windowHeight - gridHeight) / 2;

    // Calcul pour le carré de score
    //  xd et xf représentent les abscisses de début et de fin du carré de score
    float margin_width_score = 0.05;

    // largeur restante à gauche et à droite de la grille
    int width_left = (windowWidth - gridWidth) / 2;
    int width_right = (windowWidth - gridWidth) / 2;
    int xd = margin_width_score * width_left;
    //(windowWidth + gridWidth) / 2 + margin_width_score * width_right

    sf::Font font;
    sf::Text scoreDisplay;
    sf::Text enemyScoreDisplay;
    sf::Text levelDisplay;

    initScoreBox(font, scoreDisplay, enemyScoreDisplay, levelDisplay, xd, windowWidth);

    window.draw(scoreDisplay);
    window.draw(levelDisplay);
    if (multiplayer)
    {
        window.draw(enemyScoreDisplay);
    }

    // Affichage du label des prochaines pièces
    sf::Text nextPiecesLabel;
    xd = (windowWidth + gridWidth) / 2 + margin_width_score * width_right;
    initNextPieces(font, nextPiecesLabel, xd);
    window.draw(nextPiecesLabel);

    // Taille restante en pixels en dessous du label 'Next Pieces :'
    int remainingHeightRight = windowHeight - (nextPiecesLabel.getPosition().y + nextPiecesLabel.getGlobalBounds().height);

    drawNextPieces(*this, gameWindow, remainingHeightRight, width_right, windowHeight, windowWidth);

    // Elements à afficher à la fin
    sf::RectangleShape horizontalBand; // Bande noire sur laquelle sera écrit game over ou autre si multijoueur
    sf::Text gameOverText;
    sf::Text wonText;
    sf::Text lostText;

    initEndDisplays(horizontalBand, window, font, gameOverText, wonText, lostText);

    // Boucle principale
    while (window.isOpen())
    {
        sf::Event event;
        while (gameWindow.getSFWindow().pollEvent(event))
        {
            gameWindow.addEvent(event);
        }

        window.clear();
        levelDisplay.setString("LEVEL: " + std::to_string(getLevel()));
        scoreDisplay.setString("SCORE: " + std::to_string(getScore()));
        if (multiplayer)
        {
            enemyScoreDisplay.setString("SCORE: " + std::to_string(enemyScore));
        }

        // Dessiner la grille du jeu
        for (int row = 0; row < grid.getGridHeight(); ++row)
        {
            for (int col = 0; col < grid.getGridWidth(); ++col)
            {
                // Créer un carré
                sf::RectangleShape square(sf::Vector2f(gameWindow.getDimCase(), gameWindow.getDimCase()));
                square.setPosition(gridOffsetX + col * gameWindow.getDimCase(), gridOffsetY + row * gameWindow.getDimCase());
                // Déterminer la couleur (alternance noir/blanc)

                if (grid.getMatrix()[row][col] == Empty) // si case vide
                {
                    if ((row + col) % 2 == 0)
                        square.setFillColor(sf::Color::Black); // Noir
                    else
                        square.setFillColor(sf::Color(50, 50, 50, 255)); // Noir moins foncé
                }
                else
                { // On remplit la case de la couleur correspondante
                    square.setFillColor(getSFMLColor(grid.getMatrix()[row][col]));
                }

                // Ajouter le carré à la fenêtre
                window.draw(square);
            }
        }

        // Dessiner la fallingPiece si il y en a une
        if (gameWindow.displayFallingPiece)
        {
            FallingPiece &fallingPiece = gameWindow.getFallingPiece();
            std::vector<std::vector<int>> pointsInGrid = fallingPiece.getPointsInGrid();
            for (size_t k = 0; k < pointsInGrid.size(); k++)
            {
                int i = pointsInGrid[k][0];
                int j = pointsInGrid[k][1];
                sf::RectangleShape square(sf::Vector2f(gameWindow.getDimCase(), gameWindow.getDimCase()));
                square.setPosition(gridOffsetX + j * gameWindow.getDimCase(), gridOffsetY + i * gameWindow.getDimCase());
                square.setFillColor(getSFMLColor(fallingPiece.getColor()));
                window.draw(square);
            }
        }

        // Dessiner la girlle adverse si jeu en multigjouer :
        if (multiplayer)
        {
            int grid2OffsetX = windowWidth; // On commence à faire la grille enemie à droite de la fenêtre "classique"
            // Dessiner la grille du jeu
            for (int row = 0; row < grid.getGridHeight(); ++row) // TODO : vérifier que les deux joueurs jouent en meme dimension...
            {
                for (int col = 0; col < grid.getGridWidth(); ++col)
                {
                    // Créer un carré
                    sf::RectangleShape square(sf::Vector2f(gameWindow.getDimCase(), gameWindow.getDimCase()));
                    square.setPosition(grid2OffsetX + col * gameWindow.getDimCase(), gridOffsetY + row * gameWindow.getDimCase());

                    if (enemyGrid[row * grid.getGridWidth() + col] - '0' == Empty) // si case vide
                    {
                        if ((row + col) % 2 == 0)
                            square.setFillColor(sf::Color::Black); // Noir
                        else
                            square.setFillColor(sf::Color(50, 50, 50, 255)); // Noir moins foncé
                    }
                    else
                    { // On remplit la case de la couleur correspondante
                        square.setFillColor(getSFMLColor(static_cast<Color>(enemyGrid[row * grid.getGridWidth() + col] - '0')));
                    }

                    // Ajouter le carré à la fenêtre
                    window.draw(square);
                }
            }
        }

        window.draw(scoreDisplay);
        window.draw(levelDisplay);
        if (multiplayer)
        {
            window.draw(enemyScoreDisplay);
        }

        window.draw(nextPiecesLabel);
        drawNextPieces(*this, gameWindow, remainingHeightRight, width_right, windowHeight, windowWidth);

        if (gameOver)
        {
            // Affichage des informations de fin par dessus le jeu (on garde les grilles en fond)
            window.draw(horizontalBand);
            if (multiplayer)
            {
                if (isWinner)
                {
                    window.draw(wonText);
                }
                else
                {
                    window.draw(lostText);
                }
            }
            else
            {
                window.draw(gameOverText);
            }
        }

        // Afficher le contenu
        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Economiser cpu
    }
}

void Game::updateLevel()
{
    level = floor(counter) / 10;
}

void Game::updateScore()
{
    int lignesNumber = grid.checkForFullLines();
    counter += lignesNumber;
    if (lignesNumber == 1)
    {
        score += 40 * (level + 1);
    }
    if (lignesNumber == 2)
    {
        score += 100 * (level + 1);
    }
    if (lignesNumber == 3)
    {
        score += 300 * (level + 1);
    }
    if (lignesNumber == 4)
    {
        score += 1200 * (level + 1);
    }
}

bool Game::isGameOver(char type, std::vector<int> centralPosition)
{
    Piece piece(type);
    return !checkFit(grid, piece.getPoints(), centralPosition);
}

void Game::setEnemyGrid(std::string str)
{
    std::lock_guard<std::mutex> lock(enemyGridMutex); // libère automatiquement le mutex à la fin du bloc
    enemyGrid = str;
}

std::string Game::getEnemyGrid()
{
    std::lock_guard<std::mutex> lock(enemyGridMutex);
    return enemyGrid;
}

void spawnPieces(Game &game, GameWindow &gameWindow)
{
    std::vector<int> centralPosition = {1, 4}; // TODO ne pas harcoder la position centrale

    while (!game.isGameOver(game.getPiece(), centralPosition))
    {
        FallingPiece fallingPiece(game.getGrid(), centralPosition, game.getPiece());
        auto fallingPiecePtr = std::make_unique<FallingPiece>(fallingPiece);

        gameWindow.setFallingPiece(std::move(fallingPiecePtr));
        gameWindow.displayFallingPiece = true;

        while (gameWindow.getFallingPiece().canMoveDown())
        {
            // pause entre les déplacements :
            // std::cout << "Niveau" << game.getLevel() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(800 - (game.getLevel() * 200)));
            // std::this_thread::sleep_for(std::chrono::milliseconds(200));
            //  Déplace la pièce vers le bas
            gameWindow.getFallingPiece().moveDown();
        }
        gameWindow.getFallingPiece().stamp();
        game.updateScore();
        game.updateLevel();
        gameWindow.displayFallingPiece = false;
        // Modification des pièces par la pièce suivante et génération d'une nouvelle pièce aléatoirement
        game.getPiece() = game.getPieceIn1();
        game.getPieceIn1() = game.getPieceIn2();
        game.getPieceIn2() = game.getPieceIn3();
        game.getPieceIn3() = game.getPieceIn4();
        game.getPieceIn4() = game.getPieceIn5();
        game.getPieceIn5() = game.randomPiece();
    }
    std::cout << "Jeu terminé" << std::endl;
    game.gameOver = true;
}

char Game::randomPiece()
{
    /*Génère un type de pièce aléatoirement*/
    char type[] = {'I', 'O', 'T', 'L', 'J', 'Z', 'S'};
    int taille = sizeof(type) / sizeof(char); // Taille du tableau
    int index = std::rand() % taille;
    return type[index];
}

void manageEvents(Game &game, GameWindow &gameWindow)
{
    while (gameWindow.getSFWindow().isOpen())
    {
        auto evt = gameWindow.getEvent();
        if (evt)
        {
            sf::Event event = *evt;
            if (event.type == sf::Event::Closed)
                gameWindow.getSFWindow().close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Right)
                { // Touche flèche droite
                    gameWindow.getFallingPiece().moveRight();
                }
                if (event.key.code == sf::Keyboard::Left)
                { // Touche flèche gauche
                    gameWindow.getFallingPiece().moveLeft();
                }
                if (event.key.code == sf::Keyboard::Down)
                { // Touche flèche du bas
                    gameWindow.getFallingPiece().moveDown();
                }
                if (event.key.code == sf::Keyboard::D)
                { // Touche D
                    gameWindow.getFallingPiece().rotateRight();
                }
                if (event.key.code == sf::Keyboard::Q)
                { // Touche Q
                    gameWindow.getFallingPiece().rotateLeft();
                }
            }
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Economiser cpu
}

void Game::startGame()
{
    /*Lance le jeu, c'est à dire les différents thread nécessaires*/

    std::thread fallingPiecesThread(&spawnPieces, std::ref(*this), std::ref(gameWindow));
    // On détache le thread
    fallingPiecesThread.detach();

    std::thread eventsThread(&manageEvents, std::ref(*this), std::ref(gameWindow));

    // On détache le thread
    eventsThread.detach();

    if (multiplayer)
    {
        std::thread sendThread(&sendMessage, std::ref(enemySocket), std::ref(*this));
        // On détache le thread
        sendThread.detach();

        std::thread receiveThread(&receiveData, std::ref(enemySocket), std::ref(*this));
        // On détache le thread
        receiveThread.detach();
    }

    // lancement de l'affichage
    animateWindow(); // gère aussi la fin du jeu
};
