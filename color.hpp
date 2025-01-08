#pragma once
#include <SFML/Graphics.hpp>


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

sf::Color getSFMLColor(Color color);