#pragma once
#include <SFML/Network.hpp>
#include "piece.hpp" // nécessaire sinon l'include de tetris ne compile pas
#include "tetris.hpp"


void sendGrid(sf::TcpSocket& socket, Game &game);

void receiveGrid(sf::TcpSocket& socket, Game &game);

