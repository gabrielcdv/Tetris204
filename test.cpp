#include "window.hpp"
#include "tetris.hpp"


int main() {
    Game game(22,10);
    GameWindow fenetre=GameWindow();
    fenetre.animate(game);
    return 0;
}