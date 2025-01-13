#include "window.hpp"
#include "piece.hpp"



std::optional<sf::Event> GameWindow::getEvent() {
    if (!eventQueue.empty())
    {
        sf::Event evt = eventQueue.front();
        eventQueue.pop();
        return evt;
    }
    else {
        return std::nullopt;
    }
    
}