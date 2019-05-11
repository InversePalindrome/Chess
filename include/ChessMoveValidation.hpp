/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessMoveValidation.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessBoard.hpp"
#include "ChessPosition.hpp"
#include "ChessTransition.hpp"


namespace Chess
{
    bool canBeCaptured(const Chess::Board<ChessPiece>& chessBoard, Chess::Color kingColor,
        const Chess::Position& kingPos);

    bool hasValidMoves(const Chess::Board<ChessPiece>& chessBoard, Chess::Color kingColor,
        const Chess::Position& kingPos);

    bool isPawnPromoted(const Chess::Position& newPos);
}
