/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessPiece.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessConstants.hpp"

#include <cstddef>


struct ChessPiece
{
    Chess::Piece piece = Chess::Piece::None;
    Chess::Color color = Chess::Color::Light;

    bool hasMoved = false;

    bool operator==(const ChessPiece& chessPiece) const;
};

struct ChessPieceHash
{
    std::size_t operator()(const ChessPiece& chessPiece) const;
};
