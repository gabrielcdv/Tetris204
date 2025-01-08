#include "window.hpp"
#include "tetris.hpp"


int main() {
    Grid gamegrid(22,10);
    Game game(gamegrid);
    GameWindow fenetre=GameWindow();
    fenetre.animate(game);
    return 0;
}