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
        int dimCase=30;
    public:
        GameWindow() : window(sf::VideoMode(660, 660), "Fenêtre SFML") {}; // la fenêter sera redimensionnée
        void animate();
        void sendStopSignal() {stopSignal = true;};
        bool displayFallingPiece = false;
        void setFallingPiece(std::unique_ptr<FallingPiece> ptr) {fallingPiecePtr = std::move(ptr);};
        int getDimCase() {return dimCase;};
        void setDimCase(int dim) {dimCase = dim;};
        FallingPiece& getFallingPiece() {return *fallingPiecePtr;};
        sf::RenderWindow& getSFWindow() {return window;};
};
