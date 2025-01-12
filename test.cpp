#include "window.hpp"
#include "tetris.hpp"
#include "piece.hpp"
#include <vector>
#include <iostream>


int main() {
    Grid gamegrid(22,10);
    //std::vector<std::vector<Color>> gamegrid(5,        std::vector<Color>(5, Empty));


    
    






    Game game(gamegrid);
    /*
    for (size_t i = 0; i < game.getGrid().getMatrix().size(); i++)
                {
                    for (size_t j = 0; j < game.getGrid().getMatrix()[i].size(); j++)
                    {
                        std::cout << i << "," << j << "->" << game.getGrid().getMatrix()[i][j] << std::endl;
                    };
                    
                }*/


    Piece test_piece('L');
    FallingPiece fpiece(gamegrid, {3,2}, 'L');
    std::cout << fpiece.getColor() << std::endl,
    
    
    

    game.startGame();
    std::cout <<"TEST"<<std::endl;
    
    return 0;
}