/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessMoveGeneration.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessBoard.hpp"
#include "ChessPosition.hpp"

#include <vector>


namespace Chess
{
    std::vector<Chess::Position> getPawnMoves(const Chess::Board<ChessPiece>& chessBoard,
        Chess::Color pawnColor, const Chess::Position& pos, bool hasMoved);

    std::vector<Chess::Position> getKnightMoves(const Chess::Board<ChessPiece>& chessBoard,
        Chess::Color color, const Chess::Position& pos);

    std::vector<Chess::Position> getBishopMoves(const Chess::Board<ChessPiece>& chessBoard,
        Chess::Color color, const Chess::Position& pos);

    std::vector<Chess::Position> getRookMoves(const Chess::Board<ChessPiece>& chessBoard,
        Chess::Color color, const Chess::Position& pos);

    std::vector<Chess::Position> getQueenMoves(const Chess::Board<ChessPiece>& chessBoard,
        Chess::Color color, const Chess::Position& pos);

    std::vector<Chess::Position> getKingMoves(const Chess::Board<ChessPiece>& chessBoard,
        Chess::Color color, const Chess::Position& pos);

    std::vector<Chess::Position> getPieceMoves(const Chess::Board<ChessPiece>& chessBoard,
        const ChessPiece& movingPiece, const Chess::Position& pos);
}