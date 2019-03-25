/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessBoard.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessPiece.hpp"
#include "ChessConstants.hpp"

#include <array>


class ChessBoard
{  
public:
    ChessBoard();

    void resetBoard();

    std::array<ChessPiece, Chess::RANKS>& operator[](const std::size_t index);
    const std::array<ChessPiece, Chess::RANKS>& operator[](const std::size_t index) const;

private:
    std::array<std::array<ChessPiece, Chess::RANKS>, Chess::FILES> board;
};
