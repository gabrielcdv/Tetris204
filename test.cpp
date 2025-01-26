#include "window.hpp"
#include "tetris.hpp"
#include "piece.hpp"
#include <vector>
#include <iostream>


int main() {
    // Initialiser la graine du générateur de nombres aléatoires
    std::srand(static_cast<unsigned>(std::time(0)));
    
    Grid gamegrid(22,10);

    Game game(gamegrid);

    Piece test_piece('L');
    FallingPiece fpiece(gamegrid, {3,2}, 'L');
    std::cout << fpiece.getColor() << std::endl,
    
    
    

    game.startGame();
    std::cout <<"TEST"<<std::endl;
    
    return 0;
}