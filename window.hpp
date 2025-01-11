#pragma once

#include <SFML/Graphics.hpp>
#include "color.hpp"
#include <thread>
class GameWindow {
    private:
        sf::RenderWindow window;
        bool stopSignal = false;
    public:
        GameWindow() : window(sf::VideoMode(300, 660), "Fenêtre SFML") {};
        void animate();
        void sendStopSignal() {stopSignal = true;};
        sf::RenderWindow& getSFWindow() {return window;};
};
