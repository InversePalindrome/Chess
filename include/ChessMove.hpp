/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessMove.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessPiece.hpp"
#include "ChessPosition.hpp"


namespace Chess
{
    struct Move
    {
        ChessPiece movingPiece;
        Chess::Position oldPos;
        Chess::Position newPos;
    };
}