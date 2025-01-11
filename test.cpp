#include "window.hpp"
#include "tetris.hpp"
#include "piece.hpp"


int main() {
    Grid gamegrid(22,10);
    Game game(gamegrid);

    Piece test_piece('L');
    FallingPiece fpiece();



    game.startGame();
    std::cout <<"TEST"<<std::endl;
    
    return 0;
}