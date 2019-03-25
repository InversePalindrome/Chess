/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessConstants.hpp
https://inversepalindrome.com/
*/


#pragma once


namespace Chess
{
    static constexpr int RANKS = 8;
    static constexpr int FILES = 8;
    static constexpr double SQUARE_SIZE = 64.0;

    enum class Piece { None, Pawn, Knight, Bishop, Rook, King, Queen };
    enum class Color { Light, Dark };
}
