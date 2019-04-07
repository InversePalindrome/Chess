/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessPiece.cpp
https://inversepalindrome.com/
*/


#include "ChessPiece.hpp"

#include <functional>


bool ChessPiece::operator==(const ChessPiece& chessPiece) const
{
	return piece == chessPiece.piece && color == chessPiece.color;
}

std::size_t ChessPieceHash::operator()(const ChessPiece& chessPiece) const
{
    return std::hash<std::size_t>()(static_cast<std::size_t>(chessPiece.piece) ^ static_cast<std::size_t>(chessPiece.color));
}
