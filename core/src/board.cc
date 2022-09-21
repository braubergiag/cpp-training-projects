#include "../include/board.h"
#include <iostream>


Board::Board()
{
    
    for (auto row_idx = 0; row_idx < board_size; ++row_idx){
        for (auto col_idx = 0; col_idx < board_size; ++ col_idx){
            board_[row_idx][col_idx] = '-';
        }
    }
}






void Board::draw()
{
      

    std::string boarder = "+----------------------+\n";
    std::string notation = " a  b  c  d  e  f  g  h  \n";
    for (auto row_idx = 0; row_idx < board_size; ++row_idx) {
        if (row_idx == 0) {
            std::cout << notation;
            std::cout << boarder;
        }
        for (auto col_idx = 0; col_idx < board_size; ++col_idx){
            std::cout << " " << board_[row_idx][col_idx] << " ";
        }
        std::cout << '\n';
        if (row_idx == board_size - 1) {
            std::cout << boarder;
            std::cout << notation;
        }
    } 
}

