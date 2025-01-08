#include "window.hpp"
#include "tetris.hpp"
#include "piece.hpp"


int main() {
    Game game(22,10);
    GameWindow fenetre=GameWindow();
    fenetre.animate(game);
    Piece test_piece('L');
    return 0;
}