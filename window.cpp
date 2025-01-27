#include "window.hpp"
#include "piece.hpp"

std::optional<sf::Event> GameWindow::getEvent()
{
    if (!eventQueue.empty())
    {
        sf::Event evt = eventQueue.front();
        eventQueue.pop();
        return evt;
    }
    else
    {
        return std::nullopt;
    }
}

Button::Button(const std::string &buttonText, const sf::Font &font, const sf::Vector2f &position, const sf::Vector2f &size)
{
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color(70, 70, 70));
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::White);

    text.setString(buttonText);
    text.setFont(font);
    text.setCharacterSize(30); // Increased text size
    text.setFillColor(sf::Color::White);

    // Center text in button
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        position.x + (size.x - textBounds.width) / 2,
        position.y + (size.y - textBounds.height) / 2);
}

TextInput::TextInput(const sf::Font &font, const sf::Vector2f &position, const sf::Vector2f &size)
{
    background.setSize(size);
    background.setPosition(position);
    background.setFillColor(sf::Color::Black);
    background.setOutlineThickness(2);
    background.setOutlineColor(sf::Color::White);

    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(position.x + 5, position.y + (size.y - 24) / 2);
    std::string defaultText = "127.0.0.1";
    input = defaultText;
    text.setString(defaultText);
}

void TextInput::handleInput(sf::Event event)
{
    if (!isSelected)
        return;

    if (event.type == sf::Event::TextEntered)
    {
        if (event.text.unicode == '\b' && !input.empty())
        {
            input.pop_back();
        }
        else if (event.text.unicode < 128 && event.text.unicode != '\b')
        {
            input += static_cast<char>(event.text.unicode);
        }


        if (input.empty())
        {
            text.setString("Enter IP address...");
        }
        else
        {
            text.setString(input);
        }
    }
}