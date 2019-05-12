/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessMoveValidation.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessMove.hpp"
#include "ChessBoard.hpp"
#include "ChessPosition.hpp"
#include "ChessConstants.hpp"

#include <vector>


namespace Chess
{
    bool canBeCaptured(const Chess::Board<ChessPiece>& chessBoard, Chess::Color kingColor,
        const Chess::Position& piecePos);

    bool hasValidMoves(const Chess::Board<ChessPiece>& chessBoard, Chess::Color kingColor,
        const Chess::Position& kingPos);

    Chess::CastlingMode isCastling(const Chess::Board<ChessPiece>& chessBoard, const ChessPiece& movingPiece,
        const Chess::Position& oldPos, const Chess::Position& newPos);

    bool isEnPassant(const Chess::Board<ChessPiece>& chessBoard, const std::vector<Chess::Move>&
        moveHistory, const ChessPiece& movingPiece, const Chess::Position& oldPos, const Chess::Position& newPos);

    bool isPawnPromoted(const ChessPiece& movingPiece, const Chess::Position& newPos);
}
