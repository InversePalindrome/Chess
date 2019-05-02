/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessTransition.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessPiece.hpp"
#include "ChessPosition.hpp"

#include <vector>
#include <utility>


namespace Chess
{
    struct Move
    {
        Chess::Position oldPosition;
        Chess::Position newPosition;
    };

    struct Transition
    {
        std::vector<Move> moves;
        ChessPiece droppedPiece;
        ChessPiece promotedPiece;
    };
}