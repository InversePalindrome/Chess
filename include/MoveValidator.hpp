/*
Copyright (c) 2019 Inverse Palindrome
Chess - MoveValidator.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessBoard.hpp"
#include "ChessConstants.hpp"


class MoveValidator
{
public:
    explicit MoveValidator(const ChessBoard& chessBoard);

private:
    const ChessBoard& chessBoard;

    bool isPawnMoveValid(const Chess::Position& oldPos, const Chess::Position& newPos) const;
    bool isKnightMoveValid(const Chess::Position& oldPos, const Chess::Position& newPos) const;
    bool isBishopMoveValid(const Chess::Position& oldPos, const Chess::Position& newPos) const;
    bool isRookMoveValid(const Chess::Position& oldPos, const Chess::Position& newPos) const;
    bool isQueenMoveValid(const Chess::Position& oldPos, const Chess::Position& newPos) const;
    bool isKingMoveValid(const Chess::Position& oldPos, const Chess::Position& newPos) const;
};
