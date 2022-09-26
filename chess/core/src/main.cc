#include <iostream>




#include "../include/board.h"






char get_piece_repr(Piece piece){

    switch (piece)
    {
    case Piece::BlackKing:
        return 'K';
        break;
    case Piece::BlackQueen:
        return 'Q';
        break;
    default:
        break;
    }
}

int main(){

    Board board;
    // board.draw();

    std::cout << get_piece_repr(Piece::King) << "\n";


    return 0;
}