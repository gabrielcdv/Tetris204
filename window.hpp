#pragma once

#include <SFML/Graphics.hpp>
#include "color.hpp"
#include <memory>
#include <thread>

class FallingPiece;// Sera défini après dans piece.hpp

class GameWindow {
    private:
        sf::RenderWindow window;
        bool stopSignal = false;
        std::unique_ptr<FallingPiece> fallingPiecePtr;
    public:
        GameWindow() : window(sf::VideoMode(300, 660), "Fenêtre SFML") {};
        void animate();
        void sendStopSignal() {stopSignal = true;};
        bool displayFallingPiece = false;
        void setFallingPiece(std::unique_ptr<FallingPiece> ptr) {fallingPiecePtr = std::move(ptr);};
        FallingPiece& getFallingPiece() {return *fallingPiecePtr;};
        sf::RenderWindow& getSFWindow() {return window;};
};
