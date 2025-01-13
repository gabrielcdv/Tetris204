#include "color.hpp"
#include <map>



sf::Color getSFMLColor(Color color) {
    switch (color) {
        case Empty:  return sf::Color(0, 0, 0, 0); // Couleur transparente
        case Cyan:   return sf::Color::Cyan;
        case Orange: return sf::Color(255, 165, 0);
        case Yellow: return sf::Color::Yellow;
        case Purple: return sf::Color(200, 0, 200);
        case Blue:   return sf::Color::Blue;
        case Red:    return sf::Color::Red;
        case Green:  return sf::Color::Green;
        default:     return sf::Color::Black; // Si couleur introuvable
    }
}