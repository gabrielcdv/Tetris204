#pragma once
#include <SFML/Graphics.hpp>
#include <map>

enum Color {
    Empty = 0,
    Cyan = 1,
    Orange = 2,
    Yellow = 3,
    Purple = 4,
    Blue = 5,
    Red = 6,
    Green = 7
};

sf::Color getSFMLColor(Color color) {
    switch (color) {
        case Empty:  return sf::Color(0, 0, 0, 0); // Couleur transparente
        case Cyan:   return sf::Color::Cyan;
        case Orange: return sf::Color(255, 165, 0);
        case Yellow: return sf::Color::Yellow;
        case Purple: return sf::Color(128, 0, 128);
        case Blue:   return sf::Color::Blue;
        case Red:    return sf::Color::Red;
        case Green:  return sf::Color::Green;
        default:     return sf::Color::Black; // Si couleur introuvable
    }
}