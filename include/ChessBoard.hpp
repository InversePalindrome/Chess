/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessBoard.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessPiece.hpp"
#include "ChessConstants.hpp"

#include <array>


namespace Chess
{
    template<typename T>
    using Board = std::array<std::array<T, Chess::RANKS>, Chess::FILES>;

    Board<ChessPiece> getInitialBoard();
}

