#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <cmath>
#include <iostream>
#include <unistd.h>
#include "piece.hpp"
#include "launcher.hpp"
#include "window.hpp"
#include "network.hpp"


#define GRID_HEIGHT 10
#define GRID_WIDTH 5

void startSingleplayerGame()
{
    Grid gamegrid(GRID_HEIGHT, GRID_WIDTH);
    sf::TcpSocket emptySocket;
    Game game(gamegrid, false, emptySocket);
    game.startGame();
    showLauncher(); // permet de remontrer le launcher à l'issue d'une partie
}

void hostServerGame()
{
    sf::TcpListener listener;

    // Attribuer un port
    if (listener.listen(53000) != sf::Socket::Done)
    {
        std::cerr << "Erreur lors de la mise en écoute sur le port 53000" << std::endl;
        return;
    }
    std::cout << "En attente d'une connexion sur le port 53000..." << std::endl;

    sf::TcpSocket client;
    // Accepter (et attendre) une nouvelle connexion
    if (listener.accept(client) != sf::Socket::Done)
    {
        std::cerr << "Erreur lors de la connexion" << std::endl;
        return;
    }
    std::cout << "Client connecté : " << client.getRemoteAddress() << std::endl;

    // Envoi de données
    std::string message = "Bienvenue dans Tetris!";
    if (client.send(message.c_str(), message.size() + 1) != sf::Socket::Done)
    {
        std::cerr << "Erreur lors de l'envoi du message" << std::endl;
    }

    // Combiner le PID et le temps actuel pour créer une graine unique
    unsigned seed = static_cast<unsigned>(std::time(0)) + getpid();
    std::srand(seed);

    Grid gamegrid(GRID_HEIGHT, GRID_WIDTH);

    Game game(gamegrid, true, client);

    // On lance le thread d'envoi

    game.startGame();
    showLauncher();
}

void joinServerGame(std::string ipstr)
{
    sf::TcpSocket socket;

    // Connecte le socket au serveur
    if (socket.connect("127.0.0.1", 53000) != sf::Socket::Done)
    {
        std::cerr << "Erreur lors de la connexion au serveur" << std::endl;
        return;
    }
    std::cout << "Connecté au serveur!" << std::endl;

    // Combiner le PID et le temps actuel pour créer une graine unique
    unsigned seed = static_cast<unsigned>(std::time(0)) + getpid();
    std::srand(seed);

    Grid gamegrid(GRID_HEIGHT, GRID_WIDTH);

    Game game(gamegrid, true, socket);

    game.startGame();
    showLauncher();
}

void showLauncher()
{
    // Calcul de la bonne taille de fenêtre
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    // int width_pxl = desktop.width;
    int height_pxl = desktop.height;

    sf::RenderWindow window;

    sf::Font font;
    if (!font.loadFromFile("resources/font.ttf"))
    {
        std::cout << "Probleme de font" << std::endl;
        return;
    }

    // On met à jour la taille de fenêtre
    // gameWindow.getSFWindow().setSize(sf::Vector2u(window_width,window_height));
    window.create(sf::VideoMode(height_pxl, height_pxl), "Tetris204", sf::Style::Default);

    // Elements du launcher
    const float buttonWidth = height_pxl * 0.4;
    const float buttonHeight = height_pxl * 0.08;
    const float centerX = height_pxl / 2.;
    const float spacing = height_pxl * 0.04;

    // Singleplayer bouton
    Button singleplayerButton("Singleplayer", font,
                              sf::Vector2f(centerX - buttonWidth / 2, height_pxl * 0.2),
                              sf::Vector2f(buttonWidth, buttonHeight));

    // Multiplayer cadre
    const float frameWidth = buttonWidth + spacing * 2;
    const float frameHeight = buttonHeight * 4 + spacing * 3; // hautueur pr 3 elements plus un spacing
    sf::RectangleShape multiplayerFrame;
    multiplayerFrame.setSize(sf::Vector2f(frameWidth, frameHeight));
    multiplayerFrame.setPosition(centerX - frameWidth / 2, height_pxl * 0.35);
    multiplayerFrame.setFillColor(sf::Color::Transparent);
    multiplayerFrame.setOutlineThickness(2);
    multiplayerFrame.setOutlineColor(sf::Color::White);

    // Multiplayer label
    sf::Text multiplayerLabel;
    multiplayerLabel.setString("Multiplayer");
    multiplayerLabel.setFont(font);
    multiplayerLabel.setCharacterSize(24);
    multiplayerLabel.setFillColor(sf::Color::White);
    multiplayerLabel.setPosition(centerX - multiplayerLabel.getLocalBounds().width / 2,
                                 height_pxl * 0.35f - multiplayerLabel.getLocalBounds().height - 15);

    // host button iside frame
    Button hostButton("Host Server", font,
                      sf::Vector2f(centerX - buttonWidth / 2, height_pxl * 0.35f + spacing),
                      sf::Vector2f(buttonWidth, buttonHeight));

    // IP input field
    TextInput ipInput(font,
                      sf::Vector2f(centerX - buttonWidth / 2, height_pxl * 0.35f + buttonHeight + spacing * 2),
                      sf::Vector2f(buttonWidth, buttonHeight));

    // Join button
    Button joinButton("Join Server", font,
                      sf::Vector2f(centerX - buttonWidth / 2, height_pxl * 0.35f + 2 * buttonHeight + spacing * 3),
                      sf::Vector2f(buttonWidth, buttonHeight));



    // Booléens pour effectuer l'action demandée après la fermeture du launcher
    bool startSingleplayer = false;
    bool startHostServer = false;
    bool joinServer = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Gérer les input d'ip
            ipInput.handleInput(event);

            // Gérer les clics (focus et start)
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (singleplayerButton.isMouseOver(mousePos))
                {
                    std::cout << "Starting singleplayer game..." << std::endl;
                    startSingleplayer = true;
                        window.close();
                }
                else if (hostButton.isMouseOver(mousePos))
                {
                    std::cout << "Starting server..." << std::endl;
                    startHostServer = true;
                        window.close();
                }
                else if (joinButton.isMouseOver(mousePos))
                {
                    std::string ip = ipInput.getInput();
                    if (!ip.empty())
                    {
                        std::cout << "Joining server at IP: " << ip << std::endl;
                        joinServer = true;
                        window.close();
                    }
                }

                // Selection de la textbox le cas échéant
                ipInput.setSelected(ipInput.isMouseOver(mousePos));
            }

            // Effet de survol
            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                singleplayerButton.setHovered(singleplayerButton.isMouseOver(mousePos));
                hostButton.setHovered(hostButton.isMouseOver(mousePos));
                joinButton.setHovered(joinButton.isMouseOver(mousePos));
            }
        }

        
        window.clear(sf::Color(30, 30, 30));

        
        window.draw(multiplayerFrame);
        window.draw(multiplayerLabel);
        singleplayerButton.draw(window);
        hostButton.draw(window);
        ipInput.draw(window);
        joinButton.draw(window);

        window.display();
        
        
    }

    // Dès que la fenêtre est fermée :
    if (startSingleplayer)
    {
        startSingleplayerGame();
    }

    if (startHostServer)
    {
        hostServerGame();
    }
    if (joinServer)
    {
        joinServerGame(ipInput.getInput());
    }
}

int main()
{

    std::srand(static_cast<unsigned>(std::time(0)));

    showLauncher();
}