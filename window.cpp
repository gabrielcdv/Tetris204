#include <SFML/Graphics.hpp>

int main() {
    // Création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(800, 600), "Fenêtre SFML");

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Effacer l'écran avec une couleur
        window.clear(sf::Color::Blue);

        // Afficher le contenu
        window.display();
    }

    return 0;
}