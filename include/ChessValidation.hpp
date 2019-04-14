/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessValidation.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessBoard.hpp"
#include "ChessPosition.hpp"


namespace Chess
{
    bool isPawnMoveValid(const ChessBoard& chessBoard, Chess::Color pawnColor, bool hasMoved, const Chess::Position& oldPos, const Chess::Position& newPos);
    bool isKnightMoveValid(const Chess::Position& oldPos, const Chess::Position& newPos);
    bool isBishopMoveValid(const ChessBoard& chessBoard, const Chess::Position& oldPos, const Chess::Position& newPos);
    bool isRookMoveValid(const ChessBoard& chessBoard, const Chess::Position& oldPos, const Chess::Position& newPos);
    bool isQueenMoveValid(const ChessBoard& chessBoard, const Chess::Position& oldPos, const Chess::Position& newPos);
    bool isKingMoveValid(const Chess::Position& oldPos, const Chess::Position& newPos);
	bool isInCheck(const ChessBoard& chessBoard, Chess::Color kingColor, const Chess::Position kingPosition);
}
