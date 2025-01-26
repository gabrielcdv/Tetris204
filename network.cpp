#include "network.hpp"
#include "color.hpp"
void sendMessage(sf::TcpSocket &socket, Game &game)
{
    while (true)
    {
        std::vector<std::vector<Color>> matrix = game.getGrid().getMatrix(); // On fait une copie (ce n'est pas une référence vers matrix)

        // Impression de la fallingpiece eventuelle dans la grille à envoyer :
        if (game.getWindow().displayFallingPiece)
        {

            FallingPiece &fpiece = game.getWindow().getFallingPiece();
            for (size_t k = 0; k < fpiece.getPoints().size(); k++)
            {
                int i = fpiece.getPoints()[k][0] + fpiece.getGridPosition()[0];
                int j = fpiece.getPoints()[k][1] + fpiece.getGridPosition()[1];
                matrix[i][j] = fpiece.getColor();
            }
        }
        std::string data;
        for (size_t i = 0; i < matrix.size(); i++)
        {
            for (size_t j = 0; j < matrix[i].size(); j++)
            {
                data += std::to_string(matrix[i][j]);
            }
        }
        std::cout << "envoi d'un message : " << data << std::endl;
        // socket.send(packet);
        // std::string message = "Bienvenue dans Tetris!";
        socket.send(data.c_str(), data.size() + 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void receiveData(sf::TcpSocket &socket, Game &game)
{
    // Réception de données
    char data[500];
    while (true)
    {
        std::size_t received;
        if (socket.receive(data, sizeof(data), received) != sf::Socket::Done)
        {
            std::cerr << "Erreur lors de la réception des données" << std::endl;
            return;
        }
        else
        {
            std::cout << "Message reçu du serveur : " << data << std::endl;
            game.setEnemyGrid(data);
        }
    }
}