#pragma once

#include <SFML/Graphics.hpp>
#include "color.hpp"
#include <memory>
#include <thread>
#include <queue>
#include <optional>

class FallingPiece;// Sera défini après dans piece.hpp

class GameWindow {
    private:
        sf::RenderWindow window;
        bool stopSignal = false;
        std::unique_ptr<FallingPiece> fallingPiecePtr;
        int dimCase=30;
        std::queue<sf::Event> eventQueue;
        bool closeWindow = false;
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

        void addEvent(sf::Event event) {eventQueue.push(event);};
        
        std::optional<sf::Event> getEvent() ;
        void askCloseWindow() {closeWindow = true;};
        bool getAskCloseWindow() {return closeWindow;};
};



class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    bool isHovered = false;

public:
    Button(const std::string& buttonText, const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size);

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }

    bool isMouseOver(const sf::Vector2i& mousePos) {
        return shape.getGlobalBounds().contains(mousePos.x, mousePos.y);
    }

    void setHovered(bool hovered) {
        isHovered = hovered;
        shape.setFillColor(hovered ? sf::Color(100, 100, 100) : sf::Color(70, 70, 70));
    }

    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }
};

class TextInput {
private:
    sf::RectangleShape background;
    sf::Text text;
    bool isSelected = false;
    std::string input;

public:
    TextInput(const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size);

    void handleInput(sf::Event event);

    void setSelected(bool selected) {
        isSelected = selected;
        background.setOutlineColor(selected ? sf::Color::Yellow : sf::Color::White);
    }

    bool isMouseOver(const sf::Vector2i& mousePos) {
        return background.getGlobalBounds().contains(mousePos.x, mousePos.y);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(background);
        window.draw(text);
    }

    std::string getInput() const {
        return input;
    }
};