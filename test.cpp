#include "window.hpp"
#include "tetris.hpp"
#include "piece.hpp"


int main() {
    Grid gamegrid(22,10);
    Game game(gamegrid);
    GameWindow fenetre=GameWindow();
    fenetre.animate(game);
    Piece test_piece('L');
    return 0;
}