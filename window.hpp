#pragma once

#include <SFML/Graphics.hpp>
#include "tetris.hpp"
class GameWindow {
    private:
        sf::RenderWindow window;
    public:
        GameWindow() : window(sf::VideoMode(300, 660), "Fenêtre SFML") {};
        void animate(Game& game);
};
