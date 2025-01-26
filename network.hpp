#pragma once
#include <SFML/Network.hpp>
#include "piece.hpp" // nécessaire sinon l'include de tetris ne compile pas
#include "tetris.hpp"


void sendMessage(sf::TcpSocket& socket, Game &game);

void receiveData(sf::TcpSocket& socket, Game &game);

